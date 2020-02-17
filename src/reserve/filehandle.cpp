#include "filehandle.h"

#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include "Poco/Delegate.h"
#include "Poco/Zip/Decompress.h"
#include "Poco/Zip/ZipLocalFileHeader.h"
#include "Poco/Zip/ZipStream.h"
#include "Poco/Zip/ZipArchive.h"
#include "Poco/StreamCopier.h"
#include "jsconfig/jsconfig.h"

#include <stdio.h>
#include <unistd.h>

using namespace std;

/*
void FileHandle::FileHandle(void)
{


}
*/

void FileHandle::Parse(const string& archivePath, updatefileinfo *udfinfor)
{
    //updatefileinfo udfinfor[20];
	//初始化udfinfor
	
    std::ostringstream out(std::ios::binary);
    jsconfig::CObjectDocument parser;
	std::cout << "parse1 " << std::endl;
	
    if(ExtractSingleFile(archivePath, "UpdateInfo.json", out))
    {
		std::cout << "parse2 " << std::endl;
        if(parser.parseString(out.str()))
        {
			/*
            auto& obj = *(parser.root());
            udfinfor.name = obj["packageName"].toString();
            udfinfor.version = obj["version"].toString();
            udfinfor.description = obj["description"].toString();
            udfinfor.packageType = obj["packageType"].toInt32();
            udfinfor.requestType = obj["requestType"].toInt32();          
		   */
		    auto& obj = *(parser.root());
			int PacketNum = obj["packageCount"].toInt32();
			
			auto& packagesObj = obj["packages"];
			
			
			for(int i = 0; i < PacketNum; i++)
			{
				udfinfor[i].name = packagesObj[i]["name"].toString();
				udfinfor[i].version = packagesObj[i]["version"].toString();   
				udfinfor[i].description = packagesObj[i]["description"].toString();
				udfinfor[i].packageType = packagesObj[i]["type"].toInt32();
				udfinfor[i].requestType = packagesObj[i]["requestType"].toInt32();
			}
            
			
            //return udfinfor;
        }
    }
    //break;
}



bool FileHandle::ExtractSingleFile(const string& archivePath, const string& targetFile, std::ostringstream& out)
{
    try
    {
		std::cout << "extract1 " << std::endl;
		
        std::ifstream inp(archivePath, std::ios::binary);    
        Poco::Zip::ZipArchive arch(inp);

        Poco::Zip::ZipArchive::FileHeaders::const_iterator it = arch.findHeader(targetFile);
        if(it == arch.headerEnd())
        {
            return false;
        }

		
        inp.clear();    
        Poco::Zip::ZipInputStream zipin(inp, it->second);
        Poco::StreamCopier::copyStream(zipin, out);
		
		std::cout << "extract2 " << std::endl;
        std::cout << "extract single file success ： " << targetFile<< std::endl;
                            
        return true;
    } 
    catch (const Poco::Exception& e) 
    {
		
       std::cout << "Failed to extract an archive: " << e.displayText();
    } 
    catch (const std::exception& e) 
    {
		
        std::cout << "Failed to extract an archive: " << e.what();
    } 
    catch (...) 
    {
		
        std::cout << "Failed to extract an archive " << archivePath;
    }

    return false;
}

usbstate FileHandle::UsbCheck(const char *devname)
{
    if (access(devname,0) == 0)
        return usbYes;
    else if (access(devname,0) == -1)
        return usbNo;

}
filestate FileHandle::FileCheck(const char * filename)
{
    if (access(filename,0) == 0)
    {
        if (access(filename,6) == 0)
        {
            return readwrite;
        }
        else
        {
            if (access(filename,4) == 0)
                return readonly;
            else
                writeonly;
        }
    }
    else
        return noupdatefile;


}


