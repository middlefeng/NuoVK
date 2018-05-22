//
//  NuoVulkanDevice.hpp
//  Cube-iOS
//
//  Created by middleware on 5/22/18.
//

#ifndef NuoVulkanDevice_hpp
#define NuoVulkanDevice_hpp


class NuoVulkanPhysicalDevice;
class NuoVulkanDeviceInternal;

class NuoVulkanDevice
{
    NuoVulkanDeviceInternal* _internal;

    NuoVulkanDevice() = delete;
    NuoVulkanDevice(NuoVulkanDeviceInternal* internal);
    
public:
    
    ~NuoVulkanDevice();
    
    friend NuoVulkanPhysicalDevice;
    
};

#endif /* NuoVulkanDevice_hpp */
