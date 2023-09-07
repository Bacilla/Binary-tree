#include <stdio.h>
#include <stdlib.h> // atoi, malloc

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
int print_tree_data(Node **ppRoot);
void save_tree_data(Node **ppRoot, int arr[], int *pi);
// часть 2
void remove_node(Node *node_to_remove, Node **ppRoot, Node **ppParent);

// Вспомогательные функции
Node *create_node(Node **ppRoot);
int bin_search(Node **ppRoot, int val);
int get_int();
void show_command();
// часть 2
Node *find_node_to_remove(int data, Node **ppRoot, Node **parent);




int main() {
    // Корень дерева
    Node *root = NULL; 

    show_command();
    while(1) {
        printf("\ncommand: ");
        // Получаем и обрабатываем команду от пользователя
        int command = get_int();
        if(command < 1 || command > 4) {
            printf("Incorrect command!\n");
            continue;
        }

        // В зависимости от команды совершаем действие
        switch (command) {
            case 1:
                if(root == NULL) {
                    // Создание первого узла дерева (корня)
                    tree_initialization(&root);
                } else {
                    // Добавление нового узла в дерево
                    add_node(&root);
                }
                break;
            case 2:
                int res = print_tree_data(&root);
                if(res == 1) {
                    printf("Error writing file!\n");
                } else {
                    printf("Tree data successfully written in file!\n");
                }
                break;
            case 3:
                // Проверка на не пустое дерево
                if(root == NULL) {
                    printf("Error! the tree is empty\n");
                    break;
                }
                // Ввод пользователем числа, узел с которым надо удалить
                printf("data(int) to remove: ");
                int data_to_remove = get_int();
                // Поиск узла, который содержит введённое значение
                Node *parent = NULL;
                Node *node_to_remove = find_node_to_remove(data_to_remove, &root, &parent);
                if(node_to_remove == NULL) {
                    printf("Error! the tree do not have %d data\n", data_to_remove);
                    break;
                }
                // Удаляем узел
                remove_node(node_to_remove, &root, &parent);
                printf("success remove \n");
                break;
            case 4:
                printf("goodbye &_&\n");
                return 0;
        }
    }
    return 0;
}

// Функция удаляет узел из дерева. Возвращает 1 в случае ошибки и 0 если удаление прошло успешно
void remove_node(Node *node_to_remove, Node **ppRoot, Node **ppParent) {  
    // ФУНКЦИЯ РАБОТАЕТ С НЕ ПУСТЫМ ДЕРЕВОМ, СОДЕРЖАЩИМ ЭЛЕМЕНТ DATA

    // Указатель на узел, который надо удалить. Инзначально равен корню дерева
    Node **ppr_node = &(*ppRoot);
    Node *pr_node = *ppRoot;

    
    // Случай, когда у узла нет поддеревьев
    if(node_to_remove->left == NULL && node_to_remove->right == NULL) {
        // Случай когда удаляется корень дерева
        if(*ppRoot == node_to_remove) {
            *ppRoot = NULL;
        } else { // Удаляется не корень
            // В зависимости от того, в какой стороне находился дочерний удаляемый узел,
            // устанавливаем NULL у родителя
            if((*ppParent)->left == node_to_remove) {
                (*ppParent)->left = NULL;
            } else if((*ppParent)->right == node_to_remove) {
                (*ppParent)->right = NULL;
            }
        }
        //free(node_to_remove); 
        //return;
    }
    // Случай, когда у узла есть только одно поддерево
    // Случай, когда у узла два поддерева




    // Случай, когда у узла есть только одно поддерево
    // if(pr_node->left != NULL && pr_node->right == NULL) {
    //     *ppr_node = pr_node->left;
    // }
    // if(pr_node->right != NULL && pr_node->left == NULL) {
    //     *ppr_node = pr_node->right;
    // }


    
    free(node_to_remove);
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
                temp->right = new_node;
                break;
            }
            temp = temp->right;
        } else if(new_node->data < temp->data) {
            // Если правый узел конечный - сохраняем в него новый элемент
            if(temp->left == NULL) {
                temp->left = new_node;  
                break;
            }
            temp = temp->left;
        }
    }
}

// Функция создаёт файл для записи данных из дерева, возвращает 1 если произошла ошибка
int print_tree_data(Node **ppRoot) {
    if(*ppRoot == NULL) {
        return 1;
    }
    
    FILE *fp = fopen("treeData.txt", "w"); // создание нового пустого файла для записи
    if(fp == NULL) {
        return 1;
    }

    // массив для хранения упорядоченных данных из дерева
    int arr[100] = {0};
    int i = 0;

    // arr и i нужны для подсчёта и сохданения в порядке возрастания всех значений дерева
    save_tree_data(&(*ppRoot), arr, &i);

    // Выводим информацию на консоль
    for(int j = 0; j < 100; j++) {
        if(j == i) 
            break;
        printf("%d ", *(arr + j));
    }

    // Записываем информацию в файл
    for(int j = 0; j != i; j++) {
        fprintf(fp, "%d ", *(arr + j));
    }
    fclose(fp);

    return 0;
}

// Функция записывает все элементы дерева в порядке возрастания в файл,
// возвращает 1 - если возникла ошибка, и 0 - если запись прошла успешно
void save_tree_data(Node **ppRoot, int arr[], int *pi) {
    if(*ppRoot == NULL) {
        return;
    }

    save_tree_data(&((*ppRoot)->left), arr, &(*pi));

    *(arr + (*pi)) = (*ppRoot)->data;
    (*pi)++;

    save_tree_data(&((*ppRoot)->right), arr, &(*pi));
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

// Функция выводит на экран допустымие комманды
void show_command() {
    printf("Commands:\n\"1\": add note in binary tree\n\"2\": save tree data in .txt file\n\"3\": remove node\n\"4\": exit\n");
}

// Функция находит узел, который надо удалить или возвращает NULL, если такого узла не существует
Node *find_node_to_remove(int data, Node **ppRoot, Node **parent) {
    Node *node = *ppRoot;
    while(1) {
        if(node == NULL) {
            break;
        }
        if(data == node->data) {
            break;
        }

        // Ищем родителя для удаляемого элемента
        if((node->left != NULL) && (node->left->data == data) ) {
            *parent = node;
        } else if((node->right != NULL) && (node->right->data == data)) {
            *parent = node;
        }

        // Переходим на следующий узел
        if(data > node->data) {
            node = node->right;
        } else {
            node = node->left;
        }
    }
    return node;
}