#include <glew.h>
#include <iostream>
#include "Window.h"
#include "Debug.h"
#include "Scene1.h"
#include "Camera.h"
#include "GameObject.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"


Scene1::Scene1() : camera(nullptr), gameObjects(std::vector<GameObject*>()), meshPtr(nullptr), shaderPtr(nullptr), textureList(std::vector<Texture*>()) {
}


Scene1::~Scene1() {
}

bool Scene1::OnCreate() {
	camera = new Camera();

	if (ObjLoader::loadOBJ("sphere.obj") == false) {
		return false;
	}
	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	shaderPtr = new Shader("textureVert.glsl", "textureFrag.glsl");
	textureList.push_back(new Texture());
	if (meshPtr == nullptr || shaderPtr == nullptr || textureList[0] == nullptr) {
		Debug::FatalError("Couldn't create game object assets", __FILE__, __LINE__);
		return false;
	}
	if (textureList[0]->LoadImage("EARF.jpg") == false) {
		Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
		return false;
	}
	textureList.push_back(new Texture());
	if (textureList[1]->LoadImage("moon.jpg") == false) {
		Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
		return false;
	}

	gameObjects.push_back(new GameObject(meshPtr, shaderPtr, textureList[0]));
	gameObjects.push_back(new GameObject(meshPtr, shaderPtr, textureList[1]));
	/*if (gameObject == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}*/

	lightSource.push_back(Vec3(-100.0, 10.0, 0.0));

	return true;
}

void Scene1::OnDestroy() {
	if (camera) delete camera, camera = nullptr;
	if (meshPtr) delete meshPtr, meshPtr = nullptr;
	//if (texturePtr) delete texturePtr, texturePtr = nullptr;
	if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
	if (textureList.size() > 0) {
		for (Texture* tex : textureList) {
			delete tex;
			tex = nullptr;
		}
	}
	if (gameObjects.size() > 0) {
		for (GameObject* obj : gameObjects) {
			delete obj;
			obj = nullptr;
		}
	}
}

void Scene1::HandleEvents(const SDL_Event &sdlEvent) {

	switch (sdlEvent.type) {
	case SDL_KEYDOWN:
		switch (sdlEvent.key.keysym.sym) {
		case SDLK_UP:
			break;
		case SDLK_DOWN:
			break;
		}
	}

}

void Scene1::Update(const float deltaTime_) {
	for (GameObject* obj : gameObjects) {
		obj->Update(deltaTime_);
	}
		static float rotation = 0.0f;
		rotation += 0.5;
		// Rotation for the earth. Rotate at the speed of 0.5f, set the scale to 1 and flip the earth to be upright.
		gameObjects[0]->setModelMatrix(MMath::rotate(rotation, Vec3(0.0, 1.0, 0.0)) * MMath::scale(Vec3(1.0, 1.0, 1.0)) * MMath::rotate(-90.0f, Vec3(1.0, 0.0, 0.0)));
		// Rotation for the moon. Rotates at the rotation speed of 0.5f * 1.5f (50% increase), set scale to 0.25 (25%) and flip moon to the upright.
		gameObjects[1]->setModelMatrix(MMath::rotate(rotation * 2.5f, Vec3(0.0, 1.0, 0.0)) * MMath::scale(Vec3(0.25, 0.25, 0.25)) * MMath::rotate(-90.0f, Vec3(1.0, 0.0, 0.0)) * MMath::translate(Vec3(10, 0, 0)));
	
}

void Scene1::Render() const {
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLuint program;

	/// Draw your scene here
	for (GameObject* obj : gameObjects) {
		program = obj->getShader()->getProgram();

		glUseProgram(program);

		/// These pass the matricies and the light position to the GPU
		glUniformMatrix4fv(obj->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
		glUniformMatrix4fv(obj->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
		for (int i = 0; i < lightSource.size(); i++)
			glUniform3fv(obj->getShader()->getUniformID("lightPos"), lightSource.size(), lightSource[i]);

		obj->Render();
	}

	program = camera->GetSkyBox()->GetShader()->getProgram();

	glUseProgram(program);

	glUniformMatrix4fv(camera->GetSkyBox()->GetShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(camera->GetSkyBox()->GetShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());

	camera->GetSkyBox()->Render();

	glUseProgram(0);
}
