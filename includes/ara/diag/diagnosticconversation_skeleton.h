#ifndef ARA_DIAG_DIAGNOSTICCONVERSATION_SKELETON_H_
#define ARA_DIAG_DIAGNOSTICCONVERSATION_SKELETON_H_

#include "diagnosticconversation_common.h"

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
    using ActivityStatus = ara::com::internal::skeleton::FieldType<::ara::diag::ActivityStatusType,true,true,false>::type;
    using DiagnosticSession = ara::com::internal::skeleton::FieldType<::ara::diag::DiagnosticSessionType,true,true,false>::type;
    using DiagnosticSecurityLevel = ara::com::internal::skeleton::FieldType<::ara::diag::DiagnosticSecurityLevelType,true,true,false>::type;
    using Identifier = ara::com::internal::skeleton::FieldType<::ara::diag::DiagnosticConversationIdentifierType,true,true,false>::type;

} // namespace fields


class DiagnosticConversationSkeleton : public ara::com::internal::skeleton::ServiceSkeleton
{
public:
    DiagnosticConversationSkeleton(
        ara::com::InstanceIdentifier instance,
        ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent
	)
        : ara::com::internal::skeleton::ServiceSkeleton("DiagnosticConversation", instance, mode)

        , ActivityStatus(this, "ActivityStatus")
        , DiagnosticSession(this, "DiagnosticSession")
        , DiagnosticSecurityLevel(this, "DiagnosticSecurityLevel")
        , Identifier(this, "Identifier")

    {
        //Events
	
        //Fields
        addField("ActivityStatus",true,true,false);
        addField("DiagnosticSession",true,true,false);
        addField("DiagnosticSecurityLevel",true,true,false);
        addField("Identifier",true,true,false);
	
        //Methods
        addMethod("ResetToDefaultSession");
        addMethod("Cancel");
	
        //registerErrors
        registerDiagnosticConversationErrors();
		
        // init
        init();
    }

    virtual ~DiagnosticConversationSkeleton(){}

    // Events
	
    // Fields
    fields::ActivityStatus ActivityStatus;
    fields::DiagnosticSession DiagnosticSession;
    fields::DiagnosticSecurityLevel DiagnosticSecurityLevel;
    fields::Identifier Identifier;
	
    // Methods
    virtual void ResetToDefaultSession() = 0;
    virtual void Cancel() = 0;
	
    ara::core::Future<::ara::diag::ActivityStatusType> ActivityStatus_Get()
    {
        if (ActivityStatus.GetHandler)
        {
            return ActivityStatus.GetHandler();
        }
        else
        {
            return NoHandler<::ara::diag::ActivityStatusType>();
        }
    }
    ara::core::Future<::ara::diag::DiagnosticSessionType> DiagnosticSession_Get()
    {
        if (DiagnosticSession.GetHandler)
        {
            return DiagnosticSession.GetHandler();
        }
        else
        {
            return NoHandler<::ara::diag::DiagnosticSessionType>();
        }
    }
    ara::core::Future<::ara::diag::DiagnosticSecurityLevelType> DiagnosticSecurityLevel_Get()
    {
        if (DiagnosticSecurityLevel.GetHandler)
        {
            return DiagnosticSecurityLevel.GetHandler();
        }
        else
        {
            return NoHandler<::ara::diag::DiagnosticSecurityLevelType>();
        }
    }
    ara::core::Future<::ara::diag::DiagnosticConversationIdentifierType> Identifier_Get()
    {
        if (Identifier.GetHandler)
        {
            return Identifier.GetHandler();
        }
        else
        {
            return NoHandler<::ara::diag::DiagnosticConversationIdentifierType>();
        }
    }

    virtual void DispatchMethodCall(const std::shared_ptr<ara::com::internal::Message> msg, std::shared_ptr<binding_base_type> binding)
    {
        if (msg->methodName == "ResetToDefaultSession")
        {
            HandleCall(*this, &DiagnosticConversationSkeleton::ResetToDefaultSession, msg, binding);
        }
        if (msg->methodName == "Cancel")
        {
            HandleCall(*this, &DiagnosticConversationSkeleton::Cancel, msg, binding);
        }

        if (msg->methodName == "ActivityStatus_Get")
        {
            HandleCall(*this, &DiagnosticConversationSkeleton::ActivityStatus_Get, msg, binding);
        }
        if (msg->methodName == "DiagnosticSession_Get")
        {
            HandleCall(*this, &DiagnosticConversationSkeleton::DiagnosticSession_Get, msg, binding);
        }
        if (msg->methodName == "DiagnosticSecurityLevel_Get")
        {
            HandleCall(*this, &DiagnosticConversationSkeleton::DiagnosticSecurityLevel_Get, msg, binding);
        }
        if (msg->methodName == "Identifier_Get")
        {
            HandleCall(*this, &DiagnosticConversationSkeleton::Identifier_Get, msg, binding);
        }
    
    }
};
} // namespace skeleton
}
}

#endif //ARA_DIAG_DIAGNOSTICCONVERSATION_SKELETON_H_
