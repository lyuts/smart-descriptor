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

#ifndef SQLITE3_DESCRIPTORS_H
#define SQLITE3_DESCRIPTORS_H

#include <SmartDescriptor.h>
#include <sqlite3.h>

/*!
 * \class SQLite3
 * \brief Defines smart sqlite3 database descriptor.
 */
class SQLite3 : public SmartDescriptor<sqlite3>
{
    public:
        SQLite3(const char* iDbPath)
            : SmartDescriptor<sqlite3>()
        {
            if (SQLITE_OK != sqlite3_open(iDbPath, &mDescriptor)) {
                sqlite3_close(mDescriptor);
                mDescriptor = 0;
            }
        }

        ~SQLite3()
        {
            if (mDescriptor) {
                sqlite3_close(mDescriptor);
            }
        }

        bool error() const
        {
            return SQLITE_OK != sqlite3_errcode(mDescriptor);
        }

        int errcode() const
        {
            return sqlite3_errcode(mDescriptor);
        }

        const char* errmsg() const
        {
            return sqlite3_errmsg(mDescriptor);
        }
};

/*!
 * \class SQLite3Stmt
 * \brief Defines smart sqlite3 statement descriptor.
 */
class SQLite3Stmt : public SmartDescriptor<sqlite3_stmt>
{
    public:
        SQLite3Stmt(SQLite3& db, const char* zSQL, int nByte = -1, const char** pzTail = 0)
            : SmartDescriptor<sqlite3_stmt>()
        {
            if (db) {
                if (SQLITE_OK != sqlite3_prepare(db, zSQL, nByte, &mDescriptor, pzTail) || db.error()) {
                    mDescriptor = 0;
                }
            }
        }

        ~SQLite3Stmt()
        {
            if (mDescriptor) {
                sqlite3_finalize(mDescriptor);
            }
        }
};

#endif // SQLITE3_DESCRIPTORS_H

