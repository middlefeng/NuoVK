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

class NuoVulkanDevice;
class NuoVulkanSurface;

typedef std::shared_ptr<NuoVulkanDevice> PNuoVulkanDevice;
typedef std::shared_ptr<NuoVulkanSurface> PNuoVulkanSurface;


class NuoVulkanPhysicalDevice
{

private:
    
    std::shared_ptr<NuoVulkanInstance> _instance;
    
    NuoVulkanPhysicalDeviceInternal* _internal;
    NuoVulkanPhysicalDeviceProperties* _properties;
    
    std::vector<std::string> _extensions;
    std::vector<const char*> _extensionsDesired;
    
    NuoVulkanPhysicalDevice() = delete;
    NuoVulkanPhysicalDevice(const std::shared_ptr<NuoVulkanInstance>& instance,
                            NuoVulkanPhysicalDeviceInternal* internal);
    
    void CacheProperties();
    void CacheQueueFamilyProperties();
    void QueryExtensions();

public:
    
    ~NuoVulkanPhysicalDevice();
    
    const char* Name();
    PNuoVulkanDevice CreateDevice(const PNuoVulkanSurface& surface);
    
    uint32_t QueueFamiliesCount();
    bool QueueFamilySupportGraphics(uint32_t index);
    bool QueueFamilySupportPresent(uint32_t index, const PNuoVulkanSurface& surface);
    
    friend NuoVulkanInstance;

};

#endif /* NuoVulkanPhysicalDevice_hpp */
