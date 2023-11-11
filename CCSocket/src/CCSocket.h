#include<string>
#include<iostream>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

namespace cc
{
    enum CCSocketType{
        CCSocketTCP,
        CCSocketUDP
    };
    class CCSocket{
        int socketfd;
        CCSocketType type;
        sockaddr_in remote;
        int tcpRemotefd;
        pthread_t thread;
    public:
        CCSocket(CCSocketType type);
        ~CCSocket();
        void listen_at(unsigned short port);
        void connect_to(std::string remote,unsigned short port);
        void sendMsg(std::string message);
        void sendTo(std::string message,std::string address,unsigned short port);
        void recieveRemote();
        void recieveLoop();
        void getAddress();
        void acceptConnect();

    };
} // namespace cc
