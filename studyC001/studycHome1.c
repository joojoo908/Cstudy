#include <stdio.h>

void kk(char a){
    printf("kkvalue a=%c \n",a);
    a='t';
    printf("kkvalue a=%c \n",a);
    
}

void pkk(char *a){
    printf("pkkvalue *a=%c \n", *a);
    * a='t';
    printf("pkkvalue *a=%c \n", *a);
    
}

int main(){
    char c1='c';
    char * c2=&c1;
    char b1='b';

    // printf("1.c1=%c \n",c1);
    // c1='d';
    // printf("2.c1=%c \n",c1);
    // printf("3.c2=%c \n", * c2);
    // printf("4.c2=%d \n", c2);
    // printf("5.b1=%c \n",b1);
    // c2=&b1;
    // printf("6.c2=%c \n",* c2);
    // printf("7.c2=%d \n", c2);
    printf("c1=%c\n",c1);
    kk(c1);
    pkk(&c1);

    c1='A';

    kk(c1);
    printf("c1=%c\n",c1);
    pkk(&c1);
    printf("c1=%c\n",c1);


}