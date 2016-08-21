#pragma once
#include <string>
#include "Texture.h"
#include "Mesh.h"

namespace CareEngine {

	class Model : public Mesh
	{
	public:
		Model(const std::string& fileName, const std::string& textureName);

		void Draw();

		~Model();
	private:
		Texture* m_texture;
	};

}
