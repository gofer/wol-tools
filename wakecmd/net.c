#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "mac_addr.h"
#include "wake_on_lan.h"

int
magic_packet(buffer, buf_size, mac_addr)
    char                  **buffer;
    int                   *buf_size;
    const struct mac_addr *mac_addr;
{
    int i, j;
    
    /* set buffer size 
     * 
     * Target MAC address;  XX:YY:ZZ:WW:UU:VV
     *
     *      00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
     * 0000 FF FF FF FF FF FF XX YY ZZ WW UU VV XX YY ZZ WW
     * 0010 UU VV .. .. .. .. .. .. 
     * 0020
     *  :
     * 0130                         .. .. XX YY ZZ WW UU VV
     * 0140 XX YY ZZ WW UU VV
     */
    *buf_size = 6 + (6 * 16);
    
    *buffer = (char*)malloc(sizeof(char) * (*buf_size));
    for(i=0; i<6; ++i)
    {
        (*buffer)[i] = 0xFF;
    }

    for(j=0; j<16; ++j)
    {
        for(i=0; i<6; ++i)
        {
            (*buffer)[j*6+i+6] = (*mac_addr).addr[i];
        }
    }

    return 0;
}

int
send_magic_packet(port, addr)
    long                   port;
    const struct mac_addr* addr;
{
    int dgsock = -1, sflag = 0, i;
    struct sockaddr_in saddr;
    unsigned long buf_size = 0;
    char* buffer = NULL;

    /* create magic packet data buffer */
    magic_packet(&buffer, &buf_size, addr);
    
    /* initialize struct sockaddr_in */
    memset(&saddr, sizeof(struct sockaddr_in), 0);
    memset(&saddr.sin_addr.s_addr, sizeof(struct in_addr), 0);
    saddr.sin_addr.s_addr = inet_addr(BROADCAST_IPADDR);
    saddr.sin_port        = htons(port);
    saddr.sin_family      = AF_INET;
    
    /* socket() */
    dgsock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(dgsock < 0)
    {
        return errno;
    } /* if(dgsock < 0) */
    
    /* setsockopt() 
     *     to use broadcast packet sending
     */
    i = 1;
    setsockopt(dgsock, SOL_SOCKET, SO_BROADCAST, (char*)&i, sizeof(int));
    
    /* sendto() */
    i = sendto(
        dgsock, buffer, buf_size, sflag, 
        (struct sockaddr*)&saddr, sizeof(struct sockaddr_in)
    );
    fprintf(stdout, "Send magic packet:\t");
    if(i < 0)
    {
        fprintf(stdout, "failed\n");
        fprintf(stderr, "[debug] errno: %d (%s)\n", errno, strerror(errno));
        return errno;
    } /* if(i < 0) */
    fprintf(stdout, "success\n");

    /* socket close and finalize*/
    close(dgsock);
    free(buffer);

    return 0;
}

