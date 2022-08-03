#pragma once
#include <iostream>
#include <vector>
#include "CRenderable.h"
#include "Camera.h"

namespace Override
{
	class RenderableList
	{
	public:
		std::vector<CRenderable*> m_list;
		Transform m_listroot;

		RenderableList() : m_list{  }, m_listroot{ 1.0f } {}
		~RenderableList() = default;

		void push(CRenderable* obj) { 
			m_listroot.updateTransform();

			obj->m_transform.setParentTransform(m_listroot.getTransform());
			m_list.push_back(obj); 
		}
		void pop() { m_list.pop_back(); }
		void sortlist(glm::vec3 reference, bool farthestLast);	//function that sorts back to front, front to back based on world position and camera 
		CRenderable* findat(glm::vec3 position);				//Find renderable which lies at this position 

		void setRootTransform(const Transform& trans) { m_listroot = trans; }
		void setRootPosition(const glm::vec3& pos) { m_listroot.m_position = pos; }
		void setRootScale(const glm::vec3& scale) { m_listroot.m_scale = scale; }
		void setRootRotation(const glm::vec3& rot) { m_listroot.m_rotation = rot; }

		virtual std::vector<CRenderable*> getRenderList() { return m_list; }
	};
}