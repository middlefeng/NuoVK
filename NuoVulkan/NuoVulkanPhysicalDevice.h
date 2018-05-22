//
//  NuoVulkanPhysicalDevice.hpp
//  Cube-macOS
//
//  Created by middleware on 5/21/18.
//

#ifndef NuoVulkanPhysicalDevice_hpp
#define NuoVulkanPhysicalDevice_hpp


#include "NuoVulkanInstance.h"


class NuoVulkanPhysicalDeviceInternal;
class NuoVulkanPhysicalDeviceProperties;


class NuoVulkanPhysicalDevice
{

private:
    
    std::shared_ptr<NuoVulkanInstance> _instance;
    
    NuoVulkanPhysicalDeviceInternal* _internal;
    NuoVulkanPhysicalDeviceProperties* _properties;
    
    NuoVulkanPhysicalDevice() = delete;
    NuoVulkanPhysicalDevice(const std::shared_ptr<NuoVulkanInstance>& instance,
                            NuoVulkanPhysicalDeviceInternal* internal);
    
    void CacheProperties();

public:
    
    ~NuoVulkanPhysicalDevice();
    
    const char* Name();
    
    friend NuoVulkanInstance;

};

#endif /* NuoVulkanPhysicalDevice_hpp */
