#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
const int COLUMN = 30;
const int ROW = 10;
#define NUM_BARRIERS 15 

typedef struct {
    int x;
    int y;
    
} moves;

typedef struct {
    moves left_back;
    moves right_back;
    moves center_back;
    moves center_front;
} my_car;
typedef struct {
    int x;
    int y;
} barrier;
// Function declarations
void draw(my_car car, barrier barriers[], moves target);
void move_car(my_car *car, barrier barriers[], moves target);
void generate_barriers(barrier barriers[]);
int is_car_touch_barrier(my_car *car, barrier barriers[]);

void generate_barriers(barrier barriers[]) {
    srand(time(NULL)); // Seed the random number generator
    for (int i = 0; i < NUM_BARRIERS; i++) {
        barriers[i].x = rand() % ROW;       // Generate random x within the matrix size
        barriers[i].y = rand() % COLUMN;    // Generate random y within the matrix size
    }
}
int is_car_touch_barrier(my_car *car, barrier barriers[]) {
     moves parts[4] = {car->left_back, car->right_back, car->center_back, car->center_front};

     for(int p = 0; p < 4; p++){
         //Check bounday before checking barrier
         if (parts[p].x < 0 || parts[p].x >= ROW || parts[p].y < 0 || parts[p].y >= COLUMN) {
                continue; // Out of bounds, skip to next step
            }
         for (int b = 0; b < NUM_BARRIERS; b++) {
             if (barriers[b].x == parts[p].x && barriers[b].y == parts[p].y) {
                 return 1; // Path is blocked by a barrier
             }
         }
    }
    return 0; // Path is not blocked
}

void move_car(my_car *car, barrier barriers[], moves target) {
    moves direction;

   
    if (car->center_front.x == target.x && car->center_front.y == target.y)
        return; //reached target
    int original_direction_x;
    int original_direction_y;



        // Path is clear, try to move towards the bottom right corner
        if (car->center_front.x < target.x) {
            direction.x = 1;
        } else if (car->center_front.x > target.x){
            direction.x = -1;
        } else {
            direction.x = 0;
        }

        if (car->center_front.y < target.y) {
            direction.y = 1;
        } else if(car->center_front.y > target.y){
            direction.y = -1;
        }
        else{
            direction.y =0;
        }
        original_direction_x = direction.x;
        original_direction_y = direction.y;

    if (is_car_touch_barrier(car, barriers)) {
        //collision detected
        direction.x=0;
        direction.y= -1; //turn left
        if(is_car_touch_barrier(car, barriers)){
            direction.y = 1; //turn right
            if(is_car_touch_barrier(car,barriers)){
                //cornered reverse
                direction.x = -original_direction_x;
                direction.y = -original_direction_y;
            }
        }
    
    } else {
         if (car->center_front.x < target.x) {
            direction.x = 1;
        } else if (car->center_front.x > target.x){
            direction.x = -1;
        } else {
            direction.x = 0;
        }

        if (car->center_front.y < target.y) {
            direction.y = 1;
        } else if(car->center_front.y > target.y){
            direction.y = -1;
        }
        else{
            direction.y =0;
        }

    }
    // Calculate new positions based on direction
    moves new_left_back = {car->left_back.x + direction.x, car->left_back.y + direction.y};
    moves new_right_back = {car->right_back.x + direction.x, car->right_back.y + direction.y};
    moves new_center_back = {car->center_back.x + direction.x, car->center_back.y + direction.y};
    moves new_center_front = {car->center_front.x + direction.x, car->center_front.y + direction.y};

    // Check if any of the new positions are out of bounds
    if (new_left_back.x < 0 || new_left_back.x >= ROW || new_left_back.y < 0 || new_left_back.y >= COLUMN ||
        new_right_back.x < 0 || new_right_back.x >= ROW || new_right_back.y < 0 || new_right_back.y >= COLUMN ||
        new_center_back.x < 0 || new_center_back.x >= ROW || new_center_back.y < 0 || new_center_back.y >= COLUMN ||
        new_center_front.x < 0 || new_center_front.x >= ROW || new_center_front.y < 0 || new_center_front.y >= COLUMN) {
        // Do not update positions if any part is out of bounds
        draw(*car,barriers,(moves){ROW-1,COLUMN-1});
        return;
    }
        // Update positions only if all are within bounds
        car->left_back.x = new_left_back.x;
        car->left_back.y = new_left_back.y;
        car->right_back.x = new_right_back.x;
        car->right_back.y = new_right_back.y;
        car->center_back.x = new_center_back.x;
        car->center_back.y = new_center_back.y;
        car->center_front.x = new_center_front.x;
        car->center_front.y = new_center_front.y;
    draw(*car,barriers,(moves){ROW-1,COLUMN-1});
}

int main() {
    srand(time(NULL));
    my_car car = {
        .left_back = {0, 2},
        .center_back = {0, 1},
        .right_back = {0, 0},
        .center_front = {1, 1}};
    barrier barriers[NUM_BARRIERS];
    generate_barriers(barriers);
    draw(car,barriers,(moves){ROW-1,COLUMN-1});
    for (int i = 0; i < 100; i++) {
        move_car(&car, barriers,(moves){ROW-1,COLUMN-1}); 
    }
    return 0;
}

void draw(my_car car, barrier barriers[],moves target){
    system("clear");
    char current_display[ROW][COLUMN + 1];
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            if ((i == car.left_back.x && j == car.left_back.y) ||
                (i == car.center_back.x && j == car.center_back.y) ||
                (i == car.right_back.x && j == car.right_back.y) ||
                (i == car.center_front.x && j == car.center_front.y)) {
                current_display[i][j] = '*'; // Car
            } else {
                current_display[i][j] = '_';
            }
            
        }
        current_display[i][COLUMN] = '\0';
    }
    for (int i = 0; i < NUM_BARRIERS; i++) {
        current_display[barriers[i].x][barriers[i].y] = '@';
    }

    current_display[target.x][target.y] = 'T';
    
    for (int i = 0; i < ROW; i++) {
        printf("%s\n", current_display[i]);
    }
    printf("\n");
    fflush(stdout);
    sleep(1);
}
