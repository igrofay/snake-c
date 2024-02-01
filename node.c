//
// Created by sergei on 01.02.2024.
//
#include <stdlib.h>
#include "node.h"


struct Node* createNode(int yPoint, int xPoint) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->point.y = yPoint;
    newNode->point.x = xPoint;
    newNode->next = NULL;
    return newNode;
}

void freeNode(struct Node* node) {
    struct Node* current = node;
    struct Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}
void appendToStartNode(struct Node** startingNode, int yPoint, int xPoint) {
    struct Node* newNode = createNode(yPoint, xPoint);
    if (*startingNode == NULL) {
        *startingNode = newNode;
    } else {
        struct Node* head = *startingNode;
        *startingNode = newNode;
        newNode->next = head;
    }
}
void appendToEndNode(struct Node** startingNode, int yPoint, int xPoint) {
    struct Node* newNode = createNode(yPoint, xPoint);
    if (*startingNode == NULL) {
        *startingNode = newNode;
    } else {
        struct Node* temp = *startingNode;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
void deleteStart(struct Node** startingNode){
    struct Node* head = *startingNode;
    if(head->next == NULL){
        *startingNode = NULL;
    } else{
        *startingNode = head->next;
    }
    free(head);
}
void deleteEnd(struct Node** startingNode){
    if (*startingNode == NULL) return;
    if ((*startingNode)->next == NULL) {
        free(*startingNode);
        *startingNode = NULL;
        return;
    }
    struct Node* prev = NULL;
    struct Node* current = *startingNode;
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }
    free(current);
    prev->next = NULL;
}