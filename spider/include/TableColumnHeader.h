#ifndef TABLECOLUMNHEADER_H
#define TABLECOLUMNHEADER_H
#include "TableCell.h"
#include <string>
using namespace std;
namespace spider {
class TableCell;
class TableColumnHeader : public TableCell {
    public:
        TableColumnHeader(TableElement *tableElement);
        virtual ~TableColumnHeader();
    protected:
    private:
};
}

#endif // TABLECOLUMNHEADER_H
