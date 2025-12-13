#ifndef ARTISTVIEW_H
#define ARTISTVIEW_H
#include "SPTabbarViewElement.h"

namespace space {
    class SPTabbarViewElement;
    class SPElement;
    class ArtistView : public SPTabbarViewElement
    {
        public:
            ArtistView(SPElement *parent);
            virtual ~ArtistView();
            virtual string getType() override {
                return "artistview";
            }
        protected:
        private:
    };
}
#endif // ARTISTVIEW_H
