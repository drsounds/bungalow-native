#ifndef CONFIGVIEW_H
#define CONFIGVIEW_H

#include "SPViewElement.h"
#include "SPColorChooser.h"
#include "SPButtonElement.h"
#include "SPElement.h"
#include <string>

using namespace std;

namespace space {
namespace views {

class ConfigView : public SPViewElement {
public:
    ConfigView();
    explicit ConfigView(SPElement *parent);
    ~ConfigView() override;

    string getType() override { return "configview"; }

    bool acceptsUri(const string& uri) override;
    void navigate(const string& uri) override;

    static string getSettingsPath();
    void loadSettings();
    void saveSettings();

    int onSaveClicked(SPObject* sender, SPEventArgs* e);
    int onLightClicked(SPObject* sender, SPEventArgs* e);
    int onDarkClicked(SPObject* sender, SPEventArgs* e);
    int onGlossyClicked(SPObject* sender, SPEventArgs* e);

private:
    SPColorChooser*  m_colorChooser  = nullptr;
    SPButtonElement* m_saveButton    = nullptr;
    SPButtonElement* m_lightButton   = nullptr;
    SPButtonElement* m_darkButton    = nullptr;
    SPButtonElement* m_glossyButton  = nullptr;

    short m_pendingScheme = SP_COLOR_SCHEME_LIGHT;
    bool  m_pendingGlossy = true;

    void updateModeButtons();
    void updateGlossyButton();
};

} // namespace views
} // namespace space

#endif // CONFIGVIEW_H
