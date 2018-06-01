/*
 * DemoViewController.m
 *
 * Copyright (c) 2014-2018 The Brenwill Workshop Ltd. (http://www.brenwill.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#define NUO_VK 1


#import "DemoViewController.h"
#import <QuartzCore/CAMetalLayer.h>

#if !NUO_VK
#include "../Demos.h"			// The LunarG Vulkan SDK demo code
#endif

#if NUO_VK
#include "NuoVulkanInstance.h"
#include "NuoVulkanPhysicalDevice.h"
#include "NuoVulkanDevice.h"
#include "NuoVulkanShaderLibrary.h"
#include "NuoVulkanDeviceQueue.h"
#include "NuoVulkanImageView.h"
#include "NuoVulkanSwapChain.h"
#include "NuoVulkanCommandBuffer.h"
#endif

#pragma mark -
#pragma mark DemoViewController

@implementation DemoViewController {
	CVDisplayLinkRef	_displayLink;
#if !NUO_VK
	struct demo demo;
#endif
}

-(void) dealloc {
#if !NUO_VK
	demo_cleanup(&demo);
#endif
	CVDisplayLinkRelease(_displayLink);
	[super dealloc];
}

-(void) viewDidLayout
{
    static int counter = 0;
#if !NUO_VK
    if (counter++ > 3)
        demo.resized = true;
#endif
}



/** Since this is a single-view app, initialize Vulkan during view loading. */
-(void) viewDidLoad {
	[super viewDidLoad];
    
#if !NUO_VK
    demo.resized = false;
#endif

	self.view.wantsLayer = YES;		// Back the view with a layer created by the makeBackingLayer method.
	const char* arg = "cube";
#if !NUO_VK
	demo_main(&demo, self.view, 1, &arg);
#endif
    
#if NUO_VK
    PNuoVulkanInstance instance = std::make_shared<NuoVulkanInstance>("Nuo");
    instance->Initialize();
    
    NuoVulkanPhysicalDeviceList devices = instance->PhysicalDevices();
    for (PNuoVulkanPhysicalDevice device : devices)
    {
        printf("Device Name. %s.\n", device->Name());
        printf("Queue families count. %u.\n", device->QueueFamiliesCount());
    }
    
    PNuoVulkanSurface surface = instance->MakeSurface(self.view);
    PNuoVulkanDevice device = devices[0]->CreateDevice(surface);
    PNuoVulkanShaderLibrary library = std::make_shared<NuoVulkanShaderLibrary>(device,
                                                                               "/Users/middleware/UserData/Source/NuoVK/Demos/Vulkan-LoaderAndValidationLayers/demos");
    PNuoVulkanShaderModule shaderVert = library->ShaderModule("cube-vert");
    PNuoVulkanShaderModule shaderFrag = library->ShaderModule("cube-frag");
    PNuoVulkanDeviceQueue queue = device->DeviceQueue();
    PNuoVulkanSwapChain swapchain = device->CreateSwapChain(nullptr);
    
    PNuoVulkanCommandBuffer commandBuffer = queue->CommandBuffer();
    
    const std::vector<PNuoVulkanImageView> imageViews = swapchain->ImageViews();
#endif

	CVDisplayLinkCreateWithActiveCGDisplays(&_displayLink);
#if !NUO_VK
	CVDisplayLinkSetOutputCallback(_displayLink, &DisplayLinkCallback, &demo);
#endif
	CVDisplayLinkStart(_displayLink);
}


#pragma mark Display loop callback function

/** Rendering loop callback function for use with a CVDisplayLink. */
static CVReturn DisplayLinkCallback(CVDisplayLinkRef displayLink,
									const CVTimeStamp* now,
									const CVTimeStamp* outputTime,
									CVOptionFlags flagsIn,
									CVOptionFlags* flagsOut,
									void* target) {
    
#if !NUO_VK
    if (((struct demo*)target)->resized)
    {
        demo_resize(((struct demo*)target));
        ((struct demo*)target)->resized = false;
    }
    
    demo_draw((struct demo*)target);
#endif
	return kCVReturnSuccess;
}

@end


#pragma mark -
#pragma mark DemoView

@implementation DemoView

/** Indicates that the view wants to draw using the backing layer instead of using drawRect:.  */
-(BOOL) wantsUpdateLayer { return YES; }

/** Returns a Metal-compatible layer. */
+(Class) layerClass { return [CAMetalLayer class]; }

/** If the wantsLayer property is set to YES, this method will be invoked to return a layer instance. */
-(CALayer*) makeBackingLayer {
	CALayer* layer = [self.class.layerClass layer];
	CGSize viewScale = [self convertSizeToBacking: CGSizeMake(1.0, 1.0)];
	layer.contentsScale = MIN(viewScale.width, viewScale.height);
	return layer;
}

@end
