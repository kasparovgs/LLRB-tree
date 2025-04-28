#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "llrbtree.h"
#include "logic.h"

#define DELIM ",./!? :;'=+-@#$%^&*()[]{}`“”’…\t \""

int log_insert(Tree* tree, char* key, char** info){
    int flag = add_node(tree, key, info);
    return flag;
}


int log_delete(Tree* tree, char* key){
    if (is_empty(tree)){
        return 1;
    }
    int flag = delete_node(tree, key);
    return flag;
}


int log_pretty_save(Tree* tree, char* filename){
    if (is_empty(tree)){
        return 0;
    }
    FILE* file = fopen(filename, "w");
    if (file == NULL){
        free(file);
        return -1;
    }
    pretty_save(tree, file);
    fclose(file);
    return 1;
}


int log_print(Tree* tree){
    if (is_empty(tree)){
        return -1;
    }
    print_tree(get_elist(tree), get_root(tree));
    return 0;
}


int log_pretty_print(Tree* tree){
    if (is_empty(tree)){
        return -1;
    }
    pretty_print_tree(get_elist(tree), get_root(tree), 0);
    return 0;
}


int log_search(Tree* tree, char* key, char** info){
    if (is_empty(tree)){
        return -1;
    }
    int flag = search_node(tree, key, info);
    return flag;
}


int log_special_search(Tree* tree, char* key, char** result){
    if (is_empty(tree)){
        return -1;
    }
    int flag = special_search(tree, key, result);
    return flag;
}


int log_save_to_file(Tree* tree, char* filename){
    if (is_empty(tree)){
        free(filename);
        return 0;
    }
    FILE* file = fopen(filename, "w");
    if (file == NULL){
        free(file);
        free(filename);
        return -1;
    }
    save_to_file(get_elist(tree), get_root(tree), file);
    fclose(file);
    free(filename);
    return 1;
}


int log_read_from_file(Tree* tree, char* filename){
    clear_tree(tree);
    FILE* file = fopen(filename, "r");
    if (file == NULL){
        free(file);
        free(filename);
        return -1;
    }
    int flag = 0;
    int count = 0;
    int end_flag = 0;
    while (flag != -1){
        char* key, *info = NULL;
        if ((key = get_str_from_file(file, &end_flag)) == NULL){
            flag = -1;
            continue;
        }
        if ((info = get_str_from_file(file, &end_flag)) == NULL){
            flag = -1;
            free(key);
            continue;
        }
        add_node(tree, key, &info);
        count += 1;
    }
    fclose(file);
    free(filename);
    return count;
}


void calculating_time(Tree* tree, int count, int repeats){
    int arr_sizes[] = {50000, 70000, 90000, 110000, 130000, 150000,
     200000, 300000, 400000, 500000, 650000, 800000, 1000000, 1200000, 
     1400000, 1600000, 1800000, 2000000};
    for (int i = 0; i < sizeof(arr_sizes)/sizeof(int); i++){
        log_mass_work(tree, arr_sizes[i], count, repeats);
    }
}


void special_calculating_time(Tree* tree, int count, int repeats){
    int arr_sizes[] = {50000, 70000, 90000, 110000, 130000, 150000,
     200000, 300000, 400000, 500000, 650000, 800000, 1000000, 1200000, 
     1400000, 1600000, 1800000, 2000000};
    for (int i = 0; i < sizeof(arr_sizes)/sizeof(int); i++){
        log_mass_special_search(tree, arr_sizes[i], count, repeats);
    }
}


void log_mass_special_search(Tree* tree, int size, int count, int repeats){
/*count - количество элементов, которые будут искаться
size - размер дерева. repeats - количество повторений,
нужно, чтобы усреднить время*/
    double time = 0;
    for (int i = 0; i < repeats; i++){
        log_gen_tree(tree, size);
        int* arr_len = gen_arr_int(count);
        char** arr_key = gen_arr_str(count, arr_len);
        for (int k = 0; k < count; k++){
            char* result = NULL;
            clock_t start = clock();
            special_search(tree, arr_key[k], &result);
            clock_t end = clock();
            time += (double)(end - start)/CLOCKS_PER_SEC;
        }
        for (int k = 0; k < count; k++){
            free(arr_key[k]);
        }
        free(arr_len);
        free(arr_key);
    }
    printf("Количество элементов в дереве: %d\n", size);
    printf("Время специального поиска: %f\n", time/repeats);
}


void log_mass_work(Tree* tree, int size, int count, int repeats){
    double time_insert = 0;
    double time_search = 0;
    double time_delete = 0;
    for (int i = 0; i < repeats; i++){
        log_gen_tree(tree, size);
        int* arr_len = gen_arr_int(count);
        char** arr_key = gen_arr_str(count, arr_len);
        char** arr_info = gen_arr_str(count, arr_len);
        clock_t start_insert = clock();
        for (int k = 0; k < count; k++){
            int check = add_node(tree, arr_key[k], &arr_info[k]);
            if (check == 2){
                free(arr_key[k]);
                free(arr_info[k]);
                arr_key[k] = NULL;
                arr_info[k] = NULL;
            }
        }
        clock_t end_insert = clock();
        time_insert += (double)(end_insert-start_insert)/CLOCKS_PER_SEC;

        clock_t start_search = clock();
        for (int k = 0; k < count; k++){
            if (arr_key[k] != NULL){
                search_node(tree, arr_key[k], &arr_info[k]);
            }
        }
        clock_t end_search = clock();
        time_search += (double)(end_search-start_search)/CLOCKS_PER_SEC;

        clock_t start_delete = clock();
        for (int k = 0; k < count; k++){
        	if (arr_key[k]!=NULL){
				delete_node(tree, arr_key[k]);
        	}
        }
        clock_t end_delete = clock();
        time_delete += (double)(end_delete-start_delete)/CLOCKS_PER_SEC;
        free(arr_key);
        free(arr_info);
        free(arr_len);
    }
    printf("Количество элементов в дереве: %d\n", size);
    printf("Время вставки: %f\n", time_insert/repeats);
    printf("Время поиска: %f\n", time_search/repeats);
    printf("Время удаления: %f\n", time_delete/repeats);
}


int log_gen_tree(Tree* tree, int count){
    clear_tree(tree);
    char** arr_key = (char**)calloc(count, sizeof(char*));
    char** arr_info = (char**)calloc(count, sizeof(char*));
    int flag = 0;
    for (int i = 0; i < count; i++){
        int len_key = 2 + rand() % 7;
        arr_key[i] = realloc(arr_key[i], (len_key + 1)*sizeof(char));
        gen_random_str(arr_key[i], len_key);

        int len_info = 1 + rand() % 5;
        arr_info[i] = realloc(arr_info[i], (len_info + 1)*sizeof(char));
        gen_random_str(arr_info[i], len_info);
        int check = add_node(tree, arr_key[i], &arr_info[i]);
        if (check == 2 || check == 1){
            free(arr_key[i]);
            free(arr_info[i]);
        }
        flag += 1;
    }
    free(arr_key);
    free(arr_info);
    return 1;
}


int log_quick_search(Tree* tree, char* filename){
    clear_tree(tree);
    FILE* file = fopen(filename, "r");
    if (file == NULL){
        free(file);
        free(filename);
        return -1;
    }
    int flag = 0;
    int end_flag = 0;
    int count = 0;
    int line_number = 1;
    while (flag != -1){
        char* key = NULL;
        char** arr_key = NULL;
        int* arr_offsets = NULL;
        key = get_str_from_file(file, &end_flag);
        if (end_flag == -1){
            flag = -1;
            continue;
        }
        if (key == NULL){
            line_number += 1;
            continue;
        }
        int len_arr = do_normal_str(key, &arr_key, &arr_offsets);
        for (int i = 0; i < len_arr; i++){
            char* info = NULL;
            if (find(get_elist(tree), get_root(tree), arr_key[i]) == get_elist(tree)){
                info = make_info_to_format(filename,  line_number, arr_offsets[i]);
                add_node(tree, arr_key[i], &info);
                count += 1;
            }
            else{
                free(arr_key[i]);
            }
        }
        line_number += 1;
        free(arr_key);
        free(arr_offsets);
    }
    fclose(file);
    return count;
}


int do_normal_str(char* str, char*** arr, int** arr_offsets){
/*на вход получает строку и адрес вектора указателей.
из строки str с помощью strtok'а разбивает её по
словам, каждое слово приводит к нижнему регистру и 
добавляет в вектор. возвращает количество добавленных
в массив слов (длину вектора)*/
    int size = 0;
    int len = strlen(str);
    char* word = NULL;
    word = strtok(str, DELIM);
    while (word != NULL){
        size += 1;
        *arr = realloc(*arr, size * sizeof(char*));
        (*arr)[size - 1] = strdup(word);

        *arr_offsets = realloc(*arr_offsets, size * sizeof(int));
        (*arr_offsets)[size - 1] = word - str;
        word = strtok(NULL, DELIM);
    }
    for (int i = 0; i < size; i++){
        char* word = (*arr)[i];
        for(int k = 0; k < strlen(word); k++){
            if (is_upper(word, k)){
                word[k] += 32;
            }
        }
    }
    free(str);
    return size;
}


char* make_info_to_format(char* filename, int line_number, int offset){
    int len_filename = strlen(filename);
    char* line_number_str = (char*)calloc(20, sizeof(char));
    sprintf(line_number_str, "%d", line_number);
    char* offset_str = (char*)calloc(20, sizeof(char));
    sprintf(offset_str, "%d", offset);
    char* new = (char*)calloc((len_filename + strlen(line_number_str) + strlen(offset_str) + 9), sizeof(char));
    new[0] = 60; // "<"
    strcat(new, filename);
    new[len_filename + 1] = 62; // ">"
    new[len_filename + 2] = 58; // ":"
    new[len_filename + 3] = 60;
    strcat(new, line_number_str);
    new[len_filename + strlen(line_number_str) + 4] = 62;
    new[len_filename + strlen(line_number_str) + 5] = 58;
    new[len_filename + strlen(line_number_str) + 6] = 60;
    strcat(new, offset_str);
    new[len_filename + strlen(line_number_str) + strlen(offset_str) + 7] = 62;
    new = realloc(new, (strlen(new) + 1)*sizeof(char));
    free(line_number_str);
    free(offset_str);
    return new;
}


void gen_random_str(char* str, int len){
    for (int i = 0; i < len; i++){
        int randomType = rand() % 3;
        if (randomType == 0){
            str[i] = 'A' + (rand() % 26);
        }
        else if (randomType == 1){
            str[i] = 'a' + (rand() % 26);
        }
        else{
            str[i] = '0' + (rand() % 10);
        }
    }
    str[len] = '\0';
}


char** gen_arr_str(int size, int* arr_len){
    char** arr = (char**)calloc(size, sizeof(char*));
    for (int i = 0; i < size; i++){
        int len_key = arr_len[i];
        arr[i] = realloc(arr[i], (len_key + 1)*sizeof(char));
        gen_random_str(arr[i], len_key);
    }
    return arr;
}


int* gen_arr_int(int len){
    int* arr_len = (int*)malloc(len*sizeof(int));
    for (int k = 0; k < len; k++){
        arr_len[k] = 2 + rand() % 7;
    }
    return arr_len;
}

char* get_str_from_file(FILE* file, int* end_flag){
	char* input = (char*)calloc(1, sizeof(char));
	char* buf = (char*)calloc(21, sizeof(char));
	int n, len = 0;
	do{
        n = fscanf(file, "%20[^\n]", buf);
        if (n < 0){
            free(input);
            free(buf);
            input = NULL;
            *end_flag = -1;
            return input;
        }
        if (n == 0){
            fscanf(file, "%*c");
        }
        else{
            len += strlen(buf);
            input = (char*)realloc(input, (len + 1)*sizeof(char));
            strcat(input, buf);
        }
    }while(n > 0);
	free(buf);
	if (strlen(input)==0){
		free(input);
		return NULL;
	}
	return input;
}


int is_upper(char* str, int i){
    return (str[i]>64 && str[i]<91);
}
