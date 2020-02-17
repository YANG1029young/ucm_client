/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_INTERNAL_MANIFEST_H_
#define ARA_COM_INTERNAL_MANIFEST_H_

#include <ara/com/data_types.h>
#include <ara/com/e2e/profiles.h>

namespace ara
{
namespace com
{
namespace internal
{

enum class TransportLayerProtocolEnum : uint8_t
{
    udp = 0,
    tcp = 1
};

struct ServiceInterface
{
    std::string name;
    std::vector<std::string> methods;
    std::vector<std::string> events;
    std::vector<std::string> fields; 
};

struct SomeipEventDeployment
{
    std::string name;
    uint16_t eventId;
    int maximumSegmentLength;
    double separationTime;
    TransportLayerProtocolEnum transportProtocol;
};

struct SomeipMethodDeployment
{
    std::string name;
    uint16_t methodId;
    int maximumSegmentLengthRequest;
    int maximumSegmentLengthResponse;
    double separationTimeRequest;
    double separationTimeResponse;
    TransportLayerProtocolEnum transportProtocol;
};

struct SomeipFieldDeployment
{
    std::string name;
    std::shared_ptr<SomeipEventDeployment> event = nullptr;
    std::shared_ptr<SomeipMethodDeployment> get = nullptr;
    std::shared_ptr<SomeipMethodDeployment> set = nullptr;
};

struct SomeipEventGroup
{
    std::string name;
    uint16_t eventGroupId;
    uint32_t multicastThreshold = 0;
    std::vector<std::shared_ptr<SomeipEventDeployment>> events;
};

struct SomeipServiceInterfaceVersion
{
    uint8_t majorVersion;
    uint32_t minorVersion;
};

struct SomeipServiceInstanceToMachineMapping
{
    uint16_t eventMulticastUdpPort = 0;
    std::string ipv4MulticastIpAddress;
    std::string ipv6MulticastIpAddress;
    uint16_t tcpPort = 0;
    uint32_t udpCollectionBufferSizeThreshold;
    uint16_t udpPort = 0;
    std::string ipv4Address;
};

struct SomeipSdConfig
{
    double initialDelayMaxValue = 0.1;
    double initialDelayMinValue = 0.01;
    double initialRepetitionsBaseDelay = 0.2;
    uint8_t initialRepetitionsMax = 3;
    uint32_t timeToLive;
    double offerCyclicDelay;
    double requestResponseDelayMaxValue;
    double requestResponseDelayMinValue;
};

struct E2EProfileConfiguration
{
    ara::com::profile::profile11::DataIdMode dataIdMode = ara::com::profile::profile11::DataIdMode::ALL_16_BIT;
    uint16_t maxDeltaCounter;
    uint8_t maxErrorStateInit;
    uint8_t maxErrorStateInvalid;
    uint8_t maxErrorStateValid;
    uint8_t minOkStateInit;
    uint8_t minOkStateInvalid;
    uint8_t minOkStateValid;
    std::string profileName;
    uint8_t windowSize;
};

struct End2EndEventProtectionProps
{
    uint32_t dataId;
    uint32_t datalength = 8;
    double dataUpdatePeriod;
    std::shared_ptr<E2EProfileConfiguration> e2eProfileConfiguration = nullptr;
    std::string eventName;
    uint16_t maxDataLength = 4096;
    uint16_t minDataLength = 1;
    uint16_t offset = 0;
    std::array<std::uint8_t, 16> dataIdList;
};

enum class SOMEIPTransformerSessionHandlingEnum : uint8_t
{
    sessionHandlingActive = 0,
    sessionHandlingInactive = 1
};

enum class ByteOrderEnum : uint8_t
{
    MostSignificantByteFirst = 0,
    MostSignificantByteLast = 1,
    Opaque = 2
};

struct ApSomeipTransformationProps
{
    uint32_t alignment = 1;
    ByteOrderEnum byteOrder = ByteOrderEnum::MostSignificantByteFirst;
    bool isDynamicLengthFieldSize = false;
    SOMEIPTransformerSessionHandlingEnum sessionHandling = SOMEIPTransformerSessionHandlingEnum::sessionHandlingActive;
    uint32_t sizeOfArrayLengthField = 4;
    uint32_t sizeOfStringLengthField = 4;
    uint32_t sizeOfStructLengthField = 0;
    uint32_t sizeOfUnionLengthField = 0;
    uint32_t sizeOfUnionTypeSelectorField = 0;
    std::string stringEncoding = "UTF-8";
};

struct SomeipServiceInterfaceDeployment
{
    bool isProvided;
    std::string name;
    uint16_t serviceInterfaceId;
    uint16_t instanceId;
    std::shared_ptr<SomeipServiceInterfaceVersion> serviceInterfaceVersion = nullptr;
    std::vector<std::shared_ptr<SomeipMethodDeployment>> methodDeployments;
    std::vector<std::shared_ptr<SomeipEventDeployment>> eventDeployments;
    std::vector<std::shared_ptr<SomeipFieldDeployment>> fieldDeployments;
    std::vector<std::shared_ptr<SomeipEventGroup>> eventGroups;
    std::shared_ptr<SomeipServiceInstanceToMachineMapping> machineMapping = nullptr;
    std::shared_ptr<SomeipSdConfig> sdConfig = nullptr;
    std::vector<std::shared_ptr<End2EndEventProtectionProps>> e2eEventProtectionProps;
    std::shared_ptr<ApSomeipTransformationProps> apSomeipTransformationProps = std::make_shared<ApSomeipTransformationProps>();
};

class Manifest
{
    Manifest();
    virtual ~Manifest();
    
public:    
    static Manifest* GetInstance();
    std::shared_ptr<SomeipServiceInterfaceDeployment> getSomeipDeployment(std::string serviceName, uint16_t instanceId, bool provided);
    std::map<std::string, std::shared_ptr<SomeipServiceInterfaceDeployment>> getAllSomeipDeployment();
    
    bool parse(std::string file);
};

} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_MANIFEST_H_
