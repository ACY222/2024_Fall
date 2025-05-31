// Hello 回文串
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0
#define min(x, y)   (x >= y ? y : x)
#define max(x, y)   (x >= y ? x : y)

char *Input(int *len) {
    scanf("%d", len);
    char *str = (char *)malloc(sizeof(char) * (*len));
    scanf("%s", str);
    return str;
}

char *Preprocess(char *str, int len) {
    char *new_str = (char *)malloc(sizeof(char) * (2 * len + 1));
    new_str[0] = '#';
    for(int i = 0; i < len; i++) {
        new_str[2 * i + 1] = str[i];
        new_str[2 * i + 2] = '#';
    }
    // new_str[2 * len] = '$';
    if(DEBUG) {
        printf("The processed string:\n%s\n", new_str);
    }
    return new_str;
}

void Manacher(char *str, int len) {
    int center = 0, right_bound = -1, max_len = 0;
    int *p = (int *)malloc(sizeof(int) * (2 * len));
    for(int i = 0; i < 2 * len; i++) {
        p[i] = 0;
    }
    for(int i = 1; i < len * 2; i++) {
        int symmetric = 2 * center - i;
        p[i] = (i > right_bound) ? 1 : min(p[symmetric], right_bound - i + 1);
        while(i + p[i] <= 2 * len + 1 && i - p[i] >= 0 && str[i + p[i]] == str[i - p[i]]) {
            p[i]++;
        }
        p[i]--;
        max_len = max(max_len, p[i]);
        if(i + p[i] > right_bound) {
            center = i;
            right_bound = i + p[i];
        }
    }
    if(DEBUG) {
        printf("The p array:\n");
        for(int i = 1; i < len * 2; i++) {
            printf("%d, ", p[i]);
        }
        printf("\nThe max_len:\n");
    }
    printf("%d\n", max_len);
    return;
}

int main() {
    int len;
    char *str = Input(&len);
    str = Preprocess(str, len);
    Manacher(str, len);

    return 0;
}