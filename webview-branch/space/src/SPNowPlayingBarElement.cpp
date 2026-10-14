#include "SPNowPlayingBarElement.h"

#include "SPTextElement.h"
#include "SPGraphicsContext.h"
#include "SPImage.h"
#include "SPPlaybackEventArgs.h"
#include "SpacifyApp.h"

#include <wx/app.h>

namespace space {

// ── Construction ──────────────────────────────────────────────────────────────

SPNowPlayingBarElement::SPNowPlayingBarElement(SPElement* parent)
    : SPVBoxElement(parent)
{
    this->setTagName("nowplayingbar");
    this->setColorAttribute("bgcolor", SPColor(40, 40, 40, 255));
    this->setPadding({ 8, 8, 8, 8 });
    this->setGap(4);
    this->setHeight(170);

    // ── Track title label ──────────────────────────────────────────────────
    m_titleLabel = new SPTextElement(this);
    m_titleLabel->setInnerText("Nothing playing");
    m_titleLabel->setHeight(18);
    m_titleLabel->setForegroundColor(SPColor(220, 220, 220, 255));
    m_titleLabel->setIntegerAttribute("size", 12);
    this->appendChild(m_titleLabel);

    // ── Artist / info label ────────────────────────────────────────────────
    m_infoLabel = new SPTextElement(this);
    m_infoLabel->setInnerText("");
    m_infoLabel->setHeight(14);
    m_infoLabel->setForegroundColor(SPColor(150, 150, 150, 255));
    m_infoLabel->setIntegerAttribute("size", 10);
    this->appendChild(m_infoLabel);

    // ── Subscribe to playback events ───────────────────────────────────────
    if (auto* app = dynamic_cast<SpacifyApp*>(wxTheApp)) {
        app->getPlaybackEvents().addEventListener(
            "playback:changed",
            reinterpret_cast<SPCallback>(&SPNowPlayingBarElement::onPlaybackChanged),
            this,
            nullptr);
    }
}

SPNowPlayingBarElement::~SPNowPlayingBarElement() {
    delete m_cachedImage;
}

// ── Playback event handler ────────────────────────────────────────────────────

int SPNowPlayingBarElement::onPlaybackChanged(SPObject* /*sender*/, SPEventArgs* args) {
    auto* pba = dynamic_cast<SPPlaybackStateEventArgs*>(args);
    if (!pba) return 0;

    auto* app = dynamic_cast<SpacifyApp*>(wxTheApp);
    if (!app) return 0;

    if (app->getCurrentPlayable()) {
        if (m_titleLabel) m_titleLabel->setInnerText(app->getTrackTitle());
        if (m_infoLabel)  m_infoLabel->setInnerText(app->getArtistName());

        const std::string newPath = app->getCoverArtPath();
        if (newPath != m_coverArtPath) {
            m_coverArtPath = newPath;
            delete m_cachedImage;
            m_cachedImage = nullptr;
            // Image is loaded on next paint() once the graphics context is available.
        }
    } else {
        if (m_titleLabel) m_titleLabel->setInnerText("Nothing playing");
        if (m_infoLabel)  m_infoLabel->setInnerText("");
        if (!m_coverArtPath.empty()) {
            m_coverArtPath.clear();
            delete m_cachedImage;
            m_cachedImage = nullptr;
        }
    }

    this->invalidate();
    return 0;
}

// ── Rendering ─────────────────────────────────────────────────────────────────

void SPNowPlayingBarElement::paint(int x, int y, SPGraphicsContext* gc) {
    // Draw background and text children via the parent implementation.
    SPVBoxElement::paint(x, y, gc);

    // Load the cover art image the first time paint() is called after a path change.
    // (m_cachedImage is set to nullptr by onPlaybackChanged when the path changes.)
    if (!m_cachedImage && !m_coverArtPath.empty())
        m_cachedImage = gc->loadImage(m_coverArtPath);

    // Determine the vertical start of the image area (below the info label).
    int artY = absoluteBounds.y + getPadding().top;
    if (m_infoLabel) {
        artY = m_infoLabel->getAbsoluteBounds().y
             + m_infoLabel->getAbsoluteBounds().height
             + getGap();
    }

    const int artX = absoluteBounds.x + getPadding().left;
    const int artW = absoluteBounds.width - getPadding().left - getPadding().right;
    const int artH = absoluteBounds.y + absoluteBounds.height
                   - getPadding().bottom - artY;

    if (artH <= 0 || artW <= 0) return;

    if (m_cachedImage) {
        gc->drawImage(m_cachedImage, artX, artY, artW, artH);
    } else {
        // Placeholder: dark rounded rectangle when no art is available.
        gc->fillRoundedRectangle(artX, artY, artW, artH, 4,
                                 SPColor(60, 60, 60, 255));
    }
}

} // namespace space
