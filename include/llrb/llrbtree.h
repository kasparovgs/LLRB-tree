#ifndef LLRBTREE_H
#define LLRBTREE_H


typedef struct Node{
    char* key;
    char* info;
    int color; /*1 - red, 0 - black*/
    struct Node* left, *right;
}Node;


typedef struct Tree{
    Node* root;
    Node* EList;
}Tree;

Tree* init_tree();
int add_node(Tree* tree, char* key, char** info);
int search_node(Tree* tree, char* key, char** info);
int special_search(Tree* tree, char* key, char** result);
Node* rec_add_node(Node* EList, Node* current, char* key, char** info);
Node* init_node(Node* EList, char* key, char* info);
Node* rotate_left(Node* current);
Node* rotate_right(Node* current);


int delete_node(Tree* tree, char* key);
Node* rec_delete_node(Node* EList, Node* current, char* key);
Node* move_red_left(Node* current);
Node* move_red_right(Node* current);
Node* find_min(Node* EList, Node* current);
Node* fix_up(Node* current);
Node* rec_delete_min(Node* EList, Node* current);
Node* find(Node* EList, Node* current, char* key);
void colorflip(Node* current);

Node* remove_min(Node* EList, Node* current);

Node* deleteNode(Node* EList, Node* root, char* k);

void pretty_print_tree(Node* EList, Node* current, int space);
void pretty_save(Tree* tree, FILE* file);
void save_to_file(Node* EList, Node* current, FILE* file);
void rec_pretty_save(Node* EList, Node* root, FILE* file, int* num);
void print_tree(Node* EList, Node* current);
Node* get_root(Tree* tree);
Node* get_elist(Tree* tree);
int is_empty(Tree* tree);
int is_red(Node* current);
void swap_colors(Node* first, Node* second);

void free_tree(Tree* tree);
void clear_tree(Tree* tree);
void free_nodes(Node* EList, Node* current);

#endif