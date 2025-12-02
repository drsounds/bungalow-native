#ifndef TABLECOLUMNHEADER_H
#define TABLECOLUMNHEADER_H
#include "TableCell.h"
#include "TableElement.h"
#include <string>
using namespace std;
namespace spider {
class TableCell;
class TableElement;
#ifdef TABLECELL_CLASS
class TableColumnHeader : public TableCell {
    public:
        TableColumnHeader(TableElement *tableElement);
        virtual ~TableColumnHeader();
    protected:
    private:
};
#endif
}

#endif // TABLECOLUMNHEADER_H
