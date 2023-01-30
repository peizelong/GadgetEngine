#include <iostream>
#include <memory>
namespace GE {
	class windowSystem;
	class renderSystem;
	class Engine
	{
	public:
		Engine();
		~Engine();

		void initEngine();
		void run();
		void destroy();

	private:
		void renderTick();
		void logicalTick();

	private:
		std::shared_ptr<windowSystem> _windowSystem;
		std::shared_ptr<renderSystem> _renderSystem;

		


	};



}