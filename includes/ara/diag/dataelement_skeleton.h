#ifndef ARA_DIAG_DATAELEMENT_SKELETON_H_
#define ARA_DIAG_DATAELEMENT_SKELETON_H_

#include "dataelement_common.h"

#include <ara/com/internal/skeleton/types.h>

namespace ara
{
namespace diag
{
namespace DataElement
{

namespace skeleton
{

namespace events
{

} // namespace events


namespace fields
{

} // namespace fields


class DataElementSkeleton : public ara::com::internal::skeleton::ServiceSkeleton
{
public:
    DataElementSkeleton(
        ara::com::InstanceIdentifier instance,
        ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent
	)
        : ara::com::internal::skeleton::ServiceSkeleton("DataElement", instance, mode)


    {
        //Events
	
        //Fields
	
        //Methods
        addMethod("Read");
        addMethod("Cancel");
	
        //registerErrors
        registerDataElementErrors();
		
        // init
        init();
    }

    virtual ~DataElementSkeleton(){}

    // Events
	
    // Fields
	
    // Methods
    virtual ara::core::Future<ara::diag::DataElement::ReadOutput> Read(const ara::diag::MetaInfoType& MetaInfoType) = 0;
    virtual ara::core::Future<void> Cancel(const ::ara::diag::MetaInfoType& metaInfo) = 0;
	

    virtual void DispatchMethodCall(const std::shared_ptr<ara::com::internal::Message> msg, std::shared_ptr<binding_base_type> binding)
    {
        if (msg->methodName == "Read")
        {
            HandleCall(*this, &DataElementSkeleton::Read, msg, binding);
        }
        if (msg->methodName == "Cancel")
        {
            HandleCall(*this, &DataElementSkeleton::Cancel, msg, binding);
        }

    
    }
};
} // namespace skeleton
}
}
}
#endif //ARA_DIAG_DATAELEMENT_SKELETON_H_
