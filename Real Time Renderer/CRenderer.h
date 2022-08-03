#pragma once
#include <glad/glad.h>
#include <vector>
#include <iostream>
#include "globals.h"
#include "CRenderable.h"
#include "Camera.h"

//Move the loading of opengl functions here to init. We use glad proc here so as to completely separate, windowing and rendering. Windowing is the job of the end user who 
//would be implementing this (not mine) and my job is to only render 
namespace Override
{
	class CRenderer
	{
	private:
		glm::vec3 m_screenclearcolor;

	public:
		CRenderer() : m_screenclearcolor{ glm::vec3(0.0f) } {}
		virtual ~CRenderer() {}

		virtual void drawMesh(CMesh* mesh);
		virtual void drawIndexedMesh(CMesh* mesh); //virtual funcs cant be declarations

		virtual void drawrenderable(CRenderable* renderable, Camera* camera);

		virtual void init();
		//virtual void setviewport(int width, int height); for rendering to framebuffer viewport must be equal to framebuffer size so must be overriden
		void setclearcolor(glm::vec3 color) { m_screenclearcolor = color; }

		void clearcolorbuffer();
		void clearbits();

		void drawmeshinstanced();

		void bindrendertarget();		//Needed for shadowmapping and different passes (post proc etc, and brdf etc)
		void unbindrendertarget();		//needed for shadowmapping and different passes (post proc etc, and brdf etc)



	};
}

//Implementing shadowmapping is just drawing the scene with a different shader (material). so crendererables are fine. Just cmateirals are used just shaders are diff. 
//Lightspacematrix must be made tho. Can put that in draw mesh method in derived SRenderer virtual drawmesh. 

//should create a RTRenderder (rendertarget rdnerer) or smth, that renders/handles anything that must be rendered to any framebuffer etc

//Thats why i need a rendercommand thing, so i can make passes 

//then ui can have a deferredrenderer class too