#include "RUDP_Sender.h"

int main(int argc, char *argv[])
{
    int port;
    char ip[16];

    if (get_params(argc, argv, &port, ip) < 0)
    {
        printf("Error: Invalid parameters\n");
        exit(1);
    }

    printf("IP: %s\n", ip);
    printf("Port: %d\n", port);
    return 0;
}

int get_params(int argc, char *argv[], int *port, char *ip)
{
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-ip") == 0)
        {
            strcpy(ip, argv[i + 1]);
        }
        else if (strcmp(argv[i], "-p") == 0)
        {
            *port = atoi(argv[i + 1]);
        }
    }

    if (*port < 0 || *port > 65535)
        return -1;

    return 0;
}