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
class NuoVulkanFence;
class NuoVulkanSemaphore;
class NuoVulkanDeviceQueue;


typedef std::shared_ptr<NuoVulkanDevice> PNuoVulkanDevice;
typedef std::shared_ptr<NuoVulkanImageView> PNuoVulkanImageView;
typedef std::shared_ptr<NuoVulkanFence> PNuoVulkanFence;
typedef std::shared_ptr<NuoVulkanSemaphore> PNuoVulkanSemaphore;
typedef std::shared_ptr<NuoVulkanDeviceQueue> PNuoVulkanDeviceQueue;


class NuoVulkanSwapChain
{
    PNuoVulkanDevice _device;
    
    VkSwapchainKHR _vkSwapChain;
    
    uint32_t _imageCount;
    VkFormat _imageFormat;
    
    uint32_t _currentIndex;
    uint32_t _currentImageIndex;
    
    std::vector<VkImage> _images;
    std::vector<PNuoVulkanImageView> _imageViews;
    
    std::vector<PNuoVulkanFence> _fence;
    std::vector<PNuoVulkanSemaphore> _sempaphoresDrawComplete;
    std::vector<PNuoVulkanSemaphore> _sempaphoresImageAcquire;
    
    void CacheSwapImages();
    void CreateSemaphores();

public:
    
    NuoVulkanSwapChain(const PNuoVulkanDevice& device,
                       const VkSwapchainCreateInfoKHR& createInfo);
    ~NuoVulkanSwapChain();
    
    VkSwapchainKHR VulaknSwapchain() { return _vkSwapChain; }
    const std::vector<PNuoVulkanImageView>& ImageViews();
    
    const PNuoVulkanImageView& NextDrawableIndex();
    uint32_t CurrentFrameIndex() { return _currentIndex; }
    void Present(const PNuoVulkanDeviceQueue& queue);
    
};


#endif /* NuoVulkanSwapChain_hpp */
