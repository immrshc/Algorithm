#include <stdio.h>
#include <stdlib.h>

//関数プロトタイプ宣言
int partition(int a[], int l, int r);

//目的:スタックを用いてクイックソートを実装する
//quick_sort_2: int a[] -> int n -> void
void quick_sort_2(int a[], int n){
    int l, r, v;
    int low[30], high[30];
    int sp;

    //スタックを初期化する
    low[0] = 0;
    high[0] = n - 1;
    sp = 1;

    //スタックが空になるまで繰り返す
    while(sp > 0){
        //スタックから整列する範囲を取り出す
        sp--;
        l = low[sp];
        r = high[sp];
        //整列する要素が一つなら何もしない
        if(l >= r){
            ;
        }else{
            //枢軸を基準に分割する
            v = partition(a, l, r);
            //左右の部分配列のうち短い方を先に処理する
            if(v - l < r - v){
                //左部分配列を先に整列する
                low[sp] = v + 1;
                high[sp++] = r;
                low[sp] = l;
                high[sp++] = v - 1;
            }else{
                //右部分配列を先に整列する
                low[sp] = l;
                high[sp++] = v - 1;
                low[sp] = v + 1;
                high[sp++] = r;
            }
        }
    }
}

//目的: 枢軸を選び、その大小ごとに配列を分割し、枢軸のインデックスを返す
//partition: int a[] -> int l -> int r -> int v
int partition(int a[], int l, int r){
    //変数を初期化する
    int i, j, pivot, t;
    i = l - 1;
    j = r;
    pivot = a[r];
    //左右のポインタがぶつかるまで進める
    for(;;){
        //枢軸より小さければ、左のポインタを進める
        while(a[++i] < pivot);
        //枢軸より大きければ、右のポインタを進める
        while(i < --j && a[j] > pivot);
        //左右のポインタがぶつかるとループを抜ける
        if(i >= j){
            break;
        }
        //左右のポインタの指す値を入れ替える
        t = a[i]; a[i] = a[j]; a[j] = t;
    }
    //左のポインタと枢軸を入れ替える
    t = a[i]; a[i] = a[r]; a[r] = t;
    return i;
}

int main(){
    int i;
    int a[11] = {9, 20, 5, 4, 3, 55, 34, 4, 1, 11, 2};                 
    quick_sort_2(a, 11);
    for(i = 0; i < 11; i++){
        printf("%d: %d\n", i, a[i]);
    }   
    return 0;
}
