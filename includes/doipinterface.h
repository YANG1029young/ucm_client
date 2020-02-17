#ifndef DOIPINTERFACE_H
#define DOIPINTERFACE_H

#define DOIP_RETURN_SUCCESS         (0)
#define DOIP_RETURN_FAILURE         (-1)
#define DOIP_RETURN_LENGTHERR       (-2)
#define DOIP_RETURN_PTRNULL         (-3)
#define DOIP_RETURN_CONNECTIONFAIL  (-4)

enum SOAD_DOIP_NODE_TYPE
{
    DOIP_NODE_TYPE_GATEWAY=0x00,
    DOIP_NODE_TYPE_NODE=0x01,
    DOIP_NODE_TYPE_OTHER=0x02,
};

enum SOAD_DOIP_POWER_MODE_TYPE
{
    DOIP_POWER_MODE_NOT_READY = 0x00,
    DOIP_POWER_MODE_READY= 0x01,
    DOIP_POWER_MODE_NOT_SUPPORT = 0x02,
};

extern int doipSetNodeType(unsigned char nodeType);

extern int doipSetVIN(unsigned char *VIN);

extern int doipSetEID(unsigned char *EID);

extern int doipSetGID(unsigned char *GID);

extern int doipSetSA(unsigned short SA);

extern int doipSetTesterAddress(unsigned short laStart,unsigned short laEnd);

extern int doipSetMaxTCPNum(unsigned char maxTCPNum);

extern int doipSetMaxDataSize(unsigned int maxDataSize);

extern int doipSetDiaPowMode(unsigned char diaPowMode);

extern int doipRegisterUDSRevCallback(void* handleDiagnosticUds);

extern int doipSendResponse(unsigned short sa, unsigned short ta, unsigned int taType,
        unsigned char * txBuffer, unsigned int len);

extern int doipInit(unsigned char *ifaceName);

extern int doipStop(void);

extern int doipEnableLog (unsigned char* dirPath, unsigned int maxLineNum);

extern int doipSetAnnouncePara(unsigned int announceCount, unsigned int announceInterval);

extern int doipSetAliveTimeout(unsigned int tcpAliveCheckResponseTimeout);

extern int doipSetTCPTimeoutPara(unsigned int tcpGeneralInactivityTime, unsigned int tcpInitialInactivityTime);

#endif

