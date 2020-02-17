#include "packagemanagerclient.h"

bool PackageManagerClient::FindService()
{
    std::unique_ptr<ara::ucm::pkgmgr::proxy::PackageManagementProxy> ucm_proxy;
    std::string g_instanceId = "828";
    ara::com::InstanceIdentifier instance(g_instanceId);
    ara::com::ServiceHandleContainer<ara::ucm::pkgmgr::proxy::PackageManagementProxy::HandleType> handles = ara::ucm::pkgmgr::proxy::PackageManagementProxy::FindService(instance);

    if (handles.size() > 0){
        logger().LogInfo() << "FindService OK";
        ucm_proxy = std::make_unique<ara::ucm::pkgmgr::proxy::PackageManagementProxy>(handles[0]);
    }else{
        logger().LogError() << "FindService Fail,call StartFindService";
        std::shared_ptr<ara::core::Promise<bool>> find_promise = std::make_shared<ara::core::Promise<bool>>();
        ara::core::Future<bool> f = find_promise->get_future();
        ara::com::FindServiceHandle handle = ara::ucm::pkgmgr::proxy::PackageManagementProxy::StartFindService(
            [find_promise, &ucm_proxy]
            (ara::com::ServiceHandleContainer<ara::ucm::pkgmgr::proxy::PackageManagementProxy::HandleType> container)	{
                if (!ucm_proxy){
                ucm_proxy = std::make_unique<ara::ucm::pkgmgr::proxy::PackageManagementProxy>(container[0]);
                    try{
                        find_promise->set_value(true);
                    }
                    catch (std::exception &e){
                        std::cout << e.what() << std::endl;
                    }
                }
            }, instance);

        logger().LogInfo()<< "wait for the Service is found";
        f.get();
        ara::ucm::pkgmgr::proxy::PackageManagementProxy::StopFindService(handle);
        logger().LogInfo() << "the Service is found";
    }
    if(ucm_proxy){
        mProxy = std::move(ucm_proxy);
    }
    return true;
}
