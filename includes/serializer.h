#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "packagemanagerclient.h"
#include "filehandle.h"
#include "massagetype.h"

#define nameLenMax 30
#define versionLenMax 8
#define BUF_SIZE 1000

class Serializer
{
public:

    /*
    static int serialize(vector<updatefileinfo> *info,  char *ucSendBuf)
    {
        memset(ucSendBuf, 0, sizeof(ucSendBuf));

        ucSendBuf[6] = info->size();
		printf("info size is %d\n", ucSendBuf[6]);
		printf("struct size is %d\n", sizeof(updatefileinfo));
        memcpy(ucSendBuf+7, *info, info->size()*sizeof(updatefileinfo));//sizeof(ara::ucm::pkgmgr::SwClusterInfoType)*swc_info.size()

        int iSerialLen = 7 + info->size()*sizeof(updatefileinfo) + 2;

        //ucSendBuf[iSerialLen-2] = MassageTail >> 8;
        //ucSendBuf[iSerialLen-1] = MassageTail & 0xff;
        add_msg_id(ucSendBuf, ID_SoftwareChangeInfo);
        add_msg_len(ucSendBuf, iSerialLen);
        add_head_tail(ucSendBuf, iSerialLen);

        return iSerialLen;
    }
    */
	static int serialize(SwClusterInfoVectorType info,  char *ucSendBuf)
    {
        memset(ucSendBuf, 0, sizeof(ucSendBuf));
        cout<<"size of buf is:"<< sizeof(ucSendBuf)<<endl;

        ucSendBuf[6] = info.size();
        auto index = ucSendBuf+7;
        for(auto val : info)
        {
            memcpy(index, val.Name.c_str(),  val.Name.length());
            index = index + nameLenMax;
            memcpy(index, val.Version.c_str(), val.Version.length());
            index = index + versionLenMax;
            *index = (char)val.State;
            index = index + 1;
        }

        int iSerialLen = index - ucSendBuf + 2;
        add_msg_id(ucSendBuf, ID_SoftwareInfo );
        add_msg_len(ucSendBuf, iSerialLen);
        add_head_tail(ucSendBuf, iSerialLen);

        return iSerialLen;
    }
    static int serialize(vector<updatefileinfo> info,  char *ucSendBuf)
    {
        memset(ucSendBuf, 0, sizeof(ucSendBuf));
        cout<<"size of buf is:"<< sizeof(ucSendBuf)<<endl;

        ucSendBuf[6] = info.size();
        auto index = ucSendBuf+7;
        for(auto val : info)
        {
            memcpy(index, val.Name.c_str(), val.Name.length());
            index = index + nameLenMax;
            memcpy(index, val.Version.c_str(), val.Version.length());
            index = index + versionLenMax;
            *index = val.PackageType;
            index = index + 1;
            *index = val.RequestType;
            index = index + 1;
        }

        int iSerialLen = index - ucSendBuf + 2;
        add_msg_id(ucSendBuf, ID_SoftwareChangeInfo);
        add_msg_len(ucSendBuf, iSerialLen);
        add_head_tail(ucSendBuf, iSerialLen);

        return iSerialLen;
    }

    static int serialize(UInt8 info,  char *ucSendBuf)
    {
        memset(ucSendBuf, 0, sizeof(ucSendBuf));
        memcpy(ucSendBuf+6, &info, sizeof(info));//sizeof(ara::ucm::pkgmgr::SwClusterInfoType)*swc_info.size()

        int iSerialLen = 6 + sizeof(info) + 2;
        add_msg_id(ucSendBuf, 4008);
        add_msg_len(ucSendBuf, iSerialLen);
        add_head_tail(ucSendBuf, iSerialLen);

        return iSerialLen;
    }
    static int serialize(PackageManagerStatusType info,  char *ucSendBuf)
    {
        memset(ucSendBuf, 0, sizeof(ucSendBuf));


        memcpy(ucSendBuf+6, &info, sizeof(info));//sizeof(ara::ucm::pkgmgr::SwClusterInfoType)*swc_info.size()

        int iSerialLen = 6 + sizeof(info) + 2;

        //ucSendBuf[iSerialLen-2] = MassageTail >> 8;
        //ucSendBuf[iSerialLen-1] = MassageTail & 0xff;
        add_msg_id(ucSendBuf, ID_SoftwareChangeState);
        add_msg_len(ucSendBuf, iSerialLen);
        add_head_tail(ucSendBuf, iSerialLen);

        return iSerialLen;
    }



    static int serialize(auto info,  char *ucSendBuf, msgtype type)
    //int serialize(SwClusterInfoVectorType swc_info,  char *ucSendBuf)
    {
        memset(ucSendBuf, 0, sizeof(ucSendBuf));

        /*
        ucSendBuf[0] = MassageHeader >> 8;
        ucSendBuf[1] = MassageHeader & 0xff;

        ucSendBuf[2] = ID_SoftwareInfo  >> 8;
        ucSendBuf[3] = ID_SoftwareInfo  & 0xff;
        */

        int iSerialLen;
        switch (type) {
        case SoftwareInfo:
            ucSendBuf[6] = (SwClusterInfoVectorType)(info).size();
            memcpy(ucSendBuf+7, &info, sizeof(info));//sizeof(ara::ucm::pkgmgr::SwClusterInfoType)*swc_info.size()
            add_msg_id(ucSendBuf, ID_SoftwareInfo);
            iSerialLen = 7 + sizeof(info) + 2;
            break;
        case SoftwareChangeInfo:
            ucSendBuf[6] = (vector<updatefileinfo>)(info).size();
            memcpy(ucSendBuf+7, &info, sizeof(info));//sizeof(ara::ucm::pkgmgr::SwClusterInfoType)*swc_info.size()
            add_msg_id(ucSendBuf, ID_SoftwareChangeInfo );
            iSerialLen = 7 + sizeof(info) + 2;
            break;
        case SoftwareChangeState:
            memcpy(ucSendBuf+6, &info, sizeof(info));
            add_msg_id(ucSendBuf, ID_SoftwareChangeState );
            iSerialLen = 6 + sizeof(info) + 2;
            break;
        default:
            break;
        }

        add_msg_len(ucSendBuf, iSerialLen);
        add_head_tail(ucSendBuf, iSerialLen);

        return iSerialLen;
    }

    /*
    int serialize(vector<updatefileinfo> udf_info,  char *ucSendBuf)
    {

        memset(ucSendBuf, 0, sizeof(ucSendBuf));

        /*
        ucSendBuf[0] = MassageHeader >> 8;
        ucSendBuf[1] = MassageHeader & 0xff;

        ucSendBuf[2] = ID_SoftwareChangeInfo >> 8;
        ucSendBuf[3] = ID_SoftwareChangeInfo & 0xff;



        ucSendBuf[4] = 421 >> 8;
        ucSendBuf[5] = 421 & 0xff;


        ucSendBuf[6] = udf_info.size();
        memcpy(ucSendBuf+7, &udf_info, sizeof(udf_info));//swc_info.size()

        int iSerialLen = 7 + sizeof(udf_info) + 2;
        //ucSendBuf[iSerialLen-2] = MassageTail >> 8;
        //ucSendBuf[iSerialLen-1] = MassageTail & 0xff;
        add_msg_id(ucSendBuf, ID_SoftwareChangeInfo);
        add_msg_len(ucSendBuf, iSerialLen);
        add_head_tail(ucSendBuf, iSerialLen);

        return iSerialLen;

    }
    */

private:
    static void add_msg_id(char * buf, MSG_ID msg_ID)
    {
        buf[2] = msg_ID >> 8;
        buf[3] = msg_ID & 0xff;
    }
    static void add_head_tail(char * buf, int iSerialLen)
    {
        buf[0] = MassageHeader >> 8;
        buf[1] = MassageHeader & 0xff;

        buf[iSerialLen-2] = MassageTail >> 8;
        buf[iSerialLen-1] = MassageTail & 0xff;
    }
    static void add_msg_len(char * buf, int iSeriallen)
    {
        buf[4] = (iSeriallen - 8) >> 8;
        buf[5] = (iSeriallen - 8) & 0xff;
    }

};


#endif // SERIALIZER_H
