#include <stdio.h>
#include <stdlib.h>

int main() {
	int m = 3, n = 4;
	int **a = (int **)malloc(m*sizeof(int *));
	for(int i = 0; i < m; i++) {
		a[i] = (int *)malloc(n*sizeof(int));
	}
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < n; j++) {
			a[i][j] = i * 10 + j;
		}
	}
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < n; j++) {
			printf("%d, ", a[i][j]);
		}
		printf("\n");
	}
	return 0;
	
}
