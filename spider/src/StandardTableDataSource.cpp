#include "StandardTableDataSource.h"
#include <string>
#include <sstream>
using namespace std;
namespace spider {
StandardTableDataSource::StandardTableDataSource()
{
    //ctor
    this->rows = new vector<TableRow *>;
    this->columnHeaders = new vector<TableColumnHeader *>;

}
int StandardTableDataSource::getColumnCount() {
    return this->columnHeaders->size();
}

int StandardTableDataSource::getRowCount() {
    return this->rows->size();
}
StandardTableDataSource::~StandardTableDataSource() {
    delete this->rows;
    delete this->columnHeaders;
}
string StandardTableDataSource::getUriForCell (int column, int row) {
    return "spoyler:internal:debug";
}
string StandardTableDataSource::getTextForCell (int column, int row) {
    string t ("Row ");
    t.append(std::to_string(row));
    t.append(" ");
    t.append(" at column ");
    t.append(std::to_string(column));
    return t;
}    //dtor
string StandardTableDataSource::getTextForColumn (int column) {
    string t = "Column ";
    t.append(std::to_string(column));
    return t;
}
string StandardTableDataSource::getRowUri(int index) {
    return "spoyler:internal:debug";
}

bool StandardTableDataSource::isRowActive(int index) {
    if (index == 1) {
        return true;
    }
}

bool StandardTableDataSource::isCellActive (int index) {
    return false;
}

void *StandardTableDataSource::getDataForCell(int index) {
    return NULL;
}

bool StandardTableDataSource::compareTableCells(int column, TableCell *t1, TableCell *t2) {
    return false;
}
}
