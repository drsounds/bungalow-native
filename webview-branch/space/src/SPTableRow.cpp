#include "SPTableRow.h"
namespace space {
SPTableRow::SPTableRow(SPTableElement *tableElement)
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
