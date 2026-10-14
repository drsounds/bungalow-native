#pragma once

#include "SPTabBarViewElement.h"

#include <sqlite3.h>
#include <string>

namespace space {
    class SPTableElement;
    class LibraryDataSource;
    class SPObject;
    class SPEventArgs;

    namespace views {

        /**
         * LibraryView  —  spacify:library
         *
         * Displays the user's saved tracks in a three-column table:
         *   Name | Artists | Release
         *
         * Double-clicking a row looks up the track's playable URI and starts
         * playback via SpacifyApp::playTrackId().
         */
        class LibraryView : public SPTabBarViewElement {
        public:
            LibraryView();
            explicit LibraryView(SPElement* parent, sqlite3* db = nullptr);
            ~LibraryView() override;

            bool        acceptsUri(const std::string& uri) override;
            void        navigate(const std::string& uri)  override;
            void        setHash(const std::string& hash)  override;
            std::string getType()                          override { return "libraryview"; }

            /// Called when a row in the library table is double-clicked.
            int onRowDblClicked(SPObject* sender, SPEventArgs* args);

        private:
            SPTableElement*    m_table      = nullptr;
            LibraryDataSource* m_dataSource = nullptr;
        };

    } // namespace views
} // namespace space
