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


#ifndef __GQUATERNION_H__
#define __GQUATERNION_H__

#include <math.h>
#include "Config.h"
#include "Angel.h"


/*
	Axis  = (x, y, z)
	Angle = theta

				 |   cos(theta / 2.0)   |
	Quaternion = | x * sin(theta / 2.0) |
	(4x1 matrix) | y * sin(theta / 2.0) |
				 | z * sin(theta / 2.0) |

	Reference: http://www.arcsynthesis.org/gltut/Positioning/Tut08%20Quaternions.html
*/
	

template <class T>
class gQuaternion
{
public:
	// ############################ //
	// ####    Constructors    #### //
	// ############################ //
	gQuaternion()
	{
		w = (T) 1.0f;	// theta = 0.5 * arccos(1) = 0
		x = (T) 0.0f;
		y = (T) 0.0f;
		z = (T) 0.0f;
	}

	gQuaternion(T w, T x, T y, T z)
	{
		this->w = w;
		this->x = x;
		this->y = y;
		this->z = z;
	}

	// Quaternion representing a vector/axis (no rotation)
	gQuaternion(const vec3 &axis)
	{
		this->w = 0;
		this->x = axis.x;
		this->y = axis.y;
		this->z = axis.z;
	}

	gQuaternion(const vec4 &axis)
	{
		this->w = axis.w;
		this->x = axis.x;
		this->y = axis.y;
		this->z = axis.z;
	}

	// Create a quaternion from a rotation matrix
	gQuaternion(const mat4 &matrix)
    {
		mat3(matrix);
        this->matrixToQuat(matrix);
    }
	
	// Create a quaternion from axis coordinates and an agle (in radians)
	gQuaternion(T angle, const vec3 &axis)
    {
        this->axisAndAngleToQuat(angle, axis);
    }

	// Create a quaternion from axis coordinates and an agle (in radians) [same as the one above]
	gQuaternion(T angle, const vec4 &axis)
    {
        this->axisAndAngleToQuat(angle, vec3(axis.x, axis.y, axis.z));
    }

	// Create a quaternion from axes
	gQuaternion(const vec3& x, const vec3& y, const vec3& z)
    {
        this->matrixToQuat(mat3(x, y, z));
    }

	// ######################### //
	// ####    Operators    #### //
	// ######################### //
	gQuaternion operator=(const gQuaternion &src)
	{
		if(&src == this)
			return *this;

		x = src.x;
		y = src.y;
		z = src.z;
		w = src.w;
		
		return *this;
	}

	bool operator==(const gQuaternion &src) const
	{
		return (w == src.w && x == src.x && y == src.y && z == src.z);
	}
	
	bool operator!=(const gQuaternion &src) const
	{
		return !(this->operator==(src));
	}

	gQuaternion operator+(const gQuaternion &src) const
	{
		return gQuaternion(w + src.w, x + src.x, y + src.y, z + src.z);
	}

	gQuaternion operator+=(const gQuaternion &src)
	{
		w += src.w;
		x += src.x;
		y += src.y;
		z += src.z;

		return *this;
	}
	
	gQuaternion operator-(const gQuaternion &src) const
	{
		return gQuaternion(w - src.w, x - src.x, y - src.y, z - src.z);
	}

	gQuaternion operator-=(const gQuaternion &src)
	{
		w -= src.w;
		x -= src.x;
		y -= src.y;
		z -= src.z;

		return *this;
	}

	gQuaternion operator*(const gQuaternion &src) const
	{
		T resW = w * src.w - x * src.x - y * src.y - z * src.z;
		T resX = w * src.x + x * src.w + y * src.z - z * src.y;
		T resY = w * src.y - x * src.z + y * src.w + z * src.x;
		T resZ = w * src.z + x * src.y - y * src.x + z * src.w;

		
		return gQuaternion(resW, resX, resY, resZ);
	}

	gQuaternion operator*=(const gQuaternion &src) const
	{
		w = w * src.w - x * src.x - y * src.y - z * src.z;
		x = w * src.x + x * src.w + y * src.z - z * src.y;
		y = w * src.y - x * src.z + y * src.w + z * src.x;
		z = w * src.z + x * src.y - y * src.x + z * src.w;
		
		return *this;
	}

	template<class var>
	gQuaternion operator*(var val) const
	{
		return gQuaternion(w * val, x * val, y * val, z * val);
	}

	template<class var>
	gQuaternion operator*=(var val)
	{
		w *= val;
		x *= val;
		y *= val;
		z *= val;

		return *this;
	}

	gQuaternion operator/(const gQuaternion &src) const
	{
		T resW = w / src.w - x / src.x - y / src.y - z / src.z;
		T resX = w / src.x + x / src.w + y / src.z - z / src.y;
		T resY = w / src.y + y / src.w + z / src.x - x / src.z;
		T resZ = w / src.z + z / src.w + x / src.y - y / src.x;
		
		return gQuaternion(resW, resX, resY, resZ);
	}

	gQuaternion operator/=(const gQuaternion &src) const
	{
		w = w / src.w - x / src.x - y / src.y - z / src.z;
		x = w / src.x + x / src.w + y / src.z - z / src.y;
		y = w / src.y + y / src.w + z / src.x - x / src.z;
		z = w / src.z + z / src.w + x / src.y - y / src.x;
		
		return *this;
	}

	template<class var>
	gQuaternion operator/(var val) const
	{
		return gQuaternion(w / val, x / val, y / val, z / val);
	}

	template<class var>
	gQuaternion operator/=(var val)
	{
		w /= val;
		x /= val;
		y /= val;
		z /= val;

		return *this;
	}


	// ################################ //
	// ####    Useful Functions    #### //
	// ################################ //
	void quatToMatrix(mat4 &matrix) const
	{
		T doubleW = w * 2.0f;
		T doubleX = x * 2.0f;
		T doubleY = y * 2.0f;
		T doubleZ = z * 2.0f;

		T doubleWW = w * w;
		T doubleXW = x * w;
		T doubleYW = y * w;
		T doubleZW = z * w;
		T doubleXX = x * x;
		T doubleYX = y * x;
		T doubleZX = z * x;
		T doubleYY = y * y;
		T doubleZY = z * y;
		T doubleZZ = z * z;

		matrix[0] = vec4(1.0f - doubleYY - doubleZZ, doubleYX - doubleZW,		 doubleZX + doubleYW,		 0.0f);
		matrix[1] = vec4(doubleYX + doubleZW,		 1.0f - doubleXX - doubleZZ, doubleZY - doubleXW,		 0.0f);
		matrix[2] = vec4(doubleZX - doubleYW,		 doubleZY + doubleXW,		 1.0f - doubleXX - doubleYY, 0.0f);
		matrix[3] = vec4(0.0f,						 0.0f,						 0.0f,						 1.0f);
	}

	// reference: "Quaternion Calculus and Fast Animation" by Ken Shoemake
	void matrixToQuat(const mat3 &matrix)
	{
		T trace = matrix[0][0] + matrix[1][1] + matrix[2][2];

        if(trace > 0.0f)
        {
            w = sqrt(trace + 1.0f) / 2.0f;
            x = (matrix[2][1] - matrix[1][2]) / (w * 4.0f);
            y = (matrix[0][2] - matrix[2][0]) / (w * 4.0f);
            z = (matrix[1][0] - matrix[0][1]) / (w * 4.0f);
        }
        else
        {
            static size_t next[3] = { 1, 2, 0 };
            size_t i = 0;
            if(matrix[1][1] > matrix[0][0])
                i = 1;
            if(matrix[2][2] > matrix[i][i])
                i = 2;
            size_t j = next[i];
            size_t k = next[j];

            T root = sqrt(matrix[i][i] - matrix[j][j] - matrix[k][k] + 1.0f);
            T *quat[3] = { &x, &y, &z };
            *quat[i] = root / 2.0f;
            root = 1.0f / (root * 2.0f);
			w = (matrix[k][j] - matrix[j][k]) * root;
            *quat[j] = (matrix[j][i] + matrix[i][j]) * root;
            *quat[k] = (matrix[k][i] + matrix[i][k]) * root;
        }
	}

	void axisAndAngleToQuat(T angle, const vec3 &axis)
	{
        T temp = sin(angle / 2.0f);
        w = cos(angle / 2.0f);
        x = axis.x * temp;
        y = axis.y * temp;
        z = axis.z * temp;
	}

	void quatToAxisAndAngle(T &angle, vec3 &axis) const
	{
		T squareLength = dot(axis, axis);
        if(squareLength > 0.0f)
        {
#ifdef FAST_SQRT_ON
            T invLength = fastInvSqrt(squareLength);
            axis.x = x * invLength;
            axis.y = y * invLength;
            axis.z = z * invLength;
#else
			T length = sqrt(squareLength);
			axis.x = x / length;
            axis.y = y / length;
            axis.z = z / length;
#endif
        }
        else
        {
            angle  = (T) 0.0f;
            axis.x = (T) 1.0f;
            axis.y = (T) 0.0f;
            axis.z = (T) 0.0f;
        }
	}

	void quatToVector(vec4 &vec) const
	{
		vec.x = x;
		vec.y = y;
		vec.z = z;
		vec.w = w;
	}

	vec4 quatToVector() const
	{
		return vec4(x, y, z, w);
	}

	void normalize()
	{
		T squareLength = dot(*this, *this);

#ifdef FAST_SQRT_ON
        T invLength = fastInvSqrt(squareLength);
        *this *= invLength;
#else
		T length = sqrt(squareLength);
		*this /= length;
#endif
	}

	gQuaternion inverse() const
	{
		T squareLength = dot(*this, *this);
		if (squareLength != 0)
			return gQuaternion(w / squareLength, -x / squareLength, -y / squareLength, -z / squareLength);
		else
			return gQuaternion();
	}

	gQuaternion conjugate() const
	{
		return gQuaternion(w,-x,-y,-z);
	}

//private:
	T w;
	T x;
	T y;
	T z;
};

template<class T>
inline
GLfloat dot(const gQuaternion<T> &q1, const gQuaternion<T> &q2) {
    return q1.w*q2.w + q1.x*q2.x + q1.y*q2.y + q1.z*q2.z;
}

template<class T>
inline
GLfloat length(const gQuaternion<T> &q)
{
    return sqrt(dot(q, q));
}

template<class T>
inline
gQuaternion<T> normalize(const gQuaternion<T> &q)
{
		T squareLength = dot(q, q);
		gQuaternion<T> res;

#ifdef FAST_SQRT_ON
        T invLength = fastInvSqrt(squareLength);
        res = q * invLength;
#else
		T length = sqrt(squareLength);
		res = q / length;
#endif

		return res;
}

// So that you don't have to type gQuaternion every single time
typedef class gQuaternion<float> quat;

#endif // __GQUATERNION_H__