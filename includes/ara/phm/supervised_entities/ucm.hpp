#ifndef _ARA_PHM_SUPERVISED_ENTITIES_ucm_HPP
#define _ARA_PHM_SUPERVISED_ENTITIES_ucm_HPP

namespace ara {
namespace phm {
namespace supervised_entities {
namespace ucm {
enum class Checkpoints : EnumUnderlyingType {
beaten = 0U,

};
template <PrototypeType PrototypeId>
using SE = Identifier<4321U,PrototypeId,Checkpoints>;
using Prototype0= SE<0U>;

} // namespace ucm
} // namespace supervised_entities
} // namespace phm
} // namespace ara

#endif    // _ARA_PHM_SUPERVISED_ENTITIES_ucm_HPP
