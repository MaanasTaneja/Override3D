#include "CTexture.h"
#include <glad/glad.h>
#include "stb_image.h"

namespace Override
{

	void CTexture::generate()
	{
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapping);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapping);

		if (m_mipmapping)
		{
			if (m_filtering == GL_LINEAR)
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}
			else
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			}
		}
		else
		{
			//Implement ANISOTROPY HERE

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filtering);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filtering);
		}

		//stbi_set_flip_vertically_on_load(1);
		m_raw = stbi_load(m_filename.c_str(), &m_width, &m_height, &m_numcolorchannels, 0);
		if (m_raw)
		{
			if (m_numcolorchannels == 3)	//Means its a jpg(RGB)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_raw);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			
			else if (m_numcolorchannels == 4)	//Means its a png (RGBA)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_raw);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			
		}
		else
		{
			std::cout << "Texture Loading Failed! : " << m_filename << "\n";
		}

		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(m_raw);		

	}

}