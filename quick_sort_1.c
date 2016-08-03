#include <stdio.h>
#include <stdlib.h>

//関数プロトタイプ宣言
int partition(int a[], int l, int r);

//目的: 枢軸を基準にその大小ごとに分割して、再帰的に整列する
//quick_sort: int a[] -> int l -> int r -> void
void quick_sort_1(int a[], int l, int r){

    int v;
    //整列する要素が一つの場合
    if(l >= r){
        return;
    }
    //自明でない場合
    //枢軸を選んで、配列をその大小ごとの部分に分割する
    v = partition(a, l, r);
    //左の部分を再帰的に整列する
    quick_sort_1(a, l, v-1);
    //右の部分を再帰的に整列する
    quick_sort_1(a, v+1, r);
}

//目的: 枢軸を決定し、その大小ごとの部分に配列を並び替え、枢軸のインデックスを返す
//partition: int a[] -> int l -> int r -> int v
int partition(int a[], int l, int r){
    
    //変数の初期化
    int i, j, pivot, t;
    i = l - 1;
    j = r;
    pivot = a[r];
    //左右のポインタがぶつかるまで入れ替え処理をする
    for(;;){
        //左ポインタが枢軸より小さければ進む
        while(a[++i] < pivot);
        //右ポインタが枢軸より大きければ進む
        while(i < --j && pivot < a[j]);
        //ポインタがぶつかったらループを抜ける
        if(i >= j){
            break;
        }
        //ポインタの指す値を入れ替える
        t = a[i];
        a[i] = a[j];
        a[j] = t;
    }
    //枢軸と左ポインタを入れ替える
    t = a[i];
    a[i] = a[r];
    a[r] = t;
    return i;
}


int main(){
    int i;
    int a[11] = {9, 20, 5, 4, 3, 55, 34, 4, 1, 11, 2}; 
    
    quick_sort_1(a, 0, 11-1);
    for(i = 0; i < 11; i++){
        printf("%d: %d\n", i, a[i]);
    }

    return 0;

}
