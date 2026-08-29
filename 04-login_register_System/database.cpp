#include <iostream>
#include <string>

#include "sqlite3.h"
#include "database.h"

using namespace std;

bool connectToDatabase()
{
    sqlite3* db = nullptr;

    int result = sqlite3_open("usersystem.db", &db);

    if (result != SQLITE_OK)
    {
        cerr << "Database connection failed: "
             << sqlite3_errmsg(db) << endl;

        sqlite3_close(db);
        return false;
    }

    cout << "Database connected successfully!" << endl;

    const char* createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS users
        (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT NOT NULL,
            password TEXT NOT NULL,
            email TEXT NOT NULL UNIQUE,
            logged_in INTEGER NOT NULL DEFAULT 0
        );
    )";

    char* errorMessage = nullptr;

    result = sqlite3_exec(
        db,
        createTableSQL,
        nullptr,
        nullptr,
        &errorMessage
    );

    if (result != SQLITE_OK)
    {
        cerr << "Failed to create users table: "
             << errorMessage << endl;

        sqlite3_free(errorMessage);
        sqlite3_close(db);

        return false;
    }

    sqlite3_close(db);

    return true;
}

bool insertUser(
    const string& username,
    const string& password,
    const string& email
)
{
    sqlite3* db = nullptr;

    int result = sqlite3_open("usersystem.db", &db);

    if (result != SQLITE_OK)
    {
        cerr << "Failed to open database: "
             << sqlite3_errmsg(db) << endl;

        sqlite3_close(db);
        return false;
    }

    const char* sql = R"(
        INSERT INTO users
        (
            username,
            password,
            email,
            logged_in
        )
        VALUES
        (
            ?,
            ?,
            ?,
            0
        );
    )";

    sqlite3_stmt* statement = nullptr;

    result = sqlite3_prepare_v2(
        db,
        sql,
        -1,
        &statement,
        nullptr
    );

    if (result != SQLITE_OK)
    {
        cerr << "Failed to prepare INSERT SQL: "
             << sqlite3_errmsg(db) << endl;

        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(
        statement,
        1,
        username.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_text(
        statement,
        2,
        password.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_text(
        statement,
        3,
        email.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    result = sqlite3_step(statement);

    if (result != SQLITE_DONE)
    {
        cerr << "Failed to insert user: "
             << sqlite3_errmsg(db) << endl;

        sqlite3_finalize(statement);
        sqlite3_close(db);

        return false;
    }

    cout << "User registered successfully!" << endl;

    sqlite3_finalize(statement);
    sqlite3_close(db);

    return true;
}

bool loginUser(
    const string& email,
    const string& password
)
{
    sqlite3* db = nullptr;

    int result = sqlite3_open("usersystem.db", &db);

    if (result != SQLITE_OK)
    {
        cerr << "Failed to open database: "
             << sqlite3_errmsg(db) << endl;

        sqlite3_close(db);
        return false;
    }

    const char* sql = R"(
        SELECT id, password, logged_in
        FROM users
        WHERE email = ?;
    )";

    sqlite3_stmt* statement = nullptr;

    result = sqlite3_prepare_v2(
        db,
        sql,
        -1,
        &statement,
        nullptr
    );

    if (result != SQLITE_OK)
    {
        cerr << "Failed to prepare LOGIN SQL: "
             << sqlite3_errmsg(db) << endl;

        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(
        statement,
        1,
        email.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    result = sqlite3_step(statement);

    if (result != SQLITE_ROW)
    {
        cout << "User does not exist!" << endl;

        sqlite3_finalize(statement);
        sqlite3_close(db);

        return false;
    }

    const char* storedPassword =
        reinterpret_cast<const char*>(
            sqlite3_column_text(statement, 1)
        );

 if (password.compare(storedPassword) != 0)
    {
        cout << "Wrong password!" << endl;

        sqlite3_finalize(statement);
        sqlite3_close(db);

        return false;
    }

    sqlite3_finalize(statement);

    const char* updateSQL = R"(
        UPDATE users
        SET logged_in = 1
        WHERE email = ?;
    )";

    result = sqlite3_prepare_v2(
        db,
        updateSQL,
        -1,
        &statement,
        nullptr
    );

    if (result != SQLITE_OK)
    {
        cerr << "Failed to prepare login update: "
             << sqlite3_errmsg(db) << endl;

        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(
        statement,
        1,
        email.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    result = sqlite3_step(statement);

    if (result != SQLITE_DONE)
    {
        cerr << "Failed to update login status: "
             << sqlite3_errmsg(db) << endl;

        sqlite3_finalize(statement);
        sqlite3_close(db);

        return false;
    }

    sqlite3_finalize(statement);
    sqlite3_close(db);

    cout << "Login successful!" << endl;

    return true;
}

bool logoutUser(const string& email)
{
    sqlite3* db = nullptr;

    int result = sqlite3_open("usersystem.db", &db);

    if (result != SQLITE_OK)
    {
        cerr << "Failed to open database: "
             << sqlite3_errmsg(db) << endl;

        sqlite3_close(db);
        return false;
    }

    const char* sql = R"(
        UPDATE users
        SET logged_in = 0
        WHERE email = ?;
    )";

    sqlite3_stmt* statement = nullptr;

    result = sqlite3_prepare_v2(
        db,
        sql,
        -1,
        &statement,
        nullptr
    );

    if (result != SQLITE_OK)
    {
        cerr << "Failed to prepare LOGOUT SQL: "
             << sqlite3_errmsg(db) << endl;

        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(
        statement,
        1,
        email.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    result = sqlite3_step(statement);

    if (result != SQLITE_DONE)
    {
        cerr << "Failed to logout user: "
             << sqlite3_errmsg(db) << endl;

        sqlite3_finalize(statement);
        sqlite3_close(db);

        return false;
    }

    if (sqlite3_changes(db) == 0)
    {
        cout << "User does not exist!" << endl;

        sqlite3_finalize(statement);
        sqlite3_close(db);

        return false;
    }

    sqlite3_finalize(statement);
    sqlite3_close(db);

    cout << "Logout successful!" << endl;

    return true;
}

bool isUserLoggedIn(const string& email)
{
    sqlite3* db = nullptr;

    int result = sqlite3_open("usersystem.db", &db);

    if (result != SQLITE_OK)
    {
        cerr << "Failed to open database: "
             << sqlite3_errmsg(db) << endl;

        sqlite3_close(db);
        return false;
    }

    const char* sql = R"(
        SELECT logged_in
        FROM users
        WHERE email = ?;
    )";

    sqlite3_stmt* statement = nullptr;

    result = sqlite3_prepare_v2(
        db,
        sql,
        -1,
        &statement,
        nullptr
    );

    if (result != SQLITE_OK)
    {
        cerr << "Failed to prepare status SQL: "
             << sqlite3_errmsg(db) << endl;

        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(
        statement,
        1,
        email.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    result = sqlite3_step(statement);

    if (result == SQLITE_ROW)
    {
        int loggedIn = sqlite3_column_int(statement, 0);

        sqlite3_finalize(statement);
        sqlite3_close(db);

        return loggedIn == 1;
    }

    sqlite3_finalize(statement);
    sqlite3_close(db);

    return false;
}
