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

move_stack stack_copy(move_stack stack_init) {
    move_stack tmp = stack_new_empty();
    move_stack stack1 = stack_init;
    move_stack stack2 = stack_new_empty();

    // on vide stack1 dans tmp
    while (!stack_is_empty(stack1)) {
        stack_push_head(tmp, stack_peek_head(stack1));
        stack_pop_head(stack1);
    }

    // on re-remplie stack1 et stack2 avec tmp
    while (!stack_is_empty(tmp)) {
        move data = stack_peek_head(stack1);

        stack_push_head(stack1, data);
        stack_push_head(stack2, data);
        stack_pop_head(tmp);
    }

    return stack2;
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
