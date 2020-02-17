/*
 * 	sd_config.hpp
 *
 *  Created on: Dec 29, 2017
 *  Author: xuhongchao
 *  Description:  define the someip-sd config
 */

#ifndef SD_CONFIG_HPP_
#define SD_CONFIG_HPP_

#include <memory>
#include <string>
#include <map>
#include <set>

#include <common/primitive_types.hpp>

namespace vsomeip {
namespace cfg {
struct service;
struct local_port;
struct sd_option;
struct sd_config
{
    /* the IP address of running the applicaiton */
	std::string unicast;

	/*add communication port for every service*/
	std::map<service_t, std::map<instance_t, std::shared_ptr<local_port>>>clients;

	/*add sd option according to service id and instance id */
	std::map<service_t, std::map<instance_t, std::shared_ptr<sd_option>>>sd_option_list;

	/* the routing host IP address.
	 *  if the value is set,and mean that the application meeted the following conditions is routing_host.
	 *  1. the value of routing_host is set.
	 *  2. when calling the createSD method,and the name is same as the  value of routing_host.
	 *  3. the app name is same as  value of routing_host in apps.
	 *  
	 *  In general, when value of is_sd_enabled_ is 1/true, the applicaiton is routing host.
	 **/
	std::string routing_host;

	/* set the app name and id of the applicaiton */
	std::map<std::string,uint16_t> apps;

	/* the service info.
	 *  when initializing the service,and please set the value of the some variable 
	 *  according to the following  the actions  if you don't want to set the some variable.
	 *  reliable_ = unreliable_ = ILLEGAL_PORT;
        *  unicast_address_ = "local";
        *  multicast_address_ = "";
        *  multicast_port_ = ILLEGAL_PORT;
        *  protocol_ = "someip"; 
	 **/
	std::map<service_t,
		        std::map<instance_t,
		            std::shared_ptr<service> > > services;

	/*SOME/IP-SD configuration*/
	bool is_sd_enabled_;
	std::string sd_protocol_;
	std::string sd_multicast_;
	uint16_t sd_port_;

	float sd_initial_delay_min_;
	float sd_initial_delay_max_;
	float sd_repetitions_base_delay_;
	uint8_t sd_repetitions_max_;
	/*PBP-588 2019-05-23 Del st*/
	//ttl_t sd_ttl_;
	/*PBP-588 2019-05-23 Del ed*/
	float sd_cyclic_offer_delay_;
	float sd_request_response_delay_min_;
	float sd_request_response_delay_max_;
};
}
}

#endif /* SD_CONFIG_HPP_ */
