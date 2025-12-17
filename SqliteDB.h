#pragma once
#include <sqlite3.h>
#include <string>
#include <stdexcept>

class SqliteDB {
public:
    explicit SqliteDB(const std::string& path);
    ~SqliteDB();

    SqliteDB(const SqliteDB&) = delete;
    SqliteDB& operator=(const SqliteDB&) = delete;

    void exec(const std::string& sql);
    sqlite3* raw() { return db_; }

private:
    sqlite3* db_ = nullptr;
};
