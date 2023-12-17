#ifndef __SERVER_APPLICATION_HPP__
#define __SERVER_APPLICATION_HPP__

#include "serverusermanager.hpp"
#include "sqldb.hpp"
#include "serversocket.hpp"

class ServerApplication {
public:
    ServerApplication();
    int runServer();
private:
    ServerUserManagerImpl& _mgr;
};

#endif //__SERVER_APPLICATION_HPP__