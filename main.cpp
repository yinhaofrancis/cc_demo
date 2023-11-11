#include <iostream>
#include <CCMath.h>
#include <CCFile.h>
#include <string>
#include <CCSocket.h>

using namespace cc;
int main(int, char **)
{
    // std::cout << "Hello, from CC_Math_Demo!\n";
    // auto ccdb = CCDB("/Users/haoyin/am/m.cpp");
    // for (size_t i = 0; i < 500; i++)
    // {
    //     auto p = CCRecord();
    //     std::string base = "info ";
    //     base += "index";
    //     base += std::to_string(i);
    //     p.count = base.size();
    //     p.data = (char *)base.c_str();
    //     ccdb.addRecord(p);
    // }
    // ccdb.flush();
    // for (size_t i = 0; i < 500; i++)
    // {
    //     auto rc = ccdb[i];
    //     char* m = (char *)rc->data;
    //     std::cout << m <<std::endl;
    //     free(rc->data);
    //     delete rc;
    // }
    // auto w = cc::CCFileArray<size_t>("a.txt");
    // pid_t p = fork();
    // if (p > 0)
    // {
    //      w.wlock(0,SEEK_SET,1000 * sizeof(size_t));
    //     for (size_t i = 0; i < 1000; i++)
    //     {

    //         w.write(i, i);
    //         w.unlock(i * sizeof(i),SEEK_SET,sizeof(i));
    //         usleep(1000 * 10);
    //     }
    // }else{
    //     usleep(1000 * 1000);

    //     for (size_t i = 0; i < 1000; i++)
    //     {
    //         w.rlock(i * sizeof(size_t),SEEK_SET,sizeof(size_t));
    //         std::cout<<w[i]<<std::endl;
    //         w.unlock(i * sizeof(i),SEEK_SET,sizeof(i));
    //     }
    // }

    int type = 0;
    std::cout << "1 udp 2 tcp" << std::endl;
    std::cin >> type;
    CCSocket *s;
    if (type == 1)
    {
        s = new CCSocket(
            CCSocketUDP);
        int isserver = 0;
        std::cout << "is server:" << std::endl;
        std::cin >> isserver;
        if (isserver)
        {
            s->listen_at(8888);
            while (true)
            {
                s->recieveRemote();
                s->sendMsg(
                    "this is callback");
            }
        }
        else
        {
            s->recieveLoop();
            while (true)
            {
                string msg;
                string address;
                uint16_t port;
                std::cout << "address:" << std::endl;
                std::cin >> address;
                std::cout << "port:" << std::endl;
                ;
                std::cin >> port;
                std::cout << "msg:" << std::endl;
                std::cin >> msg;
                s->sendTo(msg, address, port);
                
            }
        }
    }
    else if (type == 2)
    {
        s = new CCSocket(
            CCSocketTCP);
        int isserver = 0;
        std::cout << "is server:" << std::endl;
        std::cin >> isserver;
        if (isserver)
        {
            s->listen_at(9999);
            s->acceptConnect();
            s->sendMsg("connect establish");
            while (true)
            {
                s->recieveRemote();
                s->sendMsg("this is callback");
            }
        }
        else
        {
            string msg;
            string address;
            uint16_t port;
            std::cout << "address:" << std::endl;
            std::cin >> address;
            std::cout << "port:" << std::endl;
            std::cin >> port;
            s->connect_to(address,port);
            s->recieveLoop();
            while (true)
            {
                std::cout << "msg:" << std::endl;
                std::cin >> msg;
                s->sendMsg(msg);
            }
        }
    }
}
