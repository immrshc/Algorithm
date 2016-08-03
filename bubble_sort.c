#include <stdio.h>
#include <stdlib.h>

//目的：配列の後ろから前へ前後を比較して昇順にならべる
//bubble_sort: [int] -> int -> void
void bubble_sort(int a[], int n){
    //ループ変数
    int i, j, t;

    //どのインデックスまで小さい数を求めるか
    for(i = 0; i < n - 1; i++){
        //配列の後ろから前へ求めるインデックスまで比較する
        for(j = n - 1; j > i; j--){
            //前の方が大きければ入れ替える
            if(a[j-1] > a[j]){
                t = a[j];
                a[j] = a[j-1];
                a[j-1] = t;
            }
        }
        printf("%d番目の値: %d\n", i, a[i]);
    }
}

int main(){
    int a[11] = {9, 20, 5, 4, 3, 55, 34, 4, 1, 11, 2};
    bubble_sort(a, 11);
    return 0;
}
