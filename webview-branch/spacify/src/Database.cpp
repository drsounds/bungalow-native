#include "Database.h"

#include <utility>

// ── Construction / destruction ────────────────────────────────────────────────

Database::Database(const std::string& path) {
    if (sqlite3_open(path.c_str(), &m_db) != SQLITE_OK) {
        std::string err = sqlite3_errmsg(m_db);
        sqlite3_close(m_db);
        m_db = nullptr;
        throw std::runtime_error("Failed to open database '" + path + "': " + err);
    }
    exec("PRAGMA foreign_keys = ON;");
    initialize();
}

Database::~Database() {
    if (m_db) {
        sqlite3_close(m_db);
        m_db = nullptr;
    }
}

Database::Database(Database&& other) noexcept : m_db(other.m_db) {
    other.m_db = nullptr;
}

Database& Database::operator=(Database&& other) noexcept {
    if (this != &other) {
        if (m_db) sqlite3_close(m_db);
        m_db = other.m_db;
        other.m_db = nullptr;
    }
    return *this;
}

// ── Private helpers ───────────────────────────────────────────────────────────

void Database::exec(const char* sql) {
    char* errmsg = nullptr;
    if (sqlite3_exec(m_db, sql, nullptr, nullptr, &errmsg) != SQLITE_OK) {
        std::string err(errmsg);
        sqlite3_free(errmsg);
        throw std::runtime_error("SQLite error: " + err);
    }
}

// ── Schema ────────────────────────────────────────────────────────────────────

void Database::initialize() {
    // Artists — must exist before recordings reference them
    exec(R"(
        CREATE TABLE IF NOT EXISTS artists (
            isni TEXT PRIMARY KEY,
            name TEXT NOT NULL
        );
    )");

    // Recordings
    exec(R"(
        CREATE TABLE IF NOT EXISTS recordings (
            isrc    TEXT PRIMARY KEY,
            name    TEXT NOT NULL,
            version TEXT
        );
    )");

    // Junction: recordings ↔ artists
    exec(R"(
        CREATE TABLE IF NOT EXISTS recording_artists (
            recording_id TEXT    NOT NULL REFERENCES recordings(isrc) ON DELETE CASCADE,
            artist_id    TEXT    NOT NULL REFERENCES artists(isni)    ON DELETE CASCADE,
            is_primary   INTEGER NOT NULL DEFAULT 0,
            number       INTEGER NOT NULL DEFAULT 0,
            PRIMARY KEY (recording_id, artist_id)
        );
    )");

    // Labels
    exec(R"(
        CREATE TABLE IF NOT EXISTS labels (
            id   INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT    NOT NULL
        );
    )");

    // Releases
    exec(R"(
        CREATE TABLE IF NOT EXISTS releases (
            upc          TEXT    PRIMARY KEY,
            name         TEXT    NOT NULL,
            release_date TEXT,
            label_id     INTEGER REFERENCES labels(id) ON DELETE SET NULL,
            cover_art    TEXT
        );
    )");

    // Tracks — bind a recording to a release
    exec(R"(
        CREATE TABLE IF NOT EXISTS tracks (
            id           INTEGER PRIMARY KEY AUTOINCREMENT,
            recording_id TEXT    NOT NULL REFERENCES recordings(isrc)  ON DELETE CASCADE,
            release_id   TEXT    NOT NULL REFERENCES releases(upc)     ON DELETE CASCADE
        );
    )");

    // Junction: releases ↔ artists
    exec(R"(
        CREATE TABLE IF NOT EXISTS release_artists (
            release_id TEXT    NOT NULL REFERENCES releases(upc)  ON DELETE CASCADE,
            artist_id  TEXT    NOT NULL REFERENCES artists(isni)  ON DELETE CASCADE,
            number     INTEGER NOT NULL DEFAULT 0,
            is_primary INTEGER NOT NULL DEFAULT 0,
            PRIMARY KEY (release_id, artist_id)
        );
    )");

    // Saves — soft-deletable references to a track
    exec(R"(
        CREATE TABLE IF NOT EXISTS saves (
            id         INTEGER PRIMARY KEY AUTOINCREMENT,
            track_id   INTEGER NOT NULL REFERENCES tracks(id) ON DELETE CASCADE,
            saved_at   TEXT    NOT NULL DEFAULT (datetime('now')),
            deleted_at TEXT
        );
    )");

    // Files — paths to local or remote media files
    exec(R"(
        CREATE TABLE IF NOT EXISTS files (
            id   INTEGER PRIMARY KEY AUTOINCREMENT,
            path TEXT    NOT NULL UNIQUE
        );
    )");

    // Audio files — embedded/resolved metadata for a local file
    exec(R"(
        CREATE TABLE IF NOT EXISTS audio_files (
            id        INTEGER PRIMARY KEY AUTOINCREMENT,
            file_id   INTEGER NOT NULL REFERENCES files(id) ON DELETE CASCADE,
            name      TEXT,
            version   TEXT,
            artists   TEXT,
            album     TEXT,
            duration  INTEGER,
            cover_art TEXT
        );
    )");
    // Migration: add columns introduced after initial schema (ignored if they exist)
    sqlite3_exec(m_db, "ALTER TABLE audio_files ADD COLUMN version TEXT",    nullptr, nullptr, nullptr);
    sqlite3_exec(m_db, "ALTER TABLE audio_files ADD COLUMN cover_art TEXT",  nullptr, nullptr, nullptr);

    // Junction: tracks ↔ audio_files
    exec(R"(
        CREATE TABLE IF NOT EXISTS track_audio_files (
            track_id      INTEGER NOT NULL REFERENCES tracks(id)      ON DELETE CASCADE,
            audio_file_id INTEGER NOT NULL REFERENCES audio_files(id) ON DELETE CASCADE,
            PRIMARY KEY (track_id, audio_file_id)
        );
    )");

    // Playables — a URI that can be played directly
    exec(R"(
        CREATE TABLE IF NOT EXISTS playables (
            id  INTEGER PRIMARY KEY AUTOINCREMENT,
            uri TEXT    NOT NULL UNIQUE
        );
    )");

    // Junction: playables ↔ tracks
    exec(R"(
        CREATE TABLE IF NOT EXISTS playable_tracks (
            playable_id INTEGER NOT NULL REFERENCES playables(id) ON DELETE CASCADE,
            track_id    INTEGER NOT NULL REFERENCES tracks(id)    ON DELETE CASCADE,
            PRIMARY KEY (playable_id, track_id)
        );
    )");
}
