#ifndef __I_CLIENT_SOCKET_HPP__
#define __I_CLIENT_SOCKET_HPP__

class iClientSocket {
public:
    virtual int connect() = 0;
    virtual void close() = 0;
    virtual bool receiveMessage(std::string&) = 0;
    virtual int sendMessage(const std::string&) = 0;
    virtual ~iClientSocket() = default;
};

#endif //__I_CLIENT_SOCKET_HPP__