/*
 * 	service.hpp
 *
 *  Created on: Dec 29, 2017
 *  Author: flyinsky
 *  Description:define the service info
 */

#ifndef VSOMEIP_CFG_SERVICE_HPP
#define VSOMEIP_CFG_SERVICE_HPP

#include <memory>

#include <common/primitive_types.hpp>

namespace vsomeip {
namespace cfg {

struct event;
struct eventgroup;

struct service {
    service_t service_;
    instance_t instance_;

    std::string unicast_address_;

    uint16_t reliable_;
    uint16_t unreliable_;

    std::string multicast_address_;
    uint16_t multicast_port_;
	
    std::string protocol_;

    std::map<event_t, std::shared_ptr<event> > events_;
    std::map<eventgroup_t, std::shared_ptr<eventgroup> > eventgroups_;
};

} // namespace cfg
} // namespace vsomeip

#endif // VSOMEIP_CFG_SERVICE_HPP
