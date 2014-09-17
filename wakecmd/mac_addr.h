#ifndef __MAC_ADDR_H__
#define __MAC_ADDR_H__

struct mac_addr {
    unsigned char addr[6];
};

int mac_str2byte(const char*, char*);

#endif /* __MAC_ADDR_H__ */

