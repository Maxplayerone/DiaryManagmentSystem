#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<stdbool.h>

int MainMenu();
void WriteMessage(char[]);
void ReadMessage();
void GetPassword();
bool CheckPassword();
void ArchiveMessages(char[]);
void ChangePassword();
int CalculatePasswordStrength();

static int diaryFilesCount = -1; //the counting starts at 2 
DIR *dir; 
struct dirent *ent;

char password[50];
char name[12];

int main(){
    printf("What your name? \n");
    scanf("%s", &name);

    printf("\n!---Remeber to change the password---!\n");
    GetPassword();
    MainMenu();

    printf("\nGoodbye!\n");
    return 0;
}

int MainMenu(){
    //setting the menu
    int response;
    printf("\n\nWelcome to %s's diary!\n", name);
    printf("Select your path\n");
    printf("--------------------------------");
    printf("\n-Write new message (0)");
    printf("\n-Select a path (1)");
    printf("\n-Change password (2)\n");
    printf("leave (3)\n");
    scanf("%d", &response);

    switch(response){
        case 0:
            WriteMessage(name);
            break;
        case 1:
            ReadMessage();
            break;
        case 2:
            ChangePassword();
            break;
        case 3:
            return 0;
            break;
        default:
            printf("You typed the code wrong!");
            break;
    }
}

void WriteMessage(char name[]){
    bool isWriting = true;
    do{
    //creating the message
    char message[199];
    printf("\n-------------------\n");
    printf("What's your today's message (max 200 letters)? \n");
    fgets(message, sizeof message, stdin);

    char c[200];
    scanf("%c", &c);

    fgets(message, 200, stdin);
    strncat(c, message, sizeof message);
    //getting the files count
    char dirName[] = "DiaryTexts";

    if(dir = opendir(dirName)){
        while(ent = readdir(dir)){
            //printf("\n%s", ent->d_name);
            diaryFilesCount++;
        }
        closedir(dir);
    }else{
        printf("\nThe dir %s does not exist\n", dirName);
    }
    
    //creating the file
    char filename[15];
    sprintf(filename, "DiaryTexts/Diary%d.txt", diaryFilesCount);

    FILE *pDiary = fopen(filename, "w");
    fprintf(pDiary, "\"%s\" -%s", c, name);
    fclose(pDiary);

    //asking the user to write again
    char answer[3];
    printf("\nDo you want to write another message? (yes/no) ");
    scanf("%s", answer);
    strlwr(answer);
    //O CO TU CHODZI??? CZEMU TO JEST DOBRZE???
    if(!strcmp(answer, "yes")){
        isWriting = true;
    } 
    else if(!strcmp(answer, "no")){
        MainMenu();
        isWriting = false;  
    } 
    else{
        printf("\nYou didn't write it correctly!");
        isWriting = false;
    } 
    }
    while(isWriting == true);
}

void ReadMessage(){
    if(!CheckPassword()) return;
    bool isReading = true;
    do{
    //getting the user file
    int userAnswer;
    char userSearchingFile[20];
    printf("\n-------------\n");
    printf("What message do you want to read (the diary count - 2) ");
    scanf("%d", &userAnswer);   

    //opening the file
    char dirName[] = "DiaryTexts";
    char *files[100];
    int i = 0;

    if(dir = opendir(dirName)){
        while(ent = readdir(dir)){    
            i++;   
            if(i == userAnswer){     
            strcpy(userSearchingFile, ent->d_name);
            }
        }
        closedir(dir);
    }else{
        printf("\nThe dir %s does not exist\n", dirName);
    }

    //reading from the file
    char message[255];
    char buffer[255];
    char path[30];
    sprintf(path, "DiaryTexts/%s", userSearchingFile);
    FILE *file = fopen(path, "r");
    if(fopen(path, "r")){
    
        while(fgets(buffer, 100, file)){
            //printf("\n%s\n", buffer);
            char temp[30];
            sprintf(temp, "\n %s \n", buffer);
            strcat(message, temp);
        }
    }else{
        printf("\nThe file %s didn't open properly\n", path);
    }
    fclose(file);

    //archiving
    char temp[3]; 
    printf("\nDo you want to archive the message? (yes, no) ");
    scanf("%s", temp);
    if(!strcmp(temp, "yes")){
        ArchiveMessages(message);
    }

    //asking to open another message
    
    printf("Do you want to read another message? (yes, no) ");
    scanf("%s", temp);

    if(!strcmp(temp, "yes")){
        isReading = true;
    }else{
        isReading = false;
        MainMenu();
    }
    }while(isReading);
    
}

bool CheckPassword(){
    //asking for the password
    char userResponse[sizeof(password)];
    printf("\n-----------------\nWhat's the password? \n");
    scanf("%s", &userResponse);

    if(!strcmp(password, userResponse)){
        printf("\nThe password was correct!\n");
        return true;
    }else{
        printf("The password wasn't correct :(\n");
        return false;
    }
}

void ArchiveMessages(char message[]){
    FILE *archive = fopen("other/archive.txt", "a");
    if(!fopen("other/archive.txt", "a")) printf("The archive didn't open");
    fprintf(archive, "\n%s\n", message);
    fclose(archive);
}

void GetPassword(){
    FILE *file = fopen("other/password.txt", "r");
    if(fopen("other/password.txt", "r")) printf("");
    else printf("\nThe file %s didn't open properly\n", file);
    fgets(password, sizeof(password), file);
}

void ChangePassword(){
    char userResponse[sizeof(password)];
    printf("\nWhat's the current password? \n");
    scanf("%s", userResponse);
    if(strcmp(password, userResponse)){
        printf("\nThe password wasn't correct!\n");
        return;
    }
    char newUserPassword[20];
    char newUserPasswordCopy[sizeof(newUserPassword)];
    printf("\n Select your new password (max 20 characters): \n");
    scanf("%s", &newUserPassword);
    printf("\nConfirm the new password\n");
    scanf("%s", &newUserPasswordCopy);

    if(!strcmp(newUserPassword, newUserPasswordCopy)){
        printf("The password has been changed!");
        strcpy(password, newUserPassword);
        MainMenu();

    }else{
        printf("The passwords aren't the same!");
    }
    
}

int CalculatePasswordStrength(){
    int passwordLength = strlen(password);
    int sameLetters = 0;
    for(int i =0; i < passwordLength; i++){
        for(int j=0; j < passwordLength; j++){
            if(!strcmp(password[i], password[j])){
                sameLetters++;
            }
        }
    }
    
    int numbers;
    int finalPasswordStrength = passwordLength + sameLetters + numbers;
}