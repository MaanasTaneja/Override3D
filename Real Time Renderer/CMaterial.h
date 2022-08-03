#pragma once
#include <iostream>
#include "CTexture.h"
#include "globals.h"
#include "Shader.h"

namespace Override
{

	struct Maps_phong
	{
		CTexture diffuse;
		CTexture specular;
	};

	struct Maps_pbr
	{
		CTexture albedo;
		CTexture normal;
		CTexture metallic;
		CTexture roughness;
	};

	class CMaterial
	{
	public:
		Globals::materialspec m_type;
		int m_id;
		Shader* m_shader;

		Maps_phong m_phong;
		Maps_pbr m_pbr;

		CMaterial(Globals::materialspec _type, Shader* shader) : m_type{ _type }, m_shader{ shader }, m_id{ 0 }, m_phong{}, m_pbr{} {}
		CMaterial() = default;
		virtual ~CMaterial() = default;

		void setMapsPhong(Maps_phong& ph) { m_phong = ph; }
		void setMapsPBR(Maps_pbr& pbr) { m_pbr = pbr; }

		void setshader(Shader* replace) { m_shader = replace; }
		virtual void textureload_phong(const std::string& diffuse, const std::string& specular);
		virtual void textureload_pbr(const std::string& albedo, const std::string& normal, const std::string& metallic, const std::string& roughness);

		int getmaterialspec() { return m_type; }
		void setmaterialspec(Globals::materialspec set) { m_type = set; }


		virtual void applymaterial();

	};
}

