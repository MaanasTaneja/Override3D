#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/gtx/matrix_decompose.hpp>


namespace Override
{
	class Transform
	{
	private:
		

	public:

		glm::mat4 m_transform;
		glm::mat4 m_parentTransform;


		glm::vec3 m_position;
		glm::vec3 m_scale;
		glm::vec3 m_rotation;

		Transform(float scale) : m_transform{ glm::mat4(scale) }, m_position{ glm::vec3(0.0f) }, m_scale{ glm::vec3(scale) }, m_rotation{ glm::vec3(0.0f) },
			m_parentTransform{ glm::mat4(1.0f) } {  }
		Transform() : m_transform{ glm::mat4(1.0f) }, m_position{ glm::vec3(0.0f) }, m_scale{ glm::vec3(1.0f) }, m_rotation{ glm::vec3(0.0f) },
			m_parentTransform{ glm::mat4(1.0f) } {  }	//default constructor
		~Transform() = default;

		glm::vec3 getposition() { return m_position; }
		glm::vec3 getscale() { return m_scale; }
		glm::vec3 getrotation() { return m_rotation; }

		void setParentTransform(const glm::mat4& pTrans) { m_parentTransform = pTrans; }

		void updateTransform()
		{
			m_transform = glm::mat4(1.0f);
			m_transform = glm::translate(m_transform, m_position);
			m_transform = glm::scale(m_transform, m_scale);
			m_transform = glm::rotate(m_transform, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			m_transform = glm::rotate(m_transform, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			m_transform = glm::rotate(m_transform, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

			m_transform = m_parentTransform * m_transform;
		}

		glm::mat4 getTransform()
		{
			return m_transform;
		}

		glm::mat4 getParentTransform()
		{
			return m_parentTransform;
		}

		void displayTransformation()
		{
			std::cout << "Position : " << "X: " << m_position.x << "Y: " << m_position.y << "Z: " << m_position.z << "\n";
			std::cout << "Scale: " << m_scale.x << "\n";
			std::cout <<"Rotation: " << "X: " << m_rotation.x << "Y: " << m_rotation.y << "Z: " << m_rotation.z << "\n";
		}
	};

}