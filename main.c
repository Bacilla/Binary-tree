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
void add_node(Node **ppRoot);


// Вспомогательные функции
Node *create_node(Node **ppRoot);
int bin_search(Node **ppRoot, int val);
int get_int();



int main() {
    // Корень дерева
    Node *root = NULL; 

    // Создание первого узла дерева (корня)
    tree_initialization(&root);

    add_node(&root);
    add_node(&root);
    add_node(&root);



    return 0;
}

// Функция инициализирует дерево
void tree_initialization(Node **ppRoot) {
    Node *new_node = create_node(&(*ppRoot));
    *ppRoot = new_node;
}

// Функция добавляет на своё место новый узел дерева 
void add_node(Node **ppRoot) {
    Node *new_node = create_node(&(*ppRoot));
    if(new_node == NULL) { // Если такое число уже есть в дереве
        return;
    }

    Node *temp = *ppRoot;

    while(1) {
        // Движемся по дереву влево или вправо, в зависимости от значения data
        if(new_node->data > temp->data) {
            // Если левый узел конечный - сохраняем в него новый элемент
            if(temp->right == NULL) {
                temp->right = new_node; // ТУТ НУЖНО КАКИМ-ТО ОБРАЗОМ КЛАСТЬ НЕ В КОПИЮ НИЖНОГО УЗЛА, А В ОРИГИНАЛ!
                break;
            }
            temp = temp->right;
        } else if(new_node->data < temp->data) {
            // Если правый узел конечный - сохраняем в него новый элемент
            if(temp->left == NULL) {
                temp->left = new_node; // ТУТ НУЖНО КАКИМ-ТО ОБРАЗОМ КЛАСТЬ НЕ В КОПИЮ НЕЖНОГО УЗЛА, А В ОРИГИНАЛ!
                break;
            }
            temp = temp->left;
        }
    }
}





// Функция создаёт и инициализирует новый узел, возвращает указатель на новый узел
Node *create_node(Node **ppRoot) {
    printf("creation new node... input data(int): ");
    int data = get_int();

    // Если дерево не пустое и уже содержит элемент со значение data - вывод ошибки
    if((*ppRoot) != NULL && (bin_search(&(*ppRoot), data) == 1)) {
        printf("Error! \"%d\" is already in tree\n", data);
        return NULL;
    }

    Node *new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

// Функция ищет значение val и возвращает 0, если значения нет в дереве, и 1 - если есть
int bin_search(Node **ppRoot, int val) {
    Node *temp = *ppRoot;
    while(1) {
        if(temp == NULL) {
            return 0;
        }
        if(val == temp->data) {
            return 1;
        }
        if(val > temp->data) {
            temp = temp->right;
        } else {
            temp = temp->left;
        }
    }
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
