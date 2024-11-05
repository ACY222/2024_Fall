#include<stdio.h>

/*
#define INFTY 1000
float p[6] = {0, 0.15, 0.10, 0.05, 0.10, 0.20}, q[6] = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};

float w[6][6], e[6][6];
int root[6][6];
void Optimal_BST(){
	for(int i = 0; i < 6; i++){
		e[i+1][i] = q[i];
		w[i+1][i] = q[i];
	}
	for(int len = 1; len < 6; len++){
		for(int l = 1; l <= 6 - len; l++){
			int r = l + len - 1;
			e[l][r] = INFTY;
			w[l][r] = w[l][r-1] + p[r] + q[r];
			for(int k = l; k <= r; k++){
				float t = e[l][k-1] + e[k+1][r] + w[l][r];
				if(t < e[l][r]){
					e[l][r] = t;
					root[l][r] = k;
				}
			}
		}
	}
}

int main(){
	Optimal_BST();
	for(int i = 1; i < 6; i++){
		for(int j = 0; j < 6; j++){
			printf("%f, ", e[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(int i = 1; i < 6; i++){
		for(int j = 0; j < 6; j++){
			printf("%f, ", w[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 6; j++){
			printf("%d, ", root[i][j]);
		}
		printf("\n");
	}
}
*/
/* Longest Common Subsequence Problem
char X[8] = " ABCBDAB", Y[7] = " BDCABA";
int Z[8][7];

void LCS_Length(){
	for(int i = 1; i < 8; i++){
		for(int j = 1; j < 7; j++){
			if(X[i] == Y[j]){
				Z[i][j] = Z[i-1][j-1] + 1;
			}
			else{
				if(Z[i][j-1] >= Z[i-1][j]){
					Z[i][j] = Z[i][j-1];
				}
				else{
					Z[i][j] = Z[i-1][j];
				}
			}
		}
	}
}

int main(){
	LCS_Length();
	for(int i = 1; i < 8; i++){
		for(int j = 1; j < 7; j++){
			printf("%d, ", Z[i][j]);
		}
		printf("\n");
	}
	return 0;
}
*/

/* Matrix Chain Multiplication Problem
#define N 7
#define INFTY 1000000
int p[N] = {30, 35, 15, 5, 10, 20, 25};
int res[N][N], s[N][N];

void Matrix_Chain_Order(){
	for(int i = 1; i < N; i++){
		res[i][i] = 0;
	}
	for(int len = 2; len < N; len++){
		for(int i = 1; i <= N - len; i++){
			int j = i + len - 1, min_res;
			res[i][j] = INFTY;
			
			for(int k = i; k < j; k++){
				min_res = res[i][k] + res[k+1][j] + p[i-1]*p[k]*p[j];
				if(min_res < res[i][j]){
					res[i][j] = min_res;
					s[i][j] = k;
				}
			}
		}
	}
}
int main(){
	Matrix_Chain_Order();
	for(int i = 1; i < N; i++){
		for(int j = 1; j < N; j++){
			printf("%5d, ", res[i][j]);
		}
		printf("\n");
	}
	return 0;	
}
*/
/* Cut_Rod problem
int price[11] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

void Cut_Rod(int len, int* res){
	int max_res = price[len];
	for(int i = 1; i <= len; i++){
		if(price[i] + res[len - i] > max_res){
			max_res = price[i] + res[len - i];
		}	
	}
	res[len] = max_res;
}


int main(){
	int len = 10, res[11] = {0};
	for(int i = 1; i <= len; i++){
		Cut_Rod(i, res);
		printf("%2d, ", res[i]);
	}
	printf("\n");
	return 0;
}
*/
