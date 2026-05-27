#include "ri_renderer.h"
#include <stddef.h>
#include <stdio.h>
#include <vulkan/vk_platform.h>
#include <vulkan/vulkan_core.h>

void ri_renderer_create_commands(RI_Renderer *r) {
    VkCommandPoolCreateInfo pi = {0};
    pi.sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    pi.flags            = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    pi.queueFamilyIndex = find_queue_family_indices(&r->core).graphics_family;

    if (vkCreateCommandPool(r->core.device, &pi, NULL, &r->commands.command_pool) != VK_SUCCESS) {
        printf("Failed to create command pool.\n");
        return;
    }

    printf("Command pool created.\n");


    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        VkCommandBufferAllocateInfo cmd = {0};
        cmd.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        cmd.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        cmd.commandPool        = r->commands.command_pool;
        cmd.commandBufferCount = 1;

        if (vkAllocateCommandBuffers(r->core.device, &cmd, &(r->commands.command_buffers[i])) != VK_SUCCESS) {
            printf("Failed to allocate command buffer #%zu\n", i);
            return;
        }

        printf("Command buffer #%zu allocated.\n", i);
    }
}





