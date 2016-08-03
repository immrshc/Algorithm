#include <stdio.h>
#include <stdlib.h>

//目的：挿入ソート、整列された範囲の隣の値を、
//      範囲内で比較して並び替えることで、配列全体を昇順に整列する
//insertion_sort: int a[] -> int n -> void
void insertion_sort(int a[], int n){
    //ループ変数
    int i, j, t;
    //整列された範囲を決める
    for(i = 1; i < n; i++){
        //範囲の隣の値を比較する
        j = i;
        while(j >= 1 && a[j-1] > a[j]){
            //前の値が大きければ、入れ替える
            t = a[j];
            a[j] = a[j-1];
            a[j-1] = t;
            j--;
        }
    }
}

int main(){
    int i;
    int a[11] = {9, 20, 5, 4, 3, 55, 34, 4, 1, 11, 2};
    
    insertion_sort(a, 11);
    for(i = 0; i < 11; i++){
        printf("%d番目の値: %d\n", i, a[i]);
    }
    return 0;
}
