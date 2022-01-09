#include "stack.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

move_stack stack_new_empty(void) { return NULL; }

bool stack_is_empty(move_stack stack) { return stack == NULL; }

move_stack stack_push_head(move_stack stack, move data) {
    assert(data);

    move_stack new = (move_stack)malloc(sizeof(struct move_stack_s));
    assert(new);

    new->data = data;
    new->next = stack;

    return new;
}

move_stack stack_pop_head(move_stack stack) {
    assert(stack);
    assert(stack->data);

    move_stack to_be_deleted = stack;
    stack = stack->next;
    free(to_be_deleted->data);
    free(to_be_deleted);

    return stack;
}

move stack_peek_head(move_stack stack) {
    assert(stack);
    assert(stack->data);

    return stack->data;
}

move_stack stack_clear(move_stack stack) {
    stack_free(stack);

    return NULL;
}

void stack_free(move_stack stack) {
    move_stack to_be_deleted = stack;

    while (to_be_deleted != NULL) {
        stack = stack->next;
        free(to_be_deleted->data);
        free(to_be_deleted);
        to_be_deleted = stack;
    }
}
