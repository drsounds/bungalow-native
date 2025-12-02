#ifndef ARTISTVIEW_H
#define ARTISTVIEW_H
#include "TabbarViewElement.h"
namespace spider {
    class TabbarViewElement;
    #ifdef TABBARVIEWELEMENT_CLASS
    #ifndef ARTISTVIEW_CLASS
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
    #define ARTISTVIEW_CLASS
    #endif
}
#endif // ARTISTVIEW_H
