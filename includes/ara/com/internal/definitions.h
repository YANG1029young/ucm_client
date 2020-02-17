/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */
 
#ifndef ARA_COM_INTERNAL_DEFINITIONS_H_
#define ARA_COM_INTERNAL_DEFINITIONS_H_

#include <cstdint>
#include <memory>
#include <vector>
#include <functional>

namespace ara
{
namespace com
{
namespace internal
{

// Definition of service version type
using ServiceVersion = std::uint32_t;

// Definition of internal instance ID type that should be binding agnostic.
using InstanceId = std::uint16_t;

// Definition of internal service ID type that should be binding agnostic.
using ServiceId = std::uint16_t;

// "Null" instance ID
static const InstanceId INSTANCE_ID_UNKNOWN = 0xFFFF;

enum class NetWorkBindingType: uint8_t
{
    SOMEIP,
    IPC
};

enum class MessageType : uint8_t {
    MT_REQUEST = 0x00,
    MT_REQUEST_NO_RETURN = 0x01,
    MT_NOTIFICATION = 0x02,
    MT_REQUEST_ACK = 0x40,
    MT_REQUEST_NO_RETURN_ACK = 0x41,
    MT_NOTIFICATION_ACK = 0x42,
    MT_RESPONSE = 0x80,
    MT_ERROR = 0x81,
    MT_RESPONSE_ACK = 0xC0,
    MT_ERROR_ACK = 0xC1,
    MT_SUBSCRIBE = 0xE0,
    MT_UNSUBSCRIBE = 0xE1,
    MT_SUBSCRIBE_ACK = 0xE2,
    MT_UNKNOWN = 0xFF
};


enum class ReturnCode : uint8_t {
    E_OK = 0x00,
    E_NOT_OK = 0x01,
    E_UNKNOWN_SERVICE = 0x02,
    E_UNKNOWN_METHOD = 0x03,
    E_NOT_READY = 0x04,
    E_NOT_REACHABLE = 0x05,
    E_TIMEOUT = 0x06,
    E_WRONG_PROTOCOL_VERSION = 0x07,
    E_WRONG_INTERFACE_VERSION = 0x08,
    E_MALFORMED_MESSAGE = 0x09,
    E_WRONG_MESSAGE_TYPE = 0xA,
    E_UNKNOWN = 0xFF
};

struct Message
{
    uint16_t methodId;
    uint16_t clientId;
    uint16_t sessionId;
    MessageType type;
    ReturnCode code;
    std::shared_ptr<std::vector<uint8_t>> payload = std::make_shared<std::vector<uint8_t>>();
    std::string methodName;
    NetWorkBindingType bindingType;
};

using MessageReceiveHandler = std::function<void (std::shared_ptr<Message>)>;

}  // namespace internal
}  // namespace com
}  // namespace ara

#endif // ARA_COM_INTERNAL_DEFINITIONS_H_
