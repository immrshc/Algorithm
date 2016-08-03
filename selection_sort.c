#include <stdio.h>
#include <stdlib.h>

//目的：選択ソート、配列の最後から前へ最小値を保管し、
//      それを各インデックスに対応させることで昇順に並び替える
//selection_sort: int a[] -> int n -> void
void selection_sort(int a[], int n){
    //ループ変数
    int i, j, t, low_key, low_data;

    //何番目のインデックスの値を求めるか決める
    for(i = 0; i < n - 1; i++){
        //最小値を初期化
        low_key = i;
        low_data = a[i];
        //配列の最後尾から求めるインデックスまで最小値を求める
        for(j = n - 1; j > i; j--){
            //暫定最小値との比較で、前が小さければ暫定最小とする
            if(a[j] < low_data){
                low_key = j;
                low_data = a[j];
            }
        }
        //最後にインデックスの値に最終的な最小値と入れ替える
        t = a[i];
        a[i] = a[low_key];
        a[low_key] = t;
        printf("%d番目の値: %d\n", i, a[i]);
    }
}

int main(){
    int a[11] = {9, 20, 5, 4, 3, 55, 34, 4, 1, 11, 2};
    selection_sort(a, 11);
    return 0;
}
