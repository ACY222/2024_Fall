// 女巫的炼金术
#include<stdio.h>
#include<inttypes.h>

#define mod 1000000007
#define N 1000001

int64_t check[N];
int list_val[N], pre[N*2];
// the first N is the element in the list, and the last N is for their ancestors

int Trace_Source(int x){
    int source = x;
    while(pre[source] != 0){
        source = pre[source];
    }
    pre[x] = source;
    return source;
}

void Merge(int x, int y){
    int source_x = Trace_Source(x), source_y = Trace_Source(y);
    if(source_x == source_y){     // x and y are in the same heap
        return;
    }
    else{
        pre[source_x] = source_y;   // Merge
    }
    check[source_y - N] = (check[source_x - N] * check[source_y - N]) % mod;
    return;
}

int64_t ExtendedEuclidean(int64_t a, int64_t b, int64_t *x, int64_t *y){
    if(a == 0){
        *x = 0;
        *y = 1;
        return b;
    }
    int64_t x1, y1;
    int64_t gcd = ExtendedEuclidean(b % a, a, &x1, &y1);
    *x = y1 - (b/a) * x1;
    *y = x1;
    return gcd;
}

int64_t ModInverse(int64_t a, int64_t p){
    int64_t x, y, res;
    ExtendedEuclidean(a, p, &x, &y);
    res = (x % p + p) % p;
    return res;
}


void Move(int x, int y){
    int source_x = Trace_Source(x), source_y = Trace_Source(y);
    if(source_x == source_y){           // x, y are in the same heap
        return;
    }
    int64_t check_inv = ModInverse(list_val[x], mod);
    check[source_x - N] = (check[source_x - N] * check_inv) % mod;

    pre[x] = source_y;
    check[source_y - N] = (check[source_y - N] * list_val[x]) % mod;
    return;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%d", &list_val[i]);
        check[i] = list_val[i];
        pre[i] = i + N;
    }
    for(int i = 0; i < m; i++){
        int type, x, y;
        scanf("%d", &type);
        switch(type){
            case 1:
                scanf("%d %d", &x, &y);
                Merge(x, y);
                break;
            case 2:
                scanf("%d", &x);
                printf("%"PRId64"\n", check[Trace_Source(x) - N]);
                break;
            default:
                scanf("%d %d", &x, &y);
                Move(x, y);
                break;
        }
    }
    return 0;
}