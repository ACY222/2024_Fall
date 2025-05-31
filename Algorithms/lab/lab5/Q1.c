// 魔法书架
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define DEBUG 1
#define max(x, y)   (x >= y ? x : y)
#define min(x, y)   (x >= y ? y : x)

void Print_Values(int num_rows, int num_cols, int64_t **Values, char *state) {
    if(DEBUG) {
        printf("%s:\n", state);
        for(int i = 1; i <= num_rows; i++) {
            for(int j = 1; j <= num_cols; j++) {
                printf("%2"PRId64", ", Values[i][j]);
            }
            printf("\n");
        }
    }
    return;
}

void Print_Res(int num_books, int64_t *res, char *state) {
    if(DEBUG) {
        printf("%s: \n", state);
        for(int i = 1; i <= num_books; i++) {
            printf("%2"PRId64", ", res[i]);
        }
        printf("\n");
    }
}

int64_t **Input(int *num_rows, int *num_cols, int *num_books) {
    scanf("%d %d %d", num_rows, num_cols, num_books);

    int64_t **Values = (int64_t **)malloc(sizeof(int64_t *) * (*num_rows + 1));
    for (int i = 1; i <= *num_rows; i++) {
        Values[i] = (int64_t *)malloc(sizeof(int64_t) * (*num_cols + 1));
        for (int j = 1; j <= *num_cols; j++) {
            scanf("%"SCNd64, &Values[i][j]);
        }
    }
    for(int i = 1; i <= *num_rows; i++) {
        Values[i][0] = 0;
    }
    Print_Values(*num_rows, *num_cols, Values, "Input Values");
    return Values;
}

int64_t **Preprocess(int num_rows, int num_cols, int64_t **Values) {
    for(int i = 1; i <= num_rows; i++) {
        for(int j = 2; j <= num_cols; j++) {
            Values[i][j] += Values[i][j - 1];
        }
    }
    Print_Values(num_rows, num_cols, Values, "Processed Values");
    return Values;
}

void Initialize_Res(int num_books, int64_t **res) {
    *res = (int64_t *)malloc(sizeof(int64_t) * (num_books + 1));
    
    for(int num_book = 1; num_book <= num_books; num_book++) {
        (*res)[num_book] = 0;
    }
    return;
}

int64_t *Get_Total_Knowledge(int num_rows, int num_cols, int64_t **Values,
                            int num_books, int64_t *res) {
    int limited_rows = (num_books + num_cols - 1) / num_cols;

    for(int i = 1; i <= num_rows; i++) {
        for(int num_book = min(i * num_cols, num_books); num_book >= 1; num_book--) {
            if(i == 1) {
                res[num_book] = Values[i][num_book];
            }
            else {
                for(int j = max(num_book - (num_cols * (i - 1)), 1); j <= min(num_cols, num_book); j++) {
                    res[num_book] = max(res[num_book], Values[i][j] + res[num_book - j]);
                }
            }
        }
    }
    Print_Res(num_books, res, "Total Knowledge all in one");
    return res;
}

int main() {
    int64_t **Values, *res;
    int num_rows, num_cols, num_books, **res_description, *first, *second;
    Values = Input(&num_rows, &num_cols, &num_books);
    Values = Preprocess(num_rows, num_cols, Values);

    Initialize_Res(num_books, &res);
    res = Get_Total_Knowledge(num_rows, num_cols, Values, num_books, res);

    printf("%"PRId64"\n", res[num_books]);

    return 0;
}