#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

#define N 1000

int64_t Value[N][N], Row_Value[N][N], Col_Value[N][N], Sum_Value[N][N], m, n, x;

void Get_Row_Value(){
	for(int64_t i = 0; i < n; i++){
		for(int64_t j = 0; j < x; j++){
			Row_Value[i][0] += Value[i][j];
		}
		for(int64_t j = 1; j <= m - x; j++){
			Row_Value[i][j] = Row_Value[i][j-1] - Value[i][j-1] + Value[i][j+x-1];
		}
	}
}
void Get_Col_Value(){
	for(int64_t j = 0; j < m; j++){
		for(int64_t i = 0; i < x; i++){
			Col_Value[0][j] += Value[i][j];
		}
		for(int64_t i = 1; i <= n - x; i++){
			Col_Value[i][j] = Col_Value[i-1][j] - Value[i-1][j] + Value[i-1+x][j];
		}
	}
}
void PrintRowValue(){
	printf("\nThe following is Row_Value\n");
	for(int64_t i = 0; i < n; i++){
		for(int64_t j = 0; j <= m - x; j++){
			printf("%3"PRId64", ", Row_Value[i][j]);
		}
		printf("\n");
	}
}
void PrintColValue(){
	printf("\nThe following is Col_Value\n");
	for(int64_t i = 0; i <= n - x; i++){
		for(int64_t j = 0; j < m; j++){
			printf("%3"PRId64", ", Col_Value[i][j]);
		}
		printf("\n");
	}
}
void PrintSumValue(){
	printf("\nThe following is Sum_Value\n");
	for(int64_t i = 0; i <= n - x; i++){
		for(int64_t j = 0; j <= m - x; j++){
			printf("%3"PRId64", ", Sum_Value[i][j]);
		}
		printf("\n");
	}
}
int64_t Get_Sum_Value(){
	int64_t max;
	for(int i = 0; i < x; i++){
		Sum_Value[0][0] += Col_Value[0][i];
		max = Sum_Value[0][0];
	}
	for(int i = 0; i <= n - x; i++){
		for(int j = 0; j <= m - x; j++){
			if(i == 0 && j == 0){
				continue;
			}
			if(j == 0){
				Sum_Value[i][j] = Sum_Value[i-1][j] - Row_Value[i-1][j] + Row_Value[i+x-1][j];
			}
			else{
				Sum_Value[i][j] = Sum_Value[i][j-1] - Col_Value[i][j-1] + Col_Value[i][j+x-1];
			}
			if(Sum_Value[i][j] > max){
				max = Sum_Value[i][j];
			}
		}
	}
	return max;
}
int main() {
	int64_t max;
	scanf("%"SCNd64" %"SCNd64" %"SCNd64, &n, &m, &x);
	for(int64_t i = 0; i < n; i++){
		for(int64_t j = 0; j < m; j++){
			scanf("%"SCNd64, &Value[i][j]);
		}
	}
	Get_Row_Value();
	Get_Col_Value();
	//	PrintRowValue();
	//	PrintColValue();
	max = Get_Sum_Value();
	//	PrintSumValue();
	printf("%"PRId64"\n", max);
	return 0;
		
}

