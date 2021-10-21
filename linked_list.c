#include "linked_list.h"

node_t* delete_from_position(node_t* head, int delete_position) {
    assert(head != NULL);
    node_t* current = head;
    //handle head case
    if (delete_position == 0) {
        return head->next;
    }
    //handle other cases
    for (int i = 0; i < delete_position; i++) {
        //if we are at the position before the one we want to delete point the current to next->next
        if (i == (delete_position - 1)) {
            current->next = current->next->next;
            return current;
        }
        current = current->next;
    }
}
node_t* reverse_linked_list(node_t* head) {
    //handle base cases no head and no next on head
    if (head == NULL) {
        return NULL;
    }
    if (head->next == NULL) {
        return head;
    }
    // 1 -> 2 -> 3 -> 4
    // 1 <- 2 <- 3 <- 4
    node_t* previous = NULL;
    node_t* current = head;
    node_t* next = head->next;
    while(current != NULL) {
        next = current->next;
        current->next = previous;
        previous = current;
        if(next == NULL) {
            return current;
        }
        current = next;;
    }
}
void add_to_end_linked_list(node_t* head, int val) {
    node_t* current = head;
    //go to end of linked list by poving the pointer until the next pointer is null
    while (current != NULL) {
        if(current->next == NULL) {
            current->next = (node_t*)malloc(sizeof(node_t));
            current->next->value = val;
            current->next->next = NULL;
            return;
        }
        current = current->next;
    }
}
node_t* add_to_beginning_linked_list(node_t* head, int val) {
    assert(head != NULL);
    //make a new node, set its next to the current head and return
    node_t* new_head = (node_t*)malloc(sizeof(node_t));
    new_head->value = val;
    new_head->next = head;
    return new_head;
}
int get_value_from_linked_list(node_t* head, int position) {
    node_t* current = head;
    for(int i = 0; i <= position; i++) {
        if (i == position) {
            return current->value;
        }
        current = current->next;
    }
}

void print_linked_list(node_t * head) {
    node_t* temp = head;
    while(temp != NULL) {
        printf("%d\n", temp->value);
        temp = temp->next;
    }
}

node_t* initialize_stack(int value) {
    node_t* top = (node_t*)malloc(sizeof(node_t));
    top->value = value;
    top->next = NULL;
    return top;
}

node_t* push_stack(node_t* head, int value) {
    return add_to_beginning_linked_list(head, value);
}

node_t* pop_stack(node_t* head) {
    return delete_from_position(head, 0);
}

int peep_stack(node_t* head) {
    return head->value;
}