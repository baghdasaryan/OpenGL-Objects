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


#ifndef __GUTILS_H__
#define __GUTILS_H__

template<class T>
inline
long double percentError(T exp, T theor)
{
	/* Computing Percentage Error
	Percentage error can be computed using:

					|X_exp - X_theor|
			%Error = ----------------- x 100%
						    X_theor

	where X_exp is X's experimental value and
			X_theor is X's theoretical value
	*/

	if (exp == theor)
		return 0.0L;
	else if (theor == 0.0L)
		return std::numeric_limits<long double>::infinity();
	else
		return abs(exp - theor) / theor * 100.0L;
}

// Quake's inverse square root
template<class T>
inline
T fastInvSqrt(T number)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;
 
	x2 = number * 0.5F;
	y  = number;
	i  = * (long *) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );             // what the fuck?
	y  = * (float *) &i;
	y  = y * (threehalfs - (x2 * y * y ));   // 1st iteration
    y  = y * (threehalfs - (x2 * y * y ));   // 2nd iteration (not necessary)
 
	return ((T) y);
}

#endif  // __GUTILS_H__