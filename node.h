//
// Created by sergei on 01.02.2024.
//

#ifndef UNTITLED_NODE_H
#define UNTITLED_NODE_H

struct Point{ int y, x; };
struct Node{
    struct Point point;
    struct Node* next;
};
struct Node* createNode(int yPoint, int xPoint);
void freeNode(struct Node* node);
void appendToStartNode(struct Node** startingNode, int yPoint, int xPoint);
void appendToEndNode(struct Node** startingNode, int yPoint, int xPoint);
void deleteStart(struct Node** startingNode);
void deleteEnd(struct Node** startingNode);
int contains(struct Node* node, struct Point point);
#endif //UNTITLED_NODE_H
