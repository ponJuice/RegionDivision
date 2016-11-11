#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <math.h>
#include "division.h"
#include "lbm_data.h"

void point_get_test() {
	DivData data;
	data.direct_num = 9;
	data.x_max_out = 6;
	data.y_max_out = 6;
	data.z_max_out = 1;
	data.x_max_in = 3;
	data.y_max_in = 1;
	data.z_max_in = 1;
	data.size = 3;
	data.offset = 8;
	data.max_speed = 1;

	int x = 0;
	int y = 0;
	int z = 0;

	int index_in = data.offset + x
		+ y * data.x_max_in
		+ data.max_speed * 2 * y;
}

void main() {
	int x_max = 336;
	int y_max = 336;
	int z_max = 336;

	unsigned long long data_num = x_max * y_max * z_max;

	unsigned long long limits[] = {
		17314188
		,17314188
		,4329604
	};
	int size = sizeof(limits) / sizeof(unsigned long long);

	std::vector<division:: Pack> packs;
	division::division(limits, size, x_max, y_max, z_max, packs);

	printf("result \n\n");

	for (int n = 0; n < packs.size(); n++) {
		division::Pack pack = packs.at(n);
		printf("n : %d\n", n);
		printf("gpu : %d\n", pack.gpu);
		printf("start : %d\n", pack.start);
		printf("end : %d\n", pack.end);
		printf("length : %d\n", pack.end - pack.start + 1);
		printf(" x : %f\n", std::fmin(pack.end - pack.start + 1,x_max));
		printf(" y : %f\n", std::fmin((int)((pack.end - pack.start + 1) / x_max), y_max));
		printf(" z : %f\n", (double)((pack.end - pack.start + 1) / (x_max * y_max)));
		printf("\n");
	}

	getchar();

	return;
}

/*
int test() {
	int x_max = 336;
	int y_max = 336;
	int z_max = 336;

	unsigned long long data_num = x_max * y_max * z_max;

	unsigned long long limits[] = { 
		17314188
		,17314188
		,4329604
	};
	int size = sizeof(limits) / sizeof(unsigned long long);

	//チェック
	unsigned long long sum = 0;
	int min_v = -1;
	int max_v = 1;
	int val = 0;

	for (int n = 0; n < size; n++) {
		sum += limits[n];
	}
	if (sum <= data_num) {
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
	int offset_z = 0;
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
			offset_y = offset % (x_max * y_max) / y_max;
			offset_z = offset / (x_max * y_max);

			int block_3d = offset_x == 0;
			block_3d *= offset_y == 0;
			block_3d *= limit / (x_max * y_max) != 0;

			int block_2d = offset_x == 0;
			block_2d *= limit / x_max != 0;
			block_2d *= (1 - block_3d);

			int temp = offset_x == 0;
			temp *= limit / x_max != 0;

			start = offset;
			end = start + block_3d * (limit - limit % (x_max * y_max)) + block_2d * (limit - limit % x_max) + (1 - block_2d) * (1 - block_3d) * min(remain, limit) -1;
			//end = start + (1 - temp)*min(remain,limit) + temp*(limit - limit % x_max) - 1;
			int _max = max(x_max - (offset_x + limit), 0);
			remain = (x_max + _max - 1) % x_max + 1;//clamp(1, 10, x_max - (offset_x + limit));//*max(x_max - (offset_x + limit) , 0);
			
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

	/*std::ofstream ofs;
	ofs.open("dim.dat");

	int pack_num = 0;
	Pack pack = packs.at(0);
	for (int n = 0; n < data_num; n++) {
		if (n % (x_max * y_max) == 0) {
			ofs << std::endl;
		}
		
		if (pack.end < n) {
			pack_num++;
			pack = packs.at(pack_num);
		}

		int x = n % x_max;
		int y = n % (x_max * y_max) / y_max;
		ofs << /*n << " , " <<x << " " << y << " " << pack_num << std::endl;
	}

	ofs.close();

	//char* c = (char*)malloc(sizeof(char) * 100);
	//free(c);

	//std::vector<Pack> _swap(5);
	//packs.swap(_swap);

	packs.clear();

	getchar();
	_CrtDumpMemoryLeaks();
	return 0;
}
*/