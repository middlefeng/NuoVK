//
//  NuoVulkanDevice.hpp
//  Cube-iOS
//
//  Created by middleware on 5/22/18.
//

#ifndef NuoVulkanDevice_hpp
#define NuoVulkanDevice_hpp


#include <memory>


class NuoVulkanPhysicalDevice;
class NuoVulkanShaderModule;
class NuoVulkanDeviceInternal;
class NuoVulkanDeviceQueue;

typedef std::shared_ptr<NuoVulkanShaderModule> PNuoVulkanShaderModule;
typedef std::shared_ptr<NuoVulkanDeviceQueue> PNuoVulkanDeviceQueue;
typedef std::shared_ptr<NuoVulkanPhysicalDevice> PNuoVulkanPhysicalDevice;

class NuoVulkanDevice : public std::enable_shared_from_this<NuoVulkanDevice>
{
    NuoVulkanDeviceInternal* _internal;
    PNuoVulkanPhysicalDevice _physicalDevice;
    
    // the index of the queue in the physical device for which this logic
    // device is created
    //
    uint32_t _queueIndex;

    NuoVulkanDevice() = delete;
    NuoVulkanDevice(const PNuoVulkanPhysicalDevice& physicalDevice,
                    uint32_t queueIndex,
                    NuoVulkanDeviceInternal* internal);
    
public:
    
    ~NuoVulkanDevice();
    
    PNuoVulkanShaderModule CreateShaderModule(const std::string& path);
    void DestroyShaderModule(const PNuoVulkanShaderModule& shaderModule);
    
    PNuoVulkanDeviceQueue DeviceQueue();
    
    friend NuoVulkanPhysicalDevice;
    
};

#endif /* NuoVulkanDevice_hpp */
