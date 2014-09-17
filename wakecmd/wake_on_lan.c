#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include "mac_addr.h"
#include "wake_on_lan.h"

int
usage(cmdname)
    const char *cmdname;
{
    fprintf(stdout, "[usage] %s [-p [port]] [MAC address]\n", cmdname); 
    return 0;
} /* int usage() */

int
args(argc, argv, mac, port)
    int               argc;
    char            **argv;
    struct mac_addr  *mac;
    long             *port;
{
    int opt;

    while((opt = getopt(argc, argv, "p:")) > 0)
    {
        switch(opt)
        {
        case 'p':
            *port = atoi(optarg);
            break;
        case '?':
        default:
            usage(argv[0]);
            exit(1);
            break;
        } /* switch(opt) */
    } /* while( getopt() ) */
    
    if(optind >= argc)
    {
        usage(argv[0]);
        exit(1);
    } /* if(optind >= argc) */

    while(optind < argc)
    {
        opt = mac_str2byte(argv[optind], (char*)&mac->addr);
        if(opt < 0)
        {
            fprintf(stderr, "Invalid MAC address: %s\n", argv[optind]);
            return 1;
        } /* if(opt < 0) */
        ++optind;
    } /* while(optind < argc) */

    return 0;
} /* int args(argc, argv) */

int
main(argc, argv)
    int    argc;
    char **argv;
{
    long port = PORT;
    struct mac_addr addr;
    
    if(args(argc, argv, &addr, &port) > 0)
    {
        usage(argv[0]);
        exit(1);
    } /* if(args(..) > 0) */

    send_magic_packet(port, &addr);
    
    return EXIT_SUCCESS;
} /* int main(argc, argv) */

