#include <stdio.h>
#include <unistd.h>
#include "node.h"
#include "utils.h"
#include "threads.h"
#include <conio.h>


#define Height 10
#define Width 10

Mutex mutex;
char map[Height][Width];
struct Point food = { .x=5, .y = 5};
struct Node* snake;
volatile struct Point move = {.y = 1, .x = 0};
int points = 0;
boolean isGame = 1;
void clearMap(){
    for(int h = 0; h<Height; h++){
        for(int w = 0; w<Width; w++){
            map[h][w] = '*';
        }
    }
}
void printMap(){
    for(int h = 0; h<Height; h++){
        for(int w = 0; w<Width; w++){
            printf("%c ", map[h][w]);
        }
        printf("\n");
    }
    printf("Points: %d\n",points);
}

void eventsOnMap(){
    clearMap();
    lockMutex(mutex);
    appendToStartNode(
            &snake,
            (snake->point.y + move.y + Height) % Height,
            (snake->point.x + move.x + Width) % Width
    );
    unlockMutex(mutex);
    struct Node* temp = snake;
    while (temp->next != NULL){
        temp = temp->next;
        if(temp->point.y == snake->point.y && temp->point.x == snake->point.x){
            isGame = 0;
        }
    }
    if (snake->point.y == food.y && snake->point.x == food.x){
        food.y = random(Height);
        food.x = random(Width);
        points++;
    } else{
        deleteEnd(&snake);
    }
    temp = snake;
    map[temp->point.y][temp->point.x] = '$';
    while (temp->next != NULL) {
        temp = temp->next;
        map[temp->point.y][temp->point.x] = '#';
    }
    map[food.y][food.y]= '@';
    CLEAR_SCREEN;
    printMap();
    sleepMs(200);
}
threadFunctionReturnType thReceivingPlayerClicks(void* arg){
    while (1){
        int key = tolower(_getch());
        switch (key) {
            case 'w':
                if (move.y == 1) break;
                lockMutex(mutex);
                move.y = -1;
                move.x = 0;
                unlockMutex(mutex);
                break;
            case 's':
                if (move.y == -1) break;
                lockMutex(mutex);
                move.y = 1;
                move.x = 0;
                unlockMutex(mutex);
                break;
            case 'a':
                if (move.x == 1) break;
                lockMutex(mutex);
                move.y = 0;
                move.x = -1;
                unlockMutex(mutex);
                break;
            case 'd':
                if (move.x == -1) break;
                lockMutex(mutex);
                move.y = 0;
                move.x = 1;
                unlockMutex(mutex);
                break;
        }
    }
    return 0;
}
int main() {
    initializeMutex(mutex);
    Thread  thread;
    createThreadFunction(thReceivingPlayerClicks);
    snake = createNode(7,7);
    while (isGame){
        eventsOnMap();
    }
    printf("The end: points %d\n", points);
    freeNode(snake);
    closeThreadHandle(thread);
    destroyMutex(mutex);
    return 0;
}
