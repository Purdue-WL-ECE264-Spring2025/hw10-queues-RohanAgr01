#include "queue.h"
#include "tile_game.h"

static struct list_node nodes_pool[1000];
static int pool_index = 0;


void enqueue(struct queue *q, struct game_state state) {
    if (pool_index >= 1000) return;

    struct list_node *node = &nodes_pool[pool_index++];
    node->value = serialize(state);
    node->next = NULL;

    if (!q->head) {
        q->head = node;
        q->tail = node;
    } else {
        q->tail->next = node;
        q->tail = node;
    }
}

struct game_state dequeue(struct queue *q) {
    if (!q->head) return (struct game_state){0}; 

    struct list_node *temp = q->head;
    struct game_state state = deserialize(temp->value);

    q->head = temp->next;
    if (!q->head) q->tail = NULL; 

    return state;
}

int number_of_moves(struct game_state start) {
    struct queue q = { .head = NULL, .tail = NULL };
    enqueue(&q, start);

    while (q.head) {
        struct game_state current = dequeue(&q);

        if (is_solved(current)) {
            return current.num_steps;
        }

        struct game_state neighbors[4];
        int count = get_neighbors(current, neighbors);

        for (int i = 0; i < count; i++) {
            enqueue(&q, neighbors[i]);
        }
    }

    return -1; 
}
