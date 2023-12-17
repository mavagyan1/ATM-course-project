#ifndef __CLIENT_APPLICATION_HPP__
#define __CLIENT_APPLICATION_HPP__

#include "clientuserManager.hpp"
#include "commandRegistry.hpp"

class ClientApplication{
public:
    ClientApplication();
    int getInput() const;
    void processInput();
    int runApp();
    void runATM();
    
private:
    bool isActive{true};
    ClientUserManagerImpl& _mgr;
    CommandRegistry& _reg;
    void printOptions();
    void printMenu();
};
#endif //__CLIENT_APPLICATION_HPP__