
#include "CCSocket.h"
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
void addressBuild(std::string remote, unsigned short port, sockaddr_in *out_address)
{
    in_addr address;
    memset(&address, 0, sizeof(address));
    inet_pton(AF_INET, remote.c_str(), &address);
    sockaddr_in sock_address;
    memset(&sock_address, 0, sizeof(sock_address));
    sock_address.sin_family = AF_INET;
    sock_address.sin_port = ntohs(port);
    sock_address.sin_addr = address;
    *out_address = sock_address;
}

cc::CCSocket::CCSocket(CCSocketType type)
{
    this->type = type;
    switch (type)
    {
    case CCSocketTCP:
        this->socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        break;
    case CCSocketUDP:
        this->socketfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        break;
    }
}

cc::CCSocket::~CCSocket()
{
    close(this->socketfd);
}

void cc::CCSocket::listen_at(unsigned short port)
{
    sockaddr_in sock_address;
    addressBuild("0,0,0,0", port, &sock_address);
    if (bind(this->socketfd, (const struct sockaddr *)&sock_address, sizeof(sock_address)) != 0)
    {
        std::cout << strerror(errno) << std::endl;
    }
    if (this->type == CCSocketTCP)
    {
        listen(this->socketfd, 4);
    }
}

void cc::CCSocket::connect_to(std::string remote, unsigned short port)
{
    sockaddr_in sock_address;
    addressBuild(remote, port, &sock_address);
    if (0 != connect(this->socketfd, (const sockaddr *)&sock_address, sizeof(sock_address)))
    {
        std::cout << strerror(errno) << std::endl;
        throw strerror(errno);
    }
    this->tcpRemotefd = socketfd;
}

void cc::CCSocket::sendMsg(std::string message)
{
    switch (this->type)
    {
    case CCSocketTCP:

        send(this->tcpRemotefd, message.c_str(), message.length(), 0);
        break;
    default:
        sockaddr_in sock_address = this->remote;
        sendto(this->socketfd, message.c_str(), message.length(), 0, (const sockaddr *)&sock_address, sizeof(sock_address));
        break;
    }
}

void cc::CCSocket::sendTo(std::string message, std::string address, unsigned short port)
{
    switch (this->type)
    {
    case CCSocketUDP:
        sockaddr_in sock_address;
        addressBuild(address, port, &sock_address);
        sendto(this->socketfd, message.c_str(), message.length(), 0, (const sockaddr *)&sock_address, sizeof(sock_address));
        break;
    default:
        break;
    }
}
void * callbackThread(void* cc){
    cc::CCSocket* socket = (cc::CCSocket*)cc;
    while (true)
    {
        socket->recieveRemote();
    }
    
}
void cc::CCSocket::recieveLoop(){
    pthread_create(&this->thread,NULL,callbackThread,this);
}
void cc::CCSocket::recieveRemote()
{
    
    char buffer[4096];
    switch (this->type)
    {
    case CCSocketTCP:
    {

        memset(buffer, 0, sizeof(buffer));
        if (recv(this->tcpRemotefd, buffer, sizeof(buffer), 0) < 0)
        {
            std::cout << strerror(errno) << std::endl;
        }
        break;
    }
    default:
        memset(buffer, 0, sizeof(buffer));
        {
            sockaddr_in in;
            socklen_t size;
            if (recvfrom(this->socketfd, buffer, sizeof(buffer), 0, (sockaddr *)&in, &size) < 0)
            {
                std::cout << strerror(errno) << std::endl;
            }
            this->remote = in;
            break;
        }
    }
    std::cout << buffer << std::endl;
}

void cc::CCSocket::getAddress()
{
}

void cc::CCSocket::acceptConnect()
{
    sockaddr_in in;
    socklen_t size = sizeof(in);
    int remotefd = accept(this->socketfd, (sockaddr *)&in, &size);
    if (0 > remotefd)
    {
        std::cout << strerror(errno) << std::endl;
    }
    this->tcpRemotefd = remotefd;
    this->remote = in;
}
