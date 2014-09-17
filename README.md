# What's this?
## Wake on LAN(WoL) tools in your character console.
Thess make the power management easy in your computer cluster.

# How to use?
* Clone this repository

    git clone git@github.com:gofer/wol-tools.git

* Wake up your machine
This tool broadcasts UDP magic packet to the network segment.

    ./wol [hostname or IP address or MAC address]

# Attention
It needs target NIC's MAC address to build the magic packet.
This tool estimates target MAC address in your local ARP cache or static local database.

File "local.db"; local database is as following format.

    [HOSTNAME] [IP ADDRESS] [MAC ADDRESS]

For instace,

    dev.your.local.domain 123.45.6.7 00:1a:2b:3c:4d:5e

All columns have separated unary space ' '.

