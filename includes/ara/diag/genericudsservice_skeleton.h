#ifndef ARA_DIAG_GENERICUDSSERVICE_SKELETON_H_
#define ARA_DIAG_GENERICUDSSERVICE_SKELETON_H_

#include "genericudsservice_common.h"

#include <ara/com/internal/skeleton/types.h>

namespace ara
{
namespace diag
{

namespace skeleton
{

namespace events
{

} // namespace events


namespace fields
{

} // namespace fields


class GenericUDSServiceSkeleton : public ara::com::internal::skeleton::ServiceSkeleton
{
public:
    GenericUDSServiceSkeleton(
        ara::com::InstanceIdentifier instance,
        ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent
	)
        : ara::com::internal::skeleton::ServiceSkeleton("GenericUDSService", instance, mode)


    {
        //Events
	
        //Fields
	
        //Methods
        addMethod("HandleMessage");
        addMethod("Cancel");
	
        //registerErrors
        registerGenericUDSServiceErrors();
		
        // init
        init();
    }

    virtual ~GenericUDSServiceSkeleton(){}

    // Events
	
    // Fields
	
    // Methods
    virtual ara::core::Future<ara::diag::GenericUDSService::HandleMessageOutput> HandleMessage(const ara::diag::SIDType& SIDType,const ara::diag::ByteVectorType& ByteVectorType,const ara::diag::MetaInfoType& MetaInfoType) = 0;
    virtual ara::core::Future<void> Cancel(const ::ara::diag::MetaInfoType& metaInfo) = 0;
	

    virtual void DispatchMethodCall(const std::shared_ptr<ara::com::internal::Message> msg, std::shared_ptr<binding_base_type> binding)
    {
        if (msg->methodName == "HandleMessage")
        {
            HandleCall(*this, &GenericUDSServiceSkeleton::HandleMessage, msg, binding);
        }
        if (msg->methodName == "Cancel")
        {
            HandleCall(*this, &GenericUDSServiceSkeleton::Cancel, msg, binding);
        }

    
    }
};
} // namespace skeleton
}
}

#endif //ARA_DIAG_GENERICUDSSERVICE_SKELETON_H_
