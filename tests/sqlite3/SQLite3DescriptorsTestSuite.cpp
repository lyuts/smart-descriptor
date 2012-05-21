#include <sqlite3/SQLite3DescriptorsTestSuite.h>

#include <sstream>
#include <stdlib.h>
#include <string.h>

#define TEST_DB_PATH "./test.db"

void
SQLite3DescriptorsTestSuite::setUp()
{
    sqlite3* db;
    if (SQLITE_OK != sqlite3_open(TEST_DB_PATH, &db)) {
        sqlite3_close(db);
        CPPUNIT_FAIL("Failed to open a test db.");
    }

    std::stringstream initSQL;
    initSQL << "CREATE TABLE data"
        << "("
        << " id SERIAL, "
        << " name TEXT"
        << ");";

    if (SQLITE_OK != sqlite3_exec(db, initSQL.str().c_str(), 0, 0, 0)) {
        std::string msg = "Failed to create table: ";
        msg += sqlite3_errmsg(db);

        sqlite3_close(db);
        CPPUNIT_FAIL(msg);
    }

    sqlite3_close(db);
}

void
SQLite3DescriptorsTestSuite::tearDown()
{
    CPPUNIT_ASSERT_EQUAL(0, unlink(TEST_DB_PATH));
}

/*!
 * \test Check the correct opening of a database
 *
 * \post
 * \li Database is correctly opened when using smart descriptor.
 * \li Data can be read/writtern via smart descriptor.
 */
void
SQLite3DescriptorsTestSuite::openTest1()
{
    SQLite3 db(TEST_DB_PATH);

    if (!db) {
        CPPUNIT_FAIL("Unable to open test database!");
    }

    int n = 10;
    std::stringstream sql;

    for (int i = 1; i <= n; ++i) {
        sql.str("");
        sql << "INSERT INTO data VALUES (" << i << ", 'val" << i << "');";

        sqlite3_exec(db, sql.str().c_str(), 0, 0, 0);

        CPPUNIT_ASSERT_EQUAL(db.errcode(), sqlite3_errcode(db));
        CPPUNIT_ASSERT_EQUAL(std::string(db.errmsg()), std::string(sqlite3_errmsg(db)));

        if (db.error()) {
            CPPUNIT_FAIL(sqlite3_errmsg(db));
        }
    }

    // make sure data made it to the database
    int rows = 0;
    int cols = 0;
    char** table = 0;

    sqlite3_get_table(db, "SELECT id, name FROM data;", &table, &rows, &cols, 0);

    CPPUNIT_ASSERT_EQUAL(n, rows);
    CPPUNIT_ASSERT_EQUAL(2, cols);

    for (int row = 1; row <= rows; ++row) {
        char* idField = table[cols * row];
        CPPUNIT_ASSERT(idField);
        CPPUNIT_ASSERT_EQUAL(row, atoi(idField));

        char* nameField = table[cols * row + 1];
        CPPUNIT_ASSERT(nameField);
        CPPUNIT_ASSERT_EQUAL(std::string("val") + idField, std::string(nameField));
    }

    sqlite3_free_table(table);
}

