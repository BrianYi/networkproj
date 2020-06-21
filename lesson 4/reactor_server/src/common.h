#pragma once
#include <stdio.h>
#if __linux__
#include <stdint-gcc.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <fcntl.h>
#endif

const uint32_t RECV_BUF_SIZE = 10 * 1024u;
const uint32_t SEND_BUF_SIZE = 10 * 1024u;

#define SERVER_IP	"0.0.0.0"
#define SERVER_PORT_TCP	5566