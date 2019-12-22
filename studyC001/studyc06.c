#include<stdio.h>
int SquareByValue(int num){
    return num*num;
}
void SquareByReference(int * num){
    *num = *num * *num;
}
int main(){
    int num=5;
    char a='a';
    //char * b=a;
    printf("%c, %c",a);
    printf("%d",SquareByValue(num));
    SquareByReference(&num);
    printf("%d",num);
}