#include<stdio.h>
#include<string.h>

int main(){

    char pass[12] = "aabcddefgghi"; //trzy takie same liczby
    int sameLetters = 0;
    /*
    for(int i =0; i < strlen(pass); i++){
        for(int j=0; j < strlen(pass); j++){
            if(!strcmp(pass[i], pass[j])){
                sameLetters++;
            }
        }
    }
    */
   strcmp(pass[0], pass[1]);

    printf("The same letters: %d", sameLetters);
    return 0;
}