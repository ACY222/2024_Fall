// 买花 Over
#include<stdio.h>
#include<stdint.h>
#include<inttypes.h>
#define N 100000
#define INFTY 100000
int main(){
    int n;
    int64_t input[N] = {0}, max_now = -INFTY, max_new = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%"SCNd64, &input[i]);
        max_new += input[i];
        if(max_now < max_new){
            max_now = max_new;
        }
        if(max_new < 0){
            max_new = 0;
        }
    }
    printf("%"PRId64"\n", max_now);

    return 0;
}
/* 没想到这么简单的一个代码写了这么久，总结一下过程中出现的一些问题
 * 1. 对于 int_64t, long long int 了解很少，尤其是他们在 printf(), scanf()中的参数
 * 2. scanf("%s", array)中，如果出现" "会停止输入，这个问题没有考虑到
*/