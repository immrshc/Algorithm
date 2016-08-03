#include <stdio.h>
#include <stdlib.h>

//テスト用の配列
int a[14] = {0, 1, 4, 2, 4, 3, 4, 5, 3, 0, 4, 1, 0, 1};
int b[5] = {0, 1, 4, 7, 11};

//配列の最終インデックス
int n = 13;
int m = 4;
//制約の合計値
int k = 13;
//制約を満たす配列Bの要素
int d;
//ヒープソートの関数プロトタイプ宣言
void HeapSort(int A[], int n);
int BinarySearch(int A[], int n, int key);

//a + b = kとなる配列Aの要素aと配列Bの要素bの存在を確認する
//find: int A[] -> int B[] -> int n -> int m -> int k -> int

//ヒープソートで整列し、二分探索法によって制約を満たす要素を見つける
//時間計算量: nlogn + logn = 0(nlogn)
int find(int A[], int B[], int n, int m, int k){
    int i, c;
    //配列Aをヒープソートする
    HeapSort(A, n);
    //配列Bから要素を選ぶ
    for(i = 0; i <= m; i++){
        //制約条件を満たす要素を配列Aから二分探索法で探す
        c = k - B[i];
        if(BinarySearch(A, n, c)){
            d = B[i];      
            return c;
        }
    }
    return 0;
}

//ヒープを構築する
void DownHeap(int A[], int from, int to){
    int i, j;
    int val;
    val = A[from];
    //根から初めて節が子を持っている限り繰り返す
    i = from;
    while(i <= to / 2){
        //子の最大値を持つ節を節jとする
        j = i * 2;
        if(j < to && A[j] <= A[j+1] ){
            j++;
        }
        //親より最大値を持つ節が小さければ終了
        if(val >= A[j]){
            break;
        }
        //節jを親とする
        A[i] = A[j];
        i = j;
    }
    //先頭にあった要素を節iに入れる
    A[i] = val;
}

//配列をヒープする
void HeapSort(int A[], int n){
    int i;
    int tmp;
    //ヒープを最下層の親から順に上に構築する
    for(i = n/2; i >= 0; i--){
        DownHeap(A, i, n);
    }
    //ヒープの先頭から最大値を取り出し、昇順にソートする
    for(i = n; i >= 1; i--){
        tmp = A[0];
        A[0] = A[i];
        A[i] = tmp;
        DownHeap(A, 0, i-1);
    }
}

//二分探索法
//範囲の両端の中心の値と、探す値を比較して範囲を更新する
//BinarySearch: int A[] -> int n -> int key -> int
int BinarySearch(int A[], int n, int key){
    int low, high, middle;
    low = 0;
    high = n;
    //lowが左、highが右の範囲の間、照合する
    while(low <= high){
        middle = (low + high) / 2;
        if(key == A[middle]){
            return 1;
        }else if(key < A[middle]){
            high = middle - 1;
        }else{
            low = middle + 1;
        }
    }
    return 0;
}

//テスト
int main(){
    int i;
    //HeapSort(a, n);
    //int value = BinarySearch(a, n, 5);
    //int value = CheckWhoWinsElection_1(a, n);
    int value = find(a, b, n, m, k);
    printf("Subtracting %d in B from %d, %d is found in A.\n", d, k, value);
    for(i = 0; i <= n; i++){
        printf("Array, %d: %d\n", i, a[i]);
    }
    return 0;
}

