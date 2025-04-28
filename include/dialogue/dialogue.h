#ifndef DIALOGUE_H
#define DIALOGUE_H

void print_options();
char* get_str();
int get_int(int* temp);

void dial_insert(Tree* tree);
void dial_delete(Tree* tree);
void dial_print(Tree* tree);
void dial_pretty_print(Tree* tree);
void dial_pretty_save(Tree* tree);
void dial_save_to_file(Tree* tree);
void dial_read_from_file(Tree* tree);
void dial_search(Tree* tree);
void dial_special_search(Tree* tree);
void dial_gen_tree(Tree* tree);
void dial_mass_work(Tree* tree);
void dial_dop(Tree* tree);
void dial_special_search_time(Tree* tree);

void dial_quick_search(Tree* tree);

#endif