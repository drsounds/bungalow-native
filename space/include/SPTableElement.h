#ifndef TABLEVIEWELEMENT_H
#define TABLEVIEWELEMENT_H
#include "SPElement.h"
#include <string>
#include <vector>

using namespace std;

namespace space {
class SPTableDataSource;
class SPTableRow;
class SPTableColumnHeader;
class SPTableElement : public SPElement
{
    public:
        SPTableDataSource *dataSource;
        SPTableElement();
        SPTableElement(SPElement *parent, SPTableDataSource *dataSource);
        vector<SPTableRow *> *rows;
        vector<SPTableColumnHeader *> *columns;
        virtual ~SPTableElement();
        virtual string getType() override;
        virtual void paint(int x, int y, SPGraphicsContext *g) override;
        virtual void scroll(int scrollX, int scrollY, int x, int y) override;
};
}
#endif // TABLEVIEWELEMENT_H
