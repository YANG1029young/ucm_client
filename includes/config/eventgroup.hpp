/*
 * 	eventgroup.hpp
 *
 *  Created on: Dec 29, 2017
 *  Author: flyinsky
 *  Description:define the event group info
 */

#ifndef VSOMEIP_CFG_EVENTGROUP_HPP
#define VSOMEIP_CFG_EVENTGROUP_HPP

#include <memory>

#include <common/primitive_types.hpp>

namespace vsomeip {
namespace cfg {

struct event;

struct eventgroup {
    eventgroup_t id_;
    std::set<std::shared_ptr<event> > events_;
    std::string multicast_address_;
    uint16_t multicast_port_;
    uint8_t threshold_;
};

} // namespace cfg
} // namespace vsomeip

#endif // VSOMEIP_CFG_EVENTGROUP_HPP
