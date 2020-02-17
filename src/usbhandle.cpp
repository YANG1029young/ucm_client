#include "usbhandle.h"

void UsbHandle::usbhandle()
{

}

int UsbHandle::open_luther_gliethttp_socket(void)
{
    struct sockaddr_nl addr;
    int sz = 64*1024;
    int s;

    memset(&addr, 0, sizeof(addr));
    addr.nl_family = AF_NETLINK;
    addr.nl_pid = getpid();
    addr.nl_groups = 0xffffffff;

    s = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);
    if (s < 0)
        return -1;

    setsockopt(s, SOL_SOCKET, SO_RCVBUFFORCE, &sz, sizeof(sz));

    if (bind(s, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        close(s);
        return -1;
    }

    return s;
}

void UsbHandle::parse_event(const char *msg, luther_gliethttp *lg)
{
    lg->action = "";
    lg->path = "";
    lg->subsystem = "";
    lg->firmware = "";
    lg->devname = "";
    lg->devtype = "";
    lg->major = -1;
    lg->minor = -1;


    printf("========================================================\n");
    while (*msg) {
        //printf("%s\n",msg);

        if (!strncmp(msg, "ACTION=", 7)) {
            msg += 7;
            lg->action = msg;
        } else if (!strncmp(msg, "DEVPATH=", 8)) {
            msg += 8;
            lg->path = msg;
        } else if (!strncmp(msg, "SUBSYSTEM=", 10)) {
            msg += 10;
            lg->subsystem = msg;
        } else if (!strncmp(msg, "FIRMWARE=", 9)) {
            msg += 9;
            lg->firmware = msg;
        } else if (!strncmp(msg, "MAJOR=", 6)) {
            msg += 6;
            lg->major = atoi(msg);
        } else if (!strncmp(msg, "MINOR=", 6)) {
            msg += 6;
            lg->minor = atoi(msg);
        }else if (!strncmp(msg, "DEVNAME=", 8)) {
            msg += 8;
            lg->devname = msg;
        }
        else if (!strncmp(msg, "DEVTYPE=", 8)) {
                    msg += 8;
                    lg->devtype = msg;
        }


        while(*msg++)
            ;
    }


}
