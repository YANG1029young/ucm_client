#include "massageparser.h"
#include "massagetype.h"

MassageParser::MassageParser()
{

}

int MsgLen;
int MsgID;
msgtype MassageParser::massageparse(char *magmuf, int iRecvLen)
{
    if((magmuf[0] == 0xf5)&&(magmuf[1] == 0xf5))
    {
        if((magmuf[iRecvLen-1] == 0x55)&&(magmuf[iRecvLen-2] == 0x55))
        {
            int MsgID = (magmuf[2] << 8) + magmuf[3];
            switch(MsgID)
            {
                case ID_GetSoftwareInfo:
                    MsgLen = (magmuf[4] << 8) + magmuf[5];
                    if(MsgLen == 1)
                    {
                        if(magmuf[6] == 1) return GetSoftwareInfo;
                        else return TypeError;
                    }
                    else return TypeError;
                    break;
                case ID_SoftwareInfo:
                    MsgLen = (magmuf[4] << 8) + magmuf[5];
                    if(MsgLen <= 781)
                    {
                        return SoftwareInfo;
                    }
                    else return TypeError;
                    break;
                case ID_GetSoftwareChangeInfo:
                    MsgLen = (magmuf[4] << 8) + magmuf[5];
                    if(MsgLen == 1)
                    {
                        if(magmuf[6] == 1) return GetSoftwareChangeInfo;
                        else return TypeError;
                    }
                    else return TypeError;
                    break;
                case ID_SoftwareChangeInfo:
                    MsgLen = (magmuf[4] << 8) + magmuf[5];
                    if(MsgLen <= 421)
                    {
                        return SoftwareChangeInfo;
                    }
                    else return TypeError;
                    break;
                case ID_StartSoftwareChanges:
                    MsgLen = (magmuf[4] << 8) + magmuf[5];
                    if(MsgLen == 1)
                    {
                        if(magmuf[6] == 1) return StartSoftwareChanges;
                        else return TypeError;
                    }
                    else return TypeError;
                    break;
                case ID_SoftwareChangeState:
                    MsgLen = (magmuf[4] << 8) + magmuf[5];
                    if(MsgLen == 1)
                    {
                        if(magmuf[6] == 1) return SoftwareChangeState;
                        else return TypeError;
                    }
                    else return TypeError;
                    break;
                default:
                    return TypeError;
                    break;

            }
        }
    }
}
