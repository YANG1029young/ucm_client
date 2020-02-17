#ifndef _ARA_PHM_HEALTH_CHANNELS_ucm_health_HPP
#define _ARA_PHM_HEALTH_CHANNELS_ucm_health_HPP

namespace ara {
namespace phm {
namespace health_channels {
namespace ucm_health{
enum class Checkpoints : EnumUnderlyingType {
run = 0U,

};
template <PrototypeType PrototypeId>
using HC = Identifier<1212U,PrototypeId,Checkpoints>;
using Prototype0= HC<0U>;

} // namespace ucm_health
} // namespace health_channels
} // namespace phm
} // namespace ara

#endif    // _ARA_PHM_HEALTH_CHANNELS_ucm_health_HPP
