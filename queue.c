/*
 *  queue.c 配列で待ち行列を実現する
 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef long ELEM;

#define QUEUE_SIZE 100

ELEM queue[QUEUE_SIZE];
int front;
int rear;

#define next(a) (((a) + 1) % QUEUE_SIZE)

void error(char *s)
{
    fprintf(stderr, s);
    exit(1);
}

void init()
{
    front = rear = 0;
}

void enqueue(ELEM x)
{
    if (next(rear) == front)
        error("待ち行列が埋まっているので要素を入れられません\n");
    queue[rear] = x;
    printf("queue[rear]: %ld\n", queue[rear]);
    rear = next(rear);
}

//ELEM dequeue()
void dequeue()
{
    ELEM x;
    if (front == rear)
        error("待ち行列が空なので要素を取り出せません\n");
    x = queue[front];
    printf("queue[front]: %ld\n", queue[front]);
    front = next(front);
    //return x;
}

int empty()
{
    return front == rear;
}

int  main()
{
    ELEM x;
    ELEM y;
    init();
    for (x = 0; x < QUEUE_SIZE; x++){
        enqueue(x);
        enqueue(++x);
        enqueue(++x);
        dequeue();
    }

    return empty();
}

