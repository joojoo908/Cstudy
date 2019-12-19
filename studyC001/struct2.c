#include <stdio.h>
#include <string.h>

struct person{
    char name[20];
    char phonenum[20];
    int age;
};

int main(){
    struct person man1,man2;
    strcpy(man1.name,"jhon");
    strcpy(man1.phonenum,"010-1111-2222");
    man1.age=23;
    printf("name:");
    scanf("%s",man2.name);
    printf("phonenum:");
    scanf("%s",man2.phonenum);
    printf("age:");
    scanf("%d",&(man2.age));

    printf("name: %s \n",man1.name);
    printf("phonenum: %s \n",man1.phonenum);
    printf("age: %d \n",man1.age);

    printf("name: %s \n",man2.name);
    printf("phonenum: %s \n",man2.phonenum);
    printf("age: %d \n",man2.age);

    return 0;



}