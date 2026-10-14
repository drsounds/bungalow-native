#pragma once

#include <sqlite3.h>
#include <string>
#include <stdexcept>

/**
 * Database — thin wrapper around sqlite3 that owns the connection and
 * creates the full application schema on first open.
 *
 * Schema overview
 * ───────────────
 *  recordings      – ISRC (PK), name, version
 *  artists         – ISNI (PK), name
 *  recording_artists – junction: recording_id → recordings, artist_id → artists,
 *                      is_primary, number
 *  labels          – id (PK autoincrement), name
 *  releases        – upc (PK), name, release_date, label_id → labels, cover_art
 *  tracks          – id (PK autoincrement), recording_id → recordings,
 *                    release_id → releases
 *  release_artists – junction: release_id → releases, artist_id → artists,
 *                    number, is_primary
 *  saves           – id (PK autoincrement), track_id → tracks,
 *                    saved_at, deleted_at
 */
class Database {
public:
    /**
     * Open (or create) the SQLite database at @p path.
     * Throws std::runtime_error if the file cannot be opened.
     */
    explicit Database(const std::string& path);
    ~Database();

    // Non-copyable, movable
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;
    Database(Database&&) noexcept;
    Database& operator=(Database&&) noexcept;

    /** Returns the raw sqlite3 handle for use with sqlite3_prepare_v2 etc. */
    sqlite3* handle() const { return m_db; }

private:
    sqlite3* m_db = nullptr;

    void initialize();
    void exec(const char* sql);
};
