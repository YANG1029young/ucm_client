#ifndef ARA_PHM_SUPERVISED_ENTITY_H_
#define ARA_PHM_SUPERVISED_ENTITY_H_

#include <cstdint>
#include <iostream>
#include <type_traits>

#include "ara/phm/phm.h"
#include "ara/phm/local_supervision_status.h"
#include "ara/phm/global_supervision_status.h"

namespace ara
{
namespace phm
{

template <typename T>
class SupervisedEntity
{
    static_assert(DependentFalse<T>::value, "SupervisedEntity must be created using Identifier template");
};

template <InterfaceType InterfaceId, PrototypeType PrototypeId, typename Enum>
class SupervisedEntity<Identifier<InterfaceId, PrototypeId, Enum>> : private PHM
{
public:
    /// @brief   Creation of a SupervisedEntity
    ///
    /// @uptrace{SWS_PHM_01123}
    explicit SupervisedEntity(PHM const& phm)
        : PHM{phm}
    {}

    /// @brief   ReporyCheckpoint method declaration
    ///
    /// @uptrace{SWS_PHM_01127}
    bool ReportCheckpoint(Enum t);
	bool RegisterEventCallback(EventCallback pFun);
    /// @brief   GetLocalSupervisionStatus method declaration
    ///
    /// @uptrace{SWS_PHM_01134}
    bool GetLocalSupervisionStatus(LocalSupervisionStatus& e);

    /// @brief   GetGlobalSupervisionStatus method declaration
    ///
    /// @uptrace{SWS_PHM_01135}
    bool GetGlobalSupervisionStatus(GlobalSupervisionStatus& e);
};

template <InterfaceType InterfaceId, PrototypeType PrototypeId, typename Enum>
bool SupervisedEntity<Identifier<InterfaceId, PrototypeId, Enum>>::ReportCheckpoint(Enum t)
{
    auto checkpointId = static_cast<typename std::underlying_type<Enum>::type>(t);
	
	std::cout<<"SE ReportCheckpoint"<<std::endl;
    return PHM::ReportCheckpoint(InterfaceId, PrototypeId, GetInstanceId(), checkpointId);
}

template <InterfaceType Id, PrototypeType PrototypeId, typename Enum>
bool SupervisedEntity<Identifier<Id, PrototypeId, Enum>>::GetLocalSupervisionStatus(LocalSupervisionStatus& e)
{
	UInt8 uStatus = 0;
	uStatus = PHM::GetLocalStatus(GetInstanceId(), Id, PrototypeId);
	
	printf("SupervisedEntity obtain the global status: %d\r\n",uStatus);
	if (uStatus != 255)
	{
		e = (LocalSupervisionStatus)uStatus;
		return true;
	}
	
    return false;
}

template <InterfaceType Id, PrototypeType PrototypeId, typename Enum>
bool SupervisedEntity<Identifier<Id, PrototypeId, Enum>>::GetGlobalSupervisionStatus(GlobalSupervisionStatus& e)
{
	UInt8 uStatus = 0;
	uStatus = PHM::GetGlobalStatus(GetInstanceId());
	
	std::cout<<"obtation the globalstatus: "<<uStatus<<std::endl;
	if (uStatus != 255) 
	{
		e = (GlobalSupervisionStatus)uStatus;
		return true;
	}
	return false;
}

template <InterfaceType Id, PrototypeType PrototypeId, typename Enum>
bool SupervisedEntity<Identifier<Id, PrototypeId, Enum>>::RegisterEventCallback(EventCallback pFun)
{
	std::cout<<"SE RegisterEventCallback"<<std::endl;
	return PHM::RegisterEventCallback(pFun);
}
}  // namespace phm
}  // namespace ara

#endif  // ARA_PHM_SUPERVISED_ENTITY_H_
