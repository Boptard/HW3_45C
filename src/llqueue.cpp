#include "llqueue.h"
#include "player.h"
#include <iostream>

LLNode *newLLNode(Player *p) {
    LLNode *node = new LLNode;
    node->entry = p;
    node->next = nullptr;
    return node;
}

void deleteLLNode(LLNode *ln) {
    if (ln != nullptr) {
        deletePlayer(ln->entry); // Delete the player entry
        delete ln;               // Delete the node itself
    }
}

Queue *newQueue() {
    Queue *q = new Queue;
    q->size = 0;
    q->head = nullptr;
    q->tail = nullptr;
    return q;
}

void queuePushPlayerEntry(Queue *q, Player *entry) {
    if (q == nullptr || entry == nullptr) {
        return;
    }
    LLNode *node = newLLNode(entry);
    if (q->tail == nullptr) { // Queue is empty
        q->head = node;
        q->tail = node;
    } else {
        q->tail->next = node;
        q->tail = node;
    }
    q->size++;
}

void queuePopPlayerEntry(Queue *q) {
    if (q == nullptr || q->head == nullptr) { // Queue is empty
        return;
    }
    LLNode *temp = q->head;
    q->head = q->head->next;
    if (q->head == nullptr) { // Queue is now empty
        q->tail = nullptr;
    }
    deleteLLNode(temp);
    q->size--;
}

Player *queueFront(Queue *q) {
    if (q == nullptr || q->head == nullptr) {
        return nullptr;
    }
    return q->head->entry;
}

Player *queueBack(Queue *q) {
    if (q == nullptr || q->tail == nullptr) {
        return nullptr;
    }
    return q->tail->entry;
}

std::size_t queueSize(const Queue *q) {
    if (q == nullptr) {
        return 0;
    }
    return q->size;
}

void printQueue(const Queue *q) {
    if (q == nullptr || q->head == nullptr) {
        std::cout << "Queue is empty." << std::endl;
        return;
    }
    LLNode *current = q->head;
    while (current != nullptr) {
        printPlayer(current->entry);
        current = current->next;
    }
}

void deleteQueue(Queue *q) {
    if (q != nullptr) {
        while (q->head != nullptr) {
            queuePopPlayerEntry(q);
        }
        delete q;
    }
}