#include <stdio.h>


int main(){
    int input;
    int n1=0,n2=0;
    int kk[10];
    for(int i=0;i<10;i++){ 
        scanf("%d", & input);
        if(input%2==0){
            kk[9-n1]=input;
            n1=n1+1;
        }
        else{
            kk[n2]=input;
            n2=n2+1;
        }      
    }
    for(int i=0;i<10;i++){
        printf("%d,",kk[i]);
    }

}