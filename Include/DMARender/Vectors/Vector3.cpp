#include "Vector3.h"

DMARender::Vector3 DMARender::Vector3::operator-(const Vector3& vec) {
	return Vector3(x - vec.x, y - vec.y, z - vec.z);
}

DMARender::Vector3 DMARender::Vector3::operator+(const Vector3& vec) {
	return Vector3(x + vec.x, y + vec.y, z + vec.z);
}

float DMARender::Vector3::Dot(const DMARender::Vector3& vec) {
	return x * vec.x + y * vec.y + z * vec.z;
}

float DMARender::Vector3::Dist(const DMARender::Vector3& vec) {
	return fabs(sqrt(pow(this->x - vec.x, 2) + pow(this->y - vec.y, 2) + pow(this->z - vec.z, 2)));
}