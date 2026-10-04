#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

void network_service()
{
    int sockfd;

    struct sockaddr_in server_address;

    FILE *log;


    printf("\n");
    printf("NETWORK SERVICE\n");
    printf("--------------------------------------------\n");


    /*
     * Create network log
     */

    log = fopen(
        "network_service_log.txt",
        "w"
    );

    if (log == NULL)
    {
        perror("Unable to create network log");
        exit(31);
    }


    fprintf(
        log,
        "NETWORK SERVICE LOG\n"
    );

    fprintf(
        log,
        "===================\n"
    );


    /*
     * Create actual socket
     */

    printf("Creating network socket...\n");

    fprintf(
        log,
        "Creating TCP socket...\n"
    );


    sockfd = socket(
        AF_INET,
        SOCK_STREAM,
        0
    );


    if (sockfd < 0)
    {
        perror("Socket creation failed");

        fprintf(
            log,
            "Socket creation failed.\n"
        );

        fclose(log);

        exit(32);
    }


    printf("Socket created successfully.\n");

    fprintf(
        log,
        "TCP socket created successfully.\n"
    );


    /*
     * Configure localhost
     */

    server_address.sin_family =
        AF_INET;

    server_address.sin_port =
        htons(8080);


    inet_pton(
        AF_INET,
        "127.0.0.1",
        &server_address.sin_addr
    );


    printf(
        "Connecting to 127.0.0.1:8080...\n"
    );


    fprintf(
        log,
        "Attempting connection to "
        "127.0.0.1:8080...\n"
    );


    /*
     * Actual network connection
     */

    if (connect(
            sockfd,
            (struct sockaddr *)&server_address,
            sizeof(server_address)) == 0)
    {
        printf(
            "Network connection established.\n"
        );

        fprintf(
            log,
            "Connection SUCCESS.\n"
        );
    }

    else
    {
        printf(
            "Connection failed: %s\n",
            strerror(errno)
        );

        fprintf(
            log,
            "Connection failed: %s\n",
            strerror(errno)
        );
    }


    close(sockfd);


    fprintf(
        log,
        "Socket closed.\n"
    );


    /*
     * Network failure simulation
     */

    printf("\n");
    printf(
        "[!] Network service failure detected.\n"
    );

    printf(
        "[!] Sending SIGTERM...\n"
    );


    fprintf(
        log,
        "Network service failure simulated.\n"
    );

    fprintf(
        log,
        "Process will terminate using SIGTERM.\n"
    );


    fclose(log);


    fflush(stdout);


    /*
     * Actual abnormal process termination
     */

    raise(SIGTERM);


    /*
     * Normally this line is never reached.
     */

    exit(30);
}