//
//  NuoVulkanRenderPass.hpp
//  Cube-macOS
//
//  Created by middleware on 5/24/18.
//

#ifndef NuoVulkanRenderAttachment_hpp
#define NuoVulkanRenderAttachment_hpp

#include <vulkan/vulkan.h>
#include <memory>
#include <vector>


class NuoVulkanDevice;
class NuoVulkanImageView;

typedef std::shared_ptr<NuoVulkanDevice> PNuoVulkanDevice;
typedef std::shared_ptr<NuoVulkanImageView> PNuoVulkanImageView;


enum NuoRenderPassAttachmentType
{
    kNuoRenderPassAttachment_Color,
    kNuoRenderPassAttachment_Depth,
};


class NuoVulkanRenderAttachment
{

    VkAttachmentDescription _vkAttachmentDescription;
    
    PNuoVulkanDevice _device;
    PNuoVulkanImageView _imageView;
    
    NuoRenderPassAttachmentType _type;
    
    bool _manageTexture;
    bool _needClear;
    bool _needStore;
    
    uint32_t _sampleCount;

public:
    
    NuoVulkanRenderAttachment(const PNuoVulkanDevice& device,
                              NuoRenderPassAttachmentType type);
    VkAttachmentDescription& VulkanDescription();
    
    bool ManageTexture();
    void SetManageTexture(bool manage);
    
    bool SharedTexture();
    void SetSharedtexture(bool shared);
    
    //@property (strong, nonatomic) id<MTLTexture> texture;
    //@property (assign, nonatomic) MTLPixelFormat pixelFormat;
    
    uint32_t SampleCount();
    void SetSampleCount(uint32_t count);
    
    void SetNeedResolve(bool resolve);
    void SetNeedStore(bool store);
    void SetNeedClear(bool clear);
    
    //@property (assign, nonatomic) MTLClearColor clearColor;
    
    void SetImageView(const PNuoVulkanImageView& imageView);

};


#endif /* NuoVulkanRenderPass_hpp */

