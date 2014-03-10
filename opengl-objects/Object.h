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


#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "Eigen\Dense"

class Object
{
public:
	Eigen::Vector3f gg();

private:
	Eigen::Vector3f m_color;
	Eigen::Vector3f m_location;

	float m_ambient;
	float m_diffuse;
	float m_specular;
	float m_shininess;

}


#endif  // __OBJECT_H__