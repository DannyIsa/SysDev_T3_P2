#ifndef RUDP_H
#define RUDP_H

// Include necessary headers
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Function declarations
int RUDP_handshake(int sockfd1, int sockfd2);
void RUDP_send(int sockfd, const struct sockaddr_in *peerAddr, const char *data, size_t dataSize);
void RUDP_rcv(int sockfd);
void RUDP_close(int sockfd);
char *util_generate_random_data(unsigned int size);

#endif // RUDP_H