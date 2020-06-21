#include "PlatformHeader.h"
#include "TcpSocket.h"

bool g_bQuit = false;
std::list<TcpSocket*> g_clients;
std::mutex g_mx;
sem_t g_semQuit;
void* callback_func_receive(void*)
{
    printf("SYSTEM: receive thread start...\r\n");
    char buf[1024];
    for(;!g_bQuit;)
    {
        msleep(10);
        auto it = g_clients.begin();
        while (it != g_clients.end())
        {
            TcpSocket* ptrClient = *it;
            bzero(buf,sizeof(buf));
            int32_t recvSize = ptrClient->recv(buf, sizeof(buf), Socket::NonBlocking);
            if (recvSize == 0)
            {
                printf("SYSTEM: %s:%u has lost.\r\n",
                        ptrClient->ip().c_str(), ptrClient->port());
                {
                    std::unique_lock<std::mutex> locker(g_mx);
                    it = g_clients.erase(it);
                    delete ptrClient;
                }
            }
            else if (recvSize == -1)
            {
                msleep(10);
                it++;
                continue;
            }
            else
            {
                printf(">>> received %u bytes from %s:%u, %lu connections connected. <<<\r\n", 
                       recvSize, ptrClient->ip().c_str(), ptrClient->port(), g_clients.size());
                printf("CONTENT: %s\r\n", buf);
                if (!strcmp(buf,"quit"))
                {
                    printf("SYSTEM: %s:%u has quit.\r\n",
                            ptrClient->ip().c_str(), ptrClient->port());
                    {
                        std::unique_lock<std::mutex> locker(g_mx);
                        it = g_clients.erase(it);
                        delete ptrClient;
                    }
                }
                else if (!strcmp(buf, "exit"))
                {
                    printf("SYSTEM: %s:%u has triggered exit.\r\n",
                            ptrClient->ip().c_str(), ptrClient->port());
                    g_bQuit=true;
                }
            }
        }
    }
    printf("SYSTEM: receive thread quit.\r\n");
    sem_post(&g_semQuit);
    return nullptr;
}

int main()
{
    TcpSocket server;
    server.listen(7788, 32);
    sem_init(&g_semQuit, 0, 0);
    pthread_t pid;
    int ret = pthread_create(&pid, nullptr, callback_func_receive, (void *)nullptr);
    if (ret)
    {
        printf("SYSTEM: failed with create thread.\r\n");
        exit(EXIT_FAILURE);
    }
    for(;!g_bQuit;)
    {
        TcpSocket* newClient = server.accept(Socket::NonBlocking);
        if (newClient)
        {
            printf("SYSTEM: acceped connection from %s:%u\r\n",
                    newClient->ip().c_str(), newClient->port());
            std::unique_lock<std::mutex> locker(g_mx);
            g_clients.push_back(newClient); 
        }    
        msleep(10);
    }

    sem_wait(&g_semQuit);
    return 0;    
}

