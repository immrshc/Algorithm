//チェイン法による探索
#include <stdio.h>
#include <stdlib.h>

//
#define KEY int
#define DATA int

//ハッシュ表の定義
#define BUCKET_SIZE 10

typedef struct cell {
    KEY key;
    DATA data;
    struct cell *next;
} CELL;

CELL *table[BUCKET_SIZE];

//ハッシュ関数
int hash(KEY key){
    return key % BUCKET_SIZE;
}

//keyの比較
int keyequal(KEY a, KEY b){
    if (a == b){
        return 1;
    } else {
        return 0;
    }
}

//ハッシュの初期化
void init(){
    int i;
    for (i = 0; i < BUCKET_SIZE; i++){
        table[i] = NULL;
    }
}

//ハッシュ表を探索
//find: KEY -> DATA
DATA *find(KEY key){
    CELL *p;
    //ハッシュ値のインデックスから線形探索する
    for (p = table[hash(key)]; p != NULL; p = p->next){
        //一致するかどうか確認する
        if (keyequal(key, p->key)){
            return &p->data;
        }
    }
    return NULL;
}

//ハッシュ表への挿入
//insert: KEY, DATA -> int 
int insert(KEY key, DATA *data){
    CELL *p;
    int h;
    
    //既に存在しているかどうかを確認する
    if (find(key) != NULL){
        return 0;
    }
    //メモリがあるかどうか確認する
    if ((p = malloc(sizeof(CELL))) == NULL){
        fprintf(stderr, "Out of memory\n");
        exit(2);
    }
    //ハッシュ値に応じたバケットの先頭に追加する
    h = hash(key);
    p->key = key;
    p->data = *data;
    p->next = table[h];
    table[h] = p;
    printf("ハッシュ表へ挿入したKEY: %d, DATA: %d, ハッシュ値: %d\n", p->key, p->data, h);
    return 1;
}

//ハッシュ表からの削除
//delete: KEY -> int
int delete(KEY key){
    int h;
    CELL *p, *q;

    h = hash(key);
    //存在しているかどうか確認する
    if (table[h] == NULL){
        return 0;
    }
    //バケット自体が削除の対象の場合
    if (keyequal(key, table[h]->key)){
        p = table[h];
        table[h] = p->next;
        printf("ハッシュ表の先頭から削除したKEY: %d, DATA: %d, ハッシュ値: %d\n", p->key, p->data, h);
        free(p);
        return 1;
    }
    //バケットの二番目以降のリストを探索する
    for (q = table[h], p = q->next; p != NULL; q = p, p = p->next){
        if (keyequal(key, p->key)){
            q->next = p->next;
            printf("ハッシュ表の先頭から削除したKEY: %d, DATA: %d, ハッシュ値: %d\n", p->key, p->data, h);
            free(p);
            return 1;
        }
    }
    return 0;
}   

int main(){
    int i;
  
    init();
    for (i = 0; i < BUCKET_SIZE * 3; i++){
        printf("insertの結果: %d\n", insert(i, &i));
    }
    for (i = 0; i < BUCKET_SIZE * 3; i++){
        printf("deleteの結果: %d\n", delete(i));
    }
    return 0;
}


