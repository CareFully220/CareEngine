#include "Model.h"
#include "ResourceManager.h"

namespace CareEngine {

	Model::Model(const std::string& fileName, const std::string& textureName) :
		Mesh(fileName), m_texture(ResourceManager::getTexture(textureName))
	{

	}


	Model::~Model()
	{
	}

	void Model::Draw()
	{
		m_texture->Bind(0);
		Mesh::Draw();
	}
}