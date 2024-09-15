#include <stdio.h>
#include <stdlib.h>

//prototype
int countLetter(int count, char lower, char upper);
void letterPrint(int letterArray[2][26]);

struct file_info {
    int count;
    char lower;
    char upper;
    int letterCounts[2][26];
};

int main(void) {
    
    //Intialize i counter for loop
    int i;

    //initalize struct info
    struct file_info char_info = {0, 97, 65};


    //iterate through each letter    
    for (i = 0; i < 26; i++){
        //store info into 2d array
        char_info.letterCounts[1][i] = countLetter(char_info.count, char_info.lower, char_info.upper);
        char_info.letterCounts[0][i] = char_info.upper;
        // reset counter and move to next letter
        char_info.count = 0;
        char_info.lower++;
        char_info.upper++;
        

    }
    //print function
    letterPrint(char_info.letterCounts);
    return 0;
}
int countLetter(int count, char lower, char upper){
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


    } 

    //error message for file
    else printf("Open File Error");    

    //close file
    fclose(fp);

    return count;
}  

void letterPrint(int letterArray[2][26]){
    int j;

    for (int j = 0; j < 26; j++) {
        printf("Letter %c:", letterArray[0][j]);   
        printf("%d\n", letterArray[1][j]);  
    }

}
   