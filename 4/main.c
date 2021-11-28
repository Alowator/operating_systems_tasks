#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct Node {
    char *data;
    struct Node* next;
} Node;


Node *create(char *input) {
    Node *newNode;
    newNode = malloc(sizeof(Node));
    newNode->data = malloc(sizeof(char) * (strlen(input) + 1));
    strcpy(newNode->data, input);
    newNode->next = NULL;
    return newNode;
}

int main() {
    char line[BUFSIZ];
    Node *sentinel, *tail;

    sentinel = malloc(sizeof(Node));
    sentinel->next = NULL;
    tail = sentinel;

    while (gets(line)) {
        if (line[0] == '.')
            break;
        tail->next = create(line);
        tail = tail->next;
    }

    while(sentinel->next != NULL) {
        puts(sentinel->next->data);
        tail = sentinel->next;
	if (sentinel->data != NULL)
            free(sentinel->data);
        free(sentinel);
        sentinel = tail;
    }
    free(sentinel->data);
    free(sentinel);

    return 0;
}
