
#include <thread>
#include <stdio.h>
#include <pthread.h>
#include <thread>
#include <semaphore.h>
#include <fstream>
#include <string>
#include <unistd.h>
#include "filehandle.h"
#include "usbhandle.h"
#include "massageparser.h"
#include "sys/mount.h"
#include "packagemanagerclient.h"
#include "serializer.h"

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define sleep_time 1000000
#define SERVER_PORT 8888
#define SER_IP "192.168.7.115" //写数据对象的ip
#define BACKLOG 10

void *thrd_usbhandle(void *arg);
void *thrd_icihandle(void *arg);
void *thrd_ucmhandle(void *arg);
//using namespace std;

FileHandle filehd;
UsbHandle usbhd;
vector<updatefileinfo> udfinfo;
luther_gliethttp lg;
MassageParser MP;
PackageManagerClient PMC;



struct UpdatePackageState
{
    usbstate u_s = usbNo;
    filestate f_s = noupdatefile;

}up_s;



int main(int argc, char *argv[])
{
    //建立U盘处理线程、ucm交互线程
    pthread_t usbhandle, icihandle, ucmhandle;
	static ara::log::Logger& logger = ara::log::CreateLogger("MAIN", "main context");
    if(!PMC.FindService()){
        logger.LogError() << "cannot find ucm service";
        return -1;
    }
	
	
	
    int ret = pthread_create(&usbhandle,NULL,thrd_usbhandle, NULL);

    ret += pthread_create(&icihandle,NULL,thrd_icihandle, NULL);
	

	//thread usbhandle(thrd_usbhandle);
	//thread ucmhandle(thrd_ucmhandle);
	

	ret = pthread_join(usbhandle, NULL);
	
    if (!ret)
    {
        std::cout << "pthread usbhandle joint ! " << std::endl;
    }
    else
    {
        std::cout << "pthread usbhandle joint fail ! " << std::endl;
    }

    ret = pthread_join(icihandle, NULL);
    if (!ret)
    {
        std::cout << "pthread icihandle joint ! " << std::endl;
    }
    else
    {
        std::cout << "pthread icihandle joint fail ! " << std::endl;
    }
    return 0;
    ret = pthread_join(ucmhandle, NULL);
    if (!ret)
    {
        std::cout << "pthread ucmhandle joint ! " << std::endl;
    }
    else
    {
        std::cout << "pthread ucmhandle joint fail ! " << std::endl;
    }
    return 0;
}


void *thrd_usbhandle(void *arg)
{

    int device_fd = -1;
    char msg[UEVENT_MSG_LEN+2];
    int n;
	//char prename[15] = "/dev/";
	const char* targe = "/mnt/usb";
	
    device_fd = usbhd.open_luther_gliethttp_socket();
	cout<< "device_fd = "<< device_fd <<endl;

    do{
        while((n = recv(device_fd, msg, UEVENT_MSG_LEN, 0)) > 0) {

            if(n == UEVENT_MSG_LEN)
                continue;

            msg[n] = '\0';
            msg[n+1] = '\0';

            usbhd.parse_event(msg, &lg);
			//std::cout << "find the 1 " << std::endl;
			
			//!strncmp(lg.action, "add", 3)
			if((!strncmp(lg.action, "add", 3))&&(!strncmp(lg.devtype, "partition", 9))&&(!strncmp(lg.subsystem, "block", 5)))
            //if((lg.action == "add")&&(lg.devtype == "partition")&&(lg.subsystem == "block"))
            {
				
                //guazai
                up_s.u_s = usbYes;
					
				//std::cout << "find the 2 " << lg.devname << std::endl;
				char prename[15] = "/dev/";
				const char* Source = strcat(prename, lg.devname);
				std::cout << "after strcat  :  "<< Source << std::endl;
		
                if(!mount(Source, targe, "vfat", 0, NULL))
                {
                    //解压提取jason文件，提取更新包信息
					
                    up_s.f_s = filehd.FileCheck("/mnt/usb/update.zip");
                    if(up_s.f_s == readwrite)
                    {
                        //udfinfo = filehd.Parse("/mnt/usb/update.zip");
						filehd.Parse("/mnt/usb/update.zip", udfinfo);
                    }
                }
				else
				{
					cout<<"gua zai cuo wu"<< std::endl;
				}
            }
			/*
            else if((lg.action == "remove")&&(lg.devtype == "usb_interface")&&(lg.subsystem == "usb"))
            {
				if(!umount((const char *)(strcat(prename, lg.devname))))
                {
                    cout<<"umount seccess"<<std::endl;
                }
                up_s.u_s = usbNo;
                up_s.f_s == noupdatefile;
            }
			*/
			
        }
		//*/
		//usleep(1000);
		
    }while(1);
	
}


void *thrd_icihandle(void *arg)
{
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
    while(1)
    {
        //允许多个client链接, accept返回值为服务端对客户端
        iSocketClient = accept(iSocketServer, (struct sockaddr *)&tSocketClientAddr, (socklen_t *)&iAddrLen); //等待连接 如果建立连接
        if (-1 != iSocketClient)
        {
             iClientNum++;
             printf("Get connect from client %d ,%d: %s\n",  iClientNum,iSocketClient, inet_ntoa(tSocketClientAddr.sin_addr));

             while (1)
             {
                 /* 接收客户端发来的数据并显示出来 */
                 iRecvLen = recv(iSocketClient, ucRecvBuf, 999, 0);
                 if (iRecvLen <= 0)
                 {
                      close(iSocketClient); //关闭连接
                      break;
                 }
				 
                 else
                 {
					 for(int i=0;i<iRecvLen;i++)
					{
						printf("Get Msg From Client %d: %x\n", iClientNum, ucRecvBuf[i]);
					}
                      //判断控制报文并交互,解析报文
                      massagetype = MP.massageparse(ucRecvBuf, iRecvLen);
                      switch (massagetype) {
                      case GetSoftwareInfo:
                          //send softwareinfo
						  printf("softwareinfo\n");
                          swc_info = PMC.GetSwClusterInfo();
						  printf("softwareinfo size is %d\n", sizeof(swc_info));

                          printf("softwarecluster num is %d\n",swc_info.size());
                          
                          iSerialLen = serializer.serialize(swc_info, ucSendBuf);
						  printf("iSerialLen is %d\n",iSerialLen);
                          iSendLen = send(iSocketClient, ucSendBuf, iSerialLen, 0);
                          printf("iSendLen is %d\n",iSendLen);
                          
                          if(iSendLen <= 0)
                          {
                               close(iSocketClient); //关闭连接
                               break;
                          }
                          break;
                      case GetSoftwareChangeInfo:
                          //send softwareChangeinfo
                          serializer.serialize(udfinfo, ucSendBuf);
                          iSendLen = send(iSocketClient, ucSendBuf, strlen(ucSendBuf), 0);
                          if(iSendLen <= 0)
                          {
                               close(iSocketClient); //关闭连接
                               break;
                          }
                          break;
                      case StartSoftwareChanges:
                          //开启ucmhandle线程
                          //周期发送更新状态报文
                          break;
                      default:
                          break;
                      }

                  }
              }
        }
    }
    /*
	while(1)
    {
        cout << "name is: " << udfinfo[1].name << std::endl;
        cout << "version is: " << udfinfo[1].version << std::endl;
        cout << "description is: " << udfinfo[1].description << std::endl;

        usleep(sleep_time);
    }
    */
}


void *thrd_ucmhandle(void *arg)
{

}
