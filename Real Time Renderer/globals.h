#pragma once
#include <iostream>

//COMMON specifier refers to the basic parts of the engine, CVertexBuffer are all the common vertex buffer things required for every vertex buffer (we do have
//virtuals everywhere so for AVertexBuffer we CAN redefine any function we like, BUT CVERTEXBUFFER will have all the data and anything "common" in this component.
//I removed interfaces because they were highly superfluous. Every single component requiring speciality treatment will be derived from their COMMON counterparts.
//SO BASE CLASSES FOR EVERYTHING IS COMNMON 

namespace Globals
{
	enum texturetypes
	{
		TEXTURE_RENDER_TARGET,
		TEXTURE_2D,
		TEXTURE_PROCEDURAL,
		TEXTURE_DATA,
	};

	enum lighttypes
	{
		LIGHT_DIRECTIONAL,
		LIGHT_POINT,
	};

	enum renderabletypes			
	{								
		RENDERABLE_COMMON,		
		RENDERABLE_ANIMATED,
		RENDERABLE_PARTICLE,
		RENDERABLE_UI,
		RENDERABLE_BACKGROUND_STATIC,
		RENDERABLE_BACKGROUND,
	};

	enum materialspec
	{
		MATSPEC_PHONG,
		MATSPEC_PBR,
	};

	/*________________________________________________________________________________________________________________________________________________________
	Mesh is just a mesh, container to hold vertices thats all. Even UIRENDERABLE can have a cmesh (change mesh only if different packing is required),
	just the UIRENDEERER WILL HANDLE that 2d square/riangle differently. No difference (essentially) between a flat quad wall and a ui element
	just the uirenderer causes the quad to always face the camera etc.
	__________________________________________________________________________________________________________________________________________________________
	*/

	/*
	__________________________________________________________________________________________________________________________________________________________
	Naming scheme 
		C = COMMON
		A = ANIMATED 
		S = SPECIAL
	__________________________________________________________________________________________________________________________________________________________
	*/
	
	
	inline constexpr double g_gravity = 9.8;
	inline constexpr int SCR_WIDTH = 1920;
	inline constexpr int SCR_HEIGHT = 1080;

	inline float deltaTime = 0.0f;
	inline float lastFrame = 0.0f;


}