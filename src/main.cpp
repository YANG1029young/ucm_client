
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
#include "packagemanagerclient.h"
#include "serializer.h"
#include "sys/mount.h"
#include "stateswitcher.h"

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>


#define status_sleep_time 5
#define SERVER_PORT 50008
#define SER_IP "192.168.1.9" //写数据对象的ip
#define BACKLOG 10

void *thrd_usbhandle(void *arg);
void *thrd_icihandle(void *arg);
//void *thrd_ucmhandle(int iSocketClient);
int thrd_ucmhandle(int iSocketClient);
int thrd_send_PMC_status(int iSocketClient);
//using namespace std;

FileHandle filehd;
UsbHandle usbhd;
vector<updatefileinfo> udfinfo;
luther_gliethttp lg;
MassageParser MP;
PackageManagerClient PMC;
updatestate UD_STATE = updatestate::ready;

enum ucm_stage{transferring, processing, activation};

struct UpdatePackageState
{
    usbstate u_s = usbNo;
    filestate f_s = noupdatefile;

}up_s;

//ara::exec::proxy::StateClientProxy *g_stateClientProxy = NULL;

int main(int argc, char *argv[])
{
	cout << "ucm_client start" << endl;
	int ret;
	ret = FindEM();
	if(ret) return 0;
    static ara::log::Logger& logger = ara::log::CreateLogger("MAIN", "main context");
    //建立U盘处理线程、ucm交互线程
    pthread_t usbhandle, icihandle;
    if(!PMC.FindService()){
        logger.LogError() << "cannot find ucm service";
        return -1;
    }
	
    ret = pthread_create(&usbhandle,NULL,thrd_usbhandle, NULL);
    ret += pthread_create(&icihandle,NULL,thrd_icihandle, NULL);
	
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
}


void *thrd_usbhandle(void *arg)
{

    int device_fd = -1;
    char msg[UEVENT_MSG_LEN+2];
    int n;
	//char prename[15] = "/dev/";
	const char* target = "/mnt/usb";
	
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
            {
                //guazai
                up_s.u_s = usbYes;
					
				//std::cout << "find the 2 " << lg.devname << std::endl;
				char prename[15] = "/dev/";
				const char* Source = strcat(prename, lg.devname);
				std::cout << "after strcat  :  "<< Source << std::endl;
				
				//check if there is "/mnt/usb", if no, make it
                filestate usbfolder = filehd.FileCheck(target);
                if(usbfolder == noupdatefile){

                    if(!mkdir(target, S_IRWXU)){
                        cout<<"creat /mnt/usb success"<<endl;
                    }
                    else{
                        cout<<"creat /mnt/usb fail"<<endl;
                    }
                }
                else{
                    umount(target);
                }
		
                if(!mount(Source, target, "vfat", 0, NULL))
                {
                    //解压提取jason文件，提取更新包信息
					
                    up_s.f_s = filehd.FileCheck("/mnt/usb/update.zip");
                    if(up_s.f_s == readwrite)
                    {
                        //udfinfo = filehd.Parse("/mnt/usb/update.zip");
						udfinfo.clear();
						filehd.Parse("/mnt/usb/update.zip", &udfinfo);
						cout<<"updatepackage name is "<< udfinfo[0].Name<< endl;
						cout<<"updatepackage packageType is "<< udfinfo[0].PackageType << endl;
						
                    }
					else if(up_s.f_s == readonly){
                        cout<<"updatefile readonly"<< endl;
                    }
                    else if(up_s.f_s == writeonly){
                        cout<<"updatefile writeonly"<< endl;
                    }
                    else if(up_s.f_s == noupdatefile){
                        cout<<"no updatefile"<< endl;
                    }
                }
				else
				{
					cout<<"mount error"<< std::endl;
				}
            }
			//如果拔出优盘 清空更新包中的信息&&卸载优盘
			else if((!strncmp(lg.action, "remove", 6))&&(!strncmp(lg.devtype, "partition", 9))&&(!strncmp(lg.subsystem, "block", 5)))
            {
				udfinfo.clear();
                if(!umount (target))
                {
                    cout << "umount device success" << endl;
                }
                else
                {
                    cout << "umount device fail" << endl;
                }
			}
			
        }
	
    }while(1);
	
}


void *thrd_icihandle(void *arg)
{
    //pthread_t ucmhandle;
    //建立socket链接，等待UI端控制报文
    //thread ucmhandle; 
	vector<thread> send_PMC_status;
	vector<thread> ucmhandles;
    int iSocketServer;
    int iSocketClient;
    struct sockaddr_in tSocketServerAddr; //指定服务器绑定地址
    struct sockaddr_in tSocketClientAddr;

	int index = 0;

    int iAddrLen = sizeof(struct sockaddr);
    int iRecvLen, iSendLen, iSerialLen;
    int iClientNum = 0;
    char ucRecvBuf[BUF_SIZE];
    char ucSendBuf[BUF_SIZE];
    msgtype massagetype;
    //Serializer serializer;
    SwClusterInfoVectorType swc_info;
    
    tSocketServerAddr.sin_family      = AF_INET; //一般设置为
    tSocketServerAddr.sin_port        = htons(SERVER_PORT); //将SERVER_PORT转化为网络字节序 host to net, short
    in_addr ser_addr;
    inet_aton(SER_IP, &ser_addr);
    tSocketServerAddr.sin_addr.s_addr = ser_addr.s_addr;
    //tSocketServerAddr.sin_addr.s_addr = INADDR_ANY; //INADDR_ANY表示本机上所有IP，可以和任何主机通信

    memset(tSocketServerAddr.sin_zero, 0, 8);


	bool socket_statu = false;
	do{
		socket_statu = false;
		//socket
		iSocketServer = socket(AF_INET, SOCK_STREAM, 0);//AF_INET IPV4连接 SOCK_STREAM启动TCP连接
		if (-1 == iSocketServer)
		{
			printf("socket error!\n");
			sleep(1);
			continue;
			//pthread_exit(NULL);
			//return -1;
		}

		//bind
		int iRet = bind(iSocketServer, (const struct sockaddr *)&tSocketServerAddr, sizeof(struct sockaddr)); //绑定端口
		if (-1 == iRet)
		{
			printf("bind error!\n");
			close(iSocketServer);
			sleep(1);
			continue;
			//pthread_exit(NULL);
			//return -1;
		}

		//listen
		iRet = listen(iSocketServer, BACKLOG); //设置监听 BACKLOG代表同时监听10路连接
		if (-1 == iRet)
		{
			printf("listen error!\n");
			sleep(1);
			continue;
			//pthread_exit(NULL);
			//return -1;
		}
		socket_statu = true;
		printf("socket aply success!\n");
	}while(!socket_statu);
    
    while(1)
    {
        //允许多个client链接, accept返回值为服务端对客户端
        iSocketClient = accept(iSocketServer, (struct sockaddr *)&tSocketClientAddr, (socklen_t *)&iAddrLen); //等待连接 如果建立连接
        if (-1 != iSocketClient)
        {
             iClientNum++;
             printf("Get connect from client %d ,%d: %s\n",  iClientNum,iSocketClient, inet_ntoa(tSocketClientAddr.sin_addr));

             //周期向ICI汇报ucm状态
			 send_PMC_status.push_back(thread(thrd_send_PMC_status, iSocketClient));
             while (1)
             {
                 /* 接收客户端发来的数据并显示出来 */
                 iRecvLen = recv(iSocketClient, ucRecvBuf, 999, 0);
				 printf("irecvlen is %d\n", iRecvLen);
                 if (iRecvLen <= 0)
                 {
                      close(iSocketClient); //关闭连接
                      break;
                 }
                 else
                 {
                      //判断控制报文并交互,解析报文
                      massagetype = MP.massageparse(ucRecvBuf, iRecvLen);
                      /*test*/
                      for(int i=0;i<iRecvLen;i++)
                      {
                         printf("Get Msg From Client %d: %x\n", iClientNum, ucRecvBuf[i]);
                      }
	
                      switch (massagetype) {
                      case GetSoftwareInfo:
                          //send softwareinfo
                        
                          swc_info = PMC.GetSwClusterInfo();
                          printf("softwarecluster num is %d\n",swc_info.size());
						  PMC.GetSwClusterChangeInfo();
                          iSerialLen = Serializer::serialize(swc_info, ucSendBuf);
                          iSendLen = send(iSocketClient, ucSendBuf, iSerialLen, 0);
                          if(iSendLen <= 0)
                          {
                               close(iSocketClient); //关闭连接
                               break;
                          }

                          break;
                      case GetSoftwareChangeInfo:
                          //send softwareChangeinfo
						  printf("softwarechangecluster num is %d\n", udfinfo.size());
                          iSerialLen = Serializer::serialize(udfinfo, ucSendBuf);
                          iSendLen = send(iSocketClient, ucSendBuf, iSerialLen, 0);
                          if(iSendLen <= 0)
                          {
                               close(iSocketClient); //关闭连接
                               break;
                          }
                          break;
                      case StartSoftwareChanges:
                          //开启ucmhandle线程
                          printf("StartSoftwareChanges\n");
                          try
                          {
							  ucmhandles.push_back( thread(thrd_ucmhandle, iSocketClient));
                          }
                          catch(exception &e)
                          {
                              cout<<"exception: "<< e.what() <<endl;
                          }

                          //周期发送更新状态报文
                          break;
                      default:
                          break;
                      }

                  }
             }
			 
			 try{
				 for(auto &i : ucmhandles)
				 {
					 i.join();
				 }
                 //ucmhandle.join();
             }
			 catch(...)
			 {
				 
			 }
			 
        }
		
        try{
			for(auto &i : send_PMC_status)
			{
				i.join();
			}
                 //ucmhandle.join();
        }
		catch(...)
		{
				 
		}
    }
}


int thrd_ucmhandle(int iSocketClient)
{
	cout << "ucmhandle start"<< endl;
	
	SwClusterInfoVectorType swc_info;
    swc_info = PMC.GetSwClusterInfo();
	//检查更新软件是否安装过
	if(!filehd.CheckUpdate(udfinfo, swc_info)){
		return -1;
	}
	
	//切换状态机
	if(UD_STATE == updatestate::ready) {
		StateSwitch("Update", &UD_STATE);
	}
    else {
		cout << "please wait for update state ready" << endl;
		return -1;
	}
	
	//transfer
    //计算更新包大小
    int size = filehd.GetSize("/mnt/usb/update.zip");
    if(size < 0)
    {
        cout << "update.zip size error" << endl;
		StateSwitch("Running", &UD_STATE);
        return -1;
    }
	cout << "get update.zip size success"<< endl;
    
	
    //TransferStart
    TransferStartReturnType TransferStartReturn = PMC.TransferStart(size);
    switch (TransferStartReturn.TransferStartSuccess) {
    case TransferStartSuccessType::kInsufficientMemory:
        cout<<"TransferStart return type is kInsufficientMemory"<<endl;
        StateSwitch("Running", &UD_STATE);
        return -1;
    case TransferStartSuccessType::kSuccess:
        cout<<"TransferStart return type is kSuccess"<<endl;
        break;
    default:
        return -1;
    }

    //TransferPackage
    TransferDataReturnType TransferPackageReturn = PMC.TransferPackage(TransferStartReturn.TransferId, "/mnt/usb/update.zip");
    switch (TransferPackageReturn) {
    case TransferDataReturnType::kSuccess:
        cout<<"TransferPackage return type is kSuccess"<<endl;
        break;
    case TransferDataReturnType::kIncorrectBlock:
        cout<<"TransferPackage return type is kIncorrectBlock"<<endl;
        StateSwitch("Running", &UD_STATE);
        return -1;
    case TransferDataReturnType::kIncorrectSize:
        cout<<"TransferPackage return type is kIncorrectSize"<<endl;
        StateSwitch("Running", &UD_STATE);
        return -1;
    case TransferDataReturnType::kInsufficientMemory:
        cout<<"TransferPackage return type is kInsufficientMemory"<<endl;
        StateSwitch("Running", &UD_STATE);
        return -1;
    case TransferDataReturnType::kInvalidTransferId:
        cout<<"TransferPackage return type is kInvalidTransferId"<<endl;
        StateSwitch("Running", &UD_STATE);
        return -1;
    case TransferDataReturnType::kOperationNotPermitted:
        cout<<"TransferPackage return type is kOperationNotPermitted"<<endl;
        StateSwitch("Running", &UD_STATE);
        return -1;
    default:
        return -1;
    }


    //TransferExit
    TransferExitReturnType TransferExitReturn = PMC.TransferExit( TransferStartReturn.TransferId);
    switch (TransferExitReturn) {
    case TransferExitReturnType::kSuccess:
        cout<<"TransferExit return type is kSuccess"<<endl;
        break;
    case TransferExitReturnType::kInsufficientData:
        cout<<"TransferExit return type is kInsufficientData"<<endl;
        StateSwitch("Running", &UD_STATE);
        return -1;
    case TransferExitReturnType::kInvalidTransferId:
        cout<<"TransferExit return type is kInvalidTransferId"<<endl;
        StateSwitch("Running", &UD_STATE);
        return -1;
    case TransferExitReturnType::kOperationNotPermitted:
        cout<<"TransferExit return type is kOperationNotPermitted"<<endl;
        StateSwitch("Running", &UD_STATE);
        return -1;
    case TransferExitReturnType::kPackageInconsistent:
        cout<<"TransferExit return type is kPackageInconsistent"<<endl;
        StateSwitch("Running", &UD_STATE);
        return -1;

    default:
        return -1;
    }


    //processing
    PackageManagerStatusType PM_status = PMC.GetCurrentState();
    if((PM_status != PackageManagerStatusType::kIdle) && (PM_status != PackageManagerStatusType::kReady))
    {
        //cout << "PM_status wrong : " << PM_status << endl;
		cout << "PM_status wrong : "  << endl;
        //切换状态机
        StateSwitch("Running", &UD_STATE);
        return -1;
    }
	cout << "PM_status success" << endl;

	
    auto ret = PMC.Process(TransferStartReturn.TransferId);

	/*
    while(PMC.GetCurrentState() == PackageManagerStatusType::kBusy){
        UInt8 progress = PMC.GetProcessProgress(TransferStartReturn.TransferId);
        char buf[1000];
        int iSerialLen = Serializer::serialize(progress, buf);
        int iSendLen = send(iSocketClient,  buf, iSerialLen, 0);
        if(iSendLen <= 0)
        {
             close(iSocketClient); //关闭连接
             break;
        }
        usleep(1000000);
    }
	*/
	

    //查看process的返回值，阻塞
    ProcessResultType ProcessResult = ret.get().result.result;
    switch (ProcessResult) {
    case ProcessResultType::kInsufficientMemory:
        cout<<"Process return type is kInsufficientMemory"<<endl;
		StateSwitch("Running", &UD_STATE);
        return -1;
    case ProcessResultType::kInvalidManifest:
        cout<<"Process return type is kInvalidManifest"<<endl;
		StateSwitch("Running", &UD_STATE);
        return -1;
    case ProcessResultType::kInvalidTransferId:
        cout<<"Process return type is kInvalidTransferId"<<endl;
		StateSwitch("Running", &UD_STATE);
        return -1;
    case ProcessResultType::kOperationNotPermitted:
        cout<<"Process return type is kOperationNotPermitted"<<endl;
		StateSwitch("Running", &UD_STATE);
        return -1;
    case ProcessResultType::kPackageInconsistent:
        cout<<"Process return type is kPackageInconsistent"<<endl;
		StateSwitch("Running", &UD_STATE);
        return -1;
    case ProcessResultType::kReject:
        cout<<"Process return type is kReject"<<endl;
		StateSwitch("Running", &UD_STATE);
        return -1;
    case ProcessResultType::kSuccess:
        cout<<"Process return type is kSuccess"<<endl;
        break;
    default:
        return -1;
    }

    //activation
    PM_status = PMC.GetCurrentState();
    if(PM_status != PackageManagerStatusType::kReady)
    {
		cout << "Before active wrong : " << endl;
        //切换状态机
        StateSwitch("Running", &UD_STATE);
        return -1;
    }
	cout << "Before active seccess : " << endl;
    ActivateReturnType ActivateReturn = PMC.Activate( ActivateOptionType::kDefault);
    switch (ActivateReturn) {
    case ActivateReturnType::kErrorDuringActivation:
        cout << "active return type is: kErrorDuringActivation" << endl;
        break;
    case ActivateReturnType::kErrorMissingDependencies:
        cout << "active return type is: kErrorMissingDependencies" << endl;
        break;
    case ActivateReturnType::kErrorNoProcessedPackages:
        cout << "active return type is: kErrorNoProcessedPackages" << endl;
        break;
    case ActivateReturnType::kErrorNoValidProcessing:
        cout << "active return type is: kErrorNoValidProcessing" << endl;
        break;
    case ActivateReturnType::kSuccess:
        cout << "active return type is: kSuccess" << endl;
        break;
    default:
        break;
    }
    //如果激活失败则回滚
    if(ActivateReturn != ActivateReturnType::kSuccess)
    {
        cout << "active wrong : "  << endl;

        RollbackReturnType RollbackReturn = PMC.Rollback();
        switch (RollbackReturn) {
        case RollbackReturnType::kNotAbleToRollback:
            cout << "rollback return type is: kNotAbleToRollback" << endl;
            break;
        case RollbackReturnType::kNothingToRollback:
            cout << "rollback return type is: kNothingToRollback" << endl;
            break;
        case RollbackReturnType::kSuccess:
            cout << "rollback return type is: kSuccess" << endl;
            break;
        default:
            break;
        }
        //切换状态机
        StateSwitch("Running", &UD_STATE);
        return -1;
    }
    //finish
    FinishReturnType FinishReturn = PMC.Finish();
    switch (FinishReturn) {
    case FinishReturnType::kOperationNotPermitted:
        cout << "finish return type is: kOperationNotPermitted" << endl;
        StateSwitch("Running", &UD_STATE);
        return -1;
    case FinishReturnType::kUndefinedError:
        cout << "finish return type is: kUndefinedError" << endl;
        StateSwitch("Running", &UD_STATE);
        return -1;
    case FinishReturnType::kSuccess:
        cout << "finish return type is: kSuccess" << endl;
        break;
    default:
        return -1;
    }

	StateSwitch("Running", &UD_STATE);
    return 0;
}

/* 
int thrd_ucmhandle(int iSocketClient)
{
	cout << "ucmhandle start"<< endl;
	
	SwClusterInfoVectorType swc_info;
    swc_info = PMC.GetSwClusterInfo();
	//检查更新软件是否安装过
	if(!filehd.CheckUpdate(udfinfo, swc_info)){
		return -1;
	}
	
	//切换状态机
	if(UD_STATE == updatestate::ready) {
		StateSwitch("Update", &UD_STATE);
	}
    else {
		cout << "please wait for update state ready" << endl;
		return -1;
	}
	
	//transfer
    //计算更新包大小
    int size = filehd.GetSize("/mnt/usb/update.zip");
    if(size < 0)
    {
        cout << "update.zip size error" << endl;
		StateSwitch("Running", &UD_STATE);
        return -1;
        //pthread_exit(NULL);
    }
	cout << "get update.zip size success"<< endl;
    
	
    TransferStartReturnType TransferStartReturn = PMC.TransferStart(size);
    if(TransferStartReturn.TransferStartSuccess == TransferStartSuccessType::kInsufficientMemory)
    {
        cout << "InsufficientMemory" << endl;
        //切换状态机
        StateSwitch("Running", &UD_STATE);
        return -1;
    }
	cout << "TransferStart success" << endl;

    TransferDataReturnType TransferPackageReturn = PMC.TransferPackage(TransferStartReturn.TransferId, "/mnt/usb/update.zip");
    if(TransferPackageReturn != TransferDataReturnType::kSuccess)
    {
        //cout << "transferpackage error : " << TransferPackageReturn << endl;
		cout << "transferpackage error : "<< endl;
        //切换状态机
        StateSwitch("Running", &UD_STATE);
        return -1;
    }
	cout << "TransferPackage success" << endl;

    TransferExitReturnType TransferExitReturn = PMC.TransferExit( TransferStartReturn.TransferId);
    if(TransferExitReturn != TransferExitReturnType::kSuccess)
    {
        //cout << "transferexit error : " << TransferExitReturn << endl;
		cout << "transferexit error : "  << endl;
        //切换状态机
        StateSwitch("Running", &UD_STATE);
        return -1;
    }
	cout << "TransferExit success" << endl;

    //processing
    PackageManagerStatusType PM_status = PMC.GetCurrentState();
    if((PM_status != PackageManagerStatusType::kIdle) && (PM_status != PackageManagerStatusType::kReady))
    {
        //cout << "PM_status wrong : " << PM_status << endl;
		cout << "PM_status wrong : "  << endl;
        //切换状态机
        StateSwitch("Running", &UD_STATE);
        return -1;
    }
	cout << "PM_status success" << endl;

	
    auto ret = PMC.Process(TransferStartReturn.TransferId);

	
    // while(PMC.GetCurrentState() == PackageManagerStatusType::kBusy){
        // UInt8 progress = PMC.GetProcessProgress(TransferStartReturn.TransferId);
        // char buf[1000];
        // int iSerialLen = Serializer::serialize(progress, buf);
        // int iSendLen = send(iSocketClient,  buf, iSerialLen, 0);
        // if(iSendLen <= 0)
        // {
             // close(iSocketClient); //关闭连接
             // break;
        // }
        // usleep(1000000);
    // }
	
	

    //查看process的返回值，阻塞
    ProcessResultType ProcessResult = ret.get().result.result;
    switch (ProcessResult) {
    case ProcessResultType::kInsufficientMemory:
        cout<<"Process return type is kInsufficientMemory"<<endl;
		StateSwitch("Running", &UD_STATE);
        return -1;
    case ProcessResultType::kInvalidManifest:
        cout<<"Process return type is kInvalidManifest"<<endl;
		StateSwitch("Running", &UD_STATE);
        return -1;
    case ProcessResultType::kInvalidTransferId:
        cout<<"Process return type is kInvalidTransferId"<<endl;
		StateSwitch("Running", &UD_STATE);
        return -1;
    case ProcessResultType::kOperationNotPermitted:
        cout<<"Process return type is kOperationNotPermitted"<<endl;
		StateSwitch("Running", &UD_STATE);
        return -1;
    case ProcessResultType::kPackageInconsistent:
        cout<<"Process return type is kPackageInconsistent"<<endl;
		StateSwitch("Running", &UD_STATE);
        return -1;
    case ProcessResultType::kReject:
        cout<<"Process return type is kReject"<<endl;
		StateSwitch("Running", &UD_STATE);
        return -1;
    case ProcessResultType::kSuccess:
        cout<<"Process return type is kSuccess"<<endl;
        break;
    default:
        return -1;
    }
    
	cout << "Process success" << endl;
    //activation
    PM_status = PMC.GetCurrentState();
    if(PM_status != PackageManagerStatusType::kReady)
    {
		cout << "Before active wrong : " << endl;
        //切换状态机
        StateSwitch("Running", &UD_STATE);
        return -1;
    }
	cout << "Before active seccess : " << endl;
     ActivateReturnType ActivateReturn = PMC.Activate( ActivateOptionType::kDefault);
    switch (ActivateReturn) {
    case ActivateReturnType::kErrorDuringActivation:
        cout << "active return type is: kErrorDuringActivation" << endl;
        break;
    case ActivateReturnType::kErrorMissingDependencies:
        cout << "active return type is: kErrorMissingDependencies" << endl;
        break;
    case ActivateReturnType::kErrorNoProcessedPackages:
        cout << "active return type is: kErrorNoProcessedPackages" << endl;
        break;
    case ActivateReturnType::kErrorNoValidProcessing:
        cout << "active return type is: kErrorNoValidProcessing" << endl;
        break;
    case ActivateReturnType::kSuccess:
        cout << "active return type is: kSuccess" << endl;
        break;
    default:
        break;
    }
    if(ActivateReturn != ActivateReturnType::kSuccess)
    {
        cout << "active wrong : "  << endl;

        RollbackReturnType RollbackReturn = PMC.Rollback();
        switch (RollbackReturn) {
        case RollbackReturnType::kNotAbleToRollback:
            cout << "rollback return type is: kNotAbleToRollback" << endl;
            break;
        case RollbackReturnType::kNothingToRollback:
            cout << "rollback return type is: kNothingToRollback" << endl;
            break;
        case RollbackReturnType::kSuccess:
            cout << "rollback return type is: kSuccess" << endl;
            break;
        default:
            break;
        }
        //切换状态机
        StateSwitch("Running", &UD_STATE);
        return -1;
    }
	cout << "active seccess : "  << endl;
    //finish
    FinishReturnType FinishReturn = PMC.Finish();
    switch (FinishReturn) {
    case FinishReturnType::kOperationNotPermitted:
        cout << "finish return type is: kOperationNotPermitted" << endl;
        break;
    case FinishReturnType::kUndefinedError:
        cout << "finish return type is: kOperationNotPermitted" << endl;
        break;
    case FinishReturnType::kSuccess:
        cout << "finish return type is: kOperationNotPermitted" << endl;
        break;
    default:
        break;
    }
    if(FinishReturn != FinishReturnType::kSuccess)
    {
		cout << "finish wrong : "  << endl;
        //切换状态机
        StateSwitch("Running", &UD_STATE);
        return -1;
    }
	cout << "finish success : "  << endl;
	StateSwitch("Running", &UD_STATE);
    return 0;
} */


/*
void *thrd_ucmhandle(int iSocketClient)
{
    //transfer
    //计算更新包大小
	cout << "ucmhandle start"<< endl;
    int size = filehd.GetSize("/mnt/usb/update.zip");
    if(size < 0)
    {
        cout << "update.zip size error" << endl;
        //return -1;
        pthread_exit(NULL);
    }
	cout << "get update.zip size success"<< endl;
    //切换状态机
    StateSwitch("Update");

    TransferStartReturnType TransferStartReturn = PMC.TransferStart(size);
    if(TransferStartReturn.TransferStartSuccess == TransferStartSuccessType::kInsufficientMemory)
    {
        cout << "InsufficientMemory" << endl;
        //切换状态机
        StateSwitch("Running");
        pthread_exit(NULL);
    }
	cout << "TransferStart success" << endl;

    TransferDataReturnType TransferPackageReturn = PMC.TransferPackage(TransferStartReturn.TransferId, "/mnt/usb/update.zip");
    if(TransferPackageReturn != TransferDataReturnType::kSuccess)
    {
        //cout << "transferpackage error : " << TransferPackageReturn << endl;
		cout << "transferpackage error : "<< endl;
        //切换状态机
        StateSwitch("Running");
        pthread_exit(NULL);
    }
	cout << "TransferPackage success" << endl;

    TransferExitReturnType TransferExitReturn = PMC.TransferExit( TransferStartReturn.TransferId);
    if(TransferExitReturn != TransferExitReturnType::kSuccess)
    {
        //cout << "transferexit error : " << TransferExitReturn << endl;
		cout << "transferexit error : "  << endl;
        //切换状态机
        StateSwitch("Running");
        pthread_exit(NULL);
    }
	cout << "TransferExit success" << endl;

    //processing
    PackageManagerStatusType PM_status = PMC.GetCurrentState();
	cout<<"PM_status is :"<< (UInt8)PM_status << endl;
    if((PM_status != PackageManagerStatusType::kIdle) && (PM_status != PackageManagerStatusType::kReady))
    {
        //cout << "PM_status wrong : " << PM_status << endl;
		cout << "PM_status wrong : "  << endl;
        //切换状态机
        StateSwitch("Running");
        pthread_exit(NULL);
    }
	cout << "PM_status success" << endl;

	
    auto ret = PMC.Process(TransferStartReturn.TransferId);

    while(PMC.GetCurrentState() == PackageManagerStatusType::kBusy){
        UInt8 progress = PMC.GetProcessProgress(TransferStartReturn.TransferId);
        char buf[1000];
        int iSerialLen = Serializer::serialize(progress, buf);
        int iSendLen = send(iSocketClient,  buf, iSerialLen, 0);
        if(iSendLen <= 0)
        {
             close(iSocketClient); //关闭连接
             break;
        }
        usleep(1000000);
    }

    //查看process的返回值，阻塞
    ProcessResultType ProcessResult = ret.get().result.result;
    switch (ProcessResult) {
    case ProcessResultType::kInsufficientMemory:
        cout<<"kInsufficientMemory"<<endl;
        break;
    case ProcessResultType::kInvalidManifest:
        cout<<"kInvalidManifest"<<endl;
        break;
    case ProcessResultType::kInvalidTransferId:
        cout<<"kInvalidTransferId"<<endl;
        break;
    case ProcessResultType::kOperationNotPermitted:
        cout<<"kOperationNotPermitted"<<endl;
        break;
    case ProcessResultType::kPackageInconsistent:
        cout<<"kPackageInconsistent"<<endl;
        break;
    case ProcessResultType::kReject:
        cout<<"kReject"<<endl;
        break;
    case ProcessResultType::kSuccess:
        cout<<"kSuccess"<<endl;
        break;
    default:
        break;
    }
    if(ProcessResult != ProcessResultType::kSuccess)
    {
        //cout << "PM_status wrong : " << PM_status << endl;
		cout << "Process wrong : "  << endl;
        //切换状态机
        StateSwitch("Running");
        pthread_exit(NULL);
    }
	cout << "Process success" << endl;
    //activation
    PM_status = PMC.GetCurrentState();
    if(PM_status != PackageManagerStatusType::kReady)
    {
        //cout << "PM_status wrong : " << PM_status << endl;
		cout << "Before active wrong : " << endl;
        //切换状态机
        StateSwitch("Running");
        pthread_exit(NULL);
    }
	cout << "Before active seccess : " << endl;
    ActivateReturnType ActivateReturn = PMC.Activate( ActivateOptionType::kDefault);
    if(ActivateReturn != ActivateReturnType::kSuccess)
    {
        //cout << "active wrong : " << ActivateReturn << endl;
		cout << "active wrong : "  << endl;
        //切换状态机
        StateSwitch("Running");
        pthread_exit(NULL);
    }
	cout << "active seccess : "  << endl;
    //finish
    FinishReturnType FinishReturn = PMC.Finish();
    if(FinishReturn != FinishReturnType::kSuccess)
    {
        //cout << "finish wrong : " << FinishReturn << endl;
		cout << "finish wrong : "  << endl;
        //切换状态机
        StateSwitch("Running");
        pthread_exit(NULL);
    }
	cout << "finish success : "  << endl;
	StateSwitch("Running");
    pthread_exit(NULL);
	
}

*/

int thrd_send_PMC_status(int iSocketClient)
{
	char buf[1000];
	int iSerialLen;
	int iSendLen;
    PackageManagerStatusType _status;
    while(1)
    {
        _status = PMC.GetCurrentState();
		switch (_status) {
        case PackageManagerStatusType::kIdle:
            cout<<"PM_status is kIdle"<<endl;
            break;
        case PackageManagerStatusType::kActivated:
            cout<<"PM_status is kActivated"<<endl;
            break;
        case PackageManagerStatusType::kActivating:
            cout<<"PM_status is kActivating"<<endl;
            break;
        case PackageManagerStatusType::kBusy:
            cout<<"PM_status is kBusy"<<endl;
            break;
        case PackageManagerStatusType::kCleaningUp:
            cout<<"PM_status is kCleaningUp"<<endl;
            break;
        case PackageManagerStatusType::kFailed:
            cout<<"PM_status is kFailed"<<endl;
            break;
        case PackageManagerStatusType::kReady:
            cout<<"PM_status is kReady"<<endl;
            break;
        case PackageManagerStatusType::kRolledBack:
            cout<<"PM_status is kRolledBack"<<endl;
            break;
        case PackageManagerStatusType::kRollingBack:
            cout<<"PM_status is kRollingBack"<<endl;
            break;
        default:
            break;
        }
		//_status = PackageManagerStatusType::kIdle;
        if(_status < PackageManagerStatusType::kIdle ||_status > PackageManagerStatusType::kFailed )
        {
            //cout << "PM_status wrong : " << _status << endl;
			cout << "PM_status wrong : " << endl;
            return -1;
        }
        
        iSerialLen = Serializer::serialize(_status, buf);
        iSendLen = send(iSocketClient, buf, iSerialLen, 0);
        if(iSendLen <= 0)
        {
             close(iSocketClient); //关闭连接
			 cout << "socket disconnected!"<<endl;
             break;
        }
        sleep(status_sleep_time);
    }

	return 0;
}
