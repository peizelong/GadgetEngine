#pragma once
#include <memory>
#include "RHI/vulkanRHI.h"
namespace GE {
	class windowSystem;


	class renderSystem
	{
	public:

		void init(std::shared_ptr<windowSystem> windowSystem);
		void tick();
		void w();
		void destory();
	private:
		std::shared_ptr<VulkanRHI> _RHI;
		std::shared_ptr<windowSystem> _windowSystem;
	};

}
