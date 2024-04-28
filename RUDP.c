#include "RUDP.h"

int RUDP_handshake(int sockfd1, int sockfd2)
{
    // Send a handshake message from sockfd1 to sockfd2
    const char *handshakeMsg = "RUDP Handshake";
    ssize_t bytesSent = send(sockfd1, handshakeMsg, strlen(handshakeMsg), 0);
    if (bytesSent < 0)
    {
        perror("Failed to send handshake message");
        exit(1);
    }

    // Receive the handshake message on sockfd2
    char handshakeBuffer[1024];
    memset(handshakeBuffer, 0, sizeof(handshakeBuffer));
    ssize_t bytesRead = recv(sockfd2, handshakeBuffer, sizeof(handshakeBuffer), 0);
    if (bytesRead < 0)
    {
        perror("Failed to receive handshake message");
        exit(1);
    }

    // Check if the received handshake message matches the expected message
    if (strcmp(handshakeBuffer, handshakeMsg) == 0)
    {
        printf("Handshake successful\n");
        return 1;
    }
    else
    {
        printf("Handshake failed\n");
        return 0;
    }
}

void RUDP_send(int sockfd, const struct sockaddr_in *peerAddr, const char *data, size_t dataSize)
{
    // Send the initial data packet
    ssize_t bytesSent = sendto(sockfd, data, dataSize, 0, (struct sockaddr *)peerAddr, sizeof(*peerAddr));
    if (bytesSent < 0)
    {
        perror("Failed to send data packet");
        exit(1);
    }

    // Wait for acknowledgment packet
    char ackBuffer[1024];
    memset(ackBuffer, 0, sizeof(ackBuffer));
    ssize_t bytesRead;
    int retransmitCount = 0;
    while (retransmitCount < 3)
    {
        bytesRead = recvfrom(sockfd, ackBuffer, sizeof(ackBuffer), 0, NULL, NULL);
        if (bytesRead >= 0)
        {
            // Acknowledgment received, exit the loop
            break;
        }
        else
        {
            // No acknowledgment received, retransmit the data packet
            bytesSent = sendto(sockfd, data, dataSize, 0, (struct sockaddr *)peerAddr, sizeof(*peerAddr));
            if (bytesSent < 0)
            {
                perror("Failed to retransmit data packet");
                exit(EXIT_FAILURE);
            }
            retransmitCount++;
        }
    }

    if (retransmitCount == 3)
    {
        printf("Failed to receive acknowledgment after 3 retransmissions\n");
    }
    else
    {
        printf("Acknowledgment received\n");
    }
}

void RUDP_rcv(int sockfd)
{
    // Receive data from the peer
    char dataBuffer[1024];
    memset(dataBuffer, 0, sizeof(dataBuffer));
    ssize_t bytesRead = recvfrom(sockfd, dataBuffer, sizeof(dataBuffer), 0, NULL, NULL);
    if (bytesRead < 0)
    {
        perror("Failed to receive data");
        exit(EXIT_FAILURE);
    }

    // Process the received data
    // ...

    // Print the received data
    printf("Received data: %s\n", dataBuffer);
}

void RUDP_close(int sockfd)
{
    // Close the socket
    if (close(sockfd) < 0)
    {
        perror("Failed to close socket");
        exit(EXIT_FAILURE);
    }
}

char *util_generate_random_data(unsigned int size)
{
    char *buffer = NULL;

    if (size == 0)
        return NULL;

    buffer = (char *)calloc(size, sizeof(char));

    if (buffer == NULL)
        return NULL;

    srand(time(NULL));

    for (unsigned int i = 0; i < size; i++)
        *(buffer + i) = ((unsigned int)rand() % 256);

    return buffer;
}