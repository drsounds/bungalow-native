#pragma once

#include "SPTableDataSource.h"

#include <sqlite3.h>
#include <string>
#include <vector>

namespace space {

struct LibraryRow {
    std::string name;        // recording name
    std::string artists;     // comma-joined recording artist names
    std::string releaseName; // release name
    int         trackId = 0;
};

/**
 * LibraryDataSource
 *
 * Queries the 'saves' table (non-deleted) and joins through:
 *   saves → tracks → recordings → releases
 *   recordings → recording_artists → artists   (for the Artists column)
 *
 * Columns exposed: Name | Artists | Release
 */
class LibraryDataSource : public SPTableDataSource {
public:
    explicit LibraryDataSource(sqlite3* db);
    ~LibraryDataSource() override = default;

    int         getColumnCount()                    override { return 3; }
    int         getRowCount()                       override;
    std::string getTextForCell(int column, int row) override;
    std::string getTextForColumn(int column)        override;
    int         getTrackIdForRow(int row)           override;

    /** Reload rows from the database (call after saves change). */
    void reload(sqlite3* db);

private:
    std::vector<LibraryRow> m_rows;

    void load(sqlite3* db);
};

} // namespace space
