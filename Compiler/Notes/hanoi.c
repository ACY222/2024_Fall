#include <stdio.h>
#include <time.h>

int count = 0;

void move(int order, int src, int dest) {
	printf("Step %d: Move block %d from %d to %d\n", ++count, order, src, dest);
	return;
}

void hanoi(int num, int src, int des, int by) {
	if (num == 1) {
		move(num, src, des);
	}
	else {
		hanoi(num - 1, src, by, des);
		move(1, src, des);
		hanoi(num - 1, by, des, src);
	}
	return;
}

int main() {
	int num;
	int start_time, end_time;
	while (scanf("%d", &num)) {
		start_time = clock();
		hanoi(num, 1, 2, 3);
		end_time = clock();
		printf("The time cost is: %lf\n", (end_time - start_time) * 1.0 / CLOCKS_PER_SEC);
	}
	return 0;
}
