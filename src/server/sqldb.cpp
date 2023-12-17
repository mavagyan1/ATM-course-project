
#include "sqldb.hpp"
#include <iostream>
#include <memory>
#include <functional>
#include <cassert>


namespace 
{
    std::vector<DB::ROW> sql_result_table;

    int runSqlCallback(void * data, int argc, char** argv, char** Colname)
    {
        assert(argc != 0);

        sql_result_table.push_back(DB::ROW());
        for(int i = 0; i < argc; i++)
        {
            sql_result_table.back().push_back(argv[i]);
        }

        return 0;
    }
}

SqlDBImpl& SqlDBImpl::getSqlDB() {
    static SqlDBImpl db;
    return db;
}

bool SqlDBImpl::connect(const std::string& dbName) {
    int rc = sqlite3_open(dbName.c_str(), &m_db);
    if(rc)
    {
        std::cerr << "Can't open database "<< std::endl << sqlite3_errmsg(m_db);
        return false;
    }

    std::cout << "Opened database successfully" << std::endl;

    return true;
}

bool SqlDBImpl::close() {

    int rc = sqlite3_close(m_db);
    if(rc)
    {
        std::cerr << "Can't close database "<< std::endl << sqlite3_errmsg(m_db);
        return false;
    }

    return true;
}
DB::SQL_TABLE SqlDBImpl::runSql(const std::string& sql) {
    std::cout << "** RUN SQL *** " << sql << std::endl;
    char* Errmsg = 0;
    const int  rc = sqlite3_exec(m_db,sql.c_str(), runSqlCallback , 0, &Errmsg);
        
    if(rc != 0)
    {
        return {{},rc};
    }
    std::cout<< "sql ended normally" << std::endl;
    return DB::SQL_TABLE(move(sql_result_table), rc);
}

