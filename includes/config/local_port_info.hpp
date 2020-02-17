/*
 * 	local_port_info.hpp
 *
 *  Created on: May 8, 2019
 *  Author: flyinsky
 *  Description:define the local port of service
 */

#ifndef LOCAL_PORT_INFO_HPP
#define LOCAL_PORT_INFO_HPP

#include <common/primitive_types.hpp>

namespace vsomeip {
namespace cfg {

struct local_port {
    service_t service_;
    instance_t instance_;

    uint16_t reliable_;
    uint16_t unreliable_;
};

} // namespace cfg
} // namespace vsomeip

#endif // LOCAL_PORT_INFO_HPP

