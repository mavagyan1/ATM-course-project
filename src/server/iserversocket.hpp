#ifndef __I_SERVER_SOCKET__
#define __I_SERVER_SOCKET__

class iServerSocket 
{
public:
    virtual int bind() = 0;
    virtual void listen() = 0;
    virtual int accept() = 0;

    virtual int sendMessage(const std::string&) = 0;
    virtual int receiveMessage(std::string&) = 0;

    virtual void close() = 0;
};

#endif //__I_SERVER_SOCKET__
