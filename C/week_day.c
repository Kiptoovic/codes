#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    char letter[3];

    printf("Enter the first letter of day of the week:");
    scanf("%2s", &letter);

    char lower_letter[3];
    strcpy(lower_letter, letter);
    for(int i = 0; lower_letter[i]; i++){
        lower_letter[i] = tolower(lower_letter[i]);
    }


    if(strcmp(lower_letter, "m") == 0){
        printf("it's Monday");
    }

    else if(strcmp(lower_letter, "tu") == 0){
        printf("it's Tuesday\n");
    }


    else if(strcmp(lower_letter, "w") == 0){
        printf("it's Wednesday\n");
    }

    else if(strcmp(lower_letter, "th") == 0){
        printf("it's Thursday\n");
    }

    else if(strcmp(lower_letter, "f") == 0){
        printf("it's Friday\n");
    }

    else if(strcmp(lower_letter, "sa") == 0){
        printf("it's Saturday\n");
    }

    else if(strcmp(lower_letter, "su") == 0){
        printf("it's Sunday\n");
    }

    else{
        printf("No day of the week starts with that letter!!!\n");
    }

    return 0;
}