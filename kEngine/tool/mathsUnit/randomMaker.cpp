#include "randomMaker.h"

int randomInt(int min, int max) {
	srand((unsigned int)time(NULL));
	randomMaker = rand() + randomMaker;
	if (randomMaker < 0)randomMaker *= -1;
	int range = max - min + 1;
	int num = randomMaker % range;
	return min + num;
}

float randomFloat(float min, float max, float numAfterPoint) {
	srand((unsigned int)time(NULL));
	randomMaker = rand() + randomMaker;
	if (randomMaker < 0)randomMaker *= -1;
	int range = int(max - min);
	float num = float(randomMaker % range);
	for (int i = 0; i < numAfterPoint; i++) {
		randomMaker = rand() + randomMaker;
		num += float(randomMaker % 10) / powf(10.0f, float(i + 1));
	}

	return min + num;
}

int randomNum(int numAfterPoint) {
	int resuit = 0;
	for (int i = 0; i < numAfterPoint; i++) {
		randomMaker = rand() + randomMaker;
		if (randomMaker < 0)randomMaker *= -1;
		resuit += randomMaker % 10 * int(powf(10.0f, float(i)));
	}
	return resuit;
}

