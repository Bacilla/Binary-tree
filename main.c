#include <stdio.h>
#include <stdlib.h> // atoi 

// Структура узла бинарного дерева
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// --- Прототипы функций ---
// Функции по заданию
void tree_initialization(Node **ppRoot);


// Вспомогательные функции
Node create_node();
int get_int();



int main() {
    // Корень дерева
    Node *root = NULL; 

    return 0;
}

// Функция инициализирует дерево
void tree_initialization(Node **ppRoot) {
    Node new_node = create_node();
    *ppRoot = &new_node;
}







// Функция создаёт и инициализирует новый узел
Node create_node() {
    printf("creation new node... input value: ");
    int val = get_int();

    Node new_node;
    new_node.data = val;
    new_node.left = NULL;
    new_node.right = NULL;

    return new_node;
}

// Функция получает от пользователя число типа int 
int get_int() {
    // Массив символов для вводимого числа
	char strValue[10] = {0}; 
	if(fgets(strValue, 11, stdin) == NULL) {
        printf("In \"get_int\" function: Error in fgets()\n");
    };
    // Преобразуем полученные массив символов в число типа int 
	int value = atoi(strValue);
	return value;
}
