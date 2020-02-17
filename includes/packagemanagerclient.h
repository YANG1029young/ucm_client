#ifndef PACKAGEMANAGERCLIENT_H
#define PACKAGEMANAGERCLIENT_H


#include <iostream>
#include <fstream>
#include <unistd.h>
#include "ara/ucm/pkgmgr/packagemanagement_proxy.h"
#include "ara/log/common.h"
#include "ara/log/logging.h"
#include "ara/log/logger.h"
//#include "tclap/CmdLine.h"


//using namespace TCLAP;

using namespace ara::ucm::pkgmgr;
using namespace std;
class PackageManagerClient
{
private:
std::unique_ptr<proxy::PackageManagementProxy> mProxy;
static ara::log::Logger& logger()
{
    static ara::log::Logger& loggerInstance = ara::log::CreateLogger("UCMC", "ucm client context");
    return loggerInstance;
}
public:	
    bool FindService();

	PackageManagerStatusType GetCurrentState()
	{
		auto ret = mProxy->CurrentStatus.Get().get();
		logger().LogError()<< "Current status is "<< static_cast<int>(ret);
		return ret;
	}
	TransferStartReturnType TransferStart(UInt32  size)
	{		
		auto ret = mProxy->TransferStart(size).get();	
		logger().LogError()<< "TransferStart transferid  is "<< static_cast<int>(ret.result.TransferId) ;
		logger().LogError()<< "TransferStart result  is "<< static_cast<int>(ret.result.TransferStartSuccess) ;
		return ret.result;
	}

	GeneralResponseType DeleteTransfer(UInt32 id)
	{
		auto ret = mProxy->DeleteTransfer(static_cast<TransferIdType>(id)).get();
		logger().LogError()<< "DeleteTransfer id is " << id;
		logger().LogError()<< "DeleteTransfer result is " << static_cast<int>(ret.result);
		return ret.result;
	}
	
	TransferExitReturnType TransferExit(UInt32 id)
	{
		auto ret = mProxy->TransferExit(static_cast<TransferIdType>(id)).get();
		logger().LogError()<< "TransferExit id is " << id;
		logger().LogError()<< "TransferExit result is " << static_cast<int>(ret.result);
		return ret.result;
	}
	
	TransferDataReturnType TransferData(UInt32 id, ByteVectorType data, UInt32 blockid)
	{
		auto ret = mProxy->TransferData(static_cast<TransferIdType>(id), data, blockid).get();
		logger().LogError()<< "TransferData result is " << static_cast<int>(ret.result);
		return ret.result;
	}
	
	TransferDataReturnType TransferPackage(UInt32 id, std::string path)
	{
		std::ifstream in;
		ByteVectorType byteData;
		byteData.resize(512);
		in.open(path.c_str(), std::ifstream::in|std::ifstream::binary);
		TransferDataReturnType ret;
		logger().LogDebug()<< "TransferPackage id " << id;
		logger().LogDebug()<< "TransferPackage path " << path;


		if(in.is_open()){
			uint32_t readedLength = 0;
			uint32_t blockId = 1;
			in.seekg(0, in.end);
			uint32_t totalSize = in.tellg();
			in.seekg(0, in.beg);
			logger().LogDebug()<< "package size is : " << totalSize;
			while(readedLength < totalSize){
				in.read(reinterpret_cast<char*>(&byteData[0]), 512);		
				byteData.resize(in.gcount());
				ret = TransferData(id, byteData, blockId);
				if(ret != TransferDataReturnType::kSuccess){
					break;
				}
				readedLength += byteData.size();
				++blockId;
			}
		}	

		in.close();
		return ret;

	} 

    ProcessResultType Process_Get(int id)
	{
        logger().LogDebug()<< "Process get enter ";
		auto ret = mProxy->ProcessSwPackage(static_cast<TransferIdType>(id)).get();
		logger().LogDebug()<< "process package result is " << static_cast<int>(ret.result.result);
		logger().LogDebug()<< "process package id is " << static_cast<int>(ret.result.transferId);
        return ret.result.result;
	}
    auto Process(int id)
    {
        logger().LogDebug()<< "Process enter ";
        return mProxy->ProcessSwPackage(static_cast<TransferIdType>(id));
    }

	CancelReturnType Cancel(int id)
	{
		auto ret = mProxy->Cancel(static_cast<TransferIdType>(id)).get();
		logger().LogDebug()<< "cancel package result is " << static_cast<int>(ret.result);
		return ret.result;
	}

	RevertProcessedSwPackagesReturnType Revert()
	{
		auto ret = mProxy->RevertProcessedSwPackages().get();
		logger().LogDebug()<< "cancel package result is " << static_cast<int>(ret.result);
		return ret.result;
	}
    UInt8 GetProcessProgress(int id)
	{
		auto ret = mProxy->GetSwProcessProgress(static_cast<TransferIdType>(id)).get();
		while(ret.progress < 100){
			logger().LogDebug()<< "Process package id " << id << " progress " << ret.progress;		
		}
        return ret.progress;
	}
	
	void SetLogLevel(int id, int level)
	{
		mProxy->SetLogLevel(static_cast<TransferIdType>(id), static_cast<LogLevelType>(level));
		logger().LogDebug()<< "setloglevel package result is " << level;
		return;
	}
	
	void GetLog(int id)
	{
		logger().LogDebug()<< "getloglevel result is " ;
		auto ret = mProxy->GetLog(static_cast<TransferIdType>(id)).get();	
		for(auto& log: ret.log){
			logger().LogDebug() << "log level :" << static_cast<int>(log.LogLevel)
								<< "message :" << log.Message.c_str();
		}
	
	}

    /*
	void Extract(const char* path, const char* target)
	{
		auto fs = std::make_shared<Filesystem>();
		auto extractor = LibPocoZipExtractor(fs);
		extractor.Extract(path, target);
	}
    */
	void GetSwPackages()
	{
		auto ret = mProxy->GetSwPackages().get();	
		for(auto& package: ret.Packages){
			logger().LogDebug()<< "Name: " << package.Name;		
			logger().LogDebug()<< "Version: " << package.Version;		
			logger().LogDebug()<< "ID: " << package.TransferID;		
			logger().LogDebug()<< "State: " << static_cast<int>(package.State);		
		}
	}
    /*
	void GetSwClusterInfo()
	{
		auto ret = mProxy->GetSwClusterInfo().get();
		logger().LogDebug()<< "get"<< ret.SwInfo.size() <<  "software cluster info" ;
		for(auto& info:ret.SwInfo){
			logger().LogDebug() << info.Name;
			logger().LogDebug() << info.Version;
			logger().LogDebug() << static_cast<int>(info.State);
		}
	}
    */

    SwClusterInfoVectorType GetSwClusterInfo()
    {
        auto ret = mProxy->GetSwClusterInfo().get();
        logger().LogDebug()<< "get"<< ret.SwInfo.size() <<  "software cluster info" ;
        for(auto& info:ret.SwInfo){
            logger().LogDebug() << info.Name;
            logger().LogDebug() << info.Version;
            logger().LogDebug() << static_cast<int>(info.State);
        }
        return ret.SwInfo;
    }

	void GetSwClusterChangeInfo()
	{
		auto ret = mProxy->GetSwClusterChangeInfo().get();	
		logger().LogDebug()<< "get"<< ret.SwInfo.size() <<  "software cluster change info" ;
        cout<< "software cluster num is:" << ret.SwInfo.size() <<endl;
		for(auto& info : ret.SwInfo){
			logger().LogDebug() << info.Name;
			logger().LogDebug() << info.Version;
			logger().LogDebug() << static_cast<int>(info.State);

		}
	}

    ActivateReturnType Activate( ActivateOptionType option)
	{
		auto ret = mProxy->Activate(static_cast<ActivateOptionType>(option)).get();	
		logger().LogDebug()<< "activate result is " << static_cast<int>(ret.result);
        return ret.result;
	}


/* 	void Rollback()
	{
		auto ret = mProxy->Rollback().get();	
		logger().LogDebug()<< "rollback result is " << static_cast<int>(ret.result);
	} */
    RollbackReturnType Rollback()
    {
        auto ret = mProxy->Rollback().get();
        logger().LogDebug()<< "rollback result is " << static_cast<int>(ret.result);
        return ret.result;
    }

    FinishReturnType Finish()
	{
		auto ret = mProxy->Finish().get();	
		logger().LogDebug()<< "finish result is " << static_cast<int>(ret.result);
        return ret.result;
	}

}; 


#endif // UCMCLIENT_H
