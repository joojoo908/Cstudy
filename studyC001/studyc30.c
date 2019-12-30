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

typedef struct user{
    char name[10];
    linkedCard hand;
}user;

void init(linkedCard * dack){
    card *it;
    dack->cnt = 0;
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
    int kount=0;
    while(it->next!=NULL){
        kount+=1;
        it=it->next;
        printf("%d:%c %d, ",kount,it->shape,it->num);
    }
}

void takeCard(user *p, linkedCard *dack){
    for(int i=0;i<3;i++){
        p[i].hand.head = (card *)malloc(sizeof(card));
    }
    for(int j=0;j<3;j++){
            (p[j].hand.head)->next=((* dack).head)->next;
            ((* dack).head)->next=(((* dack).head)->next)->next;
            ((p[j].hand.head)->next)->next=NULL;
            (* dack).cnt=(* dack).cnt-1;
        }
    for(int i=0;i<6;i++){
        for(int j=0;j<3;j++){
            card *tmp;
            tmp=((* dack).head)->next;
            ((* dack).head)->next=(((* dack).head)->next)->next;
            tmp->next=(p[j].hand.head)->next;
            (p[j].hand.head)->next=tmp;
            (* dack).cnt=(* dack).cnt-1;

        }
        
    }

}

int check_shape(card player, card pan){
    if (player.shape == pan.shape)
        return 1;
    else
        return 0;   
}
int check_num(card player, card pan){
    if(player.num == pan.num)
        return 1;
    else
        return 0;
    
}

void Start_game(linkedCard *dack ,user *p,linkedCard *pan){
    init(dack);
    supple(dack);
    takeCard(p,dack);
    (pan->head)->next=(dack->head)->next;
    (dack->head)->next=((dack->head)->next)->next;

}

int main(){
    linkedCard a;
    user p[3];
    linkedCard pan;
    pan.head =(card*)malloc(sizeof(card));

    init(&a);
    supple(&a);
    takeCard(p,&a);
    pan.head->next=a.head->next;
    a.head->next=(a.head->next)->next;

    printf("Front:%c %d",pan.head->next->shape,pan.head->next->num);
    printf("\ndack_list:%d", a.cnt);
    printf("\nuser1:");
    printcard(&(p[0].hand));
    printf("\nuser2:");
    printcard(&(p[1].hand));
    printf("\nuser3:");
    printcard(&(p[2].hand));

    printf("\n%c",k);

}