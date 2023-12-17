#ifndef __I_COMMAND_HPP__
#define __I_COMMAND_HPP__

#include "clientuserManager.hpp"

class ICommand {
public:
    ICommand() : _mgr{ClientUserManagerImpl::getClientUserManager()} { }
    virtual void execute() = 0;
    virtual ~ICommand() = default;
protected:
    ClientUserManagerImpl& _mgr;
};

#endif //__I_COMMAND_HPP__