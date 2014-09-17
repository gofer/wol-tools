#ifndef __WOL_H__
#define __WOL_H__

#include "mac_addr.h"

#define BROADCAST_IPADDR    "255.255.255.255"
#define PORT                12345

int send_magic_packet(long, const struct mac_addr*);

#endif /* __WOL_H__*/

