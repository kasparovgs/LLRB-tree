#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llrbtree.h"
#include "dialog.h"
#include "logic.h"


void print_options(){
	printf("*******************\n");
    printf("1. Вставить новый элемент.\n");
    printf("2. Удалить по ключу.\n");
    printf("3. Обход дерева в формате КЛП.\n");
    printf("4. Форматированный вывод дерева «виде дерева».\n");
    printf("5. Красивый вывод в graphviz.\n");
    printf("6. Поиск элемента по ключу.\n");
    printf("7. Специальный поиск по ключу.\n");
    printf("8. Сохранить дерево в текстовый файл.\n");
    printf("9. Прочитать дерево из текстового файла.\n");
    printf("10. Сгенерировать дерево.\n");
    printf("11. Вставить несколько элементов для таймирования вставки, поиска и удаления.\n");
    printf("12. Вставить несколько элементов для таймирования специального поиска.\n");
    printf("13. Считать из файла для быстрого поиска.\n");
    printf("0. Завершение работы.\n");
}


void dial_insert(Tree* tree){
    printf("Введите ключ: ");
    char* key, *info = NULL;
    key = get_str();
    if (key == NULL){
        printf("Ошибка: введены некорректные данные.\n");
        return;
    }
    printf("Введите инфо: ");
    info = get_str();
    if (info == NULL){
        free(key);
        printf("Ошибка: введены некорректные данные.\n");
        return;
    }
    int flag = log_insert(tree, key, &info);
    if (flag == 2){
        printf("Вершина с введённым ключом уже существует. Информация заменена.\n");
        printf("Старая информация: \"%s\"\n", info);
        free(info);
        free(key);
    }
    else if (flag == 1){
        printf("Вершина с введённым ключом и информацией уже существует.\n");
        free(info);
        free(key);
    }
    else{
        printf("Запись успешно добавлена.\n");
    }
}


void dial_delete(Tree* tree){
    printf("Введите ключ: ");
    char* key = NULL;
    key = get_str();
    if (key == NULL){
        printf("Ошибка: введены некорректные данные.\n");
        return;
    }
    int flag = log_delete(tree, key);
    if (flag == 2){
        printf("По данному ключу ничего не найдено.\n");
    }
    else if (flag == 1){
        printf("Дерево пустое.\n");
    }
    else{
        printf("Запись успешно удалена.\n");
    }
    free(key);
}


void dial_search(Tree* tree){
    printf("Введите ключ: ");
    char* key = NULL;
    char* info= NULL;
    key = get_str();
    if (key == NULL){
        printf("Ошибка: введены некорректные данные.\n");
        return;
    }
    int flag = log_search(tree, key, &info);
    if (flag == -1){
        printf("Дерево пустое.\n");
    }
    if (flag == 0){
        printf("По данному ключу ничего не найдено.\n");
    }
    else{
        printf("Запись найдена. key: \"%s\", info: \"%s\"\n", key, info);
    }
    free(key);
}


void dial_special_search(Tree* tree){
    printf("Введите ключ: ");
    char* key = NULL;
    char* result = NULL;
    key = get_str();
    if (key == NULL){
        printf("Ошибка: введены некорректные данные.\n");
        return;
    }
    int flag = log_special_search(tree, key, &result);
    if (flag == -1){
        printf("По данному ключу ничего не найдено.\n");
    }
    else{
        printf("Найденный ключ: \"%s\".\n", result);
    }
    free(key);
}


void dial_print(Tree* tree){
    int flag = log_print(tree);
    if (flag == -1){
        printf("Дерево пустое.\n");
    }
}


void dial_pretty_print(Tree* tree){
    int flag = log_pretty_print(tree);
    if (flag == -1){
        printf("Дерево пустое.\n");
    }
}


void dial_pretty_save(Tree* tree){
    char* filename = "test.dot";
    int flag = log_pretty_save(tree, filename);
    if (flag == 0){
        printf("Дерево пустое.\n");
        return;
    }
    printf("Дерево успешно записано.\n");
}


void dial_save_to_file(Tree* tree){
    printf("Введите имя файла (c форматом): ");
    char* filename = get_str();
    if (filename == NULL){
        printf("Ошибка: введите корректное имя файла.\n");
        return;
    }
    int flag = log_save_to_file(tree, filename);
    if (flag == 0){
        printf("Дерево пустое.\n");
        return;
    }
    if (flag == -1){
        printf("Ошибка: проверьте корректность вводимых данных.\n");
        return;
    }
    printf("Дерево успешно сохранено в текстовый файл.\n");
}


void dial_read_from_file(Tree* tree){
    printf("Введите имя файла (c форматом): ");
    char* filename = get_str();
    if (filename == NULL){
        printf("Ошибка: введите корректное имя файла.\n");
        return;
    }
    int flag = log_read_from_file(tree, filename);
    if (flag == -1){
        printf("Проверьте корректность данных.\n");
    }
    else{
        printf("Записей считано из файла: %d.\n", flag);
    }
}


void dial_gen_tree(Tree* tree){
    printf("Введите количество вершин в дереве: ");
    int count = 0;
    int check = get_int(&count);
    if (check == 1){
        return;
    }
    int flag = log_gen_tree(tree, count);
    if (flag == 1){
        printf("Успешно создано %d записей.\n", count);
    }
}


void dial_mass_work(Tree* tree){
    int count = 0;
    printf("Введите количество элементов для вставки/удаления/поиска: ");
    int check = get_int(&count);
    if (check == 1){
        return;
    }
    int repeats = 0;
    printf("Введите количество повторений для всех операций: ");
    check = get_int(&repeats);
    if (check == 1){
        return;
    }
    calculating_time(tree, count, repeats);
}


void dial_special_search_time(Tree* tree){
    int count = 0;
    printf("Введите количество элементов для специального поиска: ");
    int check = get_int(&count);
    if (check == 1){
        return;
    }
    int repeats = 0;
    printf("Введите количество повторений для всех операций: ");
    check = get_int(&repeats);
    if (check == 1){
        return;
    }
    special_calculating_time(tree, count, repeats);
}


void dial_quick_search(Tree* tree){
    printf("Введите имя файла (c форматом): ");
    char* filename = get_str();
    if (filename == NULL){
        printf("Ошибка: введите корректное имя файла.\n");
        return;
    }
    int flag = log_quick_search(tree, filename);
    if (flag == -1){
        printf("Ошибка: проверьте корректность вводимых данных.\n");
    }
    else{
        printf("Файл успешно считан.\n");
    }
    free(filename);
}


char* get_str(){
/*возвращает NULL, если EOF или пустая строка*/
    char* input = (char*)calloc(1, sizeof(char));
    char* buf = (char*)calloc(81, sizeof(char));
    int n, len = 0;
    do{
        n = scanf("%80[^\n]", buf);
        if (n < 0){
            free(input);
            free(buf);
            input = NULL;
            return input;
        }
        if (n == 0){
            scanf("%*c");
        }
        else{
            len += strlen(buf);
            input = (char*)realloc(input, (len + 1)*sizeof(char));
            strcat(input, buf);
    }
    }while(n > 0);
    free(buf);
    if (strlen(input) == 0){
        free(input);
        return NULL;
    }
  return input;
}


int get_int(int* temp){
/*функция для ввода положительного целого числа.
возвращает 1, если EOF, и 0, если всё хорошо*/
	int count = 0;
	int check = scanf("%d", temp);
	while (check != 1 || *temp <= 0){
		if (check == EOF){
			return 1;
		}
		count += 1;
		printf("Введите целое число!\n");
		scanf("%*[^\n]");
		scanf("%*c");
		check = scanf("%d", temp);
	}
	scanf("%*c");
	return 0;
}
