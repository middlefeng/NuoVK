//
//  NuoVulkanRenderTarget.hpp
//  Cube-macOS
//
//  Created by middleware on 5/30/18.
//

#ifndef NuoVulkanRenderTarget_hpp
#define NuoVulkanRenderTarget_hpp

#include <vulkan/vulkan.h>
#include <memory>

#include "NuoVulkanRenderAttachment.h"


class NuoVulkanDevice;
class NuoVulkanRenderPassEncoder;

typedef std::shared_ptr<NuoVulkanDevice> PNuoVulkanDevice;
typedef std::shared_ptr<NuoVulkanRenderAttachment> PNuoVulkanRenderAttachment;
typedef std::shared_ptr<NuoVulkanRenderPassEncoder> PNuoVulkanRenderPassEncoder;

typedef std::vector<PNuoVulkanRenderAttachment> NuoVulkanRenderAttachmentList;


class NuoVulkanRenderTarget
{
    
    VkRenderPass _vkRenderPass;
    
    PNuoVulkanDevice _device;
    NuoVulkanRenderAttachmentList _colorAttachments;
    PNuoVulkanRenderAttachment _depthAttachment;
    
    void CacheRenderPass();
    
    
public:
    
    NuoVulkanRenderTarget(const PNuoVulkanDevice& device);
    
    void SetColorAttachment(const PNuoVulkanRenderAttachment attachment, uint32_t index);
    void SetDepthAttachment(const PNuoVulkanRenderAttachment attachment);
    
    NuoVulkanRenderAttachmentList& ColorAttachments();
    const PNuoVulkanRenderAttachment& DepthAttachment();
    
    //PNuoVulkanRenderPassEncoder Retain
    
};


#endif /* NuoVulkanRenderTarget_hpp */
