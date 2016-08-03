#include <stdio.h>
#include <stdlib.h>

//作業領域の大きさを定義する
#define MAX_ELEMENTS 10000

//マージソートに使う作業領域
int b[MAX_ELEMENTS];

//目的: 配列を最小単位まで分割し、整列してから配列を結合させる
//marge_sort: int a[] -> int low -> int high -> void
void merge_sort_array(int a[], int low, int high){
    int mid, i, j, k;
    //要素が一つしかない自明な場合
    if(low >= high){
        return;
    }
    //列を分割する場所midを決める
    mid = (low + high) / 2;
    //前半の配列を再帰的に整列する
    merge_sort_array(a, low, mid);    
    //後半の配列を再帰的に整列する
    merge_sort_array(a, mid + 1, high);
    //前半の要素をそのまま作業用配列bにコピーする
    for(i = low; i <= mid; i++){
        b[i] = a[i];
    }
    //後半の要素をそのまま作業用配列bにコピーする
    for(i = mid + 1, j = high; i <= high; i++, j--){
        b[i] = a[j];
    }
    //作業用配列bの両端から取り出したデータをマージして配列aに格納する
    i = low; j = high;
    for(k = low; k <= high; k++){
        if(b[i] <= b[j]){
            a[k] = b[i++];
        }else{
            a[k] = b[j--];
        }
    }
}

int main(){
    int i;
    int a[11] = {9, 20, 5, 4, 3, 55, 34, 4, 1, 11, 2};
    merge_sort_array(a, 0, 10);
    for(i = 0; i < 11; i++){
        printf("%d: %d\n", i, a[i]);
    }
    return 0;
}
