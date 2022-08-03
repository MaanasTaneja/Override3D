#pragma once
#include <iostream>
#include <vector>

#include "globals.h"
#include "Camera.h"
#include "FlyCamera.h"
#include "CRenderable.h"
#include "CRenderer.h"

#include "RenderableList.h"
#include "Model.h"

#include <GLFW/glfw3.h>

//#include "DefaultMediaLibrary.h"


//Ive now planned to make this Real Time Rendering engine, independent of any winowing system, that is GLFW whatever. So that means im going to follwo Joey's footsteps 
//Just read his implementation of how to use his Cell API

//Also I need to get everything under NAMESPACES!

//I MUST DECOUPLE SCENE AND USER INPUT. USER INPUT ONLY SHOULD INTRACT WITH CAMERA CLASSES (AND THAT TOO ONLY WHEN INPUT HAPPENS ITS SENT THERE TO HANDLE, NO WINDOW STUFF CALLBACKS 
//ANYWHERE!!!


//I am alos thinking about making this scene thing a state machine, instead of using C++ I could make a C based Opengl style scene system. With
//bindScene(int scene ID). Then addrenderable() ->adds to the bound scene? Eh useless, id rather not 

namespace Override
{

	class Scene
	{
	private:
		void initializeobjects()
		{
			m_renderer = new CRenderer{};
			m_renderer->init();
			m_renderer->setclearcolor(glm::vec3(0.2f, 0.2f, 0.2f));
		}

	public:
		std::vector<CRenderable*> m_renderlist;
		//I can have different render lists, like transparent render lists which are sorted and rendered at the last
		std::vector<CRenderable*> m_backgroundlist;

		CRenderer* m_renderer;
		Camera* m_camera;

		Scene(Camera* camera) :m_camera{ camera } { initializeobjects(); }
		~Scene() = default;

		void addSceneNode(CRenderable* renderable);
		void addSceneNode(RenderableList list);
		void addSceneNode(CMesh& mesh);

		void addSceneLight();

		void beginframe();
		void updatescene(float dt);
		void renderscene();
		void endframe();

	};
}