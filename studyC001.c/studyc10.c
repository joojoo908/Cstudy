#include <stdio.h>

int gg(int *num){
    for(int i=0;i<10;i++)
        printf("%d ", num[i]);
    printf("\n");
}

int main(){
    int kk[10]={9,2,3,10,4,5,6,7,1,8};
    int a1,a2;
    for(int i=10;i>1;i--){
        for(int j=0;j<i;j++){
            if(kk[j]>=kk[j+1]){
                a1=kk[j];
                kk[j]=kk[j+1];
                kk[j+1]=a1;
            }
            gg(kk);
        }
        printf("\n");
    }
}