#ifndef STATESWITCHER_H
#define STATESWITCHER_H

#include <ara/exec/executionclient_proxy.h>
#include <ara/exec/stateclient_proxy.h>
#include <unistd.h>
#include <iostream>
#include <signal.h>
#include <sstream>
#include <unistd.h>

#define debug0 1
#define debug1 1
enum class updatestate:bool{updating = 0, ready = 1};
using namespace std;
/* class StateSwitcher{
public:
    void FindEM(void);
    int StateSwitch(const char * state_switch, updatestate *UD_STATE);
private:
    ara::exec::proxy::StateClientProxy *g_stateClientProxy = NULL;
    void State_Switch(const char *state_switch);
};

void StateSwitcher::FindEM(void)
{
	std::cout << "get EM Service" << std::endl;
    ara::com::InstanceIdentifier instance("1");
    ara::com::ServiceHandleContainer<ara::exec::proxy::StateClientProxy::HandleType> stateClientHandles = ara::exec::proxy::StateClientProxy::FindService(instance);

    if (stateClientHandles.size() > 0)
    {
	std::cout << "Find EM stateClient Service OK" << std::endl;
	g_stateClientProxy = new ara::exec::proxy::StateClientProxy(stateClientHandles[0]);
	g_stateClientProxy->StateChangeEvent.SetReceiveHandler([](){
		g_stateClientProxy->StateChangeEvent.Update();

		ara::com::SampleContainer<ara::com::SamplePtr<const ::ara::exec::StateChange>> samples = g_stateClientProxy->StateChangeEvent.GetCachedSamples();

		ara::exec::StateChange stateChange;
                if ( samples.size() > 0)
                {
                    stateChange = *samples[0];
		    //stateMgrServerInstance->ReceiveStateChangeEvent(stateChange);
                }
		std::cout << std::endl;
	});
 	g_stateClientProxy->StateChangeEvent.SetSubscriptionStateChangeHandler([](ara::com::SubscriptionState state){
		std::cout << "StateChangeEvent Subscription State = " << (int)state << std::endl;
	});
	g_stateClientProxy->StateChangeEvent.Subscribe(ara::com::EventCacheUpdatePolicy::kLastN, 1); 
    }
    else
    {
	std::cout << "Find EM stateClient Service Fail, call StartFindService" << std::endl;
	std::shared_ptr<ara::core::Promise<bool>> find_promise = std::make_shared<ara::core::Promise<bool>>();
	ara::core::Future<bool> f = find_promise->get_future();
	ara::com::FindServiceHandle handle = ara::exec::proxy::StateClientProxy::StartFindService(
		[find_promise](ara::com::ServiceHandleContainer<ara::exec::proxy::StateClientProxy::HandleType> container){					
		if (!g_stateClientProxy)
		{
			g_stateClientProxy = new ara::exec::proxy::StateClientProxy(container[0]);

			g_stateClientProxy->StateChangeEvent.SetReceiveHandler([](){
				g_stateClientProxy->StateChangeEvent.Update();

				ara::com::SampleContainer<ara::com::SamplePtr<const ::ara::exec::StateChange>> samples = g_stateClientProxy->StateChangeEvent.GetCachedSamples();

				ara::exec::StateChange stateChange;
				if ( samples.size() > 0)
				{
				    stateChange = *samples[0];
				    //stateMgrServerInstance->ReceiveStateChangeEvent(stateChange);
				}
				std::cout << std::endl;
			});
			g_stateClientProxy->StateChangeEvent.SetSubscriptionStateChangeHandler([](ara::com::SubscriptionState state){
				std::cout << "StateChangeEvent Subscription State = " << (int)state << std::endl;
			});
			g_stateClientProxy->StateChangeEvent.Subscribe(ara::com::EventCacheUpdatePolicy::kLastN, 1);

			try
			{
				find_promise->set_value(true);
			}
			catch (std::exception &e)
			{
				std::cout << e.what() << std::endl;
			}
		}
	}, instance);

	std::cout << "wait for the EM stateClient Service is found" << std::endl;
	f.get();
	ara::exec::proxy::StateClientProxy::StopFindService(handle);
	std::cout << "the EM stateClient Service is found" << std::endl;
    } 
}


void StateSwitcher::State_Switch(const char *state_switch)
{
	::ara::exec::SetStateRequest setReq;

	setReq.changes.emplace_back(ara::exec::StateChange{"", state_switch});
	ara::exec::StateClient::SetStateOutput setOutput = g_stateClientProxy->SetState(setReq).get();
}


int StateSwitcher::StateSwitch(const char * state_switch, updatestate *UD_STATE){
#if debug0
        try{
            State_Switch(state_switch);
        }

        catch(std::exception &e){
            std::cout << e.what() << endl;
            cout << "state switch to "<< state_switch << " failed " << endl;
            return -1;
        }
#if debug1		
		if (!strcmp(state_switch, "Update")){
			*UD_STATE = updatestate::updating;
		}
		else if(!strcmp(state_switch, "Running")){
			*UD_STATE = updatestate::ready;
		}
		else {}
#endif			
        cout << "state switch to "<< state_switch << " success " << endl;
#endif
        return 0;
    } */


ara::exec::proxy::StateClientProxy *g_stateClientProxy = NULL;
int FindEM()
{
	std::cout << "get EM Service" << std::endl;
    ara::com::InstanceIdentifier instance("1");
    ara::com::ServiceHandleContainer<ara::exec::proxy::StateClientProxy::HandleType> stateClientHandles = ara::exec::proxy::StateClientProxy::FindService(instance);

    if (stateClientHandles.size() > 0)
    {
	std::cout << "Find EM stateClient Service OK" << std::endl;
	g_stateClientProxy = new ara::exec::proxy::StateClientProxy(stateClientHandles[0]);
	g_stateClientProxy->StateChangeEvent.SetReceiveHandler([](){
		g_stateClientProxy->StateChangeEvent.Update();

		ara::com::SampleContainer<ara::com::SamplePtr<const ::ara::exec::StateChange>> samples = g_stateClientProxy->StateChangeEvent.GetCachedSamples();

		ara::exec::StateChange stateChange;
                if ( samples.size() > 0)
                {
                    stateChange = *samples[0];
		    //stateMgrServerInstance->ReceiveStateChangeEvent(stateChange);
                }
		std::cout << std::endl;
	});
 	g_stateClientProxy->StateChangeEvent.SetSubscriptionStateChangeHandler([](ara::com::SubscriptionState state){
		std::cout << "StateChangeEvent Subscription State = " << (int)state << std::endl;
	});
	g_stateClientProxy->StateChangeEvent.Subscribe(ara::com::EventCacheUpdatePolicy::kLastN, 1); 
    }
    else
    {
		cout<<"find EM service fail"<<endl;
		return -1;
	/* std::cout << "Find EM stateClient Service Fail, call StartFindService" << std::endl;
	std::shared_ptr<ara::core::Promise<bool>> find_promise = std::make_shared<ara::core::Promise<bool>>();
	ara::core::Future<bool> f = find_promise->get_future();
	ara::com::FindServiceHandle handle = ara::exec::proxy::StateClientProxy::StartFindService(
		[find_promise](ara::com::ServiceHandleContainer<ara::exec::proxy::StateClientProxy::HandleType> container){					
		if (!g_stateClientProxy)
		{
			g_stateClientProxy = new ara::exec::proxy::StateClientProxy(container[0]);

			g_stateClientProxy->StateChangeEvent.SetReceiveHandler([](){
				g_stateClientProxy->StateChangeEvent.Update();

				ara::com::SampleContainer<ara::com::SamplePtr<const ::ara::exec::StateChange>> samples = g_stateClientProxy->StateChangeEvent.GetCachedSamples();

				ara::exec::StateChange stateChange;
				if ( samples.size() > 0)
				{
				    stateChange = *samples[0];
				    //stateMgrServerInstance->ReceiveStateChangeEvent(stateChange);
				}
				std::cout << std::endl;
			});
			g_stateClientProxy->StateChangeEvent.SetSubscriptionStateChangeHandler([](ara::com::SubscriptionState state){
				std::cout << "StateChangeEvent Subscription State = " << (int)state << std::endl;
			});
			g_stateClientProxy->StateChangeEvent.Subscribe(ara::com::EventCacheUpdatePolicy::kLastN, 1);

			try
			{
				find_promise->set_value(true);
			}
			catch (std::exception &e)
			{
				std::cout << e.what() << std::endl;
			}
		}
	}, instance);

	std::cout << "wait for the EM stateClient Service is found" << std::endl;
	f.get();
	ara::exec::proxy::StateClientProxy::StopFindService(handle);
	std::cout << "the EM stateClient Service is found" << std::endl; */
    } 
	return 0;
}


void State_Switch(const char *state_switch)
{
	::ara::exec::SetStateRequest setReq;

	setReq.changes.emplace_back(ara::exec::StateChange{"", state_switch});
	ara::exec::StateClient::SetStateOutput setOutput = g_stateClientProxy->SetState(setReq).get();
}


int StateSwitch(const char * state_switch, updatestate *UD_STATE){
#if debug0
        try{
            State_Switch(state_switch);
        }

        catch(std::exception &e){
            std::cout << e.what() << endl;
            cout << "state switch to "<< state_switch << " failed " << endl;
            return -1;
        }
#if debug1		
		if (!strcmp(state_switch, "Update")){
			*UD_STATE = updatestate::updating;
		}
		else if(!strcmp(state_switch, "Running")){
			*UD_STATE = updatestate::ready;
		}
		else {}
#endif			
        cout << "state switch to "<< state_switch << " success " << endl;
#endif
        return 0;
    }



#endif // STATESWITCHER_H
