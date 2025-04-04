#include "queue.h"
#include "tile_game.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

void enqueue(struct queue *q, struct game_state state) {
    size_t serialized_state = serialize(state);
    insert_at_tail(&q->data, serialized_state);
}

struct game_state dequeue(struct queue *q) {
    if (!q->data.head) return (struct game_state){0};
    size_t serialized_state = remove_from_head(&q->data);
    return deserialize(serialized_state);
}

int number_of_moves(struct game_state start) {
    struct queue q = {0};
    enqueue(&q, start);
    
    uint64_t visited[65536] = {0};  
    visited[serialize(start) % 65536] = 1;

    while (q.data.head) {
        struct game_state current = dequeue(&q);
        if (is_goal_state(current)) return current.num_steps;

        struct game_state next_moves[4] = {current, current, current, current};
        move_up(&next_moves[0]);
        move_down(&next_moves[1]);
        move_left(&next_moves[2]);
        move_right(&next_moves[3]);

        for (int i = 0; i < 4; i++) {
            uint64_t next_state = serialize(next_moves[i]);
            if (!visited[next_state % 65536]) {
                visited[next_state % 65536] = 1;
                enqueue(&q, next_moves[i]);
            }
        }
    }

    return -1; 
}
