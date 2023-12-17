#ifndef __CLIENT_SOCKET_HPP__
#define __CLIENT_SOCKET_HPP__

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

#include "iclientsocket.hpp"

namespace CLIENT_SOCKET
{
    const std::string IP_ADDRESS = "localhost";
    const int PORT = 1372;


class ClientSocketImpl: public iClientSocket {

    sockaddr_in m_sendSockAddr;
    int m_clientSd;

public:

    ClientSocketImpl();
    int sendMessage(const std::string& message) override;
    bool receiveMessage(std::string& received_message) override;
    void close() override;
    int connect() override;
};

} //end of CLIENT_SOCKET namespace

#endif //__CLIENT_SOCKET_HPP__