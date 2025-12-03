#ifndef TABLEVIEWELEMENT_H
#define TABLEVIEWELEMENT_H
#include "Element.h"
#include <string>
#include <vector>
#include "TableRow.h"
#include "TableColumnHeader.h"
#include "TableDataSource.h"
using namespace std;

namespace spider {
#ifdef TABLEROW_CLASS
#ifdef TABLECOLUMNHEADER_CLASS
#ifdef TABLEDATASOURCE_CLASS
#ifdef ELEMENT_CLASS
#ifndef TABLEELEMENT_CLASS
class TableElement : public Element
{
    public:
        TableDataSource *dataSource;
        TableElement();
        TableElement(Element *parent, TableDataSource *dataSource);
        vector<TableRow *> *rows;
        vector<TableColumnHeader *> *columns;
        virtual ~TableElement();
        virtual string getType();
        virtual void draw(int x, int y, GraphicsContext *g);
        virtual void scroll(int scrollX, int scrollY, int x, int y);
    protected:
    private:
};
#define TABLEELEMENT_CLASS
#endif
#endif
#endif
#endif
}
#endif // TABLEVIEWELEMENT_H
