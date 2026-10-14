//
// Created by Alexander Forselius on 2025-12-03.
//

#include "SpacifyApp.h"
#include "SPElement.h"
#include "Database.h"
#include "services/LocalMediaService.h"
#include "models/SPPlayable.h"
#include "models/SPPlayableTrack.h"
#include "models/SPTrack.h"
#include "models/SPRecording.h"
#include "models/SPRecordingArtist.h"
#include "models/SPArtist.h"
#include "models/SPRelease.h"
#include "models/SPDBConnection.h"
#include "SPPlaybackEventArgs.h"

#include "MainElement.h"
#include "SPMessageType.h"
#include "SPWindowElement.h"
#include "SPSkin.h"
#include "SpaceFrame.h"
#include "Space.h"
#include "SpaceWidget.h"
#include "SPClassicSkin.h"
#include "WxWidgetsGraphicsContext.h"
#include "ConfigView.h"

#include <boost/json/parse.hpp>
#include <boost/json/value.hpp>

#include <fstream>
#include <sstream>
#include <wx/stdpaths.h>
#include <wx/filename.h>

wxIMPLEMENT_APP(SpacifyApp);

// ── Position-timer event table ────────────────────────────────────────────────
static const int ID_POSITION_TIMER = wxNewId();

wxBEGIN_EVENT_TABLE(SpacifyApp, wxApp)
    EVT_TIMER(ID_POSITION_TIMER, SpacifyApp::onPositionTimer)
wxEND_EVENT_TABLE()

// ── Initialisation ────────────────────────────────────────────────────────────

bool SpacifyApp::OnInit(){
    if( !wxApp::OnInit() )
        return false;

    // Route XUL load failures to the global info banner
    space::SPElement::s_xulErrorHandler = [this](const std::string& msg) {
        showError(msg);
    };

    // Register media services (searched in order by acceptsUri)
    m_mediaServices.push_back(new LocalMediaService());

    // Resolve the resources/ directory: it sits next to the executable, or
    // one level up when the binary lives in a build subdirectory.
    wxFileName exe(wxStandardPaths::Get().GetExecutablePath());
    wxFileName resourcesDir;
    resourcesDir.AssignDir(exe.GetPath() + "/resources");
    resourcesDir.Normalize(wxPATH_NORM_ALL);
    if (!resourcesDir.DirExists()) {
        resourcesDir.AssignDir(exe.GetPath() + "/../resources");
        resourcesDir.Normalize(wxPATH_NORM_ALL);
    }

    // Set CWD to the resources parent so relative XUL paths work from anywhere.
    wxSetWorkingDirectory(resourcesDir.GetPathWithSep() + "..");

    wxFileName appDir;
    appDir.AssignDir(resourcesDir.GetFullPath() + "/app");
    std::string appDirStr = appDir.GetPath().ToStdString();

    // Open (or create) the local SQLite database next to the resources directory.
    m_databasePath = resourcesDir.GetPath().ToStdString() + "/spacify.db";
    m_database = std::make_unique<Database>(m_databasePath);

    this->m_space = new space::Space();
    this->m_frame = new SpaceFrame(this, this->m_space);
    space::platform::wxwidgets::WxWidgetsGraphicsContext *gc = new space::platform::wxwidgets::WxWidgetsGraphicsContext(this->m_frame);
    this->m_space->setGraphicsContext(gc);
    gc->setWidget(this->m_frame->getSpaceWidget());
    space::SPSkin *skin = new space::SPClassicSkin();
    this->m_windowElement = new space::SPWindowElement(this->m_space, skin);
    this->m_windowElement->setColorScheme(SP_COLOR_SCHEME_LIGHT);
    this->m_frame->setWindowElement(this->m_windowElement);
    this->m_frame->setSpace(m_space);
    this->m_windowElement->setSpace(m_space);
    this->m_space->addWindow(this->m_windowElement);
    this->m_main = new space::MainElement(this->m_windowElement);
    this->m_main->setId("main");

    space::SPColor tintColor(100, 127, 255, 127);
    short colorScheme = SP_COLOR_SCHEME_LIGHT;
    bool  glossy      = true;
    {
        std::ifstream settingsFile(space::views::ConfigView::getSettingsPath());
        if (settingsFile.is_open()) {
            std::ostringstream ss;
            ss << settingsFile.rdbuf();
            try {
                boost::json::value jv = boost::json::parse(ss.str());
                auto& obj = jv.as_object();
                if (obj.contains("tintColor")) {
                    string hexColor = string(obj.at("tintColor").as_string().c_str());
                    tintColor = space::SPColor(hexColor);
                }
                if (obj.contains("colorScheme"))
                    colorScheme = static_cast<short>(obj.at("colorScheme").as_int64());
                if (obj.contains("glossy"))
                    glossy = obj.at("glossy").as_bool();
            } catch (...) {}
        }
    }
    this->m_windowElement->setColorScheme(colorScheme);
    skin->setGlossy(glossy);
    this->m_main->setTintColor(new space::SPColor(tintColor));
    this->m_windowElement->appendChild(this->m_main);
    this->m_windowElement->pack();
    this->m_frame->Show(true);
    this->m_frame->getSpaceWidget()->Show();

    SetTopWindow(this->m_frame);

    // Initialise the position timer (owned by this wxEvtHandler)
    m_positionTimer.SetOwner(this, ID_POSITION_TIMER);

    CallAfter([this, appDirStr]() {
        m_pythonRunner.start(appDirStr);
    });

    return true;
}

int SpacifyApp::OnExit() {
    m_positionTimer.Stop();
    m_pythonRunner.stop();
    for (SPMediaService* svc : m_mediaServices)
        delete svc;
    m_mediaServices.clear();
    // Clean up now-playing queue
    for (SPPlayable* p : m_nowPlayingQueue)
        delete p;
    m_nowPlayingQueue.clear();
    m_currentPlayable = nullptr;
    return wxApp::OnExit();
}

// ── Service lookup ────────────────────────────────────────────────────────────

SPMediaService* SpacifyApp::getMediaServiceForUri(const std::string& uri) const {
    for (SPMediaService* svc : m_mediaServices) {
        if (svc && svc->acceptsUri(uri))
            return svc;
    }
    return nullptr;
}

// ── Navigation ────────────────────────────────────────────────────────────────

void SpacifyApp::navigate(const std::string& uri) {
    if (m_main) m_main->navigate(uri);
}

void SpacifyApp::showError(const std::string& msg) {
    if (m_main) m_main->showMessage(space::Error, msg);
}

// ── Helpers ───────────────────────────────────────────────────────────────────

/// Extract the filename stem from a URI/file-path, e.g. "/a/b/track.mp3" → "track".
static std::string uriBasename(const std::string& uri) {
    const auto slash = uri.find_last_of("/\\");
    std::string name = (slash == std::string::npos) ? uri : uri.substr(slash + 1);
    const auto dot = name.rfind('.');
    if (dot != std::string::npos) name = name.substr(0, dot);
    return name;
}

// ── Playback ──────────────────────────────────────────────────────────────────

void SpacifyApp::playTrackId(int64_t trackId) {
    if (!m_database) return;
    SPDBConnection conn(*m_database);

    // Find the first playable_track row for this track
    auto ptRows = SPPlayableTrack::findByTrack(conn, trackId);
    if (ptRows.empty()) { showError("An error occurred"); return; }

    auto playableOpt = SPPlayable::find(conn, ptRows.front().playableId);
    if (!playableOpt) { showError("An error occurred"); return; }

    // Resolve track metadata from the DB
    std::string title, artist, coverArt;
    auto trackOpt = SPTrack::find(conn, trackId);
    if (trackOpt) {
        auto recOpt = SPRecording::find(conn, trackOpt->recordingId);
        if (recOpt) {
            title = recOpt->name;
            if (!recOpt->version.empty())
                title += " (" + recOpt->version + ")";
        }

        auto raRows = SPRecordingArtist::findByRecording(conn, trackOpt->recordingId);
        for (const auto& ra : raRows) {
            if (ra.isPrimaryArtist || artist.empty()) {
                auto artOpt = SPArtist::find(conn, ra.artistId);
                if (artOpt) artist = artOpt->name;
                if (ra.isPrimaryArtist) break;
            }
        }

        if (!trackOpt->releaseId.empty()) {
            auto relOpt = SPRelease::find(conn, trackOpt->releaseId);
            if (relOpt) coverArt = relOpt->coverArt;
        }
    }

    playUriWithMeta(playableOpt->uri, title, artist, coverArt);
}

void SpacifyApp::playUri(const std::string& uri) {
    playUriWithMeta(uri, "", "", "");
}

void SpacifyApp::playUriWithMeta(const std::string& uri,
                                  const std::string& trackTitle,
                                  const std::string& artistName,
                                  const std::string& coverArtPath) {
    // Stop any current playback
    m_positionTimer.Stop();
    if (m_currentPlayable && m_currentPlayable->service)
        m_currentPlayable->service->stop();

    // Clear the queue and release old playables
    for (SPPlayable* p : m_nowPlayingQueue)
        delete p;
    m_nowPlayingQueue.clear();
    m_currentPlayable = nullptr;

    // Store now-playing metadata (fall back to basename when no title provided)
    m_trackTitle   = trackTitle.empty() ? uriBasename(uri) : trackTitle;
    m_artistName   = artistName;
    m_coverArtPath = coverArtPath;

    // Create and resolve the new playable
    auto* playable = new SPPlayable(uri);
    playable->resolveService(m_mediaServices);

    // Load via the resolved service if available
    if (!playable->service) {
        delete playable;
        showError("An error occurred");
        return;
    }
    playable->service->load(uri);
    playable->service->play();

    // Place into the queue and mark as current
    m_nowPlayingQueue.push_back(playable);
    m_currentPlayable = playable;
    m_isPlaying  = true;
    m_positionMs = 0;
    // Read the actual duration from the service now that the file is loaded
    m_durationMs = playable->service ? playable->service->getDurationMs() : 0;

    dispatchPlaybackChanged();

    // Start the position tick (500 ms resolution)
    m_positionTimer.Start(500);
}

void SpacifyApp::togglePlayPause() {
    if (!m_currentPlayable) return;

    m_isPlaying = !m_isPlaying;
    if (m_currentPlayable->service) {
        if (m_isPlaying)
            m_currentPlayable->service->play();
        else
            m_currentPlayable->service->pause();
    }

    if (m_isPlaying)
        m_positionTimer.Start(500);
    else
        m_positionTimer.Stop();

    dispatchPlaybackChanged();
}

void SpacifyApp::seekTo(int posMs) {
    if (!m_currentPlayable) return;

    m_positionMs = posMs;
    if (m_currentPlayable->service)
        m_currentPlayable->service->seek(posMs);

    dispatchPlaybackChanged();
}

void SpacifyApp::playbackNext() {
    // No multi-track queue logic yet; stop current track
    if (m_currentPlayable && m_currentPlayable->service)
        m_currentPlayable->service->stop();
    m_isPlaying  = false;
    m_positionMs = 0;
    m_positionTimer.Stop();
    dispatchPlaybackChanged();
}

void SpacifyApp::playbackPrev() {
    // Restart from beginning
    seekTo(0);
    if (m_currentPlayable && !m_isPlaying) {
        m_isPlaying = true;
        if (m_currentPlayable->service)
            m_currentPlayable->service->play();
        m_positionTimer.Start(500);
    }
    dispatchPlaybackChanged();
}

// ── Internal helpers ──────────────────────────────────────────────────────────

void SpacifyApp::dispatchPlaybackChanged() {
    auto* args = new space::SPPlaybackStateEventArgs(
        m_isPlaying, m_positionMs, m_durationMs);
    m_playbackEvents.dispatchEvent("playback:changed", args, nullptr);
}

void SpacifyApp::onPositionTimer(wxTimerEvent& /*event*/) {
    if (!m_isPlaying || !m_currentPlayable) return;

    SPMediaService* svc = m_currentPlayable->service;

    // Use the real position reported by the service when available
    if (svc) {
        m_positionMs = svc->getPositionMs();
        // Refresh duration (AVAudioPlayer might not have it ready immediately)
        if (m_durationMs == 0)
            m_durationMs = svc->getDurationMs();
    } else {
        m_positionMs += 500;
    }

    // Detect natural track completion
    if (m_durationMs > 0 && m_positionMs >= m_durationMs) {
        m_positionMs = m_durationMs;
        m_isPlaying  = false;
        m_positionTimer.Stop();
    }

    auto* args = new space::SPPlaybackStateEventArgs(
        m_isPlaying, m_positionMs, m_durationMs);
    m_playbackEvents.dispatchEvent("playback:changed", args, nullptr);
}
