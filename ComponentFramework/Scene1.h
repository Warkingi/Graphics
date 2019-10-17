#ifndef SCENE1_H
#define SCENE1_H
#include "Scene.h"
#include "Vector.h"

#include <Vector>
using namespace MATH;


union SDL_Event;
class Camera;
class GameObject;
class Mesh;
class Shader;
class Texture;

class Scene1 : public Scene {
private:
	Camera *camera;
	std::vector<GameObject*> gameObjects;
	std::vector<Vec3> lightSource;
	Mesh *meshPtr;
	Shader *shaderPtr;
	//Texture *texturePtr;
	std::vector<Texture*> textureList;
public:
	explicit Scene1();
	virtual ~Scene1();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
	virtual void Update(const float deltaTime_) override;
	virtual void Render() const override;
};


#endif // !SCENE1_H