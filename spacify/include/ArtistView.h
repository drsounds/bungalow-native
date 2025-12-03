#ifndef ARTISTVIEW_H
#define ARTISTVIEW_H
#include "../../spider/include/TabbarViewElement.h"

namespace spider {
    class TabbarViewElement;
    class Element;
    class ArtistView : public TabbarViewElement
    {
        public:
            ArtistView(Element *parent);
            virtual ~ArtistView();
            virtual string getType() {
                return "artistview";
            }
        protected:
        private:
    };
}
#endif // ARTISTVIEW_H
