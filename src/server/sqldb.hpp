#ifndef __SQL_BD_HPP__
#define __SQL_BD_HPP__

#include "isqldb.hpp"
#include "sqlite3.h"

 /*
 * SqlDBImpl is a Singleton class
 */
class SqlDBImpl: public iSqlDB {
private:
    SqlDBImpl() = default;

public:
    SqlDBImpl(const SqlDBImpl&) = delete;
    SqlDBImpl& operator=(const SqlDBImpl&) = delete;

    static SqlDBImpl& getSqlDB();

    bool connect(const std::string& dbName) override;

    bool close() override;

    DB::SQL_TABLE runSql(const std::string& sql) override;
private:
    sqlite3* m_db;
};


#endif //__SQL_BD_HPP__