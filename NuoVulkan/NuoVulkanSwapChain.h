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
#include <vector>


class NuoVulkanDevice;
class NuoVulkanImageView;


typedef std::shared_ptr<NuoVulkanDevice> PNuoVulkanDevice;
typedef std::shared_ptr<NuoVulkanImageView> PNuoVulkanImageView;


class NuoVulkanSwapChain
{
    PNuoVulkanDevice _device;
    
    VkSwapchainKHR _vkSwapChain;
    
    uint32_t _imageCount;
    VkFormat _imageFormat;
    
    std::vector<VkImage> _images;
    std::vector<PNuoVulkanImageView> _imageViews;
    
    void CacheSwapImages();

public:
    
    NuoVulkanSwapChain(const PNuoVulkanDevice& device,
                       const VkSwapchainCreateInfoKHR& createInfo);
    ~NuoVulkanSwapChain();
    
    VkSwapchainKHR VulaknSwapchain() { return _vkSwapChain; }
    const std::vector<PNuoVulkanImageView>& ImageViews();
    
};


#endif /* NuoVulkanSwapChain_hpp */
