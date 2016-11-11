#pragma once
#include <vector>

namespace division {
	typedef struct Pack {
		int start;
		int end;
		int gpu;
	}Pack;
	void division(unsigned long long limits[], int arraysize, int x_max, int y_max, int z_max, std::vector<Pack> &packs);
}