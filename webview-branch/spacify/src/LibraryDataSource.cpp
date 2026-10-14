#include "LibraryDataSource.h"

namespace space {

// ── Helpers ───────────────────────────────────────────────────────────────────

static const char* kColumnNames[] = { "Name", "Artists", "Release" };

// Joins saves → tracks → recordings → releases → recording_artists → artists.
// GROUP_CONCAT aggregates artist names per save row.
static const char* kQuery = R"(
    SELECT
        rec.name                                          AS name,
        COALESCE(GROUP_CONCAT(DISTINCT a.name, ', '), '') AS artists,
        rel.name                                          AS release_name,
        t.id                                              AS track_id
    FROM saves s
    JOIN tracks             t   ON t.id            = s.track_id
    JOIN recordings         rec ON rec.isrc         = t.recording_id
    JOIN releases           rel ON rel.upc          = t.release_id
    LEFT JOIN recording_artists ra ON ra.recording_id = rec.isrc
    LEFT JOIN artists           a  ON a.isni          = ra.artist_id
    WHERE s.deleted_at IS NULL
    GROUP BY s.id
    ORDER BY s.saved_at DESC
)";

// ── Construction ──────────────────────────────────────────────────────────────

LibraryDataSource::LibraryDataSource(sqlite3* db) {
    if (db) load(db);
}

// ── SPTableDataSource interface ───────────────────────────────────────────────

int LibraryDataSource::getRowCount() {
    return static_cast<int>(m_rows.size());
}

std::string LibraryDataSource::getTextForColumn(int column) {
    if (column >= 0 && column < 3) return kColumnNames[column];
    return "";
}

std::string LibraryDataSource::getTextForCell(int column, int row) {
    if (row < 0 || row >= static_cast<int>(m_rows.size())) return "";
    const auto& r = m_rows[row];
    switch (column) {
        case 0: return r.name;
        case 1: return r.artists;
        case 2: return r.releaseName;
        default: return "";
    }
}

int LibraryDataSource::getTrackIdForRow(int row) {
    if (row < 0 || row >= static_cast<int>(m_rows.size())) return 0;
    return m_rows[row].trackId;
}

// ── Data loading ──────────────────────────────────────────────────────────────

void LibraryDataSource::reload(sqlite3* db) {
    m_rows.clear();
    if (db) load(db);
}

void LibraryDataSource::load(sqlite3* db) {
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, kQuery, -1, &stmt, nullptr) != SQLITE_OK) return;

    auto col = [&](int i) -> std::string {
        const unsigned char* txt = sqlite3_column_text(stmt, i);
        return txt ? reinterpret_cast<const char*>(txt) : "";
    };

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        LibraryRow r;
        r.name        = col(0);
        r.artists     = col(1);
        r.releaseName = col(2);
        r.trackId     = sqlite3_column_int(stmt, 3);
        m_rows.push_back(std::move(r));
    }

    sqlite3_finalize(stmt);
}

} // namespace space
