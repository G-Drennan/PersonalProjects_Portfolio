#include <stdio.h>
int main(){
    int x3=1, x2=1, x1=1;
    int num = (!x1|!x2|x3);
    //for(int n=0; n<6; n++){
        if((x3|!x2|!x1)){
            printf("%d %d %d", x3,x2,x1);
        } 
    //}
    printf("\n%d\n", num);

}