#pragma once
#include <glad/glad.h>
#include<iostream>
#include <vector>
#include "globals.h"

namespace Override
{
	class CTexture
	{
	private:
		std::string m_filename;
		unsigned int m_id;
		int m_width;
		int m_height;
		int m_numcolorchannels;
		unsigned char* m_raw;

		int m_filtering;
		int m_wrapping;

		bool m_mipmapping;
		bool m_anisotropy;

		virtual void generate();
	public:
		Globals::texturetypes m_type;


		CTexture(Globals::texturetypes type, std::string filename) : m_type{ type }, m_filename{ filename }, m_width{ 0 }, m_height{ 0 }, m_mipmapping{ false }
		, m_anisotropy{ false }, m_filtering{ 0 }, m_wrapping{ 0 }, m_numcolorchannels{ 0 }, m_id{ 0 }, m_raw{ nullptr } { generate(); }

		CTexture() : m_type{ Globals::TEXTURE_2D }, m_filename{ NULL }, m_width{ 0 }, m_height{ 0 }, m_mipmapping{ false }
			, m_anisotropy{ false }, m_filtering{ 0 }, m_wrapping{ 0 }, m_numcolorchannels{ 0 }, m_id{ 0 }, m_raw{ nullptr } {}

		//couldnt declare CTextures in Maps structs as there was no defualt constructor 

		virtual ~CTexture() { glDeleteTextures(1, &m_id); }

		unsigned int getid() { return m_id; }
		int getheight() { return m_height; }
		int getwidth() { return m_width; }

		void setfiltering(int flag) { m_filtering = flag; }

		void mipmap() {
			m_mipmapping = true;
			m_anisotropy = false;
		}

		void anisotropy() {
			m_mipmapping = false;
			m_anisotropy = true;
		}

		void wrapping(int wrap) { m_wrapping = wrap; }
		std::string getfilename() { return m_filename; }

		virtual void rebuild(Globals::texturetypes type, std::string filename) {
			m_type = type;
			m_filename = filename;
			generate();
		}


		//Common Texture can be resued in other ways 
		void procgentexture();
		void UItextureutility();

	};

}