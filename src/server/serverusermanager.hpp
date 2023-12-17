#ifndef __SERVER_USER_MANAGER_HPP__
#define __SERVER_USER_MANAGER_HPP__
#include "iserverusermanager.hpp"
#include "serverusermanager.hpp"
#include "sqldb.hpp"
#include <string>

class ServerUserManagerImpl : public iServerUserManager
{
private:
    ServerUserManagerImpl();

private:
    std::unique_ptr <iServerSocket> m_socket;
    SqlDBImpl&  m_db;
    std::string m_card_number;
    std::string m_pin;
    std::string m_received_message;

public:

    ServerUserManagerImpl(const ServerUserManagerImpl&) = delete;
    ServerUserManagerImpl& operator=(const ServerUserManagerImpl&) = delete;

    static ServerUserManagerImpl& getServerUserManager();
   
    void startServer() override;
    bool connectDb() override;
    bool connectSocket(std::unique_ptr <iServerSocket> socket);

private:

    void processMessage();
    void cardRegistration();
    bool validate();
    std::string getBalance();
    void cashIn(const std::string& amount);
    bool cashOut(std::string& amount);

};

#endif //__SERVER_USER_MANAGER_HPP__

