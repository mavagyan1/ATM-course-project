#include "clientsocket.hpp"
#include <arpa/inet.h> //inet_aadr, inet_ntoa
#include <unistd.h>
#include <netdb.h>
#include <memory>
#include <cstring>

namespace CLIENT_SOCKET {

ClientSocketImpl::ClientSocketImpl()
    : m_clientSd(socket(AF_INET, SOCK_STREAM, 0))
{
    const auto& host = gethostbyname(IP_ADDRESS.c_str());
    m_sendSockAddr.sin_addr.s_addr =
            inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    m_sendSockAddr.sin_port = htons(PORT);
    m_sendSockAddr.sin_family = AF_INET;
}

int ClientSocketImpl::sendMessage(const std::string& message)
{
    return ::send(m_clientSd, (char*)message.c_str(), message.length() + 1, 0);
}

bool  ClientSocketImpl::receiveMessage(std::string& received_message)
{
    char buff[124];
    memset(buff, 0, sizeof(buff));

    int status = recv(m_clientSd, (char*)buff, sizeof(buff), 0);
    std::string s(buff);
    received_message = s;
    return status;
}

void ClientSocketImpl::close()
{
    ::close(m_clientSd);
}

int ClientSocketImpl::connect()
{
    return ::connect(m_clientSd,
            (sockaddr*) &m_sendSockAddr, sizeof(m_sendSockAddr));
}


} //end of CLIENT_SOCKET namespace