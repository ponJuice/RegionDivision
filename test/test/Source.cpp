#include <stdio.h>
#include <vector>

typedef struct Pack {
	int start;
	int end;
}Pack;

int min(int a, int b) {
	int t = a <= b;
	return t*a + (1 - t)*b;
}

int max(int a, int b) {
	int t = a >= b;
	return t*a + (1 - t)*b;
}

int clamp(int minval, int maxval, int n) {
	return min(max(minval,n),maxval);
}

int abs(int n) {
	int t = n < 0;
	return -t * n + (1 - t)*n;
}

int main() {
	int x_max = 10;
	int y_max = 10;

	int data_num = x_max * y_max;

	int limits[] = {3,66,2,12,17};
	int size = sizeof(limits) / sizeof(int);

	//チェック
	int sum = 0;
	int min_v = -1;
	int max_v = 1;
	int val = 0;

	for (int n = 0; n < size; n++) {
		sum += limits[n];
	}
	if (sum != data_num) {
		printf("分割データが不正です\n");
		return 0;
	}

	//min チェック
	if (min(min_v, max_v) != min_v) {
		printf("min関数が不正です\n");
		return 0;
	}

	//max チェック
	if (max(max_v, min_v) != max_v) {
		printf("max関数が不正です\n");
		return 0;
	}

	//clamp チェック
	if (clamp(min_v, max_v, val) != val) {
		printf("clamp関数が不正です\n");
		return 0;
	}
	if (clamp(min_v, max_v, min_v - 1) != min_v) {
		printf("clamp関数が不正です\n");
		return 0;
	}
	if (clamp(min_v, max_v, max_v + 1) != max_v) {
		printf("clamp関数が不正です\n");
		return 0;
	}

	//abs チェック
	if (abs(-1) != 1) {
		printf("abs関数が不正です\n");
		return 0;
	}
	if (abs(0) != 0) {
		printf("clamp関数が不正です\n");
		return 0;
	}
	if (abs(1) != 1) {
		printf("clamp関数が不正です\n");
		return 0;
	}

	//チェック終わり

	std::vector<Pack> packs;
	
	int offset = 0;
	int offset_x = 0;
	int offset_y = 0;
	int start = 0;
	int end = -1;
	int remain = x_max;
	int length = 0;

	for (int n = 0; n < size; n++) {
		int limit = limits[n];
		while (limit > 0) {
			Pack pack;

			printf("n : %d\n", n);
			printf("limit : %d\n", limit);

			offset = end + 1;
			offset_x = offset % x_max;
			offset_y = offset / y_max;
			
			int temp = offset_x == 0;
			temp *= limit / x_max != 0;

			start = offset;
			end = start + (1 - temp)*min(remain,limit) + temp*(limit - limit % x_max) - 1;
			int _max = max(x_max - (offset_x + limit), 0);
			remain = (x_max + _max - 1) % x_max + 1;//clamp(1, 10, x_max - (offset_x + limit));//*/max(x_max - (offset_x + limit) , 0);
			
			int limit_remain = limit - (end - start + 1);

			limit = limit - (end - start + 1);

			pack.start = start;
			pack.end = end;
			packs.push_back(pack);
			
			printf("offset : %d\n", offset);
			printf("offset_x : %d\n", offset_x);
			printf("offset_y : %d\n", offset_y);
			printf("start : %d\n", start);
			printf("end : %d\n", end);
			printf("remain : %d\n", remain);
			printf("limit remain : %d\n", limit_remain);
			printf("\n");
		}
	}

	printf("result \n\n");

	for (int n = 0; n < packs.size(); n++) {
		Pack pack = packs.at(n);
		printf("n : %d\n", n);
		printf("start : %d\n", pack.start);
		printf("end : %d\n", pack.end);
		printf("\n");
	}

	getchar();
	return 0;
}