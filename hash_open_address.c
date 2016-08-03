#include <stdio.h>
#include <stdlib.h>

//データの定義
#define KEY int
#define DATA int
#define EMPTY (KEY)0
#define DELETED (KEY)1

//ハッシュ表の定義
#define BUCKET_SIZE 10

typedef struct bucket {
    KEY key;
    DATA data;
} BUCKET;

BUCKET table[BUCKET_SIZE];

//ハッシュ関数
int hash(KEY key){
    return key % BUCKET_SIZE;
}

//KEYの比較
int keyequal(KEY a, KEY b){ 
    if (a == b){ 
        return 1;
    } else {
        return 0;
    }   
}

//再ハッシュ関数
//rehash: int -> int
int rehash(int h){
    return (h + 1) % BUCKET_SIZE;
}

//ハッシュ表を初期化
//バケットを全てEMPTYにする
//init: void -> void
void init(){
    int i;
    for (i = 0; i < BUCKET_SIZE; i++){
        table[i].key = EMPTY;
    }
}

//ハッシュ表の探索
//find: KEY -> DATA
DATA *find(KEY key){
    //ハッシュ値を求める
    int h, count;
    KEY k;

    h = hash(key);
    count = 0;

    //空白になるまでKEYの照合をする
    while((k = table[h].key) != EMPTY){
        //削除済みではなく、KEYが等しい場合
        if (k != EMPTY && keyequal(k, key)){
            printf("データの探索key: %d, data: %d\n", k, table[h].data);
            return &table[h].data;
        }
        //見つからずに、バケット数以上を探索した場合
        if (++count > BUCKET_SIZE){
            printf("データの追加をしたが、追加する余地が存在しなかった\n");
            return NULL;
        }
        //再ハッシュ
        h = rehash(h);
    }
    return NULL;
} 

//ハッシュ表へのデータの追加
//insert: KEY -> &DATA -> int;
int insert(KEY key, DATA *data){
    //ハッシュ値を求める
    int h, count;
    KEY k;

    h = hash(key);
    count = 0;

    //空白または削除済みを探す
    while((k = table[h].key) != EMPTY && k != DELETED){
        //空白または削除済みが見つからない場合
        //既に存在していた場合
        if (keyequal(k, key)){
            return 0;
        }
        //見つからずに、バケット数以上を探索した場合
        if (++count > BUCKET_SIZE){
            printf("データの追加をしたが、追加する余地が存在しなかった\n");
            return 0;
        }
        //再ハッシュする
        h = rehash(h);
    }
    //空白または削除済みが見つかった場合
    table[h].key = key;
    table[h].data = *data;
    printf("データの追加key: %d, data: %d\n", key, table[h].data);
    return 1;
}

//ハッシュ表からのデータの削除
//空白になるまでKEYの照合をする
//delete: KEY -> int
int delete(KEY key){
    //ハッシュ値を求める
    int h, count;
    KEY k;

    h = hash(key);
    count = 0;

    //空白になるまで探索する
    while((k = table[h].key) != EMPTY){
        //KEYが一致するかどうか照合する
        if (k != DELETED && keyequal(k, key)){
            printf("データの削除key: %d, data: %d\n", k, table[h].data);
            table[h].key = DELETED;
            return 1;
        }
        //一致せずに、バケット数以上を探索した場合
        if (++count > BUCKET_SIZE){
            printf("データの削除をしたが、該当する値が存在しなかった\n");
            return 0;
        }
        //再ハッシュする
        h = rehash(h);
    }
    //空白になった場合
    return 0;
}

int main(){
    int i;
    init();

    for (i = 0; i < BUCKET_SIZE + 1; i++){
        printf("挿入の結果: %d\n", insert(i, &i));
    }

    for (i = 0; i < BUCKET_SIZE + 1; i++){
        printf("探索の結果: %p\n", find(i));
    }

    for (i = 0; i < BUCKET_SIZE + 1; i++){
        printf("削除の結果: %d\n", delete(i));
    }
    return 0;
}





