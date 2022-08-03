#include "CRenderer.h"

namespace Override
{
	void CRenderer::init()
	{
		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
	}

	void CRenderer::drawMesh(CMesh* mesh)
	{
		mesh->bindvertexarray();
		glDrawArrays(GL_TRIANGLES, 0, mesh->vertexcount()); //glint first is which is the first attrib aray (its 0 as position is in 0) and glint count is the nuimber of vertices we wanna draw
	}

	void CRenderer::drawIndexedMesh(CMesh* mesh)
	{
		mesh->bindvertexarray();
		mesh->bindelementbuffer();
		glDrawElements(GL_TRIANGLES, mesh->m_indices.size() , GL_UNSIGNED_INT, 0); //the final 0 defines an offset value after which indices are stored, this is when i store indices too in vertex buffer array 
	}

	void CRenderer::drawrenderable(CRenderable* renderable, Camera* camera)
	{
		switch (renderable->m_type)
		{
		case Globals::RENDERABLE_COMMON:
		{
			renderable->getmaterial()->applymaterial();

			renderable->getmaterial()->m_shader->setMatrix4("modelmatrix", renderable->m_transform.getTransform());	//model matrix
			renderable->getmaterial()->m_shader->setMatrix4("viewmatrix", camera->View);	//view matrix
			renderable->getmaterial()->m_shader->setMatrix4("projectionmatrix", camera->Projection);  //projection matrix

			if (renderable->getmesh()->m_indices.size() > 0)
			{
				drawIndexedMesh(renderable->getmesh());
			}
			drawMesh(renderable->getmesh());
			break;
		}

		case Globals::RENDERABLE_PARTICLE:
		{
			break;
		}

		case Globals::RENDERABLE_UI:
		{
			break;
		}

		case Globals::RENDERABLE_BACKGROUND_STATIC:	//This is if we are making a low poly game, which would not need to read lighting data from the skybox. Hacks any mesh to be a skybox.
		{
			glDepthMask(GL_FALSE);	//Disable writing to the depth buffer (to render background as first object?)
			//Background is not written in the depth buffer so its size doesnt matter (its unit sized) so its pretty small, and other renderables can easily go outside it.
			//Like a fish bowl stuck to the camera's head. But if i remove its Depth test. Itll always be there, but it must be sorted to be rendered FIRST ALWAYS!

			renderable->getmaterial()->applymaterial();

			renderable->getmaterial()->m_shader->setMatrix4("modelmatrix", glm::mat4(1.0f));	//model matrix
			renderable->getmaterial()->m_shader->setMatrix4("viewmatrix", glm::mat4(glm::mat3(camera->View)));	//view matrix
			renderable->getmaterial()->m_shader->setMatrix4("projectionmatrix", camera->Projection);  //projection matrix

			if (renderable->getmesh()->m_indices.size() > 0)
			{
				drawIndexedMesh(renderable->getmesh());
			}
			drawMesh(renderable->getmesh());
			glDepthMask(GL_TRUE);
			break;
		}

		default:
		{
			std::cout << "Invalid Renderable?" << "\n";
		}

		}

	}

	void CRenderer::clearcolorbuffer()
	{
		glClearColor(m_screenclearcolor.x, m_screenclearcolor.y, m_screenclearcolor.z, 1.0f);
	}

	void CRenderer::clearbits()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

}