#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int item;
    struct node *next;
}node;

typedef struct linkedList{
    node *head;
    int cnt;
}linkedList;

void add(linkedList *list){
    if((*list).head == NULL){
        list->cnt = 0;
        node * tmp=(node *)malloc(sizeof(node)) ;
        (*tmp).next=NULL;
        (*tmp).item=list->cnt+1;
        (*list).head =  tmp;  
        list->cnt++;
    }
    else{
        node *it;
        it = (*list).head;
        while(it->next!=NULL){
            it=(it->next);
        }
        node * tmp=(node *)malloc(sizeof(node)) ;
        (*tmp).next=NULL;
        (*tmp).item= list->cnt+1;
        it->next = tmp;
        list->cnt++;
    }
}

void delete(int index, linkedList *list){
    if(index==1){
       (*list).head = (*list).head->next;
       list->cnt--;
    }
    else {
        node *it;
        it = (*list).head;
        for(int i=0;i<index-2;i++){
            it=it->next;
        }
        it=(it->next)->next;
        list->cnt--;
    }
}
void printList(linkedList *list){
    node * it;
    it = list->head;
    for(int i=0;i<list->cnt;i++){
        printf("%d ",it->item);
        it= it->next;
    }

}
void findList(linkedList *list,int k){
    node *it;
    it = (*list).head;
    for(int i=0;i<list->cnt;i++){
        if(it->item==k){
            printf("cnt: %d \n",i+1);
            return;
        }
        it= it->next;
    }
    printf("can't find \n");
    return;
}

int main(){
    linkedList a;
    a.head=NULL;
    add(&a);
    add(&a);
    add(&a);
    add(&a);
    add(&a);
    add(&a);
    printList(&a);
    findList(&a,3);
    findList(&a,10);

}