#ifndef LIBRARYVIEW_H
#define LIBRARYVIEW_H

#include "SPTabBarViewElement.h"

namespace space {
    class SPElement;
    class SPTextElement;
    class SPTableElement;
    namespace views {
        class LibraryView : public SPTabBarViewElement
        {
            public:
                LibraryView(SPElement *parent);
                virtual ~LibraryView();
                void navigate(const string& uri) override;
                bool acceptsUri(const string& uri) override;
            protected:
                SPTableElement *table;
            private:
        };
    }
}
#endif // LIBRARY_H
