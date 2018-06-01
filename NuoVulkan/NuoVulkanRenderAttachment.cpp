//
//  NuoVulkanRenderPass.cpp
//  Cube-macOS
//
//  Created by middleware on 5/24/18.
//

#include "NuoVulkanRenderAttachment.h"
#include "NuoVulkanImageView.h"


NuoVulkanRenderAttachment::NuoVulkanRenderAttachment(const PNuoVulkanDevice& device,
                                                     NuoRenderPassAttachmentType type)
    : _device(device),
      _type(type)
{
    memset(&_vkAttachmentDescription, 0, sizeof(_vkAttachmentDescription));
}


VkAttachmentDescription& NuoVulkanRenderAttachment::VulkanDescription()
{
    VkFormat format;
    
    if (!_manageTexture)
        format = _imageView->VulkanFormat();
    
    VkSampleCountFlagBits sampleCount = VK_SAMPLE_COUNT_1_BIT;
    switch (_sampleCount)
    {
        case 2: sampleCount = VK_SAMPLE_COUNT_2_BIT; break;
        case 4: sampleCount = VK_SAMPLE_COUNT_4_BIT; break;
        case 8: sampleCount = VK_SAMPLE_COUNT_8_BIT; break;
        default: break;
    }
    
    const uint32_t* initialized = (const uint32_t*)&_vkAttachmentDescription;
    if (!(*initialized))
    {
        _vkAttachmentDescription =
        {
            .format = format,
            .flags = 0,
            .samples = sampleCount,
            .loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
            .storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
            .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
            .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
            .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
            .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
        };
        
        VkAttachmentLoadOp loadOp = _needClear ? VK_ATTACHMENT_LOAD_OP_CLEAR :
                                                 VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        VkAttachmentStoreOp storeOp = _needStore ? VK_ATTACHMENT_STORE_OP_STORE :
                                                   VK_ATTACHMENT_STORE_OP_DONT_CARE;
        
        switch (_type)
        {
            case kNuoRenderPassAttachment_Color:
                _vkAttachmentDescription.loadOp = loadOp;
                _vkAttachmentDescription.storeOp = storeOp;
                break;
            case kNuoRenderPassAttachment_Depth:
                _vkAttachmentDescription.stencilLoadOp = loadOp;
                _vkAttachmentDescription.stencilStoreOp = storeOp;
            default:
                break;
        }
    }
    
    return _vkAttachmentDescription;
}



uint32_t NuoVulkanRenderAttachment::SampleCount()
{
    return _sampleCount;
}


void NuoVulkanRenderAttachment::SetSampleCount(uint32_t count)
{
    _sampleCount = count;
}


void NuoVulkanRenderAttachment::SetNeedClear(bool clear)
{
    _needClear = clear;
}


void NuoVulkanRenderAttachment::SetNeedStore(bool store)
{
    _needStore = store;
}



void NuoVulkanRenderAttachment::SetImageView(const PNuoVulkanImageView& imageView)
{
    _manageTexture = false;
    _imageView = imageView;
}
