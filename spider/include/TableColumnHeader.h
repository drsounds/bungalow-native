#ifndef TABLECOLUMNHEADER_H
#define TABLECOLUMNHEADER_H
#include "TableCell.h"
#include "TableElement.h"
#include <string>
using namespace std;
namespace spider {
#ifdef TABLEELEMENT_CLASS
#ifdef TABLEROW_CLASS
#ifdef TABLECELL_CLASS
class TableColumnHeader {
public:
    TableColumnHeader(TableElement *tableElement);
    virtual ~TableColumnHeader();
    string uri;
    string title;
    TableElement *tableElement;
    protected:
    private:
};
#endif
#endif
#endif
}

#endif // TABLECOLUMNHEADER_H
