#include <stdio.h>
#include <stdlib.h>

//テスト用の配列
int a[14] = {0, 13, 4, 1, 11, 3, 9, 5, 8, 0, 20, 2, 10, 1};

//配列の最終インデックス
int n = 13;
//中央値からの見つけ出す個数
int k = 3;
//ヒープソートの関数プロトタイプ宣言
void HeapSort(int A[], int n);

//配列の中央値からk番目番目未満の要素の配列のポインタとして出力する
//SelectFromMedian: int A[] -> int n -> int k -> int*

//ヒープソートで整列し、インデックスの中央からK-1番目までの要素の配列ポインタを返す
//時間計算量: n + klogk = 0(n+klogk)
int *SelectFromMedian(int *ary_p, int n, int *return_ary_p, int k){
    int i;
    int median = (0 + n) / 2;
    //ヒープソートで整列する    
    HeapSort(ary_p, n);
    for(i = 0; i < k; i++){
        //出力用配列に中央値からkまでの要素を格納する
        return_ary_p[i] = ary_p[median + i];
    }
    //配列の先頭アドレスを返す
    return return_ary_p;
}

//ヒープを構築する
void DownHeap(int *A, int from, int to){
    //親を決める
    int i, j, val;
    i = from;
    val = A[from];
    //節が子を持つ限り比較する
    while(i <= to / 2){
        //子の最大値を持つ節を節jとする
        j = i * 2;
        if(j < to && A[j] <= A[j+1]){
            j++;
        }
        //節jが沈める値よりも小さければ終了する
        if(val >= A[j]){
            break;
        }
        //節jを節iとして、階層を下げる
        A[i] = A[j];
        i = j;
    }
    A[i] = val;
}
//配列をヒープする
void HeapSort(int *A, int n){
    int i, tmp;
    //最下層の親を持つ節からヒープを構築する
    for(i = n / 2; i >= 0; i--){
        DownHeap(A, i, n);
    }
    //ヒープの最大値を取り出して、配列の後ろから順に格納する
    for(i = n; i > 0; i--){
        tmp = A[0];
        A[0] = A[i];
        A[i] = tmp;
        DownHeap(A, 0, i-1);
    }
}


//テスト
int main(){
    //HeapSort(a, n);
    int i;
    int b[k];
    int *p = SelectFromMedian(a, n, b, 3);
    printf("===================================\n");
    for(i = 0; i < k; i++){
        printf("Median + %d: %d\n", i, p[i]);
    }
    printf("===================================\n");
    for(i = 0; i <= n; i++){
        printf("Array, %d: %d\n", i, a[i]);
    }
    return 0;
}
