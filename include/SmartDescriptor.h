/*-
 * Copyright (c) 2012, lyuts <dioxinu@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SMARTDESCRIPTOR_H
#define SMARTDESCRIPTOR_H

/*!
 * \class SmartDescriptor \brief Defines a smart descriptor which performs a
 * specific action on destruction. This class follows the approach of RAII, i.e.
 * resource aquisition is initalization.
 *
 * Consider the following code:
 *
 * \code
 * sqlite3* db;
 * if (SQLITE_OK != sqlite3_open("path/to/db", &db)) {
 *     // handle error
 *     sqlite3_close(db);
 * }
 *
 * sqlite3_stmt *stmt;
 * if (SQLITE_OK != sqlite3_prepare_v2(db, sql, sqlLength + 1, &stmt, &tail)) {
 *     LOG_ERROR("Failed to prepare an SQL statement." << sqlite3_errmsg(db));
 *     sqlite3_close(db);
 * }
 *
 * // bind script bytecode
 * if (SQLITE_OK != sqlite3_bind_blob(stmt, 1, data, size, SQLITE_TRANSIENT)) {
 *     LOG_ERROR("Failed to bind policy bytecode into the BLOB field." << sqlite3_errmsg(iDbHandle));
 *     sqlite3_finalize(stmt);
 *     sqlite3_close(db);
 * }
 *
 * try {
 *     if (cond1) {
 *         f();
 *     } else {
 *         g();
 *     }
 * } catch (...) {
 *     sqlite3_close(db);
 *     sqlite3_finalize(stmt);
 *     throw;
 * }
 * \endcode
 *
 * Any potential return from the function must be preceeded with a corresponding
 * \c sqlite3_close (and \c sqlite3_finalize call where appropriate) call in
 * order not to end up with a leak of \c db descriptor. Besides, the situation
 * gets even worse if \c f() and \c g() are capable of throwing exceptions. Each
 * throwing function must be wrapped with with try/catch even if the exception
 * is not supposed to be handled inside this function. The catch clause will
 * most probably rethrow the exception in this case, but it is needed at least
 * to call \c sqlite3_close and \c sqlite3_finalize. In this case the code grows
 * a lot due to extensive error handling blocks and try/catch clauses.
 *
 * If smart descriptors are used, the code may be simplified to this:
 *
 * \code
 * SQLite3 db("path/to/db");
 * if (!db) {
 *     // handle error
 * }
 *
 * SQLite3Stmt *stmt(db, sql, sqlLength + 1, &stmt, &tail);
 *
 * // bind script bytecode
 * if (stmt && SQLITE_OK != sqlite3_bind_blob(stmt, 1, data, size, SQLITE_TRANSIENT)) {
 *     LOG_ERROR("Failed to bind policy bytecode into the BLOB field." << sqlite3_errmsg(db));
 * }
 *
 * if (cond1) {
 *     f();
 * } else {
 *     g();
 * }
 * \endcode
 *
 * where no leaks occur, because the destructors of SQLite3 and SQLite3Stmt
 * handle their destruction.
 *
 * In order to use this class one must define custom constructor and destructor,
 * which perform type specific initialization and freeing.
 *
 * In fact the SmartDescriptor class usage is not limited to SQLite3 types.
 */
template<typename T> class SmartDescriptor { public: operator bool() { return
    mDescriptor != 0; }

        operator T*() { return static_cast<T*> (mDescriptor); }

    protected:
        /*! Contained pointee. */
        T* mDescriptor;

        SmartDescriptor()
            : mDescriptor(0)
        {}

        virtual ~SmartDescriptor()
        {}

    private:
        SmartDescriptor(const SmartDescriptor<T>& iRhs);
        SmartDescriptor<T>& operator=(const SmartDescriptor<T>& iRhs);
};

#endif // SMARTDESCRIPTOR_H

