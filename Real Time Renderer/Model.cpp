#include "Model.h"

/*
ENTIRE MODEL LOADER NEEDS A SERIOUS REWORK! AS OF RIGHT NOW, ITS PRETTY BADLY WRITTEN AND FULL OF HACKS!
*/

namespace Override
{
	void Model::loadmodel(const std::string& filepath)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(filepath,  aiProcess_Triangulate | aiProcess_FlipUVs);  //remove realtime quality then it loads properly ish

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "Assimp Failed Loading model! :: " << importer.GetErrorString() << std::endl;
			return;
		}

		m_directory = filepath.substr(0, filepath.find_last_of('\\'));
		processnode(scene->mRootNode, scene);
	}

	void Model::processnode(aiNode* node, const aiScene* scene)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			// the node object only contains indices to index the actual objects in the scene. 
			// SCENE OBJECT HAS ALL THE DATA, NODE JUST HAS THE INDICES TO ACCESS THAT! 
			// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).

			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			push(parseRenderable(mesh, scene));
		}
		// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processnode(node->mChildren[i], scene);
		}

	}

	CRenderable* Model::parseRenderable(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		CMesh* renderable_mesh = new CMesh();
		CMaterial* renderable_mat = new CMaterial();
		renderable_mat->setmaterialspec(m_type);
		renderable_mat->setshader(m_shader);

		std::string diffuseTex;
		std::string specularTex;

		Maps_pbr pbr;
		Maps_phong phong;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			
			vertex.position[0] = mesh->mVertices[i].x;
			vertex.position[1] = mesh->mVertices[i].y;
			vertex.position[2] = mesh->mVertices[i].z;
			
			if (mesh->HasNormals())
			{
				vertex.normal[0] = mesh->mNormals[i].x;
				vertex.normal[1] = mesh->mNormals[i].y;
				vertex.normal[2] = mesh->mNormals[i].z;
			}
			
		
			if (mesh->mTextureCoords[0])
			{
				vertex.uv[0] = mesh->mTextureCoords[0][i].x;
				vertex.uv[1] = mesh->mTextureCoords[0][i].y;

				/*
				vector.x = mesh->mTangents[i].x;
				vector.y = mesh->mTangents[i].y;
				vector.z = mesh->mTangents[i].z;
				vertex.Tangent = vector;

				vector.x = mesh->mBitangents[i].x;
				vector.y = mesh->mBitangents[i].y;
				vector.z = mesh->mBitangents[i].z;
				vertex.Bitangent = vector;
				*/
			}
			else
			{
				vertex.uv[0] = 0.0f;
				vertex.uv[1] = 0.0f;
			}

			vertices.push_back(vertex);
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		renderable_mesh->setrawmeshdata(vertices);
		//renderable_mesh->addIndices(indices);  //commenting this out makes windmill load properly (they only screw up windmill for some reason??)
		renderable_mesh->build();

		//Load material for this specific mesh
		aiMaterial* aMaterial = scene->mMaterials[mesh->mMaterialIndex];
		//Extract texture maps for this material and then load them into our formats 

		if (aMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			aiString filename;
			aMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &filename);		//Index is 0 because we are only taking the first diffuse texture in the aiMatertial diffuse tex array
			//we dont care about multi diffuse texture models, and same goes for the other types.

			std::string filepath = m_directory + '\\' + filename.C_Str();

			if (m_type == Globals::MATSPEC_PHONG)
			{
				diffuseTex = filepath;

				/*
				CTexture diff;
				diff.setfiltering(GL_LINEAR);
				diff.wrapping(GL_REPEAT);
				diff.mipmap();
				diff.rebuild(Globals::TEXTURE_2D, filepath);
				phong.diffuse = diff;
				*/

			}
			else if (m_type == Globals::MATSPEC_PBR)
			{
				CTexture albedo{ Globals::TEXTURE_2D, filepath };
				pbr.albedo = albedo;
			}
		}

		if (aMaterial->GetTextureCount(aiTextureType_SPECULAR) > 0)
		{
			aiString filename;
			aMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &filename);		

			std::string filepath = m_directory + '\\' + filename.C_Str();

			if (m_type == Globals::MATSPEC_PHONG)
			{
				specularTex = filepath;
				
				/*CTexture spec;
				spec.setfiltering(GL_NEAREST);
				spec.wrapping(GL_REPEAT);
				spec.mipmap();
				spec.rebuild(Globals::TEXTURE_2D, filepath);
				phong.specular = spec;
				*/
			}
		}

		renderable_mat->textureload_phong(diffuseTex, specularTex);

		//so for some reason set phong maps function wasnt working propely? only filename got copied not the texture data??? i had to manually rebuild every texture for the
		//model to correctly render???? what is going why? 


		CRenderable* rrr = new CRenderable(renderable_mesh, renderable_mat, Globals::RENDERABLE_COMMON);
		rrr->setcustomupdate(nullptr);
		
		return new CRenderable(renderable_mesh, renderable_mat, Globals::RENDERABLE_COMMON);;
		//TO IMPLEMENT PBR MODEL LOADING 
		//AND TO HAVE DEFAULT SHADER OPTIONS!
	}

}