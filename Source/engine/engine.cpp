#include "engine.h"
#include "windows/windowSystem.h"
#include "render/renderSystem.h"


namespace GE {
	Engine::Engine(){}
	Engine::~Engine(){}

	void Engine::initEngine()
	{
        _windowSystem = std::make_shared<windowSystem>();
        _windowSystem->init();


        _renderSystem = std::make_shared<renderSystem>();
        _renderSystem->init(_windowSystem);


	}

	void Engine::run()
	{
        while (_windowSystem->windowClose())
        {
			_windowSystem->windowEvent();

		    logicalTick();
		    renderTick();
        }
		_renderSystem->w();
	}

	void Engine::destroy()
	{
        _renderSystem->destory();
        _renderSystem.reset();

        _windowSystem->destory();
        _windowSystem.reset();

	

	}

	void Engine::renderTick()
	{
		_renderSystem->tick();
        



	}

	void Engine::logicalTick()
	{
	}



}