#include <stdio.h>
#include <stdlib.h>

int main(){

    char option;
    do {
    printf("which loop do you want to use?\n");
    scanf("%c", &option);
    } while (!(option == 'f' || option == 'w' || option == 'd'));

    if (option == 'f') {

        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                if (i == 0 || i == 3){
                    printf("*");
                } else {
                    if (j == 0 || j == 3){
                        printf("*");
                    } else {
                        printf(" ");
                    }
                }
            }
            printf("\n");
        }

    } else if (option == 'w'){
        int i = 0;
        while (i < 4){
            if (i == 0 || i == 3){
                printf("****\n");
            } else{
                printf("*  *\n");
            }
            i++;
        }
    } else {
        int i = 0;
        do {
            if (i == 0 || i == 3){
                printf("****\n");
            } else{
                printf("*  *\n");
            }
            i++;
        } while (i < 4);
    }
}

int flag () {
    //create a simple program to print shapes with *
    int rows, i, j;

    // Get the number of rows from the user
    printf("Enter the number of rows: ");
    scanf("%d", &rows);

    // Print a right-angled triangle
    printf("Right-angled Triangle:\n");
    for (i = 1; i <= rows; i++) {
        for (j = 1; j <= i; j++) {
            printf("*");
        }
        printf("\n");
    }

    // Print an inverted right-angled triangle
    printf("\nInverted Right-angled Triangle:\n");
    for (i = rows; i >= 1; i--) {
        for (j = 1; j <= i; j++) {
            printf("*");
        }
        printf("\n");
    }

    // Print a pyramid

    printf("\nPyramid:\n");
    for (i = 1; i <= rows; i++) {
        for (j = 1; j <= rows - i; j++) {
            printf(" ");
        }
        for (j = 1; j <= 2 * i - 1; j++) {
            printf("*");
        }
        printf("\n");
    }
     // Print a diamond
    printf("\nDiamond:\n");
    for (i = 1; i <= rows; i++) {
        for (j = 1; j <= rows - i; j++) {
            printf(" ");
        }
        for (j = 1; j <= 2 * i - 1; j++) {
            printf("*");
        }
        printf("\n");
    }
    for (i = rows - 1; i >= 1; i--) {
        for (j = 1; j <= rows - i; j++) {
            printf(" ");
        }
        for (j = 1; j <= 2 * i - 1; j++) {
            printf
("*");
        }
        printf("\n");
    }


    return 0;
}
