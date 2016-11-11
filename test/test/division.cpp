#include "division.h"

namespace division {
	int min(int a, int b) {
		int t = a <= b;
		return t*a + (1 - t)*b;
	}

	int max(int a, int b) {
		int t = a >= b;
		return t*a + (1 - t)*b;
	}

	int clamp(int minval, int maxval, int n) {
		return min(max(minval, n), maxval);
	}

	int abs(int n) {
		int t = n < 0;
		return -t * n + (1 - t)*n;
	}

	void division(unsigned long long limits[], int arraysize, int x_max, int y_max, int z_max, std::vector<Pack> &packs) {

		int offset = 0;
		int offset_x = 0;
		int offset_y = 0;
		int offset_z = 0;
		int start = 0;
		int end = -1;
		int remain = x_max;
		int length = 0;

		for (int n = 0; n < arraysize; n++) {
			int limit = limits[n];
			while (limit > 0) {
				Pack pack;

				printf("n : %d\n", n);
				printf("limit : %d\n", limit);

				offset = end + 1;
				offset_x = offset % x_max;
				offset_y = offset % (x_max * y_max) / y_max;
				offset_z = offset / (x_max * y_max);

				int block_3d = offset_x == 0;
				block_3d *= offset_y == 0;
				block_3d *= limit / (x_max * y_max) != 0;

				int block_2d = offset_x == 0;
				block_2d *= limit / x_max != 0;
				block_2d *= (1 - block_3d);

				start = offset;
				//end = start + block_3d * (limit - limit % (x_max * y_max)) + block_2d * (limit - limit % x_max) + (1 - block_2d) * (1 - block_3d) * division::min(remain, limit) - 1;
				length = block_3d * (limit - limit % (x_max * y_max)) + block_2d * min(limit - limit % x_max, x_max * (y_max - offset_y)) + (1 - block_2d) * (1 - block_3d) * division::min(remain, limit) - 1;
				end = start + length;
				//end = start + (1 - temp)*min(remain,limit) + temp*(limit - limit % x_max) - 1;
				int _max = division::max(x_max - (offset_x + limit), 0);
				remain = (x_max + _max - 1) % x_max + 1;//clamp(1, 10, x_max - (offset_x + limit));//*/max(x_max - (offset_x + limit) , 0);

				int limit_remain = limit - (end - start + 1);

				pack.start = start;
				pack.end = end;
				pack.gpu = n;
				packs.push_back(pack);

				printf("offset : %d\n", offset);
				printf("offset_x : %d\n", offset_x);
				printf("offset_y : %d\n", offset_y);
				printf("start : %d\n", start);
				printf("end : %d\n", end);
				printf("remain : %d\n", remain);
				printf("limit remain : %d\n", limit_remain);
				printf("\n");

				limit = limit - (end - start + 1);
			}
		}
	}
}