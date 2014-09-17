#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mac_addr.h"

int
bytes(s)
    char *s;
{
    int n = 0, i;

    if(s[2] != 0)
    {
        return -1;
    } /* if(s[2] != 0) */

    for(i=0; i<2; ++i)
    {
        if('0' <= s[i] && s[i] <= '9')
        {
            n += (s[i] - '0' + 0x00) << ((1 - i) * 4);
        } /* if('0' <= s[i] <= '9') */
        else if('a' <= s[i] && s[i] <= 'f')
        {
            n += (s[i] - 'a' + 0x0a) << ((1 - i) * 4);
        } /* else if('a' <= s[i] <= 'f') */
        else if('A' <= s[i] && s[i] <= 'F')
        {
            n += (s[i] - 'A' + 0x0A) << ((1 - i) * 4);
        } /* else if('A' <= s[i] <= 'F') */
        else
        {
            return -1;
        } /* else */
    } /* for(0 <= i < 2) */
    
    return n;
} /* int bytes(s) */

int
mac_str2byte(str, byte)
    const char *str;
    char       *byte;
{
    size_t  len = strlen(str);
    char   *buf = (char*)malloc(sizeof(char) * len);
    char   *ptr = NULL;
    
    if(len != 17)
    {
        goto INVALID_MACADDR;
    } /* if(len != 17) */

    memmove(buf, str, len); 
    
    ptr = strtok(buf, ":");
    len = 0;
    do
    {
        if(len > 6)
        {
            goto INVALID_MACADDR;
        } /* if(len > 6) */

        byte[len] = bytes(ptr);
        if(byte[len] == -1)
        {
            goto INVALID_MACADDR;
        } /* if(byte[len] == -1) */
        
        ++len;
    } /* do */
    while((ptr = strtok(NULL, ":")) != NULL);
    
    free(buf);
    buf = NULL;

    if(len != 6)
    {
        goto INVALID_MACADDR;
    } /* if(len != 6) */

    return 0;

INVALID_MACADDR:
    free(buf);
    return -1;
} /* int mac_str2byte(str, byte) */

