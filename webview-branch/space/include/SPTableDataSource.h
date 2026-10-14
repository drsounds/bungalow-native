#ifndef TABLEVIEWDATASOURCE_H
#define TABLEVIEWDATASOURCE_H
#include <string>
#include <vector>
using namespace std;

namespace space {
class SPTableCell;
class SPTableDataSource
{
    public:

        SPTableDataSource();
        virtual ~SPTableDataSource();
        virtual int getColumnCount() { return 0; }
        virtual int getRowCount() { return 0; }
        virtual string getUriForCell (int column, int row) { return ""; }
        virtual string getTextForCell (int column, int row) { return ""; }
        virtual string getTextForColumn (int column) { return ""; }
        virtual string getRowUri(int index) { return ""; }
        virtual bool isRowActive(int index) { return false; }
        virtual bool isCellActive (int index) { return false; }
        virtual void *getDataForCell(int index) { return NULL; }
        virtual bool compareTableCells(int column, SPTableCell *t1, SPTableCell *t2) { return false; }

        /// Returns an application-defined integer identifier for the given row
        /// (e.g. a database track ID).  Returns 0 if not applicable.
        virtual int getTrackIdForRow(int /*row*/) { return 0; }

        virtual vector<int> getSelectedIndexes() { return vector<int>(); }
        virtual bool isIndexSelected (int index) { return false; }
        virtual void addIndexesToSelection(int index) {}
        virtual void removeIndexesFromSelection (int index) {}

    protected:
    private:
};
}
#endif // TABLEVIEWDATASOURCE_H
