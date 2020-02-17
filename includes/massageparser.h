#ifndef MASSAGEPARSER_H
#define MASSAGEPARSER_H

#include "massagetype.h"


class MassageParser
{
public:
    MassageParser();
    msgtype massageparse(char *magmuf, int iRecvLen);
};

#endif // MASSAGEPARSER_H
