#include "ConfigView.h"
#include "SPTextElement.h"
#include "SPHBoxElement.h"
#include "SPEventArgs.h"
#include "SPWindowElement.h"
#include "SPColor.h"
#include "SPSkin.h"
#include "SPGraphicsContext.h"

#include <boost/json/object.hpp>
#include <boost/json/parse.hpp>
#include <boost/json/serialize.hpp>
#include <boost/json/value.hpp>

#include <fstream>
#include <sstream>

#include <wx/stdpaths.h>
#include <wx/filename.h>

namespace space {
namespace views {

static const SPColor kSelectedColor   = SPColor( 60, 100, 220, 220);
static const SPColor kDeselectedColor = SPColor(160, 160, 160, 255);

// ── helpers ───────────────────────────────────────────────────────────────────

static SPTextElement* makeLabel(SPElement* parent, const string& text, int height) {
    auto *lbl = new SPTextElement(parent);
    lbl->setInnerText(text);
    lbl->setHeight(height);
    parent->appendChild(lbl);
    return lbl;
}

static SPButtonElement* makeButton(SPElement* parent, const string& label,
                                   int width, int height) {
    auto *btn = new SPButtonElement(parent);
    btn->setInnerText(label);
    btn->setWidth(width);
    btn->setHeight(height);
    parent->appendChild(btn);
    return btn;
}

// ── constructor ───────────────────────────────────────────────────────────────

ConfigView::ConfigView() {}

ConfigView::ConfigView(SPElement *parent) : SPViewElement(parent) {
    this->clipView = false;
    this->setUri("spacify:config");
    this->setPadding({ 16, 16, 16, 16 });
    this->setGap(8);

    makeLabel(this, "Settings", 36);

    // ── Appearance section ─────────────────────────────────────────────────
    makeLabel(this, "Appearance", 20);

    // Mode toggle row (Light / Dark side by side)
    auto *modeRow = new SPHBoxElement(this);
    modeRow->setHeight(28);
    modeRow->setGap(6);
    this->appendChild(modeRow);

    m_lightButton = makeButton(modeRow, "Light Mode", 90, 28);
    m_lightButton->addEventListener(
        "click",
        reinterpret_cast<SPCallback>(&ConfigView::onLightClicked),
        this, m_lightButton
    );

    m_darkButton = makeButton(modeRow, "Dark Mode", 90, 28);
    m_darkButton->addEventListener(
        "click",
        reinterpret_cast<SPCallback>(&ConfigView::onDarkClicked),
        this, m_darkButton
    );

    // Glossy toggle button
    m_glossyButton = makeButton(this, "Glossy: On", 110, 28);
    m_glossyButton->addEventListener(
        "click",
        reinterpret_cast<SPCallback>(&ConfigView::onGlossyClicked),
        this, m_glossyButton
    );

    // ── Tint Color section ─────────────────────────────────────────────────
    makeLabel(this, "Tint Color", 20);

    m_colorChooser = new SPColorChooser(this);
    this->appendChild(m_colorChooser);

    // ── Save button ────────────────────────────────────────────────────────
    m_saveButton = makeButton(this, "Save Changes", 120, 28);
    m_saveButton->addEventListener(
        "click",
        reinterpret_cast<SPCallback>(&ConfigView::onSaveClicked),
        this, m_saveButton
    );

    loadSettings();
}

ConfigView::~ConfigView() {}

// ── URI handling ──────────────────────────────────────────────────────────────

bool ConfigView::acceptsUri(const string& uri) {
    return uri == "spacify:config" || uri.rfind("spacify:config", 0) == 0;
}

void ConfigView::navigate(const string& uri) {
    this->setUri(uri);
}

// ── Settings path ─────────────────────────────────────────────────────────────

string ConfigView::getSettingsPath() {
    wxFileName path;
    path.AssignDir(wxStandardPaths::Get().GetUserDataDir());
    path.Normalize(wxPATH_NORM_ALL);
    wxFileName::Mkdir(path.GetPath(), wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);
    path.SetFullName("settings.json");
    return path.GetFullPath().ToStdString();
}

// ── Button state helpers ──────────────────────────────────────────────────────

void ConfigView::updateModeButtons() {
    if (m_lightButton)
        m_lightButton->setBackgroundColor(
            m_pendingScheme == SP_COLOR_SCHEME_LIGHT ? kSelectedColor : kDeselectedColor);
    if (m_darkButton)
        m_darkButton->setBackgroundColor(
            m_pendingScheme == SP_COLOR_SCHEME_DARK ? kSelectedColor : kDeselectedColor);
}

void ConfigView::updateGlossyButton() {
    if (!m_glossyButton) return;
    m_glossyButton->setInnerText(m_pendingGlossy ? "Glossy: On" : "Glossy: Off");
    m_glossyButton->setBackgroundColor(
        m_pendingGlossy ? kSelectedColor : kDeselectedColor);
}

// ── Load / Save ───────────────────────────────────────────────────────────────

void ConfigView::loadSettings() {
    // Reset to defaults
    m_pendingScheme = SP_COLOR_SCHEME_LIGHT;
    m_pendingGlossy = true;

    std::ifstream file(getSettingsPath());
    if (file.is_open()) {
        std::ostringstream ss;
        ss << file.rdbuf();
        file.close();

        try {
            boost::json::value jv = boost::json::parse(ss.str());
            auto& obj = jv.as_object();

            if (obj.contains("tintColor") && m_colorChooser) {
                string hex = string(obj.at("tintColor").as_string().c_str());
                m_colorChooser->setSelectedColor(SPColor(hex));
            }
            if (obj.contains("colorScheme"))
                m_pendingScheme = static_cast<short>(obj.at("colorScheme").as_int64());
            if (obj.contains("glossy"))
                m_pendingGlossy = obj.at("glossy").as_bool();
        } catch (...) {}
    }

    updateModeButtons();
    updateGlossyButton();
}

void ConfigView::saveSettings() {
    if (!m_colorChooser) return;

    SPColor color = m_colorChooser->getSelectedColor();

    // Persist
    boost::json::object obj;
    obj["tintColor"]   = color.toHTMLColor();
    obj["colorScheme"] = m_pendingScheme;
    obj["glossy"]      = m_pendingGlossy;

    std::ofstream file(getSettingsPath());
    if (file.is_open()) {
        file << boost::json::serialize(boost::json::value(std::move(obj)));
        file.close();
    }

    // Apply all settings instantly
    auto *win = this->getWindowElement();
    if (!win) return;

    win->setTintColor(new SPColor(color));
    win->setColorScheme(m_pendingScheme);

    auto *skin = win->getSkin();
    if (skin) skin->setGlossy(m_pendingGlossy);

    auto *gc = win->createGraphics();
    win->invalidateRegion({0, 0, gc->getWidth(), gc->getHeight()});
}

// ── Callbacks ─────────────────────────────────────────────────────────────────

int ConfigView::onSaveClicked(SPObject* /*sender*/, SPEventArgs* /*e*/) {
    saveSettings();
    return 0;
}

int ConfigView::onLightClicked(SPObject* /*sender*/, SPEventArgs* /*e*/) {
    m_pendingScheme = SP_COLOR_SCHEME_LIGHT;
    updateModeButtons();
    this->invalidate();
    return 0;
}

int ConfigView::onDarkClicked(SPObject* /*sender*/, SPEventArgs* /*e*/) {
    m_pendingScheme = SP_COLOR_SCHEME_DARK;
    updateModeButtons();
    this->invalidate();
    return 0;
}

int ConfigView::onGlossyClicked(SPObject* /*sender*/, SPEventArgs* /*e*/) {
    m_pendingGlossy = !m_pendingGlossy;
    updateGlossyButton();
    this->invalidate();
    return 0;
}

} // namespace views
} // namespace space
