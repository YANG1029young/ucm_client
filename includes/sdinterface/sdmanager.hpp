/*
 *  sdmanager.hpp
 *
 *  Created on: Dec 29, 2017
 *  Author: flyinsky
 *  Description:manage the resource,runtime,start SOME/IP-SD
 */

#ifndef SDMANAGER_HPP_
#define SDMANAGER_HPP_

#include <memory>

#include "sd_config.hpp"

namespace vsomeip {
namespace cfg {
struct sd_config;
}
class sd_app;
class sdmanager {
public:
	static std::shared_ptr<sdmanager> get();

	virtual ~sdmanager() {
	}

	/*create someip-sd according to config and app name*/
	#if 0
	virtual std::shared_ptr<sd_app> createSD(const std::shared_ptr<cfg::sd_config> &config,std::string &name) = 0;
	#else
	virtual std::shared_ptr<sd_app> createSD(std::string &name) = 0;
	#endif
	/*close someip-sd and remove the app by name*/
	virtual void closeSD(std::string &name) = 0;
};
}

#endif /* SDMANAGER_HPP_ */
