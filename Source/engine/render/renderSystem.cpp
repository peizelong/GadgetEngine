#include "renderSystem.h"
#include "../windows/windowSystem.h"
namespace GE {
    void renderSystem::init(std::shared_ptr<windowSystem> windowSystem)
	{
        _windowSystem = windowSystem;
        _RHI = std::make_shared<VulkanRHI>();
        _RHI->init(windowSystem->getWindow());

	}
	void renderSystem::tick()
	{
        vkWaitForFences(_RHI->device, 1, &_RHI->inFlightFence, VK_TRUE, UINT64_MAX);
        vkResetFences(_RHI->device, 1, &_RHI->inFlightFence);

        uint32_t imageIndex;
        vkAcquireNextImageKHR(_RHI->device, _RHI->swapChain, UINT64_MAX, _RHI->imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

        vkResetCommandBuffer(_RHI->commandBuffer, /*VkCommandBufferResetFlagBits*/ 0);
        _RHI->recordCommandBuffer(_RHI->commandBuffer, imageIndex);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = { _RHI->imageAvailableSemaphore };
        VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &_RHI->commandBuffer;

        VkSemaphore signalSemaphores[] = { _RHI->renderFinishedSemaphore };
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        if (vkQueueSubmit(_RHI->graphicsQueue, 1, &submitInfo, _RHI->inFlightFence) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit draw command buffer!");
        }

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = { _RHI->swapChain };
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &imageIndex;

        vkQueuePresentKHR(_RHI->presentQueue, &presentInfo);

	}
	void renderSystem::destory()
	{

	}
}