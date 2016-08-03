#include <stdio.h>
#include <stdlib.h>

//ハッシュテーブルのラベル
#define EMPTY -1
#define DELETED -2
#define BUCKET_SIZE 3

//テスト用の配列
int a[16] = {0, 1, 2, 1, 1, 0, 0, 1, 2, 1, 0, 0, 2, 1, 1};

//配列の最終インデックス
int n = 15;

//クイックソートの関数プロトタイプ宣言
void QuickSort(int *A, int n);
int Partition(int *A, int l, int r);

//ハッシュテーブルをオープンアドレス法により処理する際の関数プロトタイプ宣言
int Hash(int key);
int ReHash(int h);
void InitTable();
void Insert(int key);
int GetCounterFromTable(int bucket);

//要素が三種類しかないので、一回の分割で終わる
//要素が三種類の配列の最多出現数の要素を返す
//QuickSortTreeItems: int *A -> int n -> int
//時間計算量: O(n)
int QuickSortTreeItems(int *A, int n){
    QuickSort(A, n);
    int i, j;
    int currentCounter = 1, maxCounter = 1;
    int currentNumber = A[0], maxNumber = A[0];
    //着目する要素を決める
    for(i = 1; i <= n; i++){
        //隣と一致するか確認する
        if(A[i] == currentNumber){
            //一致すればカウンタを増分する
            currentCounter++;
        }else{
            //一致しなければ次の要素から数え直す
            currentNumber = A[i];
            currentCounter = 1;
        }
        //最多出現数を更新する
        if(currentCounter > maxCounter){
            maxCounter = currentCounter;
            maxNumber = currentNumber;
        }
    }
    return maxNumber;
}

//ハッシュ表を使って探索をして見つかるとカウンタを増分する
//要素が三種類の配列の最多出現数の要素を返す
//HashTreeItems: int key -> int
int HashTreeItems(int *A, int n){
    int i, j, k, t;
    int currentCounter = 0, maxCounter = 0;
    int currentNumber = A[0], maxNumber = A[0];
    //ハッシュテーブルの作成
    InitTable();
    for(i = 0; i <= n; i++){
        Insert(A[i]);
    }
    //ハッシュテーブルから出現回数の取り出し
    for(j = 0; j < BUCKET_SIZE; j++){
        //要素の出現回数を取得
        if(t = GetCounterFromTable(j)){
            currentCounter = t;
            currentNumber = A[j];
        }
        //暫定最多回数を上回るか確認
        if(currentCounter > maxCounter){
            maxCounter = currentCounter;
            maxNumber = currentNumber;
        }
    }
    //最多出現回数を持つ要素を返す
    return maxNumber;
}

//要素の各値とその数を持つデータ構造を定義
typedef struct bucket{
    int key;// = EMPTY;
    int count;// = 0;
} BUCKET;

//ハッシュテーブルの定義
BUCKET table[BUCKET_SIZE];

//要素が一づつ異なる三種類だとわかっているので、それに対応したハッシュ関数
int Hash(int key){
    return key % BUCKET_SIZE;
}

//再ハッシュ関数
//rehash: int -> int
int ReHash(int h){
    return (h + 1) % BUCKET_SIZE;
}

//ハッシュテーブルの初期化
//Init: void -> void
void InitTable(){
    int i;
    for(i = 0; i < BUCKET_SIZE; i++){
        table[i].key = EMPTY;
    }
}

//配列の要素のハッシュテーブルへの挿入し、既に重複があるとカウンタを増分する
//Insert: int key -> void
void Insert(int key){
    //ハッシュ値を求める
    int h, round;
    int k;
    h = Hash(key);
    printf("hash: %d\n", h);
    printf("key: %d\n", table[h].key);
    printf("count: %d\n", table[h].count);
    printf("===============================\n");
    //挿入できる空白、削除済みラベルを探す
    round = 0;
    while((k = table[h].key) != EMPTY && k != DELETED){
        //既に同じ値が存在していた場合
        if(k == key){
            table[h].count++;
            return;
        }
        //バケット数以上を超えた場合
        if(++round > BUCKET_SIZE){
            printf("データを追加する余地が存在しなかった\n");
            return;
        }
        //見つからなかったので、再ハッシュする
        h = ReHash(h);
    }
    //空白、削除済みが見つかった場合
    table[h].key = key;
    table[h].count = 1;
}

//ハッシュテーブルのバケットのカウンタの値を返す
//GetCounterFromTable: int bucket -> int
int GetCounterFromTable(int bucket){
    int k;
    //ハッシュテーブルに該当する配列の値を持つバケットが存在する場合
    if(bucket < BUCKET_SIZE && (k = table[bucket].key) != EMPTY && k != DELETED){
        //配列の要素が見つかった場合
        return table[bucket].count;
    }
    //登録されていない場合
    return 0;
}

//クイックソート
//枢軸を基準にその大小ごとに分割して、再帰的に整列する
//QuickSort: int *A[] -> int l -> int r -> void
void QuickSort(int *A, int n){
    int l, r, v;
    int low[n], high[n];
    int sp;
    //スタックを初期化する
    low[0] = 0;
    high[0] = n - 1;
    sp = 1;
    //スタックが空になるまで繰り返す
    while(sp > 0){
        sp--;
        l = low[sp];
        r = high[sp];
        //整列する要素が一つなら何もしない
        if(l >= r){
            ;
        }else{
            //枢軸を基準に分割する
            v = Partition(A, l, r);
            //左右の部分配列のうち短い方を先に処理する
            if(v - l < r - v){
                //左の部分を後からスタックに乗せる
                low[sp] = v + 1;
                high[sp++] = r;
                low[sp] = l;
                high[sp++] = v - 1;
            }else{
                //右の部分を後からスタックに乗せる
                low[sp] = l;
                high[sp++] = v - 1;
                low[sp] = v + 1;
                high[sp++] = r;
            }
        }
    }
}

//枢軸を決定し、その大小ごとの部分に配列を並び替え、枢軸のインデックスを返す
//Partition: int *A[] -> int l -> int r -> int v 
int Partition(int *A, int l, int r){
    //変数の初期化
    int i, j, pivot, t;
    i = l - 1;
    j = r;
    pivot = A[r];
    //左右のポインタがぶつかるまで進める
    for(;;){
        //枢軸より小さければ右に進む
        while(A[++i] < pivot);
        //枢軸よりも大きければ左に進む
        while(i < --j && A[j] > pivot);
        //左右のポインタがぶつかるとループを抜ける
        if(i >= j){
            break;
        }
        //左右のポインタの値を交換する
        t = A[i]; A[i] = A[j]; A[j] = t;
    }
    //左のポインタと枢軸を入れ替える
    t = A[i]; A[i] = A[r]; A[r] = t;
    return i;
}

//テスト
int main(){
    int i, value;
    //QuickSort(a, n+1);
    //value = QuickSortTreeItems(a, n+1);
    value = HashTreeItems(a, n);
    printf("MaxNumber: %d\n", value);
    /*
    for(i = 0; i <= n; i++){
        printf("Array, %d: %d\n", i, a[i]);
    }
    */
    for(i = 0; i < BUCKET_SIZE; i++){
        printf("BUCKET: %d, KEY: %d, COUNT: %d\n", i, table[i].key, table[i].count);
    }
    return 0;
}
