#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Comunication{
public:
    //建立socket链接，等待UI端控制报文
    int iSocketServer;
    int iSocketClient;
    struct sockaddr_in tSocketServerAddr; //指定服务器绑定地址
    struct sockaddr_in tSocketClientAddr;


    int iAddrLen = sizeof(struct sockaddr);
    int iRecvLen, iSendLen, iSerialLen;
    int iClientNum = 0;
    char ucRecvBuf[1000];
    char ucSendBuf[1000];
    msgtype massagetype;
    Serializer serializer;
    SwClusterInfoVectorType swc_info;

    tSocketServerAddr.sin_family      = AF_INET; //一般设置为
    tSocketServerAddr.sin_port        = htons(SERVER_PORT); //将SERVER_PORT转化为网络字节序 host to net, short
    in_addr ser_addr;
    inet_aton("192.168.1.20", &ser_addr);
    tSocketServerAddr.sin_addr.s_addr = ser_addr.s_addr;
    //tSocketServerAddr.sin_addr.s_addr = INADDR_ANY; //INADDR_ANY表示本机上所有IP，可以和任何主机通信

    memset(tSocketServerAddr.sin_zero, 0, 8);


    //socket
    iSocketServer = socket(AF_INET, SOCK_STREAM, 0);//AF_INET IPV4连接 SOCK_STREAM启动TCP连接
    if (-1 == iSocketServer)
    {
        printf("socket error!\n");
        //return -1;
    }

    //bind
    int iRet = bind(iSocketServer, (const struct sockaddr *)&tSocketServerAddr, sizeof(struct sockaddr)); //绑定端口
    if (-1 == iRet)
    {
        printf("bind error!\n");
        close(iSocketServer);
        //return -1;
    }

    //listen
    iRet = listen(iSocketServer, BACKLOG); //设置监听 BACKLOG代表同时监听10路连接
    if (-1 == iRet)
    {
        printf("listen error!\n");
        //return -1;
    }
private:
}
#endif // COMMUNICATION_H
