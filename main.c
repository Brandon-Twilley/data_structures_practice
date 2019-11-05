#include <stdio.h>
#include <stdlib.h>

struct node;
struct singly_linked_list;
struct digraph_node;

struct digraph_node{
    struct digraph_node* next[26];
    int exists[26];

};

struct hash_tree {
    struct digraph_node *start;

};

struct digraph_node* create_hash_layer();
void insert_into_digraph(struct digraph_node *dg, char str[]);
struct node {
    int value;
    struct node* next;
};

struct singly_linked_list {
    struct node* head;
    struct node *list[10];
};

struct singly_linked_list* build_singly_linked_list(){
    int i = 0;
    struct singly_linked_list sll;
    struct node* new_node = NULL;
    for(i=0; i < 10; i++){
        new_node = malloc(sizeof(struct node));
        sll.list[i] = new_node;
        new_node->value = i;
    }
    sll.head = sll.list[0];
    sll.head = sll.head;
    for(i = 0; i < 9; i++){
        sll.list[i]->next = sll.list[i+1];
    }
    sll.list[9]->next = NULL;
    printf("Head pointer is 0x%p\n", sll.head);

    return &sll;
}

void print_singly_linked_list(struct singly_linked_list *sll){
    struct node* runner = sll->head;
    while(runner != NULL){
        printf("0x%p = 0x%p ->0x%p\n", runner, runner->value, runner->next);
        runner = runner->next;
    }
}

void insert_into_digraph( struct digraph_node *dg, char str[]){
    struct digraph_node *new_digraph = create_hash_layer();
    printf("Inserted: %c\t", str[0]);
    printf("Int: %d\t", (int)(str[0] - 0x61));
    printf("new_digraph pointer: 0x%p\n", new_digraph);
    if(dg->exists[str[0] - 0x61]){

    } else {
        dg->next[str[0] - 0x61] = new_digraph;
        dg->exists[str[0] - 0x61] = 1;

    }
    if(str[1] == 0){

    } else {
        insert_into_digraph( new_digraph, str+1);
    }
}

struct digraph_node* create_hash_layer(){
    struct digraph_node *dg = malloc(sizeof(struct digraph_node));
    int i = 0;
    for(i=0; i < 26; i++){
        dg->next[i] = NULL;
        dg->exists[i] = 0;
    }
    return dg;

}

void delete_digraph( struct digraph_node *dg ){
    int i = 0;
    for(i = 0; i < 26; i++){
        if(dg->exists[i] != 0){
            delete_digraph(dg->next[i]);
            free(dg->next[i]);
        }
    }
    free(dg->next);

}

void print_digraph(struct digraph_node *dg, int layer){
    //printf("layer: %d", layer);

    int i = 0;
    int j = 0;
    for(i = 0; i < 26; i++){
        if(dg->exists[i] == 1){
            for(j = 0; j < layer; j++){
                printf(" ");
            }
            printf("%c\n", (char)(i + 0x61));
            print_digraph(dg->next[i], layer+1);
        }
    }
}

int main()
{
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    char al[] = "abd";
    char a2[] = "aad";

    struct hash_tree ht;
    ht.start = create_hash_layer();
    insert_into_digraph(ht.start, alphabet);
    /*
    insert_into_digraph(ht.start, a1);
    */
    struct digraph_node* dg;
    dg = ht.start;
    int aa_exists = dg->exists[0]->exists[0];
    printf("Does aa exist? %d", aa_exists);
    insert_into_digraph(ht.start, a2);
    print_digraph(ht.start, 0);
}
