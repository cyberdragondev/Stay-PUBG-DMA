#pragma once

namespace DMARender {
	struct Vector2 {
		float x;
		float y;
		Vector2() {
			this->x = 0.0f;
			this->y = 0.0f;
		}
		Vector2(float x, float y) {
			this->x = x;
			this->y = y;
		}
	};
}