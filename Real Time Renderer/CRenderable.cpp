#include "CRenderable.h"

namespace Override
{
	void CRenderable::update()
	{
		m_transform.updateTransform();

		if (m_customupdate != nullptr)
		{
			m_customupdate(this);
		}
	}

	void CRenderable::dissectObject()
	{
		std::cout << "VAO: " << m_mesh->m_buffer->getVAO() << "\n";
		std::cout << "Material Texture Diffuse: " << m_material->m_phong.diffuse.getfilename() << " || Material Texture Specular: " << m_material->m_phong.specular.getfilename() << "\n";
		std::cout << "Custom Update Function memory Address: " << &m_customupdate << "\n";
	}
}