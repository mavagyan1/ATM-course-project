#ifndef __SERVER_SOCKET_HPP__
#define __SERVER_SOCKET_HPP__

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <memory>
#include <string>
#include <cstring>

#include "iserversocket.hpp"

namespace Socket
{

const int PORT = 1372;


class ServerSocketImpl: public iServerSocket {

    sockaddr_in m_servAddr;
    int m_serverSd;
    int m_clientSd;

public:

    ServerSocketImpl();

    int bind() override;
    void listen() override;
    int accept() override;
    void close() override;

    int sendMessage(const std::string& message) override;
    int receiveMessage(std::string& received_message) override;
};

} //end of Socket namespace

#endif //__SERVER_SOCKET_HPP__