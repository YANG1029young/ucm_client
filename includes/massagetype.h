#ifndef MASSAGETYPE_H
#define MASSAGETYPE_H

typedef  unsigned int MSG_ID;

#define ID_GetSoftwareInfo       1
#define ID_SoftwareInfo          501
#define ID_GetSoftwareChangeInfo 2
#define ID_SoftwareChangeInfo    502
#define ID_StartSoftwareChanges  3
#define ID_SoftwareChangeState   503

#define MassageHeader 0xf5f5
#define MassageTail   0x5555

enum msgtype{GetSoftwareInfo, GetSoftwareChangeInfo, StartSoftwareChanges, SoftwareInfo, SoftwareChangeInfo,SoftwareChangeState, SoftwareChangeProgress, TypeError};

#endif // MASSAGETYPE_H
