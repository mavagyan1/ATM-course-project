#ifndef _I_CLIENT_USER_MANAGER_HPP__
#define _I_CLIENT_USER_MANAGER_HPP__

#include <memory>

class iClientSocket;

class iClientUserManager
{
public:
    virtual int connectSocket(std::unique_ptr<iClientSocket>) = 0;
    virtual ~iClientUserManager() = default;
};

#endif //_I_CLIENT_USER_MANAGER_HPP__
