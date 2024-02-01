//
// Created by sergei on 01.02.2024.
//

#ifndef UNTITLED_THREADS_H
#define UNTITLED_THREADS_H

#ifdef __unix__
    #include <pthread.h>
    typedef pthread_t Thread;
    typedef pthread_mutex_t Mutex;
    #define threadFunctionReturnType void*
    #define createThreadFunction(func) pthread_create(&thread, NULL, func, NULL)
    #define joinThreadFunction(thread) pthread_join(thread, NULL)
    #define closeThreadHandle(thread) // No need to close thread handle on POSIX
    #define initializeMutex(mutex) pthread_mutex_init(&mutex, NULL)
    #define lockMutex(mutex) pthread_mutex_lock(&mutex)
    #define unlockMutex(mutex) pthread_mutex_unlock(&mutex)
    #define destroyMutex(mutex) pthread_mutex_destroy(&mutex)
#elif defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    typedef HANDLE Thread;
    typedef CRITICAL_SECTION Mutex;
    #define threadFunctionReturnType DWORD WINAPI
    #define createThreadFunction(func) CreateThread(NULL, 0, func, NULL, 0, NULL)
    #define joinThreadFunction(thread) WaitForSingleObject(thread, INFINITE)
    #define closeThreadHandle(thread) CloseHandle(thread)
    #define initializeMutex(mutex) InitializeCriticalSection(&mutex)
    #define lockMutex(mutex) EnterCriticalSection(&mutex)
    #define unlockMutex(mutex) LeaveCriticalSection(&mutex)
    #define destroyMutex(mutex) DeleteCriticalSection(&mutex)
#else

#endif

#endif //UNTITLED_THREADS_H
