#ifndef FILEHANDLE_H
#define FILEHANDLE_H

#include <string>
#include <iostream>
#include <vector>
#include "ara/ucm/pkgmgr/packagemanagement_proxy.h"
using namespace std;
using namespace ara::ucm::pkgmgr;

enum filestate{noupdatefile, noaccess, readonly, writeonly, readwrite};
enum usbstate{usbYes, usbNo};

struct updatefileinfo
{
    updatefileinfo(string nm, string vs, uint8_t PT, uint8_t RT) {
        Name = nm;
        Version = vs;
        PackageType = PT;
        RequestType = RT;
    }
    string Name;
    string Version;
    //string description = "no";
    uint8_t PackageType;
    uint8_t RequestType;
};

/*
struct updatefileinfo{
    string name = "no";
    string version = "no";
    //string description = "no";
    int packageType = 0;
    int requestType = 0;
};
*/

class FileHandle
{
public:
    //void FileHandle(void);
    usbstate UsbCheck(const char * devname);
    filestate FileCheck(const char * filename);
    void Parse(const string& archivePath, vector<updatefileinfo> *udfinfor);
    int GetSize(const char * filename);
    bool CheckUpdate(vector<updatefileinfo> &udfinfor, SwClusterInfoVectorType &swc_info);

private:
    bool ExtractSingleFile(const string& archivePath, const string& targetFile, std::ostringstream& out);

};




#endif // FILEHANDLE_H
