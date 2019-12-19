#include<stdio.h>

int aa(int *num){
    for(int i=0;i<10;i++){
        if(num[i]%2==0)
            printf("%d",num[i]);
    }
    return 0;
}
int bb(int *num){
    for(int i=0;i<10;i++){
        if(num[i]%2!=0)
            printf("%d",num[i]);
    }
    return 0;    
}
int main(){
    int kk[10];
    for(int i=0;i<10;i++)
        scanf("%d", & kk[i]);
    aa(kk);
    printf("\n");
    bb(kk);
}