#include <stdio.h>
#include <stdlib.h>

//prototype
void countLetter(int count, char lower, char upper);

struct file_info {
    int count;
    char lower;
    char upper;
    int myCounts[26];
};

int main(void) {
    
    //Intialize i counter for loop
    int i;

    //initalize struct info
    struct file_info char_info = {0, 97, 65};


    //iterate through each letter    
    for (i = 0; i < 26; i++){
        countLetter(char_info.count, char_info.lower, char_info.upper);
        // reset counter and move to next letter
        char_info.count = 0;
        char_info.lower++;
        char_info.upper++;

    }
    return 0;
}
void countLetter(int count, char lower, char upper){
    char ch;

    // Open File with pointer fp
    FILE *fp;
    fp = fopen("alice.txt", "r");

    //chech if file is not NULL
    if (fp != NULL){

    //iterate through file until end
    while ((ch = fgetc(fp)) != EOF) {   
        
        if (ch == lower || ch == upper){
            count++;
        }
        }

    // print statements
    printf("Letter %c:", lower);          
    printf("%d\n", count);  
    } 

    //error message for file
    else printf("Open File Error");    

    //close file
    fclose(fp);
}  
   