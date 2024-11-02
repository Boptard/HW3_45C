#include "player.h"
#include "llqueue.h"
#include <iostream>

// add your findBestInBatch function here (optional helper function)
// to avoid making the teamBestOfBatch function too long
// Player *findBestInBatch(Queue *q, Queue *tmp_q, int batch_size) {

Player *findBestInBatch(Queue *q, Queue *tmp_q, int batch_size) {
    if (q == nullptr || batch_size <= 0) {
        return nullptr;
    }

    Player *best_player = nullptr;
    for (int i = 0; i < batch_size && q->head != nullptr; ++i) {
        Player *current_player = queueFront(q);
        Player *player_copy = (copyPlayer(current_player));
        if (best_player == nullptr || current_player->num_goals > best_player->num_goals) {
            if (best_player != nullptr) {
                queuePushPlayerEntry(tmp_q, best_player);
            }
            best_player = player_copy;
        } else {
            queuePushPlayerEntry(tmp_q, player_copy);
        }
        queuePopPlayerEntry(q);
    }
    return best_player;
}

Player *teamBestOfBatch(Queue *q, int k) {
    if (q == nullptr || k <= 0 || k > queueSize(q)) {
        return nullptr;
    }
    Queue *tmp_q = newQueue();
    Player *best_player = findBestInBatch(q, tmp_q, k);
    while (tmp_q->head != nullptr) {
        queuePushPlayerEntry(q, copyPlayer(queueFront(tmp_q)));
        queuePopPlayerEntry(tmp_q);
    }
    deleteQueue(tmp_q);
    return best_player;
}

void teamCreateFromBest(Queue *applicant_q, Queue *welcome_q, int batch_size) {
    if (applicant_q == nullptr || welcome_q == nullptr || batch_size <= 0) {
        return;
    }
    for (int i = 0; i < 5; ++i) {
        Player *best_player = teamBestOfBatch(applicant_q, std::min(static_cast<size_t>(batch_size), queueSize(applicant_q)));
        if (best_player != nullptr) {
            queuePushPlayerEntry(welcome_q, best_player);
        }
    }
}