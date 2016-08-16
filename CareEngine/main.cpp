#include <GL/glew.h>
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"

int main(int argc, char **argv)
{
	Display display(800, 600, "Hello World!");

	Shader shader("./resource/shaders/basicShader");

	Vertex verticies[] = { Vertex(glm::vec3(0.0, -0.5, -0.5), glm::vec2(0.0, 0.0)),
							Vertex(glm::vec3(0.0, 0.5, -0.5), glm::vec2(0.5, 1.0)),
							Vertex(glm::vec3(0.0, 0.0, 0.5), glm::vec2(1.0, 0.0)) };

	unsigned int indices[] = { 0, 1, 2 };

//	Mesh mesh(verticies, sizeof(verticies) / sizeof(verticies[0]), indices, sizeof(indices) / sizeof(indices[0]));
	Mesh mesh2("./resource/models/monkey3.obj");
//	Texture texture("./resource/textures/default.jpg");
	Texture texture("./resource/textures/Wood1.jpg");
	Camera camera(glm::vec3(-5.0, 0.0, 0.0), 70.0f, (float)display.getWidth() / (float)display.getHeight(), 0.01f, 1024.0f);
	Transform transform;

	float counter = 0.0f;
	while (!display.IsClosed())
	{
		display.Clear(0.0f, 0.0f, 0.0f, 1.0f);

		//float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		transform.getPos().x = sinf(counter);
		transform.getRot().z = counter;
		transform.getRot().x = 90.0;

		shader.Bind();
		texture.Bind(0);
		shader.Update(transform, camera);
//		mesh.Draw();
		mesh2.Draw();
		display.Update();
		counter += 0.001f;
	}
	return 0;
}