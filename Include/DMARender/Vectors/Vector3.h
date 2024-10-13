#pragma once
#include <math.h>

namespace DMARender {
	struct Vector3 {
		float x;
		float y;
		float z;
		Vector3() {
			this->x = 0.0f;
			this->y = 0.0f;
			this->z = 0.0f;
		}
		Vector3(float x, float y, float z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Vector3 operator-(const Vector3& vec);

		Vector3 operator+(const Vector3& vec);

		float Dot(const Vector3& vec);

		float Dist(const Vector3& vec);
	};
}