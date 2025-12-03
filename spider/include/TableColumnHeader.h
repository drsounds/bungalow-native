#ifndef TABLECOLUMNHEADER_H
#define TABLECOLUMNHEADER_H

#include "TableCell.h"
#include "TableElement.h"

#include <string>

using namespace std;

namespace spider {
class TableColumnHeader {
public:
    TableColumnHeader(TableElement *tableElement);
    virtual ~TableColumnHeader();
    string uri;
    string title;
    TableElement *tableElement;
};
}

#endif // TABLECOLUMNHEADER_H
