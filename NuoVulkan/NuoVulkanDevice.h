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

typedef std::shared_ptr<NuoVulkanShaderModule> PNuoVulkanShaderModule;

class NuoVulkanDevice : public std::enable_shared_from_this<NuoVulkanDevice>
{
    NuoVulkanDeviceInternal* _internal;

    NuoVulkanDevice() = delete;
    NuoVulkanDevice(NuoVulkanDeviceInternal* internal);
    
public:
    
    ~NuoVulkanDevice();
    
    PNuoVulkanShaderModule CreateShaderModule(const std::string& path);
    void DestroyShaderModule(const PNuoVulkanShaderModule& shaderModule);
    
    friend NuoVulkanPhysicalDevice;
    
};

#endif /* NuoVulkanDevice_hpp */
