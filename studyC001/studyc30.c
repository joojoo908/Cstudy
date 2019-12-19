#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct card {
    char shape;
    int num;
    struct card *next;
}card;

typedef struct linkedCard{
    struct card *head;
    int cnt;
}linkedCard;

void init(linkedCard * dack){
    card *it;
    char c[4]={'s','h','d','c'};
    (* dack).head = (card *)malloc(sizeof(card));
    it=(* dack).head;
    for(int n=0;n<52;n++){
        card *tmp=(card *)malloc(sizeof(card)) ;
        tmp->shape =c[n/13];
        tmp->num =n%13+1;
        tmp->next=NULL;
        it->next=tmp;
        it=it->next;
        (* dack).cnt=(* dack).cnt+1;
    }
}

void supple(linkedCard * dack){
    card *it;
    int a1;
    char a2;
    srand(time(NULL));
    int n=0;
    while(n<200){
        it=(* dack).head;
        a2=it->next->shape;
        a1=it->next->num;
        int random;
        random = rand() %51+1 ;
        for(int n=0;n<random;n++){
            it=it->next;
        }
        (* dack).head->next->shape=it->shape;
        (* dack).head->next->num=it->num;
        it->shape=a2;
        it->num=a1;
        n=n+1;
    }
}
void printcard(linkedCard *dack){
    card *it;
    it=(* dack).head;
    while(it->next!=NULL){
        it=it->next;
        printf("card %c %d \n",it->shape,it->num);
    }
}



int main(){
    linkedCard a;
    init(&a);
    supple(&a);
    printcard(&a);

}