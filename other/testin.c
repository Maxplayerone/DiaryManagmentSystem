#include<stdio.h>
#include<string.h>

void Slice(char[], int);
int main(){

  char text[] = "Hello. My name is Jamal. Every sixty seconds in Africa a minute passes. Together we can stop this! Head on to Jamal.com/giveMeMoneyFam and you'll be blessed with luck for 10 years";
  //printf("Size of the text: %d", sizeof(text));
  Slice(text, 30);

  
  char test[] = "This is a test";
  char testTwo[11];
  /*
  for(int i=0; i < sizeof(test); i++){
    testTwo[i] = test[i];
  }
  printf("\n%s\n", testTwo);
  */
  

  return 0;
}


void Slice(char text[], int space){
  char slicedText[180];

  for(int i= 1; i < 3; i++){
    for(int j=0; j < space; j++){
      slicedText[j * i] = text[j * i];
      //printf("\nJ count: %d\n", j * i);
      printf("\n %s \n", slicedText);
    }

    slicedText[space * i + 1] = '\n';
  }
  printf("\n%s\n", slicedText);
}



