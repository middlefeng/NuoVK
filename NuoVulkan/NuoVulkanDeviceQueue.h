//
//  NuoVulkanDeviceQueue.hpp
//  Cube-iOS
//
//  Created by middleware on 5/22/18.
//

#ifndef NuoVulkanDeviceQueue_hpp
#define NuoVulkanDeviceQueue_hpp


class NuoVulkanDeviceQueueInternal;
class NuoVulkanDevice;

class NuoVulkanDeviceQueue
{
    
    NuoVulkanDeviceQueueInternal* _internal;

    NuoVulkanDeviceQueue() = delete;
    NuoVulkanDeviceQueue(NuoVulkanDeviceQueueInternal* internal);
    
public:
    
    ~NuoVulkanDeviceQueue();
    
    friend NuoVulkanDevice;

};

#endif /* NuoVulkanDeviceQueue_hpp */
