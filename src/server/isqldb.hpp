#ifndef __I_SQL_DB_HPP__
#define __I_SQL_DB_HPP__

#include <vector>
#include <string>

namespace DB { 

using ROW = std::vector<std::string>;
using SQL_TABLE =  std::pair<std::vector<ROW>, int>;
} // end of DB namespace

class iSqlDB
{
public:

    virtual bool connect(const std::string& dbName) = 0;
    virtual bool close() = 0;
    virtual DB::SQL_TABLE runSql(const std::string& sql) = 0;
};

#endif //__I_SQL_DB_HPP__