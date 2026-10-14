#include "LibraryView.h"
#include "LibraryDataSource.h"
#include "SPTableElement.h"
#include "SPSectionElement.h"
#include "SPTabStackElement.h"
#include "SPTabBarViewElement.h"
#include "SPTabBarElement.h"
#include "SPPlaybackEventArgs.h"
#include "SpacifyApp.h"
#include "SPColor.h"

#include <regex>
#include <wx/app.h>

namespace space {
    namespace views {

        LibraryView::LibraryView() : SPTabBarViewElement() {}

        LibraryView::LibraryView(SPElement* parent, sqlite3* db)
            : SPTabBarViewElement(parent)
        {
            auto* section = new SPSectionElement(this->tabStack);
            section->setId("overview");
            section->setStringAttribute("title", "Library");
            section->setFlex(1);

            m_dataSource = new LibraryDataSource(db);
            m_table = new SPTableElement(section, m_dataSource);
            m_table->fullView = true;
            section->appendChild(m_table);
            m_table->setFlex(1);

            // Listen for double-click on any row
            m_table->addEventListener(
                "rowdblclicked",
                reinterpret_cast<SPCallback>(&LibraryView::onRowDblClicked),
                this,
                m_table
            );

            this->tabStack->appendChild(section);
            this->tabBar->addTab("overview", "Library", "spacify:library");
            this->tabStack->setTabId("overview");
        }

        int LibraryView::onRowDblClicked(SPObject* /*sender*/, SPEventArgs* args) {
            auto* rowArgs = dynamic_cast<SPTableRowEventArgs*>(args);
            if (!rowArgs || !m_dataSource) return 0;

            const int trackId = m_dataSource->getTrackIdForRow(rowArgs->getRow());
            if (trackId <= 0) return 0;

            if (auto* app = dynamic_cast<SpacifyApp*>(wxTheApp))
                app->playTrackId(static_cast<int64_t>(trackId));

            return 0;
        }

        void LibraryView::navigate(const std::string& /*uri*/) {}

        void LibraryView::setHash(const std::string& hash) {
            SPTabBarViewElement::setHash(hash.empty() ? "overview" : hash);
        }

        bool LibraryView::acceptsUri(const std::string& uri) {
            return std::regex_match(uri, std::regex("spacify:library"));
        }

        LibraryView::~LibraryView() {}

    } // namespace views
} // namespace space
