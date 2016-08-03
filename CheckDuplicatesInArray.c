#include <stdio.h>
#include <stdlib.h>

//テスト用の配列
int a[11] = {9, 20, 5, 4, 3, 55, 34, 4, 1, 11, 2};
//配列の最終インデックス
int n = 10;
//ヒープソートの関数プロトタイプ宣言
void HeapSort(int A[], int n);

//重複を含む要素の有無を調べる
//CheckDuplicatesInArray: int A[] -> int n -> bool

//要素を一つずつ走査し、残りの要素と一致するか調べる
//時間計算量: O(n^2)
int CheckDuplicatesInArray_1(int A[], int n){
    //着目する要素を決める
    int i, j;
    for(i = 0; i < n; i++){
        //重複を確認する
        for(j = i + 1; j < n; j++){
            //一致するか確認
            if(A[i] == A[j]){
                return A[i];
            }
        }
    }
    return 0;
}

//ソートして、隣の要素が同じかどうか調べる
//時間計算量: nlogn + n = O(nlogn)
int CheckDuplicatesInArray_2(int A[], int n){
    //ヒープソートで整列する
    HeapSort(A, n);
    //隣の要素を確認する
    int i;
    for(i = 0; i < n - 1; i++){
        //一致するか確認
        if(A[i] == A[++i]){
            return A[i];
        }
    }
    return 0;
}

//ヒープソート
void DownHeap(int a[], int from, int to){
    int i, j;
    int val;

    val = a[from];
    //根から初めて、節iが子を持っている限り繰り返す
    i = from;
    while(i <= to/2){
        //節jのこのうち小さい方を節jとする
        j = i * 2;
        if(j+1 <= to && a[j] > a[j+1]){
            j++;
        }
        //親が子より小さい時はこれ以上沈めない
        if(val <= a[j]){
            break;
        }
        //節iに節jの値を入れて、節jに注目する
        a[i] = a[j];
        i = j;
    }
    //先頭にあった要素を節iに入れる
    a[i] = val;
}

//配列aをヒープする
void HeapSort(int a[], int n){
    int i;
    int tmp;

    for(i = n/2; i >= 0; i--){
        DownHeap(a, i, n);
    }

    for(i = n; i >= 1; i--){
        tmp = a[0];
        a[0] = a[i];
        a[i] = tmp;
        DownHeap(a, 0, i-1);
    }
}

int main(){
    int i;
    //HeapSort(a, n);
    //int value = CheckDuplicatesInArray_1(a, n);
    int value = CheckDuplicatesInArray_2(a, n);
    if(i = value){
        printf("%d is duplicated.\n", i);
    }
    for(i = 0; i < n+1; i++){
        printf("%d: %d\n", i, a[i]);
    }
    return 0;
}


