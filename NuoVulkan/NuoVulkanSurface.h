//
//  NuoVulkanSurface.hpp
//  Cube-macOS
//
//  Created by middleware on 5/22/18.
//

#ifndef NuoVulkanSurface_hpp
#define NuoVulkanSurface_hpp


#include "NuoVulkanInstance.h"

#include <memory>


class NuoVulkanSurfaceInternal;


class NuoVulkanSurface : public std::enable_shared_from_this<NuoVulkanSurface>
{
    
    NuoVulkanSurfaceInternal* _internal;
    
    NuoVulkanSurface() = delete;
    NuoVulkanSurface(const std::shared_ptr<NuoVulkanInstance>& instance,
                     NuoVulkanSurfaceInternal* internal);
    
    PNuoVulkanInstance _instance;

public:
    
    ~NuoVulkanSurface();
    
    friend NuoVulkanInstance;

};

#endif /* NuoVulkanSurface_hpp */
