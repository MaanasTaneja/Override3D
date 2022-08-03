#pragma once
#include "CMesh.h"
#include "CMaterial.h"
#include "globals.h"
#include "Transform.h"

//custom update function will be CRENDERUPDATEFCN whateevername(CRednerer currentObject)

/*
TODO
now sinced ive removed all interfaces, i must go back and optimise by removing virtuals from those functions that DONT NEED TO
be overriden for specialised objects

Like i dont need a derived animated vertex buffer to override the get id fucntion that pretty much remains same for all implementations so can be used from base
class itself
*/
namespace Override
{

	class CRenderable
	{
	private:
		CMesh* m_mesh;
		CMaterial* m_material;

		void (*m_customupdate)(CRenderable*);		//weird unsafe scripting hack - TODO - REMOVE 


		//Actually I want the renderer to apply materials and do what it wants, allows for more flexibility, CRenderable is a container to hold data 
		//Rest up to renderer

	public:
		Globals::renderabletypes m_type;
		Transform m_transform;

		virtual ~CRenderable() {
			m_mesh->~CMesh();
			m_material->~CMaterial();
			m_transform.~Transform();
		}

		CRenderable(CMesh* mesh, CMaterial* material, Globals::renderabletypes type) : m_mesh{ mesh }, m_material{ material },
			m_type{ type }, m_customupdate{ nullptr }, m_transform{ 1.0f } {}

		void setmesh(CMesh* mesh) { m_mesh = mesh; }
		void setmaterial(CMaterial* mat) { m_material = mat; }
		void setcustomupdate(void (*fcnptr)(CRenderable*)) { m_customupdate = fcnptr; }

		void setposition(glm::vec3 pos) {
			m_transform.m_position = pos;
		}
		void setscale(glm::vec3 scale) {
			m_transform.m_scale = scale;
		}
		void setrotation(glm::vec3 rotation) {
			m_transform.m_rotation = rotation;
		}

		glm::vec3 getposition() { return m_transform.m_position; }
		glm::vec3 getscale() { return m_transform.m_scale; }
		glm::vec3 getrotation() { return m_transform.m_rotation; }

		CMesh* getmesh() { return m_mesh; }
		CMaterial* getmaterial() { return m_material; }

		virtual void update();
		virtual void dissectObject();
	};
}

