#ifndef VIEWSTACKELEMENT_H
#define VIEWSTACKELEMENT_H
#include "SPVBoxElement.h"
#include <stack>
#include <string>
using namespace std;
namespace space {
    class SPElement;
    class SPViewElement;
    class SPViewStackElement : public SPVBoxElement {
    private:
        std::stack<string> *history;
        std::stack<string> *future;
        SPViewElement *activeView;

    public:
        virtual void pack() override;
        virtual string getType() override {
            return "viewstack";
        }
        SPViewStackElement();
        SPViewStackElement(SPElement *parent);
        void registerView(SPViewElement *view);
        void navigate(const string& uri);
        virtual void appendChild(SPNode *child) override;
    };
}
#endif // VIEWSTACKELEMENT_H
