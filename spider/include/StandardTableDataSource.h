#ifndef STANDARDTABLEDATASOURCE_H
#define STANDARDTABLEDATASOURCE_H
#include <vector>
#include "TableDataSource.h"

using namespace std;
namespace spider {
#ifdef TABLEDATASOURCE_CLASS
#ifndef STANDARDTABLEDATASOURCE_CLASS
class StandardTableDataSource : public TableDataSource
{
    public:
        StandardTableDataSource();
        virtual ~StandardTableDataSource();
        virtual int getColumnCount();
        virtual int getRowCount();
        virtual string getUriForCell (int column, int row);
        virtual string getTextForCell (int column, int row);
        virtual string getTextForColumn (int column);
        virtual string getRowUri(int index);
        virtual bool isRowActive(int index);
        virtual bool isCellActive (int index);
        virtual void *getDataForCell(int index);
        virtual bool compareTableCells(int column, TableCell *t1, TableCell *t2);
        vector<TableRow *> *rows;
        vector<TableColumnHeader *> *columnHeaders;
    protected:
    private:
};
#define STANDARDTABLEDATASOURCE_CLASS
#endif
#endif
}

#endif // STANDARDTABLEDATASOURCE_H
