#include <stdio.h>
void pibo(int);
int main(){
    int k;
    printf("input?");
    scanf("%d",&k);
    pibo(k);
    return 0;
}

void pibo(int k){
    int p1=0,p2=1,pk;
    printf("%d ,",p1);
    printf("%d ,",p2);
    for(int i=2;i<k;i++){
        pk= p1+p2;
        printf("%d ,",pk);
        p1=p2;
        p2=pk;
    }
}