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


#include "Camera.h"

Camera::Camera(float radius, float initAngle, vec4 at,
			   GLfloat zNear, GLfloat zFar, GLfloat fovy)
{
	m_angle = 90.0f - initAngle;

	m_phi = 0.0f;
	m_theta = m_angle;

	m_at = at;
	m_up = vec4(0.0f, 1.0f, 0.0f, 0.0f);
	m_eye = vec4(0.0f, 0.0f, radius, 1.0);

	m_initRadius = radius;
	m_radius = m_initRadius;

	m_zNear = zNear;
	m_zFar = zFar;
	m_fovy = fovy;

	m_perspective = Perspective(m_fovy, m_aspect, m_zNear, m_zFar);

	// Used for quaternion analysis
#ifdef QUAT_ANALYSIS_ON
	count = 0;
	camHorRotAngle = 270.0f;
#endif // QUAT_ANALYSIS_ON
}

mat4 Camera::getPerspective()
{
	return m_perspective;
}

mat4 Camera::getTranslation()
{
#ifndef QUATERNIONS_ON
	updateLocs();
#endif // QUATERNIONS_ON
	return LookAt(m_eye, m_at, m_up);
}

vec4 Camera::getPosition()
{
#ifndef QUATERNIONS_ON
	updateLocs();
#endif // QUATERNIONS_ON
	return m_eye;
}

#ifndef QUATERNIONS_ON
void Camera::updateLocs()
{
	m_eye.x = m_radius * sin(m_theta*DegreesToRadians) * sin(m_phi*DegreesToRadians) + m_moveHor;
	m_eye.y = m_radius * cos(m_theta*DegreesToRadians) + m_moveVert;
	m_eye.z = m_radius * sin(m_theta*DegreesToRadians) * cos(m_phi*DegreesToRadians);

	// ERROR.... quats and euler coords killing each other  -->  set QUATERNIONS_ON option in Config.h
	m_up.x = sin((m_theta - 90.0f)*DegreesToRadians) * sin(m_phi*DegreesToRadians);
	m_up.y = cos((m_theta - 90.0f)*DegreesToRadians);
	m_up.z = sin((m_theta - 90.0f)*DegreesToRadians) * cos(m_phi*DegreesToRadians);
}
#endif // QUATERNIONS_ON

void Camera::updateAspect(GLfloat aspect)
{
	m_initAspect = aspect;
	m_aspect = m_initAspect;
	m_perspective = Perspective(m_fovy, m_aspect, m_zNear, m_zFar);
}

void Camera::updateAspect(double mult)
{
	m_aspect *= mult;
	m_perspective = Perspective(m_fovy, m_aspect, m_zNear, m_zFar);
}

void Camera::updateFovy(GLfloat fovy)
{
	m_fovy = fovy;
	m_perspective = Perspective(m_fovy, m_aspect, m_zNear, m_zFar);
}

void Camera::horizontal(float delta)
{
	m_moveHor += delta;
	m_at.x += delta;
}

void Camera::vertical(float delta)
{
	m_moveVert += delta;
	m_at.y += delta;
}
	
void Camera::distance(float delta)
{
	m_radius += delta;
}

void Camera::altitude(float angle)
{
#ifndef QUATERNIONS_ON		// Use Euler angles
	m_theta += angle;
#else	// QUATERNIONS_ON	// Use Quaternions
	vec4 origin = vec4(0.0f, 0.0f, 0.0f, 1.0f);

	// Represent the necessary rotation using a quaternion, and normalize it
	quat gQuat = quat(angle * DegreesToRadians, normalize(cross(m_eye - origin, m_up)));
	gQuat.normalize();

	// Rotate current position using quaternions and convert it back to a point
	m_eye = (gQuat * quat(m_eye - origin) * gQuat.conjugate()).quatToVector() + origin;
		
	// We also need rotate the up vector
	m_up = (gQuat * quat(m_up) * gQuat.conjugate()).quatToVector();
#endif	// QUATERNIONS_ON
}

void Camera::azimuth(float angle)
{
#ifndef QUATERNIONS_ON		// Use Euler angles
	m_phi += angle;

	if(m_phi >= 360.0f)
		m_phi -= 360.0f;
	else if(m_phi <= -360.0f)
		m_phi += 360.0f;
#else	// QUATERNIONS_ON	// Use Quaternions
	// Represent the necessary rotation using a quaternion, and normalize it
	quat gQuat = quat(angle * DegreesToRadians, vec3(0.0f, 1.0f, 0.0f));
	gQuat.normalize();

	vec4 origin = vec4(0.0f, 0.0f, 0.0f, 1.0f);

	// Rotate current position using quaternions and convert it back to a point
	m_eye = (gQuat * quat(m_eye - origin) * gQuat.conjugate()).quatToVector() + origin;

	// We also need rotate the up vector
	m_up = (gQuat * quat(m_up) * gQuat.conjugate()).quatToVector();
#endif	// QUATERNIONS_ON
}

// use negative angle for positive yaw
void Camera::yaw(float angle)
{
#ifdef QUAT_ANALYSIS_ON
	quatEulerComparison(-angle);
	return;
#endif // QUAT_ANALYSIS_ON

	// Represent the necessary rotation using a quaternion, and normalize it
	quat gQuat = quat(angle * DegreesToRadians, normalize(m_up));
	gQuat.normalize();

	// Rotate lookVec using quaternions and convert it back to a point
	m_at = (gQuat * quat(m_at - m_eye) * gQuat.conjugate()).quatToVector() + m_eye;
}

// use negative angle for positive pitch
void Camera::pitch(float angle)
{
	// Represent the necessary rotation using a quaternion, and normalize it
	quat gQuat = quat(angle * DegreesToRadians, normalize(cross(m_up, m_at - m_eye)));
	gQuat.normalize();

	// Rotate lookVec using quaternions and convert it back to a point
	m_at = (gQuat * quat(m_at - m_eye) * gQuat.conjugate()).quatToVector() + m_eye;

	// We also need rotate the up vector
	m_up = (gQuat * quat(m_up) * gQuat.conjugate()).quatToVector();
}

// use negative angle for positive roll
void Camera::roll(float angle)
{
	// Represent the necessary rotation using a quaternion, and normalize it
	quat gQuat = quat(angle * DegreesToRadians, normalize(m_at - m_eye));
	gQuat.normalize();

	// Rotate the up looking vector
	m_up = (gQuat * quat(m_up) * gQuat.conjugate()).quatToVector();
}

void Camera::reset()
{
	m_theta = m_angle;
	m_phi = 0.0f;
	m_radius = m_initRadius;

	m_at = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_up = vec4(0.0f, 1.0f, 0.0f, 0.0f);

	m_moveHor = 0.0f;
	m_moveVert = 0.0f;

	m_aspect = m_initAspect;
	m_perspective = Perspective(m_fovy, m_aspect, m_zNear, m_zFar);
}


#ifdef QUAT_ANALYSIS_ON
void Camera::quatEulerComparison(float angle)
{
	count ++;
	camHorRotAngle += angle;
	if(camHorRotAngle >= 360.0f)
		camHorRotAngle -= 360.0f;
	else if(camHorRotAngle <= -0.0f)
		camHorRotAngle += 360.0f;

	// Rotate around Y-axis using cylindrical/spherical coordinates
	vec4 eulerRes;
	eulerRes.x = m_radius * cos(camHorRotAngle*DegreesToRadians);
	eulerRes.y = m_at.y;
	eulerRes.z = m_radius * sin(camHorRotAngle*DegreesToRadians) + m_radius;

	// Now, let's so the same thing but using quaternion
	// Represent the necessary rotation using a quaternion, and normalize it
	quat gQuat = quat(-angle * DegreesToRadians, normalize(m_up));
	gQuat.normalize();

	// Rotate lookVec using quaternions and convert it back to a point
	vec4 quatRes = (gQuat * quat(m_at - m_eye) * gQuat.conjugate()).quatToVector() + m_eye;

	// Compare the results
	std::cout << std::endl;
	std::cout << "Iteration#: " << count << std::endl;
	std::cout << "X_euler = " << eulerRes.x << "; X_quat. = " << quatRes.x << "; Percent Error: " << percentError(quatRes.x, eulerRes.x) << "%" << std::endl;
	std::cout << "Y_euler = " << eulerRes.y << "; Y_quat. = " << quatRes.y << "; Percent Error: " << percentError(quatRes.y, eulerRes.y) << "%" << std::endl;
	std::cout << "Z_euler = " << eulerRes.z << "; Z_quat. = " << quatRes.z << "; Percent Error: " << percentError(quatRes.z, eulerRes.z) << "%" << std::endl;

	m_at = quatRes; // eulerRes
}
#endif // QUAT_ANALYSIS_ON
