#ifndef LOGIC_H
#define LOGIC_H

int log_insert(Tree* tree, char* key, char** info);
int log_delete(Tree* tree, char* key);
int log_pretty_save(Tree* tree, char* filename);
int log_print(Tree* tree);
int log_pretty_print(Tree* tree);
int log_search(Tree* tree, char* key, char** info);
int log_special_search(Tree* tree, char* key, char** result);
int log_save_to_file(Tree* tree, char* filename);
int log_read_from_file(Tree* tree, char* filename);
char* get_str_from_file(FILE* file, int* end_flag);

int log_gen_tree(Tree* tree, int count);
char** gen_arr_str(int size, int* arr_len);
int* gen_arr_int(int len);
void gen_random_str(char* str, int len);
void calculating_time(Tree* tree, int count, int repeats);
void special_calculating_time(Tree* tree, int count, int repeats);
void log_mass_special_search(Tree* tree, int size, int count, int repeats);
void log_mass_work(Tree* tree, int size, int count, int repeats);

int do_normal_str(char* str, char*** arr, int** arr_offsets);
int log_quick_search(Tree* tree, char* filename);
char* make_info_to_format(char* filename, int line_number, int offset);
int is_upper(char* str, int i);

#endif