#ifndef TABLEROW_H
#define TABLEROW_H
#include "TableElement.h"
#include <vector>
#include <string>
using namespace std;
namespace spider {
class TableElement;
class TableRow
{
    public:
        bool isSelected;
        string uri;
        string title;
        TableRow(TableElement *tableView);
        TableElement *tableElement;
        virtual ~TableRow();
        std::vector<TableRow *> *children;
    protected:
    private:
};
#define TABLEROW_CLASS
}

#endif // TABLEROW_H
