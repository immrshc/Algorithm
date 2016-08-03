#include <stdio.h>
#include <stdlib.h>

//目的:シェルソート、配列のインデックスの数列に応じた値の
//     部分配列を挿入ソートし、数列の間隔を1になるまで、繰り返す
//shell_sort: int a[] -> int n -> void
void shell_sort(int a[], int n){
    //ループ変数
    int i, j, t, h;
    //数列を作るループ文
    for(h = 1; h < n/9; h = h * 3 + 1);
    //数列を進むループ文
    for(;h > 0; h /= 3){
        //整列された範囲を決める
        for(i = h; i < n; i++){
            j = i;
            //範囲の隣の値を比較する
            while(j >= h && a[j-h] > a[j]){
                //前の値が大きければ入れ替える
                t = a[j];
                a[j] = a[j-h];
                a[j-h] = t;
                //次の値に進むためにhだけ移動
                j -= h;
            }
        }
    }
}

int main(){
    int i;
    int a[11] = {9, 20, 5, 4, 3, 55, 34, 4, 1, 11, 2};
    
    shell_sort(a, 11);
    for(i = 0; i < 11; i++){
        printf("%d番目の値: %d\n", i, a[i]);
    }
    
    return 0;
}
