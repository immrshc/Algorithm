#include <stdio.h>
#include <stdlib.h>

//テスト用の配列
int a[14] = {0, 1, 4, 2, 4, 3, 4, 5, 3, 0, 4, 1, 0, 1};
//配列の最終インデックス
int n = 13;
//ヒープソートの関数プロトタイプ宣言
void HeapSort(int A[], int n);

//重複回数が最も多い要素を見つける
//CheckWhoWinsElection: int A[] -> int n -> int

//要素を一つづつ走査し、残りの要素を一致する場合は、カウンタを増分する
//時間計算量: 0(n^2)
int CheckWhoWinsElection_1(int A[], int n){
    int i, j;
    int counter = 1;
    int maxCounter = 1;
    int candidate;
    int maxCandidate;

    candidate = A[0];
    maxCandidate = A[0];

    //着目する要素を決める
    for(i = 0; i < n; i++){
        //候補者を取得
        candidate = A[i];
        //カウンタを初期化
        counter = 1;
        //着目する要素以降に同じ要素があるか確認する
        for(j = i + 1; j <= n; j++){
            //重複を確認
            if(A[i] == A[j]){
                //カウンタを増分する
                counter++;
            }
        }
        //最大カウンタ数と比較
        if(counter >= maxCounter){
            //最大カウンタ数を更新
            maxCounter = counter;
            //最大カウンタ数を持つ候補者を更新
            maxCandidate = A[i];        
        }
    }
    //最大カウンタ数を持つ候補者を返す
    return maxCandidate;
}

//ソートして、隣の要素が同じかどうか調べる
//時間計算量: nlogn + n = O(nlogn)
int CheckWhoWinsElection_2(int A[], int n){
    int i, j;
    int currentCounter = 1;
    int maxCounter = 1;
    int currentCandidate;
    int maxCandidate;

    currentCandidate = A[0];
    maxCandidate = A[0];
    
    //ソートする
    HeapSort(A, n);
    //着目する要素を選択する
    for(i = 1; i < n; i++){
        //隣の要素と比較する
        if(A[i] == currentCandidate){
            //カウンタを増分する
            currentCounter++;
        }else{
            //候補者を更新する
            currentCandidate = A[i];
            //カウンタを初期化
            currentCounter = 1; 
        }
        //最大カウンタと比較
        if(currentCounter >= maxCounter){
            //最大カウンタを更新
            maxCounter = currentCounter;
            //最大カウンタを持つ候補者を更新
            maxCandidate = currentCandidate;
        }
    }
    //最大カウンタを持つ候補者を返す
    return maxCandidate; 
}

//ヒープを構築する
void DownHeap(int A[], int from, int to){
    int i, j;
    int val;

    val = A[from];
    //根から初めて、節iが子を持っている限り繰り返す
    i = from;
    while(i <= to / 2){
        //子の最小の節を見つけて、節jとする
        j = i * 2;
        if(j < to && A[j] >= A[j+1]){
            j++;
        }
        //親が子よりも小さい時はこれ以上沈めない
        if(val <= A[j]){
            break;
        }
        //節iに節jの値を入れて、節jに注目する
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
    
    //最下層の親から上にヒープを構築する
    for(i = n/2; i >= 0; i--){
        DownHeap(A, i, n);
    }
    //ヒープから先頭を取り出して、降順にソートする
    for(i = n; i >= 1; i--){
        tmp = A[0];
        A[0] = A[i];
        A[i] = tmp;
        DownHeap(A, 0, i-1);
    }
}

//テスト
int main(){
    int i;
    //HeapSort(a, n);
    //int value = CheckWhoWinsElection_1(a, n);
    int value = CheckWhoWinsElection_2(a, n);
    printf("%d is maxCandidate.\n", value);
    for(i = 0; i <= n; i++){
        printf("Array, %d: %d\n", i, a[i]);
    }
    return 0;
}
