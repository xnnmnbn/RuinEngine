#include "ri_renderer.h"
#include <stdint.h>
#include <stdio.h>
#include <vulkan/vulkan_core.h>


void record_command(RI_Renderer *r, VkCommandBuffer cmd, uint32_t img_idx) {
    
    VkCommandBufferBeginInfo cbi = {0};
    cbi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    RI_Renderer_Pipeline *test = &r->pipelines.test_pipeline;

    VkClearValue clear = {0};
    clear.color.float32[0] = 0.8f;
    clear.color.float32[1] = 0.8f;
    clear.color.float32[2] = 0.8f;
    clear.color.float32[3] = 1.0f;

    vkResetCommandBuffer(cmd, 0);

    if (vkBeginCommandBuffer(cmd, &cbi) != VK_SUCCESS) {
        printf("Failed to begin command buffer #%d\n", img_idx);
        return;
    }

    VkRenderPassBeginInfo rpi = {0};
    rpi.sType             = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpi.renderPass        = r->renderpasses.present_pass;
    rpi.framebuffer       = r->swapchain.swapchain_framebuffers[img_idx];
    rpi.renderArea.offset = (VkOffset2D){ 0, 0};
    rpi.renderArea.extent = r->swapchain.swapchain_extent;
    rpi.pClearValues      = &clear;
    rpi.clearValueCount   = 1;

    VkViewport vw = (VkViewport){
        .x = 0.0f,
        .y = 0.0f,
        .width  = r->swapchain.swapchain_extent.width,
        .height = r->swapchain.swapchain_extent.height,
        .minDepth = 0.0f,
        .maxDepth = 1.0f
    };

    VkRect2D scissor = (VkRect2D){
        .extent = r->swapchain.swapchain_extent,
        .offset.x = 0,
        .offset.y = 0
    };

    vkCmdBeginRenderPass(cmd, &rpi, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(cmd, test->bind_point, test->pipeline);

    vkCmdSetViewport(cmd, 0, 1, &vw);
    vkCmdSetScissor(cmd, 0, 1, &scissor);

    vkCmdDraw(cmd, 3, 1, 0, 0);

    vkCmdEndRenderPass(cmd);

    if (vkEndCommandBuffer(cmd) != VK_SUCCESS) {
        printf("Failed to record command #%d\n", img_idx);
        return;
    }

    // printf("Command buffer recorded.\n");
}





