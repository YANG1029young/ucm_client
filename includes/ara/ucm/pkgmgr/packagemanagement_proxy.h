/***************************************************************************//**
 * @copyright Copyright (c) by Hinge-Tech R&D Center.
 * @file  PackageManagementProxy.h
 * @brief proxy file of package-manager 
 * @author Richard.Z  
 * @version 00.00.01
 * @date  2019-07-17 
 * @par Description
 * @par Others 
 * @par Function List
 *      1. Execute
 *    
 * @par History:
 *      Date | Author| Modification
 *      -|-|-
 *      2019-07-17 | Richard.Z | add new style of comment |
 *      2019-07-17 | Richard.Z | add  |
 *     
 ******************************************************************************/
#ifndef ARA_UCM_PKGMGR_PACKAGEMANAGEMENT_PROXY_H_
#define ARA_UCM_PKGMGR_PACKAGEMANAGEMENT_PROXY_H_

#include "packagemanagement_common.h"
#include <ara/com/internal/proxy/types.h>

namespace ara
{
namespace ucm
{
namespace pkgmgr
{

namespace proxy
{

namespace events
{

} // namespace events


namespace fields
{
    using CurrentStatus = ara::com::internal::proxy::FieldType<::ara::ucm::pkgmgr::PackageManagerStatusType,true,true,false>::type;

} // namespace fields

namespace methods
{
    using TransferStart = ara::com::internal::proxy::Method<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput(const UInt32&)>;
    using TransferData = ara::com::internal::proxy::Method<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput(const ara::ucm::pkgmgr::TransferIdType&,const ara::ucm::pkgmgr::ByteVectorType&,const UInt32&)>;
    using TransferExit = ara::com::internal::proxy::Method<ara::ucm::pkgmgr::PackageManagement::TransferExitOutput(const ara::ucm::pkgmgr::TransferIdType&)>;
    using DeleteTransfer = ara::com::internal::proxy::Method<ara::ucm::pkgmgr::PackageManagement::DeleteTransferOutput(const ara::ucm::pkgmgr::TransferIdType&)>;
    using ProcessSwPackage = ara::com::internal::proxy::Method<ara::ucm::pkgmgr::PackageManagement::ProcessSwPackageOutput(const ara::ucm::pkgmgr::TransferIdType&)>;
    using GetSwProcessProgress = ara::com::internal::proxy::Method<ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput(const ara::ucm::pkgmgr::TransferIdType&)>;
    using Cancel = ara::com::internal::proxy::Method<ara::ucm::pkgmgr::PackageManagement::CancelOutput(const ara::ucm::pkgmgr::TransferIdType&)>;
    using RevertProcessedSwPackages = ara::com::internal::proxy::Method<ara::ucm::pkgmgr::PackageManagement::RevertProcessedSwPackagesOutput()>;
    using SetLogLevel = ara::com::internal::proxy::Method<ara::ucm::pkgmgr::PackageManagement::SetLogLevelOutput(const ara::ucm::pkgmgr::TransferIdType&,const ara::ucm::pkgmgr::LogLevelType&)>;
    using GetLog = ara::com::internal::proxy::Method<ara::ucm::pkgmgr::PackageManagement::GetLogOutput(const ara::ucm::pkgmgr::TransferIdType&)>;
    using GetSwClusterChangeInfo = ara::com::internal::proxy::Method<ara::ucm::pkgmgr::PackageManagement::GetSwClusterChangeInfoOutput()>;
    using GetSwClusterInfo = ara::com::internal::proxy::Method<ara::ucm::pkgmgr::PackageManagement::GetSwClusterInfoOutput()>;
    using GetSwPackages = ara::com::internal::proxy::Method<ara::ucm::pkgmgr::PackageManagement::GetSwPackagesOutput()>;
    using Activate = ara::com::internal::proxy::Method<ara::ucm::pkgmgr::PackageManagement::ActivateOutput(const ara::ucm::pkgmgr::ActivateOptionType&)>;
    using Rollback = ara::com::internal::proxy::Method<ara::ucm::pkgmgr::PackageManagement::RollbackOutput()>;
    using Finish = ara::com::internal::proxy::Method<ara::ucm::pkgmgr::PackageManagement::FinishOutput()>;

} // namespace methods

///@brief proxy interface of package-manager(UCM)
///
///Application end create an instance of this class, use cm find function to search ucm serice, 
///then access ucm's functions
class PackageManagementProxy : public ara::com::internal::proxy::ServiceProxy
{
public:
    using HandleType = ara::com::internal::proxy::ServiceProxy::HandleType;
	
    explicit PackageManagementProxy(HandleType handle)
    	: ara::com::internal::proxy::ServiceProxy("PackageManagement", handle)
    	
        , CurrentStatus(this, "CurrentStatus")
    	
        , TransferStart(this, "TransferStart")
        , TransferData(this, "TransferData")
        , TransferExit(this, "TransferExit")
        , DeleteTransfer(this, "DeleteTransfer")
        , ProcessSwPackage(this, "ProcessSwPackage")
        , GetSwProcessProgress(this, "GetSwProcessProgress")
        , Cancel(this, "Cancel")
        , RevertProcessedSwPackages(this, "RevertProcessedSwPackages")
        , SetLogLevel(this, "SetLogLevel")
        , GetLog(this, "GetLog")
        , GetSwClusterChangeInfo(this, "GetSwClusterChangeInfo")
        , GetSwClusterInfo(this, "GetSwClusterInfo")
        , GetSwPackages(this, "GetSwPackages")
        , Activate(this, "Activate")
        , Rollback(this, "Rollback")
        , Finish(this, "Finish")

    {
        //Events
	
        //Fields
        addField("CurrentStatus",true,true,false);
	
        //Methods
        addMethod("TransferStart");
        addMethod("TransferData");
        addMethod("TransferExit");
        addMethod("DeleteTransfer");
        addMethod("ProcessSwPackage");
        addMethod("GetSwProcessProgress");
        addMethod("Cancel");
        addMethod("RevertProcessedSwPackages");
        addMethod("SetLogLevel");
        addMethod("GetLog");
        addMethod("GetSwClusterChangeInfo");
        addMethod("GetSwClusterInfo");
        addMethod("GetSwPackages");
        addMethod("Activate");
        addMethod("Rollback");
        addMethod("Finish");
	
        //registerErrors
        registerPackageManagementErrors();
		
        // init
        init();
    }
	
    virtual ~PackageManagementProxy(){}

    static ara::com::ServiceHandleContainer<HandleType> FindService(
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::FindService("PackageManagement", instance);
    }
    	
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandler<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("PackageManagement", handler, instance);
    }
    
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandlerExt<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("PackageManagement", handler, instance);
    }
	
    // Events
	
    // Fields
    fields::CurrentStatus CurrentStatus; ///< report status field
    /// @fn TransferStart	
    /// @param UInt32 Size of packge in byte
    /// @return 
    ///    - if success, {kSuccess, id}  will be returned 
    ///    - if failed, {errorcode , id} will be returned, id field is invalid
    /// @par Functional Description
    /// Use this function to initialize a transfer to ucm , it will create a 
    /// unique id for later function call.Everytime you want to transfer package 
    /// data to ucm,this function should be called first.
    ///
    /// @par others
    ///     Function call will not cause ucm inner state change
    /// @par Particularities and Limitations
    ///  
    /// @par Call Context
    ///     
    /// @todo 
    ///     param will change from UInt32 to UInt64, to support large files.
    methods::TransferStart TransferStart;
    /// @fn TransferData
    /// @param TransferIdType 
    ///     Id of transfer instance to transfer data to, id is generated by 
    ///     call @ref TransferStart.
    /// @param ByteVectorType buffer of data to be transfered
    /// @param UInt32 fragment number of data.
    /// @return 
    ///     - if success, TransferDataReturnType::kSuccess will be returned
    ///     - others, see @ref TransferDataReturnType
    /// @par Functional Description
    ///     Use this fuction to transfer package data to ucm,usually a package should
    ///     be split into some small fragments, then transfer one by one. 
    /// @par others
    /// 
    /// @par Call Context
    /// @todo 
    ///     error will be reported by throw exception.
    methods::TransferData TransferData;
    /// @fn TransferExit
    /// @param TransferIdType 
    ///     Id of transfer instance to transfer data to, id is generated by 
    ///     call @ref TransferStart
    /// @return
    ///     - if success, TransferExitReturnType::kSuccess will be returned.
    ///     - others, see @ref TransferExitReturnType.
    /// @par Functional Description
    ///     When all package data is transferd, call this function to exit a transfer
    ///     ,ucm will then check the package
    /// @par Particularities and Limitations
    /// @todo 
    ///     error will be reported by throw exception.
    methods::TransferExit TransferExit;
    /// @fn DeleteTransfer
    /// @param TransferIdType 
    ///     Id of transfer instance to transfer data to, id is generated by 
    ///     call @ref TransferStart
    /// @return
    ///     -if success, 
    /// @par Functional Description
    ///     Used to delete a transfer,that you processed, or error occur when 
    ///     call TransferData, TransferExit.
    /// @par Particularities and Limitations
    /// @todo 
    ///      error will be reported by throw exception.
    methods::DeleteTransfer DeleteTransfer;
    /// @fn ProcessSwPackage
    /// @param TransferIdType 
    ///     Id of transfer instance to transfer data to, id is generated by 
    ///     call @ref TransferStart
    /// @return
    ///     - if success 
    /// @par Functional Description
    ///     To process a transfered package, the id reference to the package to
    ///     be process, this action will consume a few time.After this function 
    ///     to be called, the ucm will enter into kBusy status, some function call 
    ///     will be reject. 
    /// @par Particularities and Limitations
    /// @todo 
    ///      error will be reported by throw exception.
    methods::ProcessSwPackage ProcessSwPackage;
    /// @fn GetSwProcessProgress
    /// @param TransferIdType 
    ///     Id of transfer instance to transfer data to, id is generated by 
    ///     call @ref TransferStart
    /// @return
    ///     - if success, the current process progress will be returned 0-100.
    ///     - otherwise, will return 0xff.
    ///
    /// @par Functional Description
    ///     This Fuction is used to get the progress of process a package,when 
    ///     it reched 100, the package process is finished.
    /// @par Particularities and Limitations
    /// @todo 
    ///      error will be reported by throw exception.
    methods::GetSwProcessProgress GetSwProcessProgress;
    /// @fn Cancel
    /// @param TransferIdType 
    ///     Id of transfer instance to transfer data to, id is generated by 
    ///     call @ref TransferStart
    /// @return 
    ///     - if success, the process is canceld , CancelReturnType::kSuccess returned.
    ///     - otherwise, see @ref CancelReturnType.
    /// @par Functional Description
    ///     Used to cancel a process that at executing.
    /// @par Particularities and Limitations
    /// @todo 
    ///      error will be reported by throw exception.
    methods::Cancel Cancel;
    /// @fn RevertProcessedSwPackages
    /// @param None
    /// @return 
    ///     - if success, RevertProcessedSwPackagesReturnType::kSuccess will be returned
    ///     - otherwise, see @ref RevertProcessedSwPackagesReturnType
    /// @par Functional Description
    ///     Used to revert the changes that process do.It should be called after @ref Cancel
    /// @par Particularities and Limitations
    /// @todo 
    ///      error will be reported by throw exception.
    methods::RevertProcessedSwPackages RevertProcessedSwPackages;
    /// @fn SetLogLevel
    /// @param TransferIdType
    ///     Id of transfer instance to transfer data to, id is generated by 
    ///     call @ref TransferStart
    /// @param LogLevelType
    ///     The log level to be set, such as kOff, kFatal,kError,kWarning,kInfo,
    ///     kDebug,kVerbose.
    /// @return None
    /// @par Functional Description
    ///     To set log level that of a transfer instance, the log will stored in a 
    ///     log file, client can get the log to print on display.
    /// @par Particularities and Limitations
    /// @todo 
    ///      error will be reported by throw exception.
    methods::SetLogLevel SetLogLevel;
    /// @fn GetLog
    /// @param TransferIdType
    ///     Id of transfer instance to transfer data to, id is generated by 
    ///     call @ref TransferStart
    /// @return
    ///    - GetLogOutput returned, log messages stored in GetLogOutput::log
    /// @par Functional Description
    ///    Get log message that produced in process routine.
    /// @par Particularities and Limitations
    /// @todo 
    ///      error will be reported by throw exception.
    methods::GetLog GetLog;
    /// @fn GetSwClusterChangeInfo
    /// @param None
    /// @return 
    ///     - GetSwClusterChangeInfoOutput returned , software cluster info stored in 
    ///       GetSwClusterChangeInfoOutput::SwInfo.
    /// @par Functional Description
    ///     Used to get the software cluster changed info, Softwarecluster not in kPresent
    ///     status will be included.
    /// @par Particularities and Limitations
    /// @todo 
    ///      error will be reported by throw exception.
    methods::GetSwClusterChangeInfo GetSwClusterChangeInfo;
    /// @fn GetSwClusterInfo
    /// @param None
    /// @return 
    ///     - GetSwClusterInfoOutput returned , software cluster info stored in 
    ///       GetSwClusterInfoOutput::SwInfo.
    /// @par Functional Description
    ///     Used to get the software cluster changed info, Softwarecluster in kPresent
    ///     status will be included.
    /// @par Particularities and Limitations
    /// @todo 
    ///      error will be reported by throw exception.
    methods::GetSwClusterInfo GetSwClusterInfo;
    /// @fn GetSwPackages
    /// @param None
    /// @return
    ///     - GetSwPackagesOutput will be returned, software packages's info will be stored
    ///       in GetSwPackagesOutput::Packages
    /// @par Functional Description
    ///     Get the packages info that transfered to ucm.The package info contains the staus(
    ///     kTransferring,kTransferred,kProcessing,kProcessed), and the name of package, request
    ///     type etc.
    /// @par Particularities and Limitations
    /// @todo 
    ///      error will be reported by throw exception.
    methods::GetSwPackages GetSwPackages;
    /// @fn Activate
    /// @param ActivateOptionType
    ///     The request to activate an app, usually select ActivateOptionType::kDefault.
    /// @return 
    ///     - if success, ActivateOutput::result will be set by  ActivateReturnType::kSuccess.
    ///     - otherwise, ActivateOutput::result will be set by  ActivateReturnType.
    /// @par Functional Description
    ///     To activate processed software cluster , this action will try to run the installed
    ///     app, or to restart function group or to reboot system 
    /// @par Particularities and Limitations
    /// @todo 
    ///      error will be reported by throw exception.
    methods::Activate Activate;
    /// @fn Rollback
    /// @param  None
    /// @return
    ///     - if success, RollbackOutput::result will be set by  RollbacktReturnType::kSuccess.
    ///     - otherwise, see @ref RollbackReturnType.
    /// @par Functional Description
    ///     Used to rollback the processed install path
    /// @par Particularities and Limitations
    /// @todo 
    ///      error will be reported by throw exception.
    methods::Rollback Rollback;
    /// @fn Finish
    /// @param None
    /// @return
    ///     - if success ,FinishReturnType::kSuccess will set to FinishOutput::result
    ///     - otherwise , see @ref FinishReturnType
    /// @par Functional Description
    ///     After activate success, call finish to clean the temp file or data.
    /// @par Particularities and Limitations
    /// @todo 
    ///      error will be reported by throw exception.
    methods::Finish Finish;
};

} // namespace proxy
}
}
}

#endif //ARA_UCM_PKGMGR_PACKAGEMANAGEMENT_PROXY_H_
