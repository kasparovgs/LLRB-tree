#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llrbtree.h"


Tree* init_tree(){
    Tree* tree = (Tree*)calloc(1, sizeof(Tree));
    tree->EList = (Node*)calloc(1, sizeof(Node));
    tree->root = tree->EList;
    return tree;
}


int add_node(Tree* tree, char* key, char** info){
    char* prev_info = strdup(*info);
    Node* current = rec_add_node(tree->EList, tree->root, key, info);
    tree->root = current;
    tree->root->color = 0;
    if (*info == NULL){
        free(prev_info);
        return 1;
    }
    if (strcmp(prev_info, *info) != 0){
        free(prev_info);
        return 2;
    }
    free(prev_info);
    return 0;
}


Node* rec_add_node(Node* EList, Node* current, char* key, char** info){
    if (current == EList){
        return init_node(EList, key, *info);
    }
    if (strcmp(key, current->key) > 0){
        current->right = rec_add_node(EList, current->right, key, info);
    }
    else if (strcmp(key, current->key) < 0){
        current->left = rec_add_node(EList, current->left, key, info);
    }
    else{ //ключи совпадают
        if ((strcmp(*info, current->info)) == 0){
            free(*info);
            *info = NULL;
        }
        else{
            char* str = current->info;
            current->info = *info;
            *info = str;
        }
    }

    if (is_red(current->right) && !is_red(current->left)){
        current = rotate_left(current);
    }
    if (is_red(current->left) && is_red(current->left->left)){
        current = rotate_right(current);
    }
    if (is_red(current->left) && is_red(current->right)){
        colorflip(current);
    }
    return current;
}


Node* fix_up(Node* current){
    if (is_red(current->right)){
        current = rotate_left(current);
    }

    if (is_red(current->left) && is_red(current->left->left)){
        current = rotate_right(current);
    }
    if (is_red(current->left) && is_red(current->right)){
        colorflip(current);
    }
    return current;
}


int delete_node(Tree* tree, char* key){
    if (find(tree->EList, tree->root, key) == tree->EList){
        return 2;
    }
    Node* new_root = rec_delete_node(tree->EList, tree->root, key);
    tree->root = new_root;
    tree->root->color = 0;
    return 0;
}


Node* rec_delete_node(Node* EList, Node* current, char* key){
    if (current == EList){
        return EList;
    }
    int cmp = strcmp(key, current->key);
    if (cmp < 0){
        if (current->left != EList && !is_red(current->left) && !is_red(current->left->left)){
            current = move_red_left(current);
        }
        current->left = rec_delete_node(EList, current->left, key);
    }
    else{
        int recmp = 0;
        if (is_red(current->left)){
            current = rotate_right(current);
            recmp = 1;
        }
        if (current->right == EList){
            if (recmp == 1){
                recmp = 0;
                cmp = strcmp(key, current->key);
            }
            if (cmp == 0){
                free(current->info);
                free(current->key);
                free(current);
                current = NULL;
                return EList;
            }
        }
        if (current->right != EList && (!is_red(current->right) && !is_red(current->right->left))){
            current = move_red_right(current);
            recmp = 1;
        }
        if (recmp == 1){
            cmp = strcmp(key, current->key);
        }
        if (cmp == 0){
            Node* min = find_min(EList, current->right);
            free(current->info);
            free(current->key);
            current->info = min->info;
            current->key = min->key;
            
            current->right = remove_min(EList, current->right);
        }
        else{
            current->right = rec_delete_node(EList, current->right, key);
        }   
    }
    return fix_up(current);
}


Node* remove_min(Node* EList, Node* current){
    if (current->left == EList){
        /*тут не нужно очищать current->key, info,
        т.к. мы переопределяем в функции удаления
        информацию из этого минимального узла*/
        free(current);
        return EList;
    }
    if (!is_red(current->left) && !is_red(current->left->left)){
        current = move_red_left(current);
    }
    current->left = remove_min(EList, current->left);
    return fix_up(current);
}


Node* find_min(Node* EList, Node* current){
    if (current == EList){
        return EList;
    }
    while (current->left != EList){
        current = current->left;
    }
    return current;
}


Node* move_red_left(Node* current){
    colorflip(current);
    if (is_red(current->right->left)){
        current->right = rotate_right(current->right);
        current = rotate_left(current);
        colorflip(current);
    }
    return current;
}


Node* move_red_right(Node* current){
    colorflip(current);
    if (is_red(current->left->left)){
        current = rotate_right(current);
        colorflip(current);
    }
    return current;
}


Node* init_node(Node* EList, char* key, char* info){
    Node* new = (Node*)calloc(1, sizeof(Node));
    new->key = key;
    new->info = info;
    new->color = 1;
    new->left = EList;
    new->right = EList;
    return new;
}


void colorflip(Node* current){
    current->color = 1 - current->color;
    current->left->color = 1 - current->left->color;
    current->right->color = 1 - current->right->color;
}

Node* find(Node* EList, Node* current, char* key){
/*ищет ноду по ключу, возвращает указатель на неё, либо EList,
если ничего не найдено*/
    while (current != EList){
        if (strcmp(current->key,key) == 0){
            return current;
        }
        current = (strcmp(key, current->key) < 0) ? current->left : current->right;
    }
    return EList;
}


Node* rotate_left(Node* current){
/*функция для поворота против часовой стрелки.
т.к. в структуре ноды нет указателя на родителя,
то в эту функцию нужно передавать самого родителя,
чтобы сделать поворот*/
    Node* child = current->right;
    current->right = child->left;
    child->left = current;
    child->color = current->color;
    current->color = 1;
    return child;
}


Node* rotate_right(Node* current){
/*функция для поворота по часовой стрелки.
т.к. в структуре ноды нет указателя на родителя,
то в эту функцию нужно передавать самого родителя,
чтобы сделать поворот*/
    Node* child = current->left;
    current->left = child->right;
    child->right = current;
    child->color = current->color;
    current->color = 1;
    return child;
}


int search_node(Tree* tree, char* key, char** info){
    Node* EList = tree->EList;
    Node* current = tree->root;
    while (current != EList){
        if (strcmp(current->key, key) == 0){
            *info = current->info;
            return 1;
        }
        current = (strcmp(key, current->key) < 0) ? current->left : current->right;
    }
    return 0;
}


int special_search(Tree* tree, char* key, char** result){
/*функция для поиска ноды с наименьшим значением ключа, 
превышающим заданное (то есть минимум из бОльших).
Принцип работы функции: идем по strcmp по дереву, 
1. Если надо пойти влево, то это норм, там потенциально может 
находиться результат, ибо если мы хотя бы один раз пошли влево,
значит ключ в просматриваемой ноде уже больше введенного,
а значит нам всего лишь остаётся найти минимум точно так же
идя влево (если так говорит strcmp).
2. Если же по strcmp надо пойти вправо, то это значит, что 
мы ключ в ноде пока что меньше введенного, а это значит, что
эти ноды не являются потенциальным результатом
3. В конце проверяем, если найденый ключ совпадает с введенным,
то нас такое не устраивает (по условию)*/
    Node* current = tree->root;
    Node* EList = tree->EList;
    Node* res_node = NULL;
    while (current != EList){
        if (strcmp(key, current->key) < 0){
            res_node = current;
            current = current->left;
        }
        else{ // strcmp(key, current->key) >= 0
            current = current->right;
        }
    }
    if (res_node == NULL || strcmp(res_node->key, key) == 0){
        return -1;
    }
    *result = res_node->key;
    return 0;
}


void pretty_save(Tree* tree, FILE* file){
    fprintf(file, "digraph LLRB{\n");
    fprintf(file, "\tnode [fontcolor=white, style=filled];\n");
    int num = 0;
    rec_pretty_save(get_elist(tree), get_root(tree), file, &num);
    fprintf(file, "}");
}


void rec_pretty_save(Node* EList, Node* current, FILE* file, int* num){
    if (current == EList){
        return;
    }
    *num += 1;
    int color = current->color;
    fprintf(file, "\t\"%s\" [fillcolor=%s];\n", current->key, color == 1 ? "red" : "black");
    if (current->left != EList){
        fprintf(file, "\t\"%s\" -> \"%s\" [label=\"left\"];\n", current->key, current->left->key);
        if (current->right == EList){
            fprintf(file, "\t%d [style=invis];\n\t\"%s\" -> %d [style=invis];\n", *num, current->key, *num);
        }
        rec_pretty_save(EList, current->left, file, num);
    }
    if (current->right != EList){
        if (current->left == EList){
            fprintf(file, "\t%d [style=invis];\n\t\"%s\" -> %d [style=invis];\n", *num, current->key, *num);
        }
        fprintf(file, "\t\"%s\" -> \"%s\" [label=\"right\"];\n", current->key, current->right->key);
        rec_pretty_save(EList, current->right, file, num);
    }
}


void print_tree(Node* EList, Node* current){
    if (current != EList){
        printf("Key: \"%s\" ", current->key);
        printf("Info: \"%s\" \n", current->info);
        print_tree(EList, current->left);
        print_tree(EList, current->right);
    }
}


void pretty_print_tree(Node* EList, Node* current, int space){
    if (current == EList){
        return;
    }
    space += 5;
    pretty_print_tree(EList, current->right, space);
    printf("\n");
    for (int i = 5; i < space; i++){
        printf(" ");
    }
    int color = current->color;
    printf("\"%s\", \"%s\"\n", current->key, color == 1 ? "red" : "black");
    pretty_print_tree(EList, current->left, space);
}


void save_to_file(Node* EList, Node* current, FILE* file){
    if (current == EList){
        return;
    }
    fprintf(file, "%s\n", current->key);
    fprintf(file, "%s\n", current->info);
    save_to_file(EList, current->left, file);
    save_to_file(EList, current->right, file);
}


Node* get_root(Tree* tree){
    return tree->root;
}


Node* get_elist(Tree* tree){
    return tree->EList;
}


int is_empty(Tree* tree){
    return (tree->root == tree->EList);
}


int is_red(Node* current){
    return current->color;
}


void swap_colors(Node* first, Node* second){
    int temp = first->color;
    first->color = second->color;
    second->color = temp;
}


void free_tree(Tree* tree){
    clear_tree(tree);
    free(tree->EList);
    free(tree);
}


void clear_tree(Tree* tree){
    free_nodes(tree->EList, tree->root);
    tree->root = tree->EList;
}


void free_nodes(Node* EList, Node* current){
    if (current != EList){
        free_nodes(EList, current->left);
        free_nodes(EList, current->right);
        free(current->key);
        free(current->info);
        free(current);
        current = NULL;
    }
}
