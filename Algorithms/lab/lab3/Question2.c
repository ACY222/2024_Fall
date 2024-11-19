#include <stdio.h>

#define MAX_WORD_NUM    5000001
#define MAX_WORD_LEN    51
#define MAX_STR_LEN     100001
// next -> Trie Tree, number -> the number of node x
int next[MAX_WORD_NUM][26], number[MAX_WORD_NUM], word_num, text_len, node_id;
char text[MAX_STR_LEN];

void insert(int len, char* word) {
    int node = 0, letter;
    for(int i = 0; i < len; i++){
        letter = word[i] - 'a';
        if(!next[node][letter]) {
            next[node][letter] = ++node_id;
        }
        node = next[node][letter];
    }
    number[node]++;
}

void input() {
    int len; 
    char word[MAX_WORD_LEN];
    scanf("%d %d", &word_num, &text_len);
    for(int i = 0; i < word_num; i++) {
        scanf("%d %s", &len, word);
        insert(len, word);
    }
    scanf("%s", text);
    return;
}

int match() {
    int count = 0;
    for(int ptr = 0; ptr < text_len; ptr++) {
        int node = 0, letter;
        for(int i = ptr; i < text_len; i++) {
            letter = text[i] - 'a';
            node = next[node][letter];
            if(node == 0) {        // no such subsequence
                break;
            }
            count += number[node];
        }
    }
    return count;
}

void print() {
    for(int i = 0; i < node_id; i++) {
        for(int j = 0; j < 4; j++) {
            printf("%d, ", next[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for(int i = 0; i < node_id; i++) {
        printf("%d, ", number[i]);
    }
    printf("\n");
    return;
}

int main() {
    input();
    // print();
    printf("%d\n", match());
    return 0;
}
