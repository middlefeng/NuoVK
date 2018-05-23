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

class NuoVulkanDevice;

class NuoVulkanShaderModuleInternal;

typedef std::shared_ptr<NuoVulkanDevice> PNuoVulkanDevice;


class NuoVulkanShaderModule : public std::enable_shared_from_this<NuoVulkanShaderModule>
{

    NuoVulkanShaderModuleInternal* _internal;
    NuoVulkanShaderModule(const PNuoVulkanDevice& device,
                          uint8_t* pCode, size_t pCodeSize,
                          NuoVulkanShaderModuleInternal* internal);
    
    uint8_t* _pCode;
    size_t _pCodeSize;
    
    PNuoVulkanDevice _device;

public:

    ~NuoVulkanShaderModule();
    
    friend NuoVulkanDevice;
    
};

#endif /* NuoVulkanShaderModule_hpp */
