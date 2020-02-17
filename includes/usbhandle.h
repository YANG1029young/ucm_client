#ifndef USBHANDLE_H
#define USBHANDLE_H

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <linux/netlink.h>

#define UEVENT_MSG_LEN 4096

struct luther_gliethttp {
    const char *action;
    const char *path;
    const char *subsystem;
    const char *firmware;
    const char *devname;
    const char *devtype;
    int major;
    int minor;
};


class UsbHandle
{
public:
    void usbhandle();
    
    int open_luther_gliethttp_socket(void);
       
    void parse_event(const char *msg, luther_gliethttp *luther_gliethttp);

private:

};
#endif // USBHANDLE_H
