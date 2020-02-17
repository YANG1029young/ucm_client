/***************************************************************************//**
 * @copyright Copyright (c) by Hinge-Tech R&D Center.
 * @file  phm.h
 * @brief define the phm class 
 * @author aijun.yang  
 * @version 00.00.01
 * @date  2019-09-09 
 ******************************************************************************/
#ifndef ARA_PHM_PHM_H_
#define ARA_PHM_PHM_H_

#include <cstdint>
#include <iostream>
#include <type_traits>

#include <ara/log/logging.h>
#include <ara/log/common.h>
#include <ara/log/logger.h>
#include <ara/log/logstream.h>
#include "phmser_proxy.h"
namespace ara
{
namespace phm
{

/// some  brief description
using InterfaceType = UInt16;
using PrototypeType = UInt8;
using InstanceType = Int32;
using EnumUnderlyingType = UInt8;
typedef void (*EventCallback)(UInt8 uStatus, UInt8 uType, UInt8 uInstanceId);

/// @brief This class represents the Adaptive Application
/// @details App that inherit this class to be a ap platform application. 
/// @note some function need to be implemented in App.
class PHM
{
public:
	
	/// @brief A method represents construct the Class.
    /// @par Description: 
    ///         this is used to option a instance of the phm class.
    /// @param NULL NULL
    /// @return instance of the phm.
    PHM();

	
	/// @brief A method represents copy construct function.
    /// @par Description: 
    ///         this is used to option a instance of the phm class from other instance.
    /// @param other instanced for a phm class.
    /// @return instance of the phm class.
    PHM(PHM const& other);
    PHM(PHM&& other) = delete;
    PHM& operator=(PHM const& other) = delete;
    PHM& operator=(PHM&& other) = delete;

	/// @brief A method represents destruct the phm class instanced.
    /// @par Description: 
    ///         this is used to release the phm class object and free use space which the instance new/malloc.
    /// @param NULL NULL
    /// @return void.
    ~PHM();
	
	/// @brief A method represents the callback for status change envent.
    /// @par Description: 
    ///         this is used to resived the notify for status change.
    /// @param NULL NULL
    /// @return none
	static void StatusEventCallback(void);

	/// @brief A method is report a checkpoint for a supervised entityed.
    /// @par Description: 
    ///         this is used to send a supervision checkpoint by cm.
    /// @param supervisedEntityId the identifier for the SE.
    /// @param prototypeId        the identifier for a SE instanced.
    /// @param instanceId         the identifier for the process that contains the SE. 
    /// @param checkpointId       the identifier for the checkpoint.
    /// @return true sucessful; false failure.
    bool ReportCheckpoint(InterfaceType supervisedEntityId,
        PrototypeType prototypeId,
        InstanceType instanceId,
        EnumUnderlyingType checkpointId);

	/// @brief A method is report a status for a supervised channel.
    /// @par Description: 
    ///         this is used to send a status for supervision channel by cm.
    /// @param healthChannelId    the identifier for the healthChannel.
    /// @param prototypeId        the identifier for a  healthChannel instanced.
    /// @param instanceId         the identifier for the process that contains the  healthChannel. 
    /// @param healthStatusId     the identifier for the status.
    /// @return true sucessful; false failure.
    bool ReportHealthStatus(InterfaceType healthChannelId,
        PrototypeType prototypeId,
        InstanceType instanceId,
        EnumUnderlyingType healthStatusId);

	/// @brief A method is register a callback function.
    /// @par Description: 
    ///         this is used to register a function for recived the notify infomation for status change.
    /// @param pFun    the function you want to register.
    /// @return true sucessful; false failure.
	bool RegisterEventCallback(EventCallback pFun);

	
	/// @brief A method is get local status.
    /// @par Description: 
    ///         this is used to get the SE current local status.
    /// @param instanceId    the identifier for the process that contains the SE.
    /// @param seID          the identifier for the SE.
    /// @param prototypeId   the identifier for the instance for the SE..
    /// @return 255 failure; other sucessful.
	UInt8 GetLocalStatus(InstanceType instanceId, UInt16 seID, PrototypeType prototypeId);

	/// @brief A method is get Global status.
    /// @par Description: 
    ///         this is used to get the supersied process global status.
    /// @param instanceId    the identifier for the process.
    /// @return 255 failure; other sucessful.
	UInt8 GetGlobalStatus(InstanceType instanceId);

	
	/// @brief A method is get the instanced(witch is the process id) id.
    /// @par Description: 
    ///         this is used to get the supersied process id.
    /// @param NULL NULL
    /// @return -1 error; process id sucessful.
    InstanceType GetInstanceId(void) const;
	
	/// @brief A method is init the supervision.
    /// @par Description: 
    ///         this is used to init the supervision context.
    /// @param NULL NULL
    /// @return 0  sucessful; -1 faulure.
	int InitObject(void);
private:
    explicit PHM(InstanceType instanceId);
    InstanceType instanceId_;
    ara::log::Logger& logger_;
};

template <InterfaceType InterfaceId, PrototypeType PrototypeId, typename Enum>
struct Identifier
{

    /// definition of the supervised entity Id / health channel Id
    constexpr static InterfaceType interfaceId = InterfaceId;

    /// definition of the prototype Id,
    constexpr static PrototypeType prototypeId = PrototypeId;

    /// definition of all checkpoints/health statuses of this SE
    using EnumType = Enum;
};

template <typename T>
struct DependentFalse : std::false_type
{};

}  // namespace phm
}  // namespace ara

#endif  // ARA_PHM_PHM_H_
