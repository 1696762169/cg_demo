#pragma once
#include<random>
const double PI = 3.1415926;
inline double random_double() {
	return rand() / (RAND_MAX + 1.0);
}
inline double random_double(double min, double max) {
	return min + (max - min) * random_double();
}
inline double clamp(double x, double min, double max) {
	if (x < min)
		return min;
	if (x > max)
		return max; 
	return x;
	//return (x < min ? min : (x > max ? max : x));
}
inline int random_int(int min, int max) {
	return int(random_double(min, max + 1));
}

