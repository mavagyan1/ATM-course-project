#ifndef __CLIENT_USER_MANAGER_HPP__
#define __CLIENT_USER_MANAGER_HPP__

#include <iostream>
#include <cassert>

#include "iclientusermanager.hpp"
#include "iclientsocket.hpp"

using namespace std;

namespace {

    const string PROCESS_REGISTRATION = "1";
    const string PROCESS_CARD = "2";
    const string GET_BAL = "3";
    const string PROCESS_CASHIN = "4";
    const string PROCESS_CASHOUT = "5";
    const string EX_MSG = "6";
    const string OK = "1";
    const string NOT_OK = "2";
}

class ClientUserManagerImpl : public iClientUserManager
{
private:
    string m_card_number;
    string m_pin;
    unique_ptr<iClientSocket> m_socket;
    bool m_isActive{true};

private:
    ClientUserManagerImpl();

public:

    ClientUserManagerImpl(const ClientUserManagerImpl&) = delete;
    ClientUserManagerImpl& operator=(const ClientUserManagerImpl&) = delete;
    static ClientUserManagerImpl& getClientUserManager();
    ~ClientUserManagerImpl();
    int connectSocket(std::unique_ptr<iClientSocket> socket) override;

public:
    void setCredentials();
    bool processRegistration();
    bool processCard();
    bool cashIn(int amount);
    bool cashOut(int amount);
    double getBalance();
    void setCardNumber(std::string&);
    void setPin(std::string&);
    inline void activate() { m_isActive = true; }
    inline void deactivate() { m_isActive = false; }
    inline bool isActive() const { return m_isActive; }
};


#endif //__CLIENT_USER_MANAGER_HPP__
