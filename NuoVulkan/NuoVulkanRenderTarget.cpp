//
//  NuoVulkanRenderTarget.cpp
//  Cube-macOS
//
//  Created by middleware on 5/30/18.
//

#include "NuoVulkanRenderTarget.h"
#include "NuoVulkanDevice.h"
#include "NuoVulkanRenderAttachment.h"



NuoVulkanRenderTarget::NuoVulkanRenderTarget(const PNuoVulkanDevice& device)
    : _device(device)
{
    memset(&_vkRenderPass, 0, sizeof(_vkRenderPass));
}


void NuoVulkanRenderTarget::CacheRenderPass()
{
    const uint32_t* initialized = (uint32_t*)&_vkRenderPass;
    if (initialized)
        return;
    
    const uint32_t attachmentCount = _colorAttachments.size() + 1;
    VkAttachmentDescription* descriptions = new VkAttachmentDescription[attachmentCount];
    for (size_t i = 0; i < _colorAttachments.size(); ++i)
    {
        PNuoVulkanRenderAttachment& attachment = _colorAttachments[i];
        descriptions[i] = attachment->VulkanDescription();
    }
    
    descriptions[attachmentCount - 1] = _depthAttachment->VulkanDescription();
    
    const VkAttachmentReference colorReference =
    {
        .attachment = 0,
        .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
    };
    const VkAttachmentReference depthReference =
    {
        .attachment = attachmentCount - 1,
        .layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
    };
    
    const VkSubpassDescription subpass =
    {
        .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
        .flags = 0,
        .inputAttachmentCount = 0,
        .pInputAttachments = NULL,
        .colorAttachmentCount = (uint32_t)_colorAttachments.size(),
        .pColorAttachments = &colorReference,
        .pResolveAttachments = NULL,
        .pDepthStencilAttachment = &depthReference,
        .preserveAttachmentCount = 0,
        .pPreserveAttachments = NULL,
    };
    
    const VkRenderPassCreateInfo renderPassInfo =
    {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        .pNext = NULL,
        .flags = 0,
        .attachmentCount = attachmentCount,
        .pAttachments = descriptions,
        .subpassCount = 1,
        .pSubpasses = &subpass,
        .dependencyCount = 0,
        .pDependencies = NULL,
    };
    
    vkCreateRenderPass(_device->VulkanDevice(), &renderPassInfo, nullptr, &_vkRenderPass);
    
    delete[] descriptions;
}


void NuoVulkanRenderTarget::SetColorAttachment(const PNuoVulkanRenderAttachment attachment, uint32_t index)
{
    if (index < _colorAttachments.size())
    {
        _colorAttachments[index] = attachment;
    }
    else
    {
        _colorAttachments.resize(index + 1);
        _colorAttachments[index] = attachment;
    }
}


void NuoVulkanRenderTarget::SetDepthAttachment(const PNuoVulkanRenderAttachment attachment)
{
    _depthAttachment = attachment;
}


NuoVulkanRenderAttachmentList& NuoVulkanRenderTarget::ColorAttachments()
{
    return _colorAttachments;
}



const PNuoVulkanRenderAttachment& NuoVulkanRenderTarget::DepthAttachment()
{
    return _depthAttachment;
}
