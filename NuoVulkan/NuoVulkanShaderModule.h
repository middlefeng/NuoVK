//
//  NuoVulkanShaderModule.hpp
//  Cube-iOS
//
//  Created by middleware on 5/22/18.
//

#ifndef NuoVulkanShaderModule_hpp
#define NuoVulkanShaderModule_hpp

#include <vector>
#include <string>
#include <vulkan/vulkan.h>

class NuoVulkanDevice;

typedef std::shared_ptr<NuoVulkanDevice> PNuoVulkanDevice;


class NuoVulkanShaderModule : public std::enable_shared_from_this<NuoVulkanShaderModule>
{
    
    VkShaderModule _vkShaderModule;
    std::vector<uint32_t> _pCode;
    
    PNuoVulkanDevice _device;

public:

    NuoVulkanShaderModule(const PNuoVulkanDevice& device,
                          const std::string& path);
    ~NuoVulkanShaderModule();
    
};

#endif /* NuoVulkanShaderModule_hpp */
