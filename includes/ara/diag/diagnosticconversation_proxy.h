#ifndef ARA_DIAG_DIAGNOSTICCONVERSATION_PROXY_H_
#define ARA_DIAG_DIAGNOSTICCONVERSATION_PROXY_H_

#include "diagnosticconversation_common.h"
#include <ara/com/internal/proxy/types.h>

namespace ara
{
namespace diag
{

namespace proxy
{

namespace events
{

} // namespace events


namespace fields
{
    using ActivityStatus = ara::com::internal::proxy::FieldType<::ara::diag::ActivityStatusType,true,true,false>::type;
    using DiagnosticSession = ara::com::internal::proxy::FieldType<::ara::diag::DiagnosticSessionType,true,true,false>::type;
    using DiagnosticSecurityLevel = ara::com::internal::proxy::FieldType<::ara::diag::DiagnosticSecurityLevelType,true,true,false>::type;
    using Identifier = ara::com::internal::proxy::FieldType<::ara::diag::DiagnosticConversationIdentifierType,true,true,false>::type;

} // namespace fields


namespace methods
{
    using ResetToDefaultSession = ara::com::internal::proxy:: FireAndForgetMethod<void()>;
    using Cancel = ara::com::internal::proxy:: FireAndForgetMethod<void()>;

} // namespace methods


class DiagnosticConversationProxy : public ara::com::internal::proxy::ServiceProxy
{
public:
    using HandleType = ara::com::internal::proxy::ServiceProxy::HandleType;
	
    explicit DiagnosticConversationProxy(HandleType handle)
    	: ara::com::internal::proxy::ServiceProxy("DiagnosticConversation", handle)
    	
        , ActivityStatus(this, "ActivityStatus")
        , DiagnosticSession(this, "DiagnosticSession")
        , DiagnosticSecurityLevel(this, "DiagnosticSecurityLevel")
        , Identifier(this, "Identifier")
    	
        , ResetToDefaultSession(this, "ResetToDefaultSession")
        , Cancel(this, "Cancel")

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
	
    virtual ~DiagnosticConversationProxy(){}

    static ara::com::ServiceHandleContainer<HandleType> FindService(
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::FindService("DiagnosticConversation", instance);
    }
    	
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandler<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("DiagnosticConversation", handler, instance);
    }
    
    static ara::com::FindServiceHandle StartFindService(
    	ara::com::FindServiceHandlerExt<HandleType> handler,
    	ara::com::InstanceIdentifier instance)
    {
    	return ara::com::internal::proxy::ServiceProxy::StartFindService("DiagnosticConversation", handler, instance);
    }
	
    // Events
	
    // Fields
    fields::ActivityStatus ActivityStatus;
    fields::DiagnosticSession DiagnosticSession;
    fields::DiagnosticSecurityLevel DiagnosticSecurityLevel;
    fields::Identifier Identifier;
	
    // Methods
    methods::ResetToDefaultSession ResetToDefaultSession;
    methods::Cancel Cancel;

};

} // namespace proxy
}
}

#endif //ARA_DIAG_DIAGNOSTICCONVERSATION_PROXY_H_
