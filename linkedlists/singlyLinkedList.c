#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

int
listLength(Node *head)
{
    int len = 0;
    Node *current = head;

    while (current != NULL) {
        printf("index %d = %d\n", len, current->data);
        current = current->next;
        len++;
    }

    return (len);
}

void
insert(Node **head, int data, int pos)
{
    int i = 1;
    Node *cur, *prev, *new_node;

    /* allocate and assign the new entry */
    new_node = malloc(sizeof(Node));
    if (!new_node) {
        printf("insert: could not allocate new node mem\n");
        return;
    }
    new_node->data = data;

    /* point to first element in the list */
    cur = *head;

    /* insert entry at the beginning */
    if (pos == 1) {
        new_node->next = cur;
        *head = new_node;
    } else {
        /* traverse list until it reaches pos */
        for (i = 0; i < pos && cur != NULL; i++) {
            prev = cur;
            cur = cur->next;
        }
        prev->next = new_node;
        new_node->next = cur;
    }
}

void
delete(Node **head, int pos)
{
    Node *cur, *prev;
    cur = *head;

    if (*head == NULL) {
        printf("delete: head is NULL\n");
        return;
    }
    
    if (pos == 0) {
        *head = (*head)->next;
        free(cur);
    } else {
        int i = 0;
        for (i = 0; i < pos && cur != NULL; i++) {
            prev = cur;
            cur = cur->next;
        }

        /* at the end of the list */
        if (cur == NULL) {
            printf("delete: cannot delete pos %d\n", pos);
            return;
        }

        prev->next = cur->next;
        free(cur);
    }
}

void
deleteList(Node **head)
{
    Node *iterator = *head;
    Node *tmp;
    int cnt = 0;

    while (iterator != NULL) {
        tmp = iterator;
        iterator = iterator->next;
        free(tmp);
        cnt++;
    }
    *head = NULL;
    printf("deleteList: deleted %d elements\n", cnt);
}

int
main(int argc, char *argv[])
{
    Node *head;
    head = malloc(sizeof(Node));
    head->data = 1;

    printf("main: insert 4 elements\n");

    insert(&head, 2, 2);
    insert(&head, 3, 3);
    insert(&head, 4, 4);
    insert(&head, 5, 9);
    listLength(head);

    printf("main: delete three elements\n");

    delete(&head, 2);
    delete(&head, 0);
    delete(&head, 2);
    listLength(head);

    printf("main: delete rest of list\n");

    deleteList(&head);
    listLength(head);

    if (head == NULL) {
        printf("success!\n");
    }

    return (0);
}
