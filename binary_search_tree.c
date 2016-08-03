//二分探索木
#include <stdio.h>
#include <stdlib.h>

//データ型のマクロ
#define KEY int

//節の定義
typedef struct node {
    KEY data;
    struct node *left, *right;
} NODE;

//節の初期化
NODE *root = NULL;

//関数プロトタイプ宣言
NODE *deletemin(NODE **p);

//目的：二つの引数のKEY型を比較し一致すれば1を返す
//keyequal: KEY -> KEY -> int
int keyequal(KEY a, KEY b){
    if (a == b) {
        return 1;
    }
    return 0;
}

//目的：二つの引数のKEY型を比較し、第二引数が大きいと1を返す
//keylt: KEY -> KEY -> int
int keylt(KEY a, KEY b){
    if (b > a) {
        return 1;
    }
    return 0;
}

//目的：二分探索木を探索する
//search: KEY -> NODE*
NODE *search(KEY key){
    NODE *p;
    p = root;
    
    //節が存在する場合
    while(p != NULL){
        //keyと節を比較する再帰
        //一致する場合
        if (keyequal(key, p->data)) {
            return p;
        //左部分木に進む場合
        } else if (keylt(key, p->data)) {
            printf("左部分木に進む: %p\n", p->left);
            p = p->left;    
        //右部分木に進む場合
        } else {
            printf("右部分木に進む: %p\n", p->right);
            p = p->right;
        }
    }
    //節が存在しない場合
    return NULL;
}

//目的：二分探索木への挿入
//insert: KEY -> NODE*
NODE *insert(KEY key){
    NODE **p, *new;
    p = &root;
    
    //節の子が存在する場合
    while(*p != NULL){
        //keyと*p->keyを比較する
        if (keyequal(key, (*p)->data)){
            //一致した場合
            printf("挿入しようとしたが、既に存在している\n");
            return NULL;
        } else if (keylt(key, (*p)->data)) {
            //左部分木に進む場合
            printf("左部分木に進む: %p\n", &(*p)->left);
            p = &(*p)->left;
        } else {
            //右部分木に進む場合
            printf("右部分木に進む: %p\n", &(*p)->right);
            p = &(*p)->right;
        }
    }
    //節の子が存在しない場合
    if((new = malloc(sizeof(NODE))) == NULL){
        fprintf(stderr, "out of memory");
    }
    new->left = NULL;
    new->right = NULL;
    new->data = key;
    *p = new;
    return new;
}   

//目的：二分探索木から要素を削除する
//delete: KEY -> int
int delete(KEY key){
    NODE **p, *x;
    p = &root;

    //削除対象の節の子が存在する場合
    while(*p != NULL){
        //keyを探索する
        if (keyequal(key, (*p)->data)){
            x = *p;
            //一致する場合
            if (x->left == NULL && x->right == NULL) {
                //葉を削除する
                *p = NULL;
            } else if (x->left == NULL) {
                //子が一つの節を削除してくり上げる
                *p = x->right;
            } else if (x->right == NULL) {
                //子が一つの節を削除してくり上げる
                *p = x->left;
            } else {
                //子が二つの節を削除する
                *p = deletemin(&x->right);
                (*p)->right = x->right;
                (*p)->left = x->left;
            }
            printf("要素を削除: %d\n", x->data);
            free(x);
            return 1;
        } else if (keylt(key, (*p)->data)) {
            //左部分木に進む場合
            printf("左部分木に進む: %p\n", &(*p)->left);
            p = &(*p)->left;
        } else {
            //右部分木に進む場合
            printf("右部分木に進む: %p\n", &(*p)->right);
            p = &(*p)->right;
        }
    }
    //削除対象が見つからなかった場合
    return 0;
}

//目的：引数の節の子から最小の節を削除して、引数の節と入れ替える
//deletemin: NODE** -> NODE*
NODE *deletemin(NODE **p){
    NODE *x;

    while((*p)->left != NULL){
        p = &(*p)->left;
    }
    x = *p;
    *p = (*p)->right;
    return x;
}

//目的：二分探索木への挿入、探索、削除を実施する
//main: void -> int
int main(){
    KEY i;
    NODE *result;

    for (i = 5; i < 10; i++){
        if ((result = insert(i)) != NULL){
            printf("挿入の結果: %d\n", result->data);
        } else {
            printf("挿入の結果: %p\n", result);
        }
    }
    

    for (i = 0; i < 15; i++){
        if ((result = insert(i)) != NULL){
            printf("挿入の結果: %d\n", result->data);
        } else {
            printf("挿入の結果: %p\n", result);
        }
    }
    
    for (i = 0; i < 20; i++){
        if ((result = search(i)) != NULL){
            printf("探索の結果: %d\n", result->data);
        } else {
            printf("探索の結果: 見つからない\n");
        }
    }
    
    for (i = 0; i < 15; i++){
        printf("削除の結果: %d\n", delete(i));
    }
    
    return 0;
}


