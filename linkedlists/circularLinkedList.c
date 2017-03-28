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
    Node *tmp = head;

    if (head == NULL) {
        return 0;
    }

    do {
        printf("index %d = %d\n", len, tmp->data);
        tmp = tmp->next;
        len++;
    } while (tmp != head);

    return (len);
}

void
insert(Node **head, int data, int pos)
{
    Node *tmp = *head;
    Node *tail;
    Node *newNode = malloc(sizeof(*newNode));
    if (newNode == NULL) {
        printf("insert: failed to alloc new node\n");
        return;
    }
    newNode->data = data;

    /* insert at head position */
    if (pos == 0) {

        /* need to find out what the final element in list is */
        while (tmp->next != *head) {
            tmp = tmp->next;
        }
        tmp->next = newNode;
        newNode->next = *head;
        *head = newNode;
        return;
    }

    /* cycle through until we find element at position pos-1 */
    int i = 0;
    while ((tmp->next != *head) && (i < pos-1)) {
        tmp = tmp->next;
        i++;
    }

    if (i != pos-1) {
        printf("insert: pos %d does not exist\n", pos);
    }

    newNode->next = tmp->next;
    tmp->next = newNode;
}

void
delete(Node **head, int pos)
{
    Node *tmp = *head;

    /* delete head */
    if (pos == 0) {
        Node *tail = *head;
        /* find tail of list - need to point to new head */
        while (tail->next != *head) {
            tail = tail->next;
        }
        tail->next = (*head)->next;
        *head = (*head)->next;
        free(tmp);
        return;
    }

    int i = 0;
    Node *prev = NULL;
    while ((tmp->next != *head) && (i < pos)) {
        prev = tmp;
        tmp = tmp->next;
        i++;
    }

    if (i != pos) {
        printf("delete: no element at pos %d\n", pos);
        return;
    }

    prev->next = tmp->next;
    free(tmp);
}

void
deleteList(Node **head)
{
    Node *iterator = *head;
    Node *tmp;
    int count = 0;
    
    do {
        tmp = iterator;
        iterator = iterator->next;
        free(tmp);
        count++;
    } while (iterator != *head);

    *head = NULL;

    printf("deleted %d elements\n", count);
}

int
main(int argc, char *argv[])
{
    Node *head = malloc(sizeof(*head));
    head->data = 99;
    head->next = head;

    printf("inserting elements: \n");

    insert(&head, 10, 1);
    insert(&head, 20, 1);
    insert(&head, 30, 0);
    insert(&head, 50, 99);
    listLength(head);

    printf("delete elements: \n");
    delete(&head, 1);
    delete(&head, 6);
    delete(&head, 0);
    delete(&head, 1);
    listLength(head);

    deleteList(&head);
    if (head == NULL) {
        printf("success\n");
    }
}
