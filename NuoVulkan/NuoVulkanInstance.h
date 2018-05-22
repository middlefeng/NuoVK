//
//  NuoVulkanInstance.hpp
//  Cube-macOS
//
//  Created by middleware on 5/21/18.
//

#ifndef NuoVulkanInstance_hpp
#define NuoVulkanInstance_hpp


#include <string>
#include <memory>
#include <vector>


class NuoVulkanInstanceInternal;

class NuoVulkanInstance
{
    std::string _name;
    std::vector<const char*> _extensionsDesired;
    std::vector<std::string> _extensions;
    
    NuoVulkanInstanceInternal* _internal;
    
public:
    
    NuoVulkanInstance(const std::string& name);
    ~NuoVulkanInstance();
    
    void Initialize();
    
};


typedef std::shared_ptr<NuoVulkanInstance> PNuoVulkanInstance;


#endif /* NuoVulkanInstance_hpp */
