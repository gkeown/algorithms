#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

int
listLength(Node *head)
{
    Node *tmp = head;
    int len = 0;

    while (tmp != NULL) {
        printf("item at index %d : %d\n", len, tmp->data);
        len++;
        tmp = tmp->next;
    }
    return (len);
}

void
insert(Node **head, int data, int pos)
{
    Node *newNode = malloc(sizeof(*newNode));
    if (newNode == NULL) {
        printf("insert: failed to allocate memory\n");
        return;
    }
    newNode->data = data;

    /* insert at head */
    if (pos == 0) {
        newNode->next = *head;
        newNode->prev = NULL;
        (*head)->prev = newNode;
        *head = newNode;
        return;
    }

    int i = 0;
    Node *tmp = *head;

    /* iterate through list to find element at pos */
    while ((tmp->next != NULL) && (i < pos-1)) {
        tmp = tmp->next;
        i++;
    }

    if (i != pos-1) {
        printf("insert: desired position %d does not exist\n", pos);
    }

    newNode->next = tmp->next;
    newNode->prev = tmp;
    if (tmp->next) {
        tmp->next->prev = newNode;
    }
    tmp->next = newNode;
}

void
delete(Node **head, int pos)
{
    Node *tmp = *head;

    if (pos == 0) {
        *head = (*head)->next;
        if (*head) {
            (*head)->prev = NULL;
            free(tmp);
            return;
        }
    } else {
        int i = 0;
        while (tmp->next != NULL && i < pos) {
            tmp = tmp->next;
            i++;
        }

        if (i < pos) {
            printf("delete: no element at pos %d\n", pos);
            return;
        }

        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        free(tmp);
    }
}

void
deleteList(Node **head)
{
    Node *iterator = *head;
    Node *tmp = NULL;

    while (iterator != NULL) {
        tmp = iterator;
        iterator = iterator->next;
        free(tmp);
    }
    *head = NULL;
}

int
main(int argc, char *argv[])
{
    Node *head = malloc(sizeof(*head));
    head->data = 1;
    head->prev = NULL;
    head->next = NULL;

    printf("Insert elements:\n\n");

    insert(&head, 10, 1);
    insert(&head, 20, 1);
    insert(&head, 80, 1);
    insert(&head, 99, 1);
    insert(&head, 150, 1);
    listLength(head);

    printf("Delete elements:\n\n");

    delete(&head, 1);
    delete(&head, 50);
    delete(&head, 0);
    listLength(head);

    deleteList(&head);
    int res = listLength(head);
    if (res == 0 && head == NULL) {
        printf("success\n");
    }

    return (0);
}
