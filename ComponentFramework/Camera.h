#ifndef CAMERA_H
#define CAMERA_H
#include "Vector.h"
#include "Matrix.h"
#include "SkyBox.h"
using namespace MATH;
class Camera {
private:
	Matrix4 projection;
	Matrix4 view;

	SkyBox* sky;

public:
	inline Matrix4 getProjectionMatrix() const { return projection; }
	inline Matrix4 getViewMatrix() const { return view; }

	void createProjection(float fovy, float aspectRatio, float near, float far);
	void createView(Vec3 pos, Vec3 at, Vec3 up);
	Camera();
	~Camera();

	inline SkyBox* GetSkyBox() const { return sky; }
};

#endif



