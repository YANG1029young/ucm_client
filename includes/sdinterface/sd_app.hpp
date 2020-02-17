/*
 *  sd_app.hpp
 *
 *  Created on: Dec 29, 2017
 *  Author: flyinsky
 *  Description: init,start,stop SOME/IP-SD,and the same time
 *  will provide registration function.
 */

#ifndef SD_APP_HPP_
#define SD_APP_HPP_

#include <memory>
#include <vector>
#include <common/handler.hpp>
#include <common/constants.hpp>
#include <config/event.hpp>
#include <config/eventgroup.hpp>
#include "sd_config.hpp"

namespace vsomeip
{
class message;
class payload;
namespace cfg
{
struct sd_config;
}
class sd_app {
public:
    virtual ~sd_app() {}

    /*init sd and routing data*/
    virtual bool init() = 0;

    /*start sd and create thread*/
    virtual void start() = 0;

    /*stop sd*/
    virtual void stop() = 0;

    /*register the handler*/
	virtual void register_state_handler(state_handler_t _handler) = 0;
	virtual void unregister_state_handler() = 0;

	virtual void register_availability_handler(service_t _service,
	            instance_t _instance, availability_handler_t _handler,
	            major_version_t _major = DEFAULT_MAJOR, minor_version_t _minor = DEFAULT_MINOR) = 0;
	virtual void unregister_availability_handler(service_t _service,
	            instance_t _instance,
	            major_version_t _major = DEFAULT_MAJOR, minor_version_t _minor = DEFAULT_MINOR) = 0;

	virtual void register_message_handler(service_t _service,
            instance_t _instance, method_t _method,
            message_handler_t _handler) = 0;

	virtual void unregister_message_handler(service_t _service,
            instance_t _instance, method_t _method) = 0;

	/* Register handler for subscription errors */
	virtual void register_subscription_error_handler(service_t _service,
	            instance_t _instance, eventgroup_t _eventgroup,
	            error_handler_t _handler) = 0;
	virtual void unregister_subscription_error_handler(service_t _service,
	                instance_t _instance, eventgroup_t _eventgroup) = 0;

	/* Registers a subscription handler. */
	virtual void register_subscription_handler(service_t _service,
	            instance_t _instance, eventgroup_t _eventgroup,
	            subscription_handler_t _handler) = 0;
	virtual void unregister_subscription_handler(service_t _service,
	                instance_t _instance, eventgroup_t _eventgroup) = 0;

	/* Registers a subscription status listener */
	virtual void register_subscription_status_handler(service_t _service,
	            instance_t _instance, eventgroup_t _eventgroup, event_t _event,
	            subscription_status_handler_t _handler) = 0;

	/*clear all handler registered*/
	virtual void clear_all_handler() = 0;


	/*find the service intresting */
	virtual void request_service(service_t _service, instance_t _instance,
	            major_version_t _major = ANY_MAJOR,
	            minor_version_t _minor = ANY_MINOR,
	            bool _use_exclusive_proxy = false) = 0;

	virtual void release_service(service_t _service, instance_t _instance) = 0;

	/* Registers the application as user of an event or field.
	 * A user application must call this method before being able to receive
	 * event or field data. The method registers the event or field at the
	 * routing component.
	 * */
	virtual void request_event(service_t _service, instance_t _instance,
	            event_t _event, const std::set<eventgroup_t> &_eventgroups,
	            bool _is_field) = 0;
	virtual void release_event(service_t _service, instance_t _instance,
	            event_t _event) = 0;

	/* register service,and make it visible to other clients
	 * To offer a service to the external network, the configuration must
     * contain a port for the offered service instance
	 * */
	virtual void offer_service(service_t _service, instance_t _instance,
	            major_version_t _major = DEFAULT_MAJOR, minor_version_t _minor =
	                    DEFAULT_MINOR) = 0;

	virtual void stop_offer_service(service_t _service, instance_t _instance,
	            major_version_t _major = DEFAULT_MAJOR, minor_version_t _minor =
	                    DEFAULT_MINOR) = 0;

	/* Offers a SOME/IP event or field
	 * A user application must call this method for each event/field it wants
	 * to offer. The event is registered at the vsomeip routing component that
	 * enables other applications to subscribe to the event/field as well as
	 * to get and set the field value.
	 * */
	virtual void offer_event(service_t _service,
	            instance_t _instance, event_t _event,
	            const std::set<eventgroup_t> &_eventgroups,
	            bool _is_field) = 0;
	virtual void stop_offer_event(service_t _service,
	            instance_t _instance, event_t _event) = 0;

	/* Subscribes to an eventgroup
	 * A user application must call this function to subscribe to an eventgroup.
	 * Before calling subscribe it must register all events it interested in by
	 * calls to @ref request_event. The method additionally allows to specify
	 * a specific event. If a specific event is specified, all other events of
	 * the eventgroup are not received by the application.
	 * */
	virtual void subscribe(service_t _service, instance_t _instance,
	            eventgroup_t _eventgroup, major_version_t _major = DEFAULT_MAJOR,
	            subscription_type_e _subscription_type = subscription_type_e::SU_PREFER_RELIABLE,
	            event_t _event = ANY_EVENT) = 0;

	/* unsubscribe all events in eventgroup */
	virtual void unsubscribe(service_t _service, instance_t _instance,
	            eventgroup_t _eventgroup) = 0;	

	virtual void notify(service_t _service, instance_t _instance,
                event_t _event, std::shared_ptr<payload> _payload) const = 0;

	virtual void notify_one(service_t _service, instance_t _instance,
                event_t _event, std::shared_ptr<payload> _payload,
                client_t _client) const = 0;

    /*
         * Retrieve for the availability of a service instance.
         **/
	virtual bool is_available(service_t _service, instance_t _instance,
            major_version_t _major = DEFAULT_MAJOR, minor_version_t _minor = DEFAULT_MINOR) const = 0;

    /**
     *
     * \brief Sends a message.
     *
     * Serializes the specified message object, determines the taget and sends
     * the message to the target. For requests, the request identifier is
     * automatically built from the client identifier and the session
     * identifier.
     *
     * \param _message Message object.
     * \param _flush If set to true, the message is immediately sent. Otherwise
     * the message might be deferred and sent together with other messages.
     *
     */
	virtual void send(std::shared_ptr<message> _message, bool _flush = true) = 0;

	/**
     *
     * \brief Constructs an empty message object.
     *
     * The message can then be used to call @application::send to send a
     * SOME/IP message. The user application is responsible for setting
     * the message type, the service instance and the message payload
     * after this call and before calling @application::send.
     *
     * \param _reliable Determines whether this message shall be sent
     * over a reliable connection (TCP) or not (UDP).
     *
     */
    virtual std::shared_ptr<message> create_message(
            bool _reliable = false) const = 0;

	/**
     *
     * \brief Constructs an empty request message.
     *
     * The message can then be used to call @ref application::send to send a
     * SOME/IP message. The message type is set to REQUEST after the
     * call and the request identifier is automatically set during the
     * @ref application::send call.
     *
     * The user application is responsible for setting the service instance
     * and the payload.
     *
     * \param _reliable Determines whether this message shall be sent
     * over a reliable connection (TCP) or not (UDP).
     *
     */
    virtual std::shared_ptr<message> create_request(
            bool _reliable = false) const = 0;

	/*
     * \brief Constructs an empty response message from a given request
     * message.
     *
     * The message can then be used to call @ref application::send to send a
     * SOME/IP message. The message type is set to RESPONSE after the
     * call and the request identifier is automatically set from the
     * request message.
     *
     * The user application is responsible for setting the service instance
     * and the payload.
     *
     * \param _request The request message that shall be answered by
     * the response message.
     *
     */
    virtual std::shared_ptr<message> create_response(
            const std::shared_ptr<message> &_request) const = 0;

	/**
     *
     * \brief Creates an empty notification message.
     *
     * The message can then be used to call @ref application::send to send a
     * SOME/IP message. The message type is set to NOTIFICATION after the
     * call.
     *
     * The user application is responsible for setting the service instance
     * and the payload.
     *
     * \param _reliable Determines whether this message shall be sent
     * over a reliable connection (TCP) or not (UDP).
     *
     * Note: Creating notification messages and sending them using
     * @ref application::send is possible but not the standard way of sending
     * notification with vsomeip. The standard way is calling
     * @ref application::offer_event and setting the value using the
     * @ref application::notify / @ref application::notify_one methods.
     *
     */
    virtual std::shared_ptr<message> create_notification(
            bool _reliable = false) const = 0;

	/**
     *
     * \brief Creates a payload object filled with the given data.
     *
     * \param _data Bytes to be copied into the payload object.
     *
     */
    virtual std::shared_ptr<payload> create_payload(
            const std::vector<byte_t> &_data) const = 0;

	virtual bool set_configuration(const std::string cfgFilePath) = 0;

	/**
     *
     * \brief set the sd configuration.
     *
     * \param config_ sd_config data.
     *
     */
     virtual void set_sd_config(const std::shared_ptr<cfg::sd_config> config_) = 0;

	/*******************add the following interface***********************************/

	/**
     *
     * \brief add the events to service.
     *
     * This interface will override the events of service.
     * Note: this interface shall be called afer set_sd_config and set_configuration and before init().
     *
     */
     virtual void add_events(service_t _service,
            instance_t _instance, const std::map<event_t, std::shared_ptr<cfg::event> >& _events) = 0;

	/**
     *
     * \brief add the event to service.
     *
     * if the event id exists and will modify the event data.otherwise will add the event to service.
     * if call add_events after this interface and the event will be override.
     * Note: this interface shall be called afer set_sd_config and set_configuration and before init().
     *
     */
     virtual void add_event(service_t _service,
            instance_t _instance, event_t _event, bool _is_field, bool _is_reliable) = 0;

	/**
     *
     * \brief add the eventgroups to service.
     *
     * This interface will override the eventgroup of service.
     * Note: this interface shall be called afer set_sd_config and set_configuration and before init().
     *
     */
	 virtual void add_eventgroups(service_t _service,
            instance_t _instance, const std::map<eventgroup_t, std::shared_ptr<cfg::eventgroup> >& _eventgroups)= 0;

	 /**
     *
     * \brief set the multicast IP and port of service.
     *
     * Only after the multicast IP and multicast port of service are set, and multicast IP and multicast port of eventgroup 
     * is valid.because that the multicast IP and multicast port of eventgroup will copy from the service.
     * Note: this interface shall be called afer set_sd_config and set_configuration and before init().
     *
     */
     virtual void set_service_multicast(service_t _service,
            instance_t _instance, std::string _multicast_addr, uint16_t _multicast_port) = 0;

	/**
     *
     * \brief set the multicast IP and port of eventgroup.
     *
     * If _enable is true,will copy the multicast IP and multicast port from service.
     * Note: this interface shall be called afer set_sd_config and set_configuration and before init().
     *
     */
     virtual void enable_eventgroup_multicast(service_t _service,
            instance_t _instance, eventgroup_t _eventgroup, bool _enable) = 0;

	/**
     *
     * \brief set the threshold value of eventgroup.
     *
     * Note: this interface shall be called afer set_sd_config and set_configuration and before init().
     *
     */
	 virtual void set_eventgroup_threshold(service_t _service,
        instance_t _instance, eventgroup_t _eventgroup, uint8_t threshold_) = 0;

	/* unsubscribe the specific event in eventgroup */
	 virtual void unsubscribe(service_t _service, instance_t _instance,
	            eventgroup_t _eventgroup, event_t _event) = 0;
	
};

}

#endif /* SD_APP_HPP_ */
