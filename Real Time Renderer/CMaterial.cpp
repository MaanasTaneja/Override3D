#include "CMaterial.h"

namespace Override
{

	void CMaterial::textureload_phong(const std::string& diffuse, const std::string& specular)//make mutulally exlusiove 
	{
		if (m_type != Globals::MATSPEC_PHONG)
		{
			std::cout << "Material ID : " << m_id << "Incorrect Material Specification input function!" << "\n";
			return;
		}

		m_phong.diffuse.setfiltering(GL_LINEAR);
		m_phong.diffuse.wrapping(GL_REPEAT);
		m_phong.diffuse.mipmap();

		m_phong.specular.setfiltering(GL_LINEAR);
		m_phong.specular.wrapping(GL_REPEAT);
		m_phong.specular.mipmap();


		m_phong.diffuse.rebuild(Globals::TEXTURE_2D, diffuse);
		m_phong.specular.rebuild(Globals::TEXTURE_2D, specular);
	}

	void CMaterial::textureload_pbr(const std::string& albedo, const std::string& metallic, const std::string& normal, const std::string& roughness)
	{
		if (m_type != Globals::MATSPEC_PBR)
		{
			std::cout << "Material ID : " << m_id << "Incorrect Material Specification input fucntion!" << "\n";
			return;
		}

		m_pbr.albedo.setfiltering(GL_LINEAR);
		m_pbr.albedo.wrapping(GL_REPEAT);
		m_pbr.albedo.mipmap();

		m_pbr.metallic.setfiltering(GL_LINEAR);
		m_pbr.metallic.wrapping(GL_REPEAT);
		m_pbr.metallic.mipmap();

		m_pbr.normal.setfiltering(GL_LINEAR);
		m_pbr.normal.wrapping(GL_REPEAT);
		m_pbr.normal.mipmap();

		m_pbr.roughness.setfiltering(GL_LINEAR);
		m_pbr.roughness.wrapping(GL_REPEAT);
		m_pbr.roughness.mipmap();


		m_pbr.albedo.rebuild(Globals::TEXTURE_2D, albedo);
		m_pbr.metallic.rebuild(Globals::TEXTURE_2D, metallic);
		m_pbr.normal.rebuild(Globals::TEXTURE_2D, normal);
		m_pbr.roughness.rebuild(Globals::TEXTURE_2D, roughness);
	}

	void CMaterial::applymaterial()		//Run shader and submit all textures
	{
		glUseProgram(m_shader->getshader());

		if (m_type == Globals::MATSPEC_PHONG)
		{
			glUniform1i(glGetUniformLocation(m_shader->getshader(), "diffuse"), 0);
			glUniform1i(glGetUniformLocation(m_shader->getshader(), "specular"), 1);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_phong.diffuse.getid());
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, m_phong.specular.getid());

		}

		else
		{
			std::cout << "Material Spec : PBR : render pipeline still work in progress!" << "\n";
		}

	}
}