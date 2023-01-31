#pragma once
#include "glfw/glfw3.h"
namespace GE {
	
	class windowSystem
	{
	public:

		void init();
		
		GLFWwindow* getWindow();

		bool windowClose();
		void windowEvent();
	
		void destory();

	private:
		GLFWwindow* window;

		
	};

}
