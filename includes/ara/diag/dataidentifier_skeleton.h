#ifndef ARA_DIAG_DATAIDENTIFIER_SKELETON_H_
#define ARA_DIAG_DATAIDENTIFIER_SKELETON_H_

#include "dataidentifier_common.h"

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


class DataIdentifierSkeleton : public ara::com::internal::skeleton::ServiceSkeleton
{
public:
    DataIdentifierSkeleton(
        ara::com::InstanceIdentifier instance,
        ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent
	)
        : ara::com::internal::skeleton::ServiceSkeleton("DataIdentifier", instance, mode)


    {
        //Events
	
        //Fields
	
        //Methods
        addMethod("Write");
        addMethod("Read");
        addMethod("Cancel");
	
        //registerErrors
        registerDataIdentifierErrors();
		
        // init
        init();
    }

    virtual ~DataIdentifierSkeleton(){}

    // Events
	
    // Fields
	
    // Methods
    virtual ara::core::Future<ara::diag::DataIdentifier::ReadOutput> Read(const ara::diag::MetaInfoType& MetaInfoType) = 0;
    virtual ara::core::Future<void> Write(const ::ByteArray& dataRecord,const ::ara::diag::MetaInfoType& metaInfo) = 0;
    virtual ara::core::Future<void> Cancel(const ::ara::diag::MetaInfoType& metaInfo) = 0;
	

    virtual void DispatchMethodCall(const std::shared_ptr<ara::com::internal::Message> msg, std::shared_ptr<binding_base_type> binding)
    {
        if (msg->methodName == "Write")
        {
            HandleCall(*this, &DataIdentifierSkeleton::Write, msg, binding);
        }
        if (msg->methodName == "Read")
        {
            HandleCall(*this, &DataIdentifierSkeleton::Read, msg, binding);
        }
        if (msg->methodName == "Cancel")
        {
            HandleCall(*this, &DataIdentifierSkeleton::Cancel, msg, binding);
        }

    
    }
};
} // namespace skeleton
}
}

#endif //ARA_DIAG_DATAIDENTIFIER_SKELETON_H_
