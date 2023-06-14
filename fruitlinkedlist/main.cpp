#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct ListNode {
    char fruit[20];
    struct ListNode* link;
} ListNode;

// 과일 리스트에 과일 추가
ListNode* insert_fruit(ListNode* current, const char* fruit) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    strcpy(node->fruit, fruit);

    if (current == NULL) {
        node->link = node;
        return node;
    }
    else {
        node->link = current->link;
        current->link = node;
        return current;
    }
}

// 현재 과일 삭제
ListNode* delete_current(ListNode* current) {
    if (current == NULL) {
        printf("Fruit list is empty!\n");
        return NULL;
    }

    if (current->link == current) {
        free(current);
        return NULL;
    }
    else {
        ListNode* prev = current;
        while (prev->link != current)
            prev = prev->link;

        prev->link = current->link;
        ListNode* temp = current;
        current = current->link;
        free(temp);
        return current;
    }
}

// 다음 과일 선택
ListNode* select_next(ListNode* current) {
    if (current == NULL) {
        printf("Fruit list is empty!\n");
        return NULL;
    }
    else {
        return current->link;
    }
}

// 이전 과일 선택
ListNode* select_previous(ListNode* current) {
    if (current == NULL) {
        printf("Fruit list is empty!\n");
        return NULL;
    }
    else {
        ListNode* prev = current;
        while (prev->link != current)
            prev = prev->link;
        return prev;
    }
}

// 과일 리스트 출력
void print_list(ListNode* current) {
    if (current == NULL) {
        printf("Fruit list is empty!\n");
        return;
    }

    ListNode* start = current;
    do {
        printf("%s", current->fruit);
        if (current->link == start)
            printf(" [O]");
        printf("\n");
        current = current->link;
    } while (current != start);
}

int main() {
    ListNode* current = NULL;
    int menu;
    char fruit[20];

    do {
        printf("\n***** Menu *****\n");
        printf("n) Next fruit\n");
        printf("p) Previous fruit\n");
        printf("d) Delete current fruit\n");
        printf("i) Insert fruit after current fruit\n");
        printf("o) Print fruit list\n");
        printf("e) Exit\n");
        printf("Select a menu: ");
        scanf_s("% c", &menu);

        switch (menu) {
        case 'n':
            current = select_next(current);
            break;
        case 'p':
            current = select_previous(current);
            break;
        case 'd':
            current = delete_current(current);
            break;
        case 'i': 
            printf("Enter the fruit to insert: ");
            scanf_s("%s", &fruit);
            current = insert_fruit(current, fruit);
            break;
        case 'o':
            print_list(current);
            break;
        case 'e':
            printf("Exit the program.\n");
            break;
        default:
            printf("Invalid choice.\n");
            break;
        }
    } while (menu != 'e');

    // Free memory for the remaining nodes in the list
    if (current != NULL) {
        ListNode* start = current;
        while (current->link != start) {
            ListNode* temp = current;
            current = current->link;
            free(temp);
        }
        free(current);
    }

    return 0;
}
