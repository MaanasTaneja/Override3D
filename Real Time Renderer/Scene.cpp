#include "Scene.h"

namespace Override
{

	void Scene::addSceneNode(CRenderable* renderable)
	{
		if (renderable->m_type == Globals::RENDERABLE_BACKGROUND || renderable->m_type == Globals::RENDERABLE_BACKGROUND_STATIC)
		{
			m_backgroundlist.push_back(renderable);
		}
		else if(renderable->m_type == Globals::RENDERABLE_COMMON)
		{
			m_renderlist.push_back(renderable);
		}
	
	}

	void Scene::addSceneNode(RenderableList list)
	{
		for (auto i : list.getRenderList())
		{
			if (i->m_type == Globals::RENDERABLE_BACKGROUND || i->m_type == Globals::RENDERABLE_BACKGROUND_STATIC)
			{
				m_backgroundlist.push_back(i);
			}
			else if (i->m_type == Globals::RENDERABLE_COMMON)
			{
				m_renderlist.push_back(i);
			}
		}
	}

	void Scene::beginframe()
	{
		m_renderer->clearcolorbuffer();
		m_renderer->clearbits();
	}


	void Scene::updatescene(float dt)
	{
		m_camera->Update(dt);

		if (m_backgroundlist.size() > 0)
		{
			for (auto current : m_backgroundlist)
			{
				current->update();
			}
		}

		if (m_renderlist.size() > 0)
		{
			for (auto current : m_renderlist)
			{
				current->update();
			}
		}

		else
		{
			std::cout << "Empty Render List!" << "\n";
		}
	}

	void Scene::renderscene()
	{
		//Here I can create different passes, etc based on if we want shadows, PBR etc, custom pipelines

		for (auto back_current : m_backgroundlist)	//Backgrounds are always rendered first
		{
			m_renderer->drawrenderable(back_current, m_camera);
		}

		for (auto common_current : m_renderlist)		//opaque shadowless objects rendering loop
		{
			m_renderer->drawrenderable(common_current, m_camera);
		}
	}

	void Scene::endframe()
	{

	}
}
