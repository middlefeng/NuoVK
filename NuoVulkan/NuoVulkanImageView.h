//
//  NuoVulkanImageView.hpp
//  Cube-macOS
//
//  Created by middleware on 5/23/18.
//

#ifndef NuoVulkanImageView_hpp
#define NuoVulkanImageView_hpp

#include <vulkan/vulkan.h>
#include <memory>



class NuoVulkanDevice;

typedef std::shared_ptr<NuoVulkanDevice> PNuoVulkanDevice;


class NuoVulkanImageView
{

    VkImageView _vkImageView;
    VkFormat _vkFormat;
    
    PNuoVulkanDevice _device;
    
public:
    
    NuoVulkanImageView(const PNuoVulkanDevice& device,
                       const VkImageViewCreateInfo& createInfo);
    ~NuoVulkanImageView();
    
    VkFormat VulkanFormat() { return _vkFormat; }

};


#endif /* NuoVulkanImageView_hpp */
