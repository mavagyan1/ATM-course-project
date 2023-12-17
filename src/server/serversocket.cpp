#include "serversocket.hpp"
#include <iostream>


namespace Socket {


ServerSocketImpl::ServerSocketImpl()
        : m_serverSd(socket(AF_INET, SOCK_STREAM, 0))
{
    bzero((char*)&m_servAddr, sizeof(m_servAddr));
    m_servAddr.sin_family = AF_INET;
    m_servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_servAddr.sin_port = htons(PORT);
}

int ServerSocketImpl::bind()
{
    int bindStatus = ::bind(m_serverSd, (struct sockaddr*) &m_servAddr,
                            sizeof(m_servAddr));
    return bindStatus;
}

void ServerSocketImpl::listen()
{
    ::listen(m_serverSd, 5);
}

int ServerSocketImpl::accept()
{
    sockaddr_in clientSockaddr_in;
    socklen_t clientSockAddrSize = sizeof(clientSockaddr_in);
    m_clientSd = ::accept(m_serverSd, (sockaddr *)&clientSockaddr_in, &clientSockAddrSize);
    return m_clientSd;
}
    
void ServerSocketImpl::close()
{
    ::close(m_clientSd);
    ::close(m_serverSd);
}

int ServerSocketImpl::sendMessage(const std::string& message)
{
    return send(m_clientSd, message.c_str(), sizeof(message), 0);
}

int ServerSocketImpl::receiveMessage(std::string& received_message)
{
    char buff[128];
    memset(buff, 0, sizeof(buff));

    int bytes = ::recv(m_clientSd, (char*)buff, sizeof(buff), 0);
    std::string s(buff);
    received_message = s;
    return bytes;
}


} //end of Socket namespaace