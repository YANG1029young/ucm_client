/***************************************************************************//**
 * @copyright Copyright (c) by Hinge-Tech R&D Center.
 * @file  packagemanagement_skeleton.h
 * @brief skeleton file of package-manager 
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
#ifndef ARA_UCM_PKGMGR_PACKAGEMANAGEMENT_SKELETON_H_
#define ARA_UCM_PKGMGR_PACKAGEMANAGEMENT_SKELETON_H_

#include "packagemanagement_common.h"

#include <ara/com/internal/skeleton/types.h>

namespace ara
{
namespace ucm
{
namespace pkgmgr
{

namespace skeleton
{

namespace events
{

} // namespace events


namespace fields
{
    using CurrentStatus = ara::com::internal::skeleton::FieldType<::ara::ucm::pkgmgr::PackageManagerStatusType,true,true,false>::type;

} // namespace fields

/// @brief Interface class of ucm server end
///
/// @details interface of packagemanager need to be implemented by serverice side
class PackageManagementSkeleton : public ara::com::internal::skeleton::ServiceSkeleton
{
public:
    PackageManagementSkeleton(
        ara::com::InstanceIdentifier instance,
        ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent
	)
        : ara::com::internal::skeleton::ServiceSkeleton("PackageManagement", instance, mode)

        , CurrentStatus(this, "CurrentStatus")

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

    virtual ~PackageManagementSkeleton(){}

    // Events
	
    // Fields
    fields::CurrentStatus CurrentStatus;///< status of ucm
	
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
    virtual ara::core::Future<ara::ucm::pkgmgr::PackageManagement::TransferStartOutput> TransferStart(const UInt32& UInt32) = 0;

    /// @param TransferIdType represent an unique transfer,this valued is get from result of call TransferStart
    /// @param ByteVectorType a data vector that contains package data will transfer to ucm
    /// @param UInt32 is the data size in ByteVectorType
    /// @return 
    ///  - if success, kSuccess will set to TransferDataOutput::result
    ///  - if failed, related error no will be set to TransferDataOutput::result
    /// @par Functional Description
    /// This function is used to transfer data to ucm,usually client split 
    /// a large package into small fragments(512bytes/per),then transfer it to
    /// ucm by call this function.The largest fragment size supported by ucm is 
    /// configured in package_manager_cofing.json file in ucm's etc diretory
    ///
    /// @par others
    ///     will be call after TransferStart, if any error occur, should delete transfer
    /// 
    /// @par Particularities and Limitations
    ///     Block size limited less than 512 bytes
    /// @par Call Context
    ///     invoke in task context
    virtual ara::core::Future<ara::ucm::pkgmgr::PackageManagement::TransferDataOutput> TransferData(const ara::ucm::pkgmgr::TransferIdType& TransferIdType,const ara::ucm::pkgmgr::ByteVectorType& ByteVectorType,const UInt32& UInt32) = 0;
    virtual ara::core::Future<ara::ucm::pkgmgr::PackageManagement::TransferExitOutput> TransferExit(const ara::ucm::pkgmgr::TransferIdType& TransferIdType) = 0;
    virtual ara::core::Future<ara::ucm::pkgmgr::PackageManagement::DeleteTransferOutput> DeleteTransfer(const ara::ucm::pkgmgr::TransferIdType& TransferIdType) = 0;
    virtual ara::core::Future<ara::ucm::pkgmgr::PackageManagement::ProcessSwPackageOutput> ProcessSwPackage(const ara::ucm::pkgmgr::TransferIdType& TransferIdType) = 0;
    virtual ara::core::Future<ara::ucm::pkgmgr::PackageManagement::GetSwProcessProgressOutput> GetSwProcessProgress(const ara::ucm::pkgmgr::TransferIdType& TransferIdType) = 0;
    virtual ara::core::Future<ara::ucm::pkgmgr::PackageManagement::CancelOutput> Cancel(const ara::ucm::pkgmgr::TransferIdType& TransferIdType) = 0;
    virtual ara::core::Future<ara::ucm::pkgmgr::PackageManagement::RevertProcessedSwPackagesOutput> RevertProcessedSwPackages() = 0;
    virtual ara::core::Future<ara::ucm::pkgmgr::PackageManagement::SetLogLevelOutput> SetLogLevel(const ara::ucm::pkgmgr::TransferIdType& TransferIdType,const ara::ucm::pkgmgr::LogLevelType& LogLevelType) = 0;
    virtual ara::core::Future<ara::ucm::pkgmgr::PackageManagement::GetLogOutput> GetLog(const ara::ucm::pkgmgr::TransferIdType& TransferIdType) = 0;
    virtual ara::core::Future<ara::ucm::pkgmgr::PackageManagement::GetSwClusterChangeInfoOutput> GetSwClusterChangeInfo() = 0;
    virtual ara::core::Future<ara::ucm::pkgmgr::PackageManagement::GetSwClusterInfoOutput> GetSwClusterInfo() = 0;
    virtual ara::core::Future<ara::ucm::pkgmgr::PackageManagement::GetSwPackagesOutput> GetSwPackages() = 0;
    virtual ara::core::Future<ara::ucm::pkgmgr::PackageManagement::ActivateOutput> Activate(const ara::ucm::pkgmgr::ActivateOptionType& ActivateOptionType) = 0;
    virtual ara::core::Future<ara::ucm::pkgmgr::PackageManagement::RollbackOutput> Rollback() = 0;
    virtual ara::core::Future<ara::ucm::pkgmgr::PackageManagement::FinishOutput> Finish() = 0;
	
    ara::core::Future<::ara::ucm::pkgmgr::PackageManagerStatusType> CurrentStatus_Get()
    {
        if (CurrentStatus.GetHandler)
        {
            return CurrentStatus.GetHandler();
        }
        else
        {
            return NoHandler<::ara::ucm::pkgmgr::PackageManagerStatusType>();
        }
    }

    virtual void DispatchMethodCall(const std::shared_ptr<ara::com::internal::Message> msg, std::shared_ptr<binding_base_type> binding)
    {
        if (msg->methodName == "TransferStart")
        {
            HandleCall(*this, &PackageManagementSkeleton::TransferStart, msg, binding);
        }
        if (msg->methodName == "TransferData")
        {
            HandleCall(*this, &PackageManagementSkeleton::TransferData, msg, binding);
        }
        if (msg->methodName == "TransferExit")
        {
            HandleCall(*this, &PackageManagementSkeleton::TransferExit, msg, binding);
        }
        if (msg->methodName == "DeleteTransfer")
        {
            HandleCall(*this, &PackageManagementSkeleton::DeleteTransfer, msg, binding);
        }
        if (msg->methodName == "ProcessSwPackage")
        {
            HandleCall(*this, &PackageManagementSkeleton::ProcessSwPackage, msg, binding);
        }
        if (msg->methodName == "GetSwProcessProgress")
        {
            HandleCall(*this, &PackageManagementSkeleton::GetSwProcessProgress, msg, binding);
        }
        if (msg->methodName == "Cancel")
        {
            HandleCall(*this, &PackageManagementSkeleton::Cancel, msg, binding);
        }
        if (msg->methodName == "RevertProcessedSwPackages")
        {
            HandleCall(*this, &PackageManagementSkeleton::RevertProcessedSwPackages, msg, binding);
        }
        if (msg->methodName == "SetLogLevel")
        {
            HandleCall(*this, &PackageManagementSkeleton::SetLogLevel, msg, binding);
        }
        if (msg->methodName == "GetLog")
        {
            HandleCall(*this, &PackageManagementSkeleton::GetLog, msg, binding);
        }
        if (msg->methodName == "GetSwClusterChangeInfo")
        {
            HandleCall(*this, &PackageManagementSkeleton::GetSwClusterChangeInfo, msg, binding);
        }
        if (msg->methodName == "GetSwClusterInfo")
        {
            HandleCall(*this, &PackageManagementSkeleton::GetSwClusterInfo, msg, binding);
        }
        if (msg->methodName == "GetSwPackages")
        {
            HandleCall(*this, &PackageManagementSkeleton::GetSwPackages, msg, binding);
        }
        if (msg->methodName == "Activate")
        {
            HandleCall(*this, &PackageManagementSkeleton::Activate, msg, binding);
        }
        if (msg->methodName == "Rollback")
        {
            HandleCall(*this, &PackageManagementSkeleton::Rollback, msg, binding);
        }
        if (msg->methodName == "Finish")
        {
            HandleCall(*this, &PackageManagementSkeleton::Finish, msg, binding);
        }

        if (msg->methodName == "CurrentStatus_Get")
        {
            HandleCall(*this, &PackageManagementSkeleton::CurrentStatus_Get, msg, binding);
        }
    
    }
};
} // namespace skeleton
}
}
}

#endif //ARA_UCM_PKGMGR_PACKAGEMANAGEMENT_SKELETON_H_
