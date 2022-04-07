#include <stdio.h>
#include "list.h"
#include <string.h>
#include <stdlib.h>



int main(void){
    char cards[14] = "AKQJT98765432";
    int value[14] = {15, 14, 13, 12, 10, 9, 8, 7, 6, 5, 4, 3, 2};
    TList list = create();
    TList copyList = list;

    for(int i = 0; i < 13; i++){
        insertLast(copyList, value[i], cards[i], 's');
        copyList = copyList->next;
        insertLast(copyList, value[i], cards[i], 'h');
        copyList = copyList->next;
        insertLast(copyList, value[i], cards[i], 'c');
        copyList = copyList->next;
        insertLast(copyList, value[i], cards[i], 'd');
        copyList = copyList->next;
    }

    list = list->next;
    
    char *task = (char *)malloc (LEN_TASK * sizeof(char));

    FILE *in = fopen("in", "r");
    FILE *out = fopen("out", "w");

    fscanf(in, "%s", task);

    if(strcmp(task, "amestecare") == 0){

       list = amestecare(list, in);

       printDeck(list, out);

    }

    if(strcmp(task, "razboi") == 0){

        list = amestecare(list, in);
        razboi(list, out);

    }

    if(strcmp(task, "rollingstone") == 0){
        list = amestecare(list, in);
        rollingStone(list, out);
    }

    if(strcmp(task, "scarabei") == 0){
        list = amestecare(list, in);
        scarabei(list, out);
    }

    fclose(in);
    fclose(out);
    
    list = freeTList(list);
      
    return 0;
}