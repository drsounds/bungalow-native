#ifndef ARTISTVIEW_H
#define ARTISTVIEW_H
#include "SPTabbarViewElement.h"

namespace spider {
    class SPTabbarViewElement;
    class SPElement;
    class ArtistView : public SPTabbarViewElement
    {
        public:
            ArtistView(SPElement *parent);
            virtual ~ArtistView();
            virtual string getType() {
                return "artistview";
            }
        protected:
        private:
    };
}
#endif // ARTISTVIEW_H
