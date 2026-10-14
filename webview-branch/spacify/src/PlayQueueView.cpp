#include "PlayQueueView.h"
#include "PlayQueueDataSource.h"
#include "SPTableElement.h"
#include "SPSectionElement.h"
#include "SPTabStackElement.h"
#include "SpacifyApp.h"
#include "SPTabBarElement.h"

#include <wx/app.h>

namespace space {
namespace views {

PlayQueueView::PlayQueueView() : SPTabBarViewElement() {}

PlayQueueView::PlayQueueView(SPElement* parent)
    : SPTabBarViewElement(parent)
{
    // Override the default flex=1 from SPTabBarViewElement so the panel
    // keeps a fixed width when used as a sidebar column.
    this->setFlex(0);
    this->setWidth(240);

    auto* section = new SPSectionElement(this->tabStack);
    section->setId("playqueue");
    section->setStringAttribute("title", "Play queue");
    section->setFlex(1);

    m_dataSource = new PlayQueueDataSource();
    m_table = new SPTableElement(section, m_dataSource);
    m_table->fullView = true;
    m_table->setFlex(1);
    section->appendChild(m_table);

    this->tabStack->appendChild(section);
    this->tabBar->addTab("playqueue", "Play queue", "spacify:internal:playqueue#playqueue");
    this->tabStack->setTabId("playqueue");

    // Populate with the current queue immediately.
    reload();
}

void PlayQueueView::reload() {
    if (!m_dataSource) return;
    if (auto* app = dynamic_cast<SpacifyApp*>(wxTheApp)) {
        m_dataSource->setQueue(app->getNowPlayingQueue());
    }
    if (m_table) m_table->invalidate();
}

PlayQueueView::~PlayQueueView() {}

} // namespace views
} // namespace space
