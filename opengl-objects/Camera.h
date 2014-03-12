// ############################################ //
// ############################################ //
// ####                                    #### //
// ####    Program: OpenGL-Objects         #### //
// ####    Language: C++                   #### //
// ####    Author: Georgi Baghdasaryan     #### //
// ####    Email: baghdasaryan@ucla.edu    #### //
// ####                                    #### //
// ############################################ //
// ############################################ //


#ifndef __CAMERA_H__
#define __CAMERA_H__


#include <math.h>
#include "Config.h"
#include "gUtils.h"
#include "Angel.h"
#include "gQuaternion.h"

#ifdef QUAT_ANALYSIS_ON
#include <iostream>
#endif // QUAT_ANALYSIS_ON


class Camera
{
public:
	Camera(float radius, float initAngle, vec4 at,
		GLfloat zNear, GLfloat zFar, GLfloat fovy);

	mat4 getPerspective();
	mat4 getTranslation();
	vec4 getPosition();

#ifndef QUATERNIONS_ON
	void updateLocs();
#endif // QUATERNIONS_ON

	void updateAspect(GLfloat aspect);
	void updateAspect(double mult);
	void updateFovy(GLfloat fovy);

	void horizontal(float delta);
	void vertical(float delta);
	void distance(float delta);

	void altitude(float angle);
	void azimuth(float angle);
	
	void yaw(float angle);		// use negative angle for positive yaw
	void pitch(float angle);	// use negative angle for positive pitch
	void roll(float angle);		// use negative angle for positive roll

	void reset();

#ifdef QUAT_ANALYSIS_ON
	void quatEulerComparison(float angle);
#endif // QUAT_ANALYSIS_ON

private:
	vec4 m_eye;
	vec4 m_at;
	vec4 m_up;
	
	float m_angle;
	float m_theta;
	float m_phi;

	double m_initRadius;
	double m_radius;

	float m_moveVert;
	float m_moveHor;

	// Projection attributes
	GLfloat m_zNear;
	GLfloat m_zFar;
	GLfloat m_fovy;
	GLfloat m_initAspect;
	GLfloat m_aspect;

	mat4 m_perspective;

	// Used for quaternion analysis
#ifdef QUAT_ANALYSIS_ON
	double camHorRotAngle;
	int count;
#endif // QUAT_ANALYSIS_ON
};

#endif  // __CAMERA_H__
