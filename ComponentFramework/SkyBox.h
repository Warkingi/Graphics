#ifndef SKYB0X_H
#define SKYBOX_H

#include "ObjLoader.h"
#include "Matrix.h"

#include <glew.h>

class SkyBox {

private:

	class Mesh* mesh;
	class Texture* texture;
	class Shader* shader;

	Matrix4 modelMatrix;
	GLuint modelMatrixID;
	GLuint normalMatrixID;

public:

	SkyBox();
	~SkyBox();

	void Render() const;
	void LoadCubemap();

	inline Shader* GetShader() const { return shader; }

};
#endif
