#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define longlong    int64_t
#define pll         PRId64
#define sll         SCNd64
#define DEBUG       0

typedef struct {
    longlong pos, height;
}lego;

longlong pop(lego *stack, longlong *sp) {
    if(*sp <= 0) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack[--(*sp)].height;
}

void push(lego *stack, longlong *sp, longlong height, longlong pos) {
    while(*sp >= 1 && height <= stack[*sp - 1].height) {
        longlong pop_height = pop(stack, sp);
        if(DEBUG) {
            printf("stack[top].height(%"pll") >= height(%"pll")\n", pop_height, height);
        }
    }
    stack[*sp].height = height;
    stack[*sp].pos = pos;
    (*sp)++;
    return;
}


longlong *Input(longlong *num) {
    scanf("%"pll, num);
    longlong *height = (longlong *)malloc(sizeof(longlong) * *num);
    for(int i = 0; i < *num; i++) {
        scanf("%"pll, &height[i]);
    }

    if(DEBUG) {
        printf("The input lego heights are:\n");
        for(int i = 0; i < *num; i++) {
            printf("%"pll" ", height[i]);
        }
        printf("\n");
    }
    return height;
}

longlong *Scan_Forward(longlong *height, longlong num) {
    lego *mono_stack = (lego *)malloc(num * sizeof(lego));
    longlong *record = (longlong *)malloc(num * sizeof(longlong)), sp = 0;
    for(int i = 0; i < num; i++) {
        push(mono_stack, &sp, height[i], i);
        if(sp == 1) {
            record[i] = -1;
        }
        else {
            record[i] = mono_stack[sp - 2].pos;
        }
    }

    if(DEBUG) {
        printf("The scan_forward record are:\n");
        for(int i = 0; i < num; i++) {
            printf("%"pll", ", record[i]);
        }
        printf("\n");
    }
    return record;
}

longlong *Reverse_Height(longlong *height, longlong num) {
    longlong *reverse = (longlong *)malloc(num * sizeof(longlong));
    for(int i = 0; i < num; i++) {
        reverse[i] = height[num - i - 1];
    }
    return reverse;
}

longlong *Reverse_Record(longlong *reverse_record, longlong num) {
    longlong *record = (longlong *)malloc(num * sizeof(longlong));
    for(int i = 0; i < num; i++) {
        record[i] = num - 1 - reverse_record[num - 1 - i];
    }
    return record;
}

longlong *Scan_Backward(longlong *height, longlong num) {
    longlong *reverse_height = Reverse_Height(height, num);
    longlong *reverse_record = Scan_Forward(reverse_height, num);
    longlong *record = Reverse_Record(reverse_record, num);
    free(reverse_record);
    free(reverse_height);
    if(DEBUG) {
        printf("The scan_backward record are:\n");
        for(int i = 0; i < num; i++) {
            printf("%"pll", ", record[i]);
        }
        printf("\n");
    }
    return record;
}

void Find_Max_Area(longlong *height, longlong *record1, longlong *record2, longlong num) {
    longlong *broadth = (longlong *)malloc(num * sizeof(longlong)); 
    longlong *area = (longlong *)malloc(num * sizeof(longlong));
    longlong max_area = 0;
    for(int i = 0; i < num; i++) {
        broadth[i] = record2[i] - record1[i] - 1;
        area[i] = broadth[i] * height[i];
        max_area = area[i] > max_area ? area[i] : max_area;
    }

    if(DEBUG) {
        printf("The area of all fabrics are:\n");
        for(int i = 0; i < num; i++) {
            printf("%"pll", ", area[i]);
        }
        printf("\n");
    }
    printf("%"pll"\n", max_area);
    return;
}
int main() {
    longlong num, *height, *record1, *record2;
    height = Input(&num);
    record1 = Scan_Forward(height, num);
    record2 = Scan_Backward(height, num);
    Find_Max_Area(height, record1, record2, num);

    return 0;
}