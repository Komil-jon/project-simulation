#include <stdio.h>

float calculateArea(float legth, float width){
    return legth * width;
}

float calculatePerimeter(float legth, float width){
    return 2 * (legth + width);
}

int main(){
    float legth1, width1, legth2, width2;

    printf("enter the first rectangle's legth and width: ");
    scanf("%f %f", &legth1, &width1);

    printf("enter the second rectangle's legth and width: ");
    scanf("%f %f", &legth2, &width2);

    printf("area of 1-rectngle: %f\n", calculateArea(legth1, width1));
    printf("perimeter of 2-rectngle: %f\n", calculatePerimeter(legth2, width2));

    return 0;
}