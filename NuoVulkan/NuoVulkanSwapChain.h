//
//  NuoVulkanSwapChain.hpp
//  Cube-macOS
//
//  Created by middleware on 5/22/18.
//

#ifndef NuoVulkanSwapChain_hpp
#define NuoVulkanSwapChain_hpp


#include <vulkan/vulkan.h>
#include <memory>


class NuoVulkanDevice;


typedef std::shared_ptr<NuoVulkanDevice> PNuoVulkanDevice;



class NuoVulkanSwapChain
{
    PNuoVulkanDevice _device;
    
    VkSwapchainKHR _swapChain;

public:
    
    NuoVulkanSwapChain(const PNuoVulkanDevice& device,
                       const VkSwapchainCreateInfoKHR& createInfo);
    ~NuoVulkanSwapChain();
    
    VkSwapchainKHR VulaknSwapchain() { return _swapChain; }
    
};


#endif /* NuoVulkanSwapChain_hpp */
