/*
 * 	sd_option.hpp
 *
 *  Created on: May 23, 2019
 *  Author: flyinsky
 *  Description:define the configuration accoring to service id and instance id.
 */

#ifndef SD_OPTION_HPP
#define SD_OPTION_HPP

#include <common/primitive_types.hpp>

namespace vsomeip {
namespace cfg {

struct sd_option {
    service_t service_;
    instance_t instance_;

    ttl_t sd_ttl_;
};

} // namespace cfg
} // namespace vsomeip

#endif // SD_OPTION_HPP


