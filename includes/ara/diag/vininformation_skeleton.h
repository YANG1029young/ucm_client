#ifndef ARA_DIAG_VININFORMATION_SKELETON_H_
#define ARA_DIAG_VININFORMATION_SKELETON_H_

#include "vininformation_common.h"

#include <ara/com/internal/skeleton/types.h>

namespace ara
{
namespace diag
{
namespace VINInformation
{

namespace skeleton
{

namespace events
{

} // namespace events


namespace fields
{

} // namespace fields


class VINInformationSkeleton : public ara::com::internal::skeleton::ServiceSkeleton
{
public:
    VINInformationSkeleton(
        ara::com::InstanceIdentifier instance,
        ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent
	)
        : ara::com::internal::skeleton::ServiceSkeleton("VINInformation", instance, mode)


    {
        //Events
	
        //Fields
	
        //Methods
        addMethod("Read");
        addMethod("Write");
        addMethod("Cancel");
	
        //registerErrors
        registerVINInformationErrors();
		
        // init
        init();
    }

    virtual ~VINInformationSkeleton(){}

    // Events
	
    // Fields
	
    // Methods
    virtual ara::core::Future<ara::diag::VINInformation::ReadOutput> Read(const ara::diag::MetaInfoType& MetaInfoType) = 0;
    virtual ara::core::Future<void> Write(const ::ara::diag::VINType& vin,const ::ara::diag::MetaInfoType& metaInfo) = 0;
    virtual ara::core::Future<void> Cancel(const ::ara::diag::MetaInfoType& metaInfo) = 0;
	

    virtual void DispatchMethodCall(const std::shared_ptr<ara::com::internal::Message> msg, std::shared_ptr<binding_base_type> binding)
    {
        if (msg->methodName == "Read")
        {
            HandleCall(*this, &VINInformationSkeleton::Read, msg, binding);
        }
        if (msg->methodName == "Write")
        {
            HandleCall(*this, &VINInformationSkeleton::Write, msg, binding);
        }
        if (msg->methodName == "Cancel")
        {
            HandleCall(*this, &VINInformationSkeleton::Cancel, msg, binding);
        }

    
    }
};
} // namespace skeleton
}
}
}
#endif //ARA_DIAG_VININFORMATION_SKELETON_H_
