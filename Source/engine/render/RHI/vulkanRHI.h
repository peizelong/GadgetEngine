#include <vector>
#include <set>
#include <algorithm>
#include <fstream>
#include "vulkan/vulkan.h"
#include "glfw/glfw3.h"
#include "RHIStruct.h"



namespace GE{
	class VulkanRHI 
	{
	public:
		VulkanRHI();
		~VulkanRHI();

		void init(GLFWwindow* window);

		VkShaderModule createShaderModule(const std::string& filename);
		void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	public:
		VkInstance instance{ VK_NULL_HANDLE };
		VkDebugUtilsMessengerEXT debugMessenger{ VK_NULL_HANDLE };
		VkSurfaceKHR surface{ VK_NULL_HANDLE };

		VkPhysicalDevice physicalDevice{ VK_NULL_HANDLE };
		VkDevice device{ VK_NULL_HANDLE };
		VkSwapchainKHR swapChain{ VK_NULL_HANDLE };
		VkRenderPass renderPass{ VK_NULL_HANDLE };
		VkPipelineLayout pipelineLayout{ VK_NULL_HANDLE };
		VkPipeline graphicsPipeline{ VK_NULL_HANDLE };

		VkQueue graphicsQueue{ VK_NULL_HANDLE };
		VkQueue presentQueue{ VK_NULL_HANDLE };

		std::vector<VkImage> swapChainImages;
		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;
		std::vector<VkImageView> swapChainImageViews;
		std::vector<VkFramebuffer> swapChainFramebuffers;

		VkCommandPool commandPool{ VK_NULL_HANDLE };
		VkCommandBuffer commandBuffer{ VK_NULL_HANDLE };

		VkSemaphore imageAvailableSemaphore;
		VkSemaphore renderFinishedSemaphore;
		VkFence inFlightFence;
		
	private:
		PFN_vkCreateDebugUtilsMessengerEXT CreateDebugUtilsMessengerEXT{};
		PFN_vkDestroyDebugUtilsMessengerEXT DestroyDebugUtilsMessengerEXT{};

	
	private:
		void createInstance();
		void createSurface();
		void pickPhysicalDevice();
		void createLogicalDevice();
		void createSwapChain();
		void createImageViews();

		void createGraphicsPipeline();
		void createRenderPass();
		void createFramebuffers();
		void createCommandPoolAndBuffer();

		void createSyncObjects();

		std::vector<const char*> getRequiredExtensions();
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice physicalDevice);
		bool isDeviceSuitable(VkPhysicalDevice physicalDevice);
		bool checkDeviceExtensionSupport(VkPhysicalDevice physicalDevice);
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice physicalDevice);
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& formats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> presentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
		static std::vector<char> readFile(const std::string& filename);

		void destroy();
	private:
		GLFWwindow* glfwWindow;

		bool enableValidationLayers{ true };
		const std::vector<const char*> validationLayers = {	"VK_LAYER_KHRONOS_validation"};
		const std::vector<const char*> deviceExtensions = {	VK_KHR_SWAPCHAIN_EXTENSION_NAME	};
	};


}