#include "SPTableRow.h"
namespace spider {
SPTableRow::SPTableRow(TableElement *tableElement)
{
    this->tableElement = tableElement;
    this->children = new vector<SPTableRow *>;
    //ctor
}

SPTableRow::~SPTableRow()
{
    //dtor
}
}
