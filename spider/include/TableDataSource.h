#ifndef TABLEVIEWDATASOURCE_H
#define TABLEVIEWDATASOURCE_H
#include <string>
#include <vector>
using namespace std;

namespace spider {
class TableCell;
class TableDataSource
{
    public:

        TableDataSource();
        virtual ~TableDataSource();
        virtual int getColumnCount() { return 0; }
        virtual int getRowCount() { return 0; }
        virtual string getUriForCell (int column, int row) { return ""; }
        virtual string getTextForCell (int column, int row) { return ""; }
        virtual string getTextForColumn (int column) { return ""; }
        virtual string getRowUri(int index) { return ""; }
        virtual bool isRowActive(int index) { return false; }
        virtual bool isCellActive (int index) { return false; }
        virtual void *getDataForCell(int index) { return NULL; }
        virtual bool compareTableCells(int column, TableCell *t1, TableCell *t2) { return false; }

        virtual vector<int> getSelectedIndexes() { return vector<int>(); }
        virtual bool isIndexSelected (int index) { return false; }
        virtual void addIndexesToSelection(int index) {}
        virtual void removeIndexesFromSelection (int index) {}

    protected:
    private:
};
}
#endif // TABLEVIEWDATASOURCE_H
