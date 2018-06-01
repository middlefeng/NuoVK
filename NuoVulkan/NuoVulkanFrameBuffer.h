//
//  NuoVulkanFrameBuffer.hpp
//  Cube-macOS
//
//  Created by middleware on 5/24/18.
//

#ifndef NuoVulkanFrameBuffer_hpp
#define NuoVulkanFrameBuffer_hpp

#include <vulkan/vulkan.h>
#include <memory>



class NuoVulkanDevice;

typedef std::shared_ptr<NuoVulkanDevice> PNuoVulkanDevice;


class NuoVulkanFrameBuffer
{

public:
    
    NuoVulkanFrameBuffer();

};


#endif /* NuoVulkanFrameBuffer_hpp */
