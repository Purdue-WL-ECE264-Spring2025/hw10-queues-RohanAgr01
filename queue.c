#include "queue.h"
#include "tile_game.h"
#include <stdlib.h>

void enqueue(struct queue *q, struct game_state state) {
    struct queue_node *node = malloc(sizeof(struct queue_node));
    if (!node) return;
    
    node->state = state;
    node->next = NULL;

    if (!q->tail) {
        q->head = q->tail = node;
    } else {
        q->tail->next = node;
        q->tail = node;
    }
}

struct game_state dequeue(struct queue *q) {
    if (!q->head) return (struct game_state){0};

    struct queue_node *temp = q->head;
    struct game_state state = temp->state;

    q->head = q->head->next;
    if (!q->head) {
        q->tail = NULL;
    }

    free(temp);
    return state;
}

int number_of_moves(struct game_state start) {
    struct queue q = {NULL, NULL};
    enqueue(&q, start);

    while (q.head) {
        struct game_state current = dequeue(&q);

        if (is_solved(current)) {
            return current.num_steps;
        }

        struct game_state neighbors[4];
        int num_neighbors = get_neighbors(current, neighbors);

        for (int i = 0; i < num_neighbors; i++) {
            neighbors[i].num_steps = current.num_steps + 1;
            enqueue(&q, neighbors[i]);
        }
    }

    return -1;
}
