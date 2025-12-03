#ifndef TABLEROW_H
#define TABLEROW_H
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
};
}

#endif // TABLEROW_H
