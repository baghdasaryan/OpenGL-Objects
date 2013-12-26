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


#ifndef __OBJECTMANAGER_H__
#define __OBJECTMANAGER_H__

#include "Eigen/Dense"

class Drawer
{
public:
	void RotateX(double angle);
	void RotateY(double angle);
	void RotateZ(double angle);
	void Rotate(const Eigen::Vector3f &rotation);

	void Scale(double scale);
	void Scale(const Eigen::Vector3f &scale);

	void Translate(const Eigen::Vector3f& a_translation);

private:
	
};

#endif  // __OBJECTMANAGER_H__
