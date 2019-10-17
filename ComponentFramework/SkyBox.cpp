#include "SkyBox.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "MMath.h"

SkyBox::SkyBox() : mesh(nullptr), shader(nullptr), texture(nullptr) {
	// Force load cube as skybox
	ObjLoader::loadOBJ("cube.obj");
	mesh = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);

	modelMatrix = MMath::scale(Vec3(1.0, 1.0, 1.0)) * MMath::translate(Vec3(10, 0, 0));

	shader = new Shader("phongVert.glsl", "phongFrag.glsl");

	modelMatrixID = shader->getUniformID("modelMatrix");
	normalMatrixID = shader->getUniformID("normalMatrix");
}

SkyBox::~SkyBox() {
	delete mesh;
	mesh = nullptr;
	delete texture;
	texture = nullptr;
	delete shader;
	shader = nullptr;
}

void SkyBox::Render() const {

	Matrix3 normalMatrix = modelMatrix;
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, modelMatrix);
	glUniformMatrix3fv(normalMatrixID, 1, GL_FALSE, normalMatrix);
	if (texture) {
		glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
	}

	glUniform3fv(shader->getUniformID("lightPos"), 1, Vec3(-5.0f, 2.0f, 1.0f));

	mesh->Render();

	glBindTexture(GL_TEXTURE_2D, 0);
}

void SkyBox::LoadCubemap() {

}