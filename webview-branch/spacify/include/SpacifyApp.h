#ifndef SPACE_APP_H
#define SPACE_APP_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "PythonRunner.h"
#include "Database.h"
#include "SPObservable.h"

#include <memory>
#include <string>
#include <vector>

class SpaceFrame;
class SPMediaService;
class SPPlayable;

namespace space
{
    class Space;
    class SPWindowElement;
    class MainElement;
}

class SpacifyApp : public wxApp
{
protected:
    space::Space* m_space;
    space::SPWindowElement *m_windowElement;
    SpaceFrame* m_frame;
    space::MainElement* m_main;
    PythonRunner m_pythonRunner;
    std::unique_ptr<Database> m_database;
    std::string m_databasePath;

    /// Registered media service instances, searched in order by acceptsUri.
    std::vector<SPMediaService*> m_mediaServices;

    // ── Playback state ────────────────────────────────────────────────────────
    SPPlayable*              m_currentPlayable = nullptr;
    std::vector<SPPlayable*> m_nowPlayingQueue;
    bool                     m_isPlaying  = false;
    int                      m_positionMs = 0;
    int                      m_durationMs = 0;

    // ── Now-playing metadata (title, artist, cover art path) ─────────────────
    std::string m_trackTitle;
    std::string m_artistName;
    std::string m_coverArtPath;

    /// Observable that footer (and others) subscribe to for playback events.
    /// Events: "playback:changed", "position:changed"
    space::SPObservable m_playbackEvents;

    wxTimer m_positionTimer;

    void dispatchPlaybackChanged();
    void onPositionTimer(wxTimerEvent& event);

    /// Internal: play a URI with pre-resolved track metadata.
    void playUriWithMeta(const std::string& uri,
                         const std::string& trackTitle,
                         const std::string& artistName,
                         const std::string& coverArtPath);

public:
    virtual bool OnInit() override;
    virtual int OnExit() override;
    Database* getDatabase() { return m_database.get(); }
    const std::string& getDatabasePath() const { return m_databasePath; }

    const std::vector<SPMediaService*>& getMediaServices() const { return m_mediaServices; }
    SPMediaService* getMediaServiceForUri(const std::string& uri) const;

    void navigate(const std::string& uri);

    /// Show an error banner in the main view with an optional custom message.
    void showError(const std::string& msg = "An error occurred");

    // ── Playback API ──────────────────────────────────────────────────────────
    void playTrackId(int64_t trackId);
    void playUri(const std::string& uri);
    void togglePlayPause();
    void seekTo(int posMs);
    void playbackNext();
    void playbackPrev();

    bool        isPlaying()    const { return m_isPlaying; }
    int         getPositionMs()const { return m_positionMs; }
    int         getDurationMs()const { return m_durationMs; }
    SPPlayable* getCurrentPlayable() const { return m_currentPlayable; }
    const std::vector<SPPlayable*>& getNowPlayingQueue() const { return m_nowPlayingQueue; }

    const std::string& getTrackTitle()   const { return m_trackTitle; }
    const std::string& getArtistName()   const { return m_artistName; }
    const std::string& getCoverArtPath() const { return m_coverArtPath; }

    space::SPObservable& getPlaybackEvents() { return m_playbackEvents; }

    wxDECLARE_EVENT_TABLE();
};

#endif
