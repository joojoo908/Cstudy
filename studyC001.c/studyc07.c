#include<stdio.h>
void k1(int *n1,int *n2,int *n3){
    int k1;
    k1=*n1;
    *n1=*n2;
    *n2=*n3;
    *n3=k1;
}
int main(){
    int num1=10,num2=20,num3=30;
    k1(&num1,&num2,&num3);
    printf("%d,%d,%d",num1,num2,num3);
}