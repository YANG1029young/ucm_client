#ifndef ARA_DIAG_SECURITYACCESS_SKELETON_H_
#define ARA_DIAG_SECURITYACCESS_SKELETON_H_

#include "securityaccess_common.h"

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


class SecurityAccessSkeleton : public ara::com::internal::skeleton::ServiceSkeleton
{
public:
    SecurityAccessSkeleton(
        ara::com::InstanceIdentifier instance,
        ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent
	)
        : ara::com::internal::skeleton::ServiceSkeleton("SecurityAccess", instance, mode)


    {
        //Events
	
        //Fields
	
        //Methods
        addMethod("GetSeed");
        addMethod("CompareKey");
        addMethod("Cancel");
	
        //registerErrors
        registerSecurityAccessErrors();
		
        // init
        init();
    }

    virtual ~SecurityAccessSkeleton(){}

    // Events
	
    // Fields
	
    // Methods
    virtual ara::core::Future<ara::diag::SecurityAccess::GetSeedOutput> GetSeed(const ara::diag::ByteVectorType& ByteVectorType,const ara::diag::MetaInfoType& MetaInfoType) = 0;
    virtual ara::core::Future<ara::diag::SecurityAccess::CompareKeyOutput> CompareKey(const ara::diag::ByteVectorType& ByteVectorType,const ara::diag::MetaInfoType& MetaInfoType) = 0;
    virtual ara::core::Future<void> Cancel(const ::ara::diag::MetaInfoType& metaInfo) = 0;
	

    virtual void DispatchMethodCall(const std::shared_ptr<ara::com::internal::Message> msg, std::shared_ptr<binding_base_type> binding)
    {
        if (msg->methodName == "GetSeed")
        {
            HandleCall(*this, &SecurityAccessSkeleton::GetSeed, msg, binding);
        }
        if (msg->methodName == "CompareKey")
        {
            HandleCall(*this, &SecurityAccessSkeleton::CompareKey, msg, binding);
        }
        if (msg->methodName == "Cancel")
        {
            HandleCall(*this, &SecurityAccessSkeleton::Cancel, msg, binding);
        }

    
    }
};
} // namespace skeleton
}
}

#endif //ARA_DIAG_SECURITYACCESS_SKELETON_H_
