#ifndef TABLECELL_H
#define TABLECELL_H
#include "TableRow.h"
#include "TableElement.h"
#include <string>
using namespace std;
namespace spider {
#ifdef TABLEELEMENT_CLASS
#ifndef TABLECELL_CLASS
#ifdef TABLEROW_CLASS
class TableCell
{
    public:
        TableCell(TableRow *tableRow);
        virtual ~TableCell();
        string uri;
        string title;
        TableRow *tableRow;
        TableElement *tableElement;
    protected:
    private:
};
#define TABLECELL_CLASS
#endif
#endif
#endif
}

#endif // TABLECELL_H
