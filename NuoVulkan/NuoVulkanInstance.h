//
//  NuoVulkanInstance.hpp
//  Cube-macOS
//
//  Created by middleware on 5/21/18.
//

#ifndef NuoVulkanInstance_hpp
#define NuoVulkanInstance_hpp


#include <string>
#include <memory>
#include <vector>

#include <vulkan/vulkan.h>


class NuoVulkanPhysicalDevice;

typedef std::shared_ptr<NuoVulkanPhysicalDevice> PNuoVulkanPhysicalDevice;
typedef std::vector<PNuoVulkanPhysicalDevice> NuoVulkanPhysicalDeviceList;


class NuoVulkanSurface;

typedef std::shared_ptr<NuoVulkanSurface> PNuoVulkanSurface;


class NuoVulkanInstance : public std::enable_shared_from_this<NuoVulkanInstance>
{
    std::string _name;
    std::vector<const char*> _extensionsDesired;
    std::vector<std::string> _extensions;
    
    VkInstance _vkInstance;
    
public:
    
    NuoVulkanInstance(const std::string& name);
    ~NuoVulkanInstance();
    
    void Initialize();
    
    NuoVulkanPhysicalDeviceList PhysicalDevices();
    PNuoVulkanSurface MakeSurface(void* view);
    
    VkInstance VulkanInstance() { return _vkInstance; }
    
};


typedef std::shared_ptr<NuoVulkanInstance> PNuoVulkanInstance;


#endif /* NuoVulkanInstance_hpp */
