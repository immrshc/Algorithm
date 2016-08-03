//タイトル：二分探索方による探索

#include <stdio.h>
#define ARRAY_SIZE 50

//目的：データのインデックスを示すint型のkeyと、データ内容のint型のdataの構造体
struct {
    int key;
    int data;
}table[ARRAY_SIZE];

int n = ARRAY_SIZE;

//目的：keyとmiddleを比較して大小に応じてlowとhighの値を変え続ける再帰関数
//binary_search: int -> int
int binary_search(int key){

    int low, high, middle;
    low = 0;
    high = n - 1;

    while(low <= high){
        middle = (low + high) / 2;
        printf("low: %d, middle: %d, high: %d\n", low, middle, high);
        //一致した場合
        if (key == table[middle].key)
            //自明な場合
            return table[middle].data;
        //より対象が小さい場合
        else if (key < table[middle].key)
            //範囲が狭まり収束する
            high = middle - 1;
        //より対象が大きい場合
        else
            //範囲が狭まり収束する
            low = middle + 1;
    }
    //見つからなかった場合
    return (-1);
}

int main(void){
    
    int i;
    for (i = 0; i < ARRAY_SIZE; i++){
        table[i].key = i;
        table[i].data = i * 3 + 1;
    }
    
    int result;
    int key = 0;

    result = binary_search(key);
    printf("二分探索をする値: %d, 結果: %d \n", key, result);
    return 0;
}


