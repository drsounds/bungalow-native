#include "TableCell.h"
namespace spider {
TableCell::TableCell(TableRow *tableRow)
{
    this->tableRow = tableRow;
    this->tableElement = tableRow->tableElement;
    //ctor
}

TableCell::~TableCell()
{
    //dtor
}
}
