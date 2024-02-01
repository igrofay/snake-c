//
// Created by sergei on 01.02.2024.
//

#ifndef UNTITLED_UTILS_H
#define UNTITLED_UTILS_H
#include<stdlib.h>
#include <time.h>
#ifdef __unix__
    #define CLEAR_SCREEN_COMMAND "clear"
    #include <unistd.h>
#elif defined(_WIN32) || defined(_WIN64)
    #define CLEAR_SCREEN_COMMAND "cls"
    #include <windows.h>

#else
    #define CLEAR_SCREEN_COMMAND ""
    #include <time.h>
#endif

#define CLEAR_SCREEN system(CLEAR_SCREEN_COMMAND)

void sleepMs(int milliseconds){
#ifdef __unix__
    usleep(milliseconds);
#elif defined(_WIN32) || defined(_WIN64)
    Sleep(milliseconds);
#else
    clock_t start_time, end_time;
        start_time = clock();
        while (1){
            end_time = clock();
            double elapsed_time = ((double)(end_time - start_time) / CLOCKS_PER_SEC) * 1000.0;
            if(elapsed_time >= milliseconds) break;
        }
#endif
}



int random(int range){
    return ( (int) time(NULL)/2) % range;
}

#endif //UNTITLED_UTILS_H
