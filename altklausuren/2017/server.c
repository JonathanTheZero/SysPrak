#define _POSIX_C_SOURCE 200809L

#include "server.h"
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define HOST "sysprak.priv.lab.nm.ifi.lmu.de"
#define PORT 1357 // TCP Port

void test_connect()
{
    struct addrinfo hints, *result, *rp;

    int sfd, status;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET;       /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;     /* For wildcard IP address */
    hints.ai_protocol = 0;           /* Any protocol */
    hints.ai_canonname = NULL;

    char port[20];
    snprintf(port, sizeof(port), "%d", PORT);

    status = getaddrinfo(HOST, port, &hints, &result);
    if (status != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1)
            continue;

        if (connect(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break; /* Success */
    }

    if (rp == NULL)
    { /* No address succeeded */
        fprintf(stderr, "Could not bind\n");
        exit(EXIT_FAILURE);
    }

    char addrstr[999];
    inet_ntop(rp->ai_family, &((struct sockaddr_in *)rp->ai_addr)->sin_addr, addrstr, sizeof addrstr);
    printf("Eine Verbindung konnte erfolgreich aufgebaut werden.\n");
    printf("IPv4 address: %s (%s)\n", addrstr, rp->ai_canonname);

    freeaddrinfo(result);
}
