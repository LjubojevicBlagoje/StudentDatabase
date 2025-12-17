#include "SqliteDB.h"

SqliteDB::SqliteDB(const std::string& path) {
    if (sqlite3_open(path.c_str(), &db_) != SQLITE_OK) {
        std::string msg = sqlite3_errmsg(db_);
        sqlite3_close(db_);
        db_ = nullptr;
        throw std::runtime_error("sqlite3_open failed: " + msg);
    }
    // Enforce foreign keys (SQLite requires enabling this per-connection)
    exec("PRAGMA foreign_keys = ON;");
}

SqliteDB::~SqliteDB() {
    if (db_) sqlite3_close(db_);
}

void SqliteDB::exec(const std::string& sql) {
    char* errMsg = nullptr;
    if (sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::string msg = errMsg ? errMsg : "unknown sqlite error";
        sqlite3_free(errMsg);
        throw std::runtime_error("sqlite exec failed: " + msg + "\nSQL: " + sql);
    }
}
