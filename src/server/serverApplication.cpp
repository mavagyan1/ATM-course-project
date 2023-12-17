#include "serverApplication.hpp"
#include "serversocket.hpp"
#include "iserversocket.hpp"
#include <iostream>
#include <memory>


ServerApplication::ServerApplication() 
: _mgr{ServerUserManagerImpl::getServerUserManager()} { }


int ServerApplication::runServer() {
    
    std::unique_ptr<iServerSocket> s = std::make_unique<Socket::ServerSocketImpl>();

    if(!_mgr.connectSocket(std::move(s)) ) {
        std::cerr<<"Connection Error" <<std::endl;
        return -1;
    }

    if(!_mgr.connectDb()) {
        std::cerr<<"Database Error" <<std::endl;
        return -1;
    }

    _mgr.startServer();

    return 0;
}

