#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "llrbtree.h"
#include "dialog.h"

int main(){
	srand(time(NULL));
    void (*menu[])(Tree*) = {NULL, dial_insert, dial_delete, dial_print, 
	dial_pretty_print, dial_pretty_save, dial_search, dial_special_search, 
	dial_save_to_file, dial_read_from_file, dial_gen_tree, dial_mass_work,
	dial_special_search_time, dial_quick_search};
    int count_of_options = sizeof(menu)/sizeof(menu[0]);
	int option = -1;
    Tree* tree = init_tree();
	do{
		option = -1;
		print_options();
		int r = scanf("%d", &option);
		if (r == EOF){
			free_tree(tree);
			return 1;
		}
		scanf("%*[^\n]");
		scanf("%*c");
		if (option >= 1 && option < count_of_options){
			menu[option](tree);
		}
	}while(option != 0);
	free_tree(tree);
    return 0;
}
