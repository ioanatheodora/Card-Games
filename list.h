#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define CARDS_NO 52
#define LEN_TASK 13
#define LEN_TYPE 20


typedef struct{
    char number, color;
    int value;
}TCard;

typedef TCard* Item;
#include "Stack.h"

typedef struct node{
    TCard* card;
    struct node* next;
} TNode, *TList;

typedef struct rstone{
    char color;
    int player[4];//retinem cate carti de culoarea color are fiecare jucator
    struct rstone *next;
} rStone;

typedef struct doubleLinkedList{
    TList cards;
    int no;
    struct doubleLinkedList *next, *prev;
}ListScarabei, *TListScarabei;

TList create(){
    TList node = NULL;
    node = (TList)malloc(sizeof(TNode));
    node->card = (TCard *)malloc(sizeof(TCard));
    node->next = NULL;
    return node;
}

void insertLast(TList list, int value, char number, char color){
    TNode* node = create();
    node->card->number = number;
    node->card->color = color;
    node->card->value = value;
    list->next = node;
    return;
}

void insertEnd(TList list, TNode  *cards){
    TList copyList = list;
    while(copyList->next != NULL){
        copyList = copyList->next;
    }
    copyList->next = cards;
 
}

TList insertFirst(TList list, int value,  char number, char color){
    TNode *node = create();
    node->card->number = number;
    node->card->color = color;
    node->card->value = value;
    node->next = list;

    return node;
}

TNode *top(TList *list){
    TNode *node = *list;
    *list = (*list) -> next;

    return node;
}

TNode* extract(TList *list, char color){
    if((*list)->card->color == color)   return top(list);

    TList copy = *list;
    while(copy->next->next != NULL){
        if(copy->next->card->color == color){
            TList aux = copy->next;
            copy->next = copy->next->next;
            aux->next = NULL;
            return aux;
        }
        copy = copy ->next;
    }
    TList aux = copy->next;
    copy->next = NULL;
    aux->next = NULL;
    return aux;
}

void printDeck(TList list, FILE *out){
    TList aux = list;
    
    for(int i = 0 ; i < 52; i++){
        if(i == 51) fprintf(out, "%c%c\n", aux->card->number, aux->card->color); 
        else fprintf(out, "%c%c ", aux->card->number, aux->card->color);
        aux = aux->next;
    }
}


TList reverse(TList list){
    TList reversedList;
    if(list->next == NULL)
        return list;
    reversedList = reverse(list->next);
    TList next = list->next, crt = list;
    next->next = crt;
    if(crt == list){
        crt->next = NULL;
    }

    return reversedList;
}

TList freeTList(TList head){
    while(head != NULL){
        TNode *node = head;
        head = head->next;
        free(node);
    }
    return NULL;
}


TList NPiles(TList list, int N, int *order){
    TList copyList = list, *piles = NULL;
    piles =(TList *)malloc(N*sizeof(TList));

    int set = CARDS_NO/N;
    
    for(int i = 0; i < N; i++){
        
        piles[i] = copyList;
        
        for(int j = 0; j < set; j++){
            copyList = copyList->next;
        }
    }

    int prev , crt ;
    TList aux;

    for(int i = 1; i < N; i++){
        prev = i - 1;
        crt = i;

        aux = piles[order[prev] - 1];

        for(int j = 0; j < set - 1; j++)    
            aux = aux->next;

        aux->next = piles[order[crt] - 1];
    }

    for(int i = 0; i < set; i++){
        aux = aux->next; // parcurgem pana la ultimul elem pentru a pune NULL 
    }

    aux->next = NULL;
    list = piles[order[0] - 1];
    free(piles);
    return list;
}


TList intercalation(TList list){
    TList part1, part2, aux;
    part1 = list;
    aux = list;

    for(int i = 0; i < CARDS_NO/2 - 1; i++){
        aux = aux->next;
    }

    part2 = aux->next;
    aux->next = NULL;
    aux = part1;

    while(part2 != NULL){
        TList aux2 = part2;
        part2 = part2->next;

        aux2->next = aux->next;
        aux->next = aux2;

        aux = aux->next->next;
    }

    return part1;
}

TList Mongean(TList list){
    TList front, end, copy = list;
    front = create();
    front->card->color = copy->card->color;
    front->card->number = copy->card->number;
    front->card->value = copy->card->value;
    copy = copy->next;
    front->next = NULL;
   
    front = insertFirst(front, copy->card->value, copy->card->number, copy->card->color);
    copy = copy->next;
    end = front->next;

    while(copy != NULL){
        insertLast(end, copy->card->value, copy->card->number, copy->card->color);
        end = end->next;
        copy = copy->next;
        front = insertFirst(front, copy->card->value, copy->card->number, copy->card->color);
        copy = copy->next;
    }
    
    list = freeTList(list);

    return front;
} 


TList amestecare(TList list, FILE *in){
    int N, k;
        char *type = (char *)malloc(LEN_TYPE * sizeof(char));
        fscanf(in, "%d", &N);
        
        for(int i = 0; i < N; i++){
            fscanf(in, "%s", type);
            if (strcmp(type, "inversare") == 0){
                list = reverse(list);
                }
                else if (strcmp(type, "npiles") == 0){
                    fscanf(in, "%d", &k);

                    int *v =(int *)malloc(k * sizeof(int));

                    for(int j = 0; j < k; j++){
                        fscanf(in, "%d ", &v[j]);
                    }

                    list = NPiles(list, k, v);
                    free(v);
                     }
                     else if (strcmp(type, "intercalare") == 0){
                        list = intercalation(list);
                         } else list = Mongean(list);
            }

    return list; 

}

int min(int a, int b){
    if(a>b) return b;
    else return a;
}

int cards_left(TList player){
    if(player == NULL) return 0;

    return 1 + cards_left(player->next);
}

void war(TList *player1, TNode *card1, TList *player2, TNode *card2){
    int cards_played = min( min( cards_left(*player1), card1->card->value),\
                                min(cards_left(*player2), card2->card->value));

    Stack *stack1 = NULL, *stack2 = NULL;
    stack1 = createStack();
    stack2 = createStack();
    push(stack1, card1->card);
    free(card1);
    push(stack2, card2->card);
    free(card2);


    for(int i = 0; i < cards_played; i++){
        push(stack1, (*player1)->card);
        card1 = top(player1);
        free(card1);
        push(stack2, (*player2)->card);
        card2 = top(player2);
        free(card2);
    }

    TList copy1 = (*player1), copy2 = (*player2);
    while(copy1 != NULL && copy1->next != NULL){
        copy1 =copy1->next;
    }
    while(copy2 != NULL && copy2->next != NULL){
        copy2 =copy2->next;
    }

    if(stack1->head->elem->value > stack2->head->elem->value){
        while (isStackEmpty(stack1) == 0)
        {
             if( copy1 == NULL) {
                copy1 = create(); 
                copy1->card->color= stack1->head->elem->color;
                copy1->card->number = stack1->head->elem->number;
                copy1->card->value = stack1->head->elem->value;
                pop(stack1);
                *player1 = copy1;
            }else{
                insertLast(copy1, stack1->head->elem->value,\
                    stack1->head->elem->number, stack1->head->elem->color);
                pop(stack1);
                copy1=copy1->next;
            }
        }
        while (isStackEmpty(stack2) == 0)
        {
            insertLast(copy1,  stack2->head->elem->value,\
                 stack2->head->elem->number, stack2->head->elem->color);
            pop(stack2);
            copy1 = copy1->next;
        }
    }else
    {        
        
        while (isStackEmpty(stack2) == 0)
        {
            if( copy2 == NULL) {
                copy2 = create(); 
                copy2->card->color= stack2->head->elem->color;
                copy2->card->number = stack2->head->elem->number;
                copy2->card->value = stack2->head->elem->value;
                pop(stack2);
                *player2 = copy2;
                }
                else{
                    insertLast(copy2, stack2->head->elem->value, \
                        stack2->head->elem->number, stack2->head->elem->color);
                    pop(stack2);
                    copy2 = copy2->next;
            }
        }
        while (isStackEmpty(stack1) == 0)
        {
            insertLast(copy2,  stack1->head->elem->value,\
                 stack1->head->elem->number, stack1->head->elem->color);
            pop(stack1);
            copy2 = copy2->next;
        }
    }

}


void findWinner(TList player1, TList player2, FILE *out){
    int v1[16] = {0}, v2[16] = {0}, j;
    char cards[14] = "AKQJT98765432";
    int value[14] = {15, 14, 13, 12, 10, 9, 8, 7, 6, 5, 4, 3, 2};
    while(player1 != NULL){
        v1[player1->card->value]++;
        player1 = player1->next;
        
    }
    while(player2 != NULL){
        v2[player2->card->value]++;
        player2 = player2->next;
    }
    for(int i = 15; i > 0; i--){
        if(v1[i] > v2[i]){
            for(j = 0; j < 13; j++){
                if(i == value[j]){
                    
                    break;
                }
            }
                fprintf(out, "1 %c", cards[j]);
                return;
            }
        else {if(v1[i] < v2[i])
        {
            for( j = 0; j < 13; j++){
                if(i == value[j]){
                    break;
                }
            }
                fprintf(out, "2 %c", cards[j]);
                return;
            }
        }
    }
}


void razboi(TList list, FILE *out){
    TList player1, player2, copyList = list;
    //initializare pachete jucatori
    player1 = list;
    for(int i = 0; i < CARDS_NO/2 - 1; i++){
        copyList = copyList->next;
    }
    player2 = copyList->next;
    copyList->next = NULL;
    
    while(copyList !=NULL){
        copyList = copyList->next;
    }

    int round = 0;
    while(player1 != NULL && player2 != NULL && round < 100){
        round++;
        
        TNode *card1, *card2; 
        card1 = top(&player1);
        card1->next = NULL;
        card2 = top(&player2);  
        card2->next = NULL;
    
        if(card1->card->value > card2->card->value){
            insertEnd(player1, card1);
            insertEnd(player1, card2);
        }
        else if(card1->card->value < card2->card->value){
            insertEnd(player2, card2);
            insertEnd(player2, card1);
        }
        else{
           
            war(&player1, card1, &player2, card2); }
    
    }
   

    if(player1 == NULL) {
        fprintf(out, "2");
        return;
    }

    if(player2 == NULL){
        fprintf(out, "1");
        return;
    }

    findWinner(player1, player2, out);
}


int no_cards_color(TList player, char color){
    TList x = player;
    int no_cards = 0;
    while(x != NULL){
        if(x->card->color == color)
            no_cards++;
        x = x->next;
    }
    return no_cards;
}


void rollingStone(TList list, FILE *out){
    TList *player = (TList *)malloc(4 * sizeof(TList)), copyList = list;
    //impartire carti
    player[0] = list;
    for(int i = 0;  i < 3; i++){
        copyList = player[i];
        for(int j = 0; j < 12; j++)
            copyList = copyList->next;
        
    player[i+1] = copyList->next;
    copyList->next = NULL;
    }

    //creare lista circulara
    rStone *head = (rStone *)malloc(sizeof(rStone));
    rStone *copyHead = head;
    char colors[5] = "shcd";

    head->next = head;

    for(int i = 0; i < 3; i++){
        rStone *node =(rStone *)malloc(sizeof(rStone));
        copyHead->next = node;
        node->next = head;
        copyHead = copyHead->next;
    }
    copyHead = head;
    //aflam cate carti din fiecare culoare are fiecare jucator
    for(int i = 0; i < 4; i++){
        copyHead->color = colors[i];
        for(int j = 0; j < 4; j++)
            {copyHead->player[j] = no_cards_color(player[j], colors[i]);
            }  
        copyHead = copyHead->next;
    }

    copyHead = head;

    //incepem jocul
    TList round;
    int newGame = 1, currentPlayer = 0;
    while(player[0] != NULL && player[1] != NULL && \
            player[2] != NULL && player[3] != NULL){ //daca nu s a castigat inca
        if(newGame == 1){//runda noua
            while(copyHead->player[currentPlayer] == 0) copyHead = copyHead->next;
                    //incercam o alta culoare
            round = extract(&player[currentPlayer], copyHead->color);
            round->next = NULL;
            newGame = 0;
            copyHead->player[currentPlayer]--;
            currentPlayer++;
            if(currentPlayer > 3)   currentPlayer = 0;
            }else{
            if(copyHead->player[currentPlayer] > 0){
            //daca are carte de culoarea data           
            TNode *n = extract( &player[currentPlayer], copyHead->color );
            n->next = NULL;
                insertEnd( round, n );
                copyHead->player[currentPlayer]--;
                currentPlayer++;
                if(currentPlayer > 3)   currentPlayer = 0;
            }else{//daca nu are cartea de culoarea data
                if(copyHead->player[currentPlayer] == 0)
                {newGame = 1;//s-a terminat runda curenta
                insertEnd(player[currentPlayer], round);
                //se adauga cartile in pachet
                copyHead->player[currentPlayer] = no_cards_color(player[currentPlayer], copyHead->color);
                copyHead = copyHead->next;//trecem la urmatoarea culoare
                
                }
            }
        }
    }
    int winner;

    for(int i = 0; i < 4; i++){
        if(player[i] == NULL){
            winner = i+1;
            break;
        }
    }

    free(player);

    fprintf(out, "%d", winner);
}

void nextPlayer(TListScarabei *s ,int direction){
    if(direction%2 == 0) {
        while((*s)->next->cards == NULL) (*s) = (*s)->next;
            (*s) = (*s)->next;
    }else {
        while((*s)->prev->cards == NULL) (*s) = (*s)->prev;
            *s = (*s)->prev;
    }        
}


void winRound(Stack **stack, TListScarabei *s, int winner){
    while((*s)->no != winner) (*s) = (*s)->next; //gasim castigatorul
    TList copy = (*s)->cards;
    while(copy != NULL && copy->next != NULL) {copy = copy->next;}
     while(isStackEmpty(*stack) == 0){
        if( copy == NULL) {
            copy = create(); 
            copy->card->color= (*stack)->head->elem->color;
            copy->card->number = (*stack)->head->elem->number;
            copy->card->value = (*stack)->head->elem->value;
            (*s)->cards = copy;
            pop(*stack);
        }else{
            insertLast(copy, (*stack)->head->elem->value, \
            (*stack)->head->elem->number, (*stack)->head->elem->color);
            pop(*stack);
            copy = copy->next;
        }
    }
}

void scarabei(TList list, FILE *out)
{
    TListScarabei s = NULL;
    //cream o lista circulara pentru jucatori
    s = (TListScarabei)malloc(sizeof(ListScarabei));
    s->cards = NULL;
    s->next = s;
    s->prev = s;
    for(int i = 0; i < 3; i++){
        TListScarabei newcell = (TListScarabei)malloc(sizeof(ListScarabei));
        newcell->cards = NULL;
        newcell->prev = s;
        newcell->next = s->next;
        newcell->prev->next = newcell;
        newcell->next->prev = newcell;
        s = s->next;
    }
    s = s->next;//ajungem la primul jucator
    
    //impartire carti
    TList copyList = list;
    s->cards = list;
    for(int i = 0; i < 3; i++){
        copyList = s->cards;
        for(int j = 0; j < 12; j++)
            copyList = copyList->next;
        s->no = i;
        s->next->cards = copyList->next;
        copyList->next = NULL;
        s = s->next;
    }
    s->no = 3;
    s = s->next;//revenim la primul jucator

    int no_of_players = 4, winner = -1, direction = 0;
    //direction == par => sens inv trigonometric
    //direction == impar => sens trigonometric
    
    while(no_of_players > 1){//o runda
        if(direction%2 == 0) {
            while(s->no == -1) s = s->next;
        }else {
            while(s->no == -1) s = s->prev;
        }
        Stack *stack;
        stack = createStack();
        TList card = top(&s->cards);
        push(stack, card->card);
        free(card);
        winner = -1;
        if(stack->head->elem->value > 10) winner = s->no;
        if(stack->head->elem->value == 8) {direction++; }
        
        nextPlayer(&s, direction);//trecem la urmatorul jucator
        while(isStackEmpty(stack) == 0 && no_of_players > 1){
            //unul dintre jucatori nu a castigat runda
            TNode *node;
            if(stack->head->elem->value <= 10){
                //carte cu numar
                node = top(&s->cards);
                if(node->card->value > 10){
                    winner = s->no;// castigatorul "aparent" este cel de pe pozitia no
                }
                if(node->card->value == 8){
                    direction++;//se schimba sensul
                }
                push(stack, node->card);
                free(node);
                nextPlayer(&s, direction);     

            }else if(stack->head->elem->value > 10){
               node = top(&s->cards);
                if(node->card->value > 10){
                winner = s->no;
                push(stack, node->card);
                free(node);
                //trecem la urmatorul jucator
                nextPlayer(&s, direction);         
            }else if(node->card->value <= 10 && node->card->value != 8){
                    //player-ul de pe pozitia winner ia cartile
                    push(stack, node->card);
                    free(node);
                    winRound(&stack, &s, winner);
                }else if(node->card->value == 8) {
                    push(stack, node->card);
                    free(node);
                    winner = -1;
                    //trecem la urmatorul jucator
                   nextPlayer(&s, direction);
           }
            }
            for(int i = 0; i < 4; i++){
                if(s->cards == NULL && s->no != -1 && winner != s->no) {
                    //a ramas fara carti si nu mai poate castiga
                    s->no = -1;
                    no_of_players--;
                }
                s = s->next;
            }
        }
    }
    while(s->cards == NULL) s = s->next;
    winner = s->no + 1;
    free(s);
    fprintf(out, "%d", winner);
}