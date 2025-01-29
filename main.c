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

     for(int p = 0; p < 4; p++)
        if (parts[p].x < 0 || parts[p].x >= ROW || parts[p].y < 0 || parts[p].y >= COLUMN)
                return 1;
     for(int p = 0; p < 4; p++){
         for (int b = 0; b < NUM_BARRIERS; b++) {
             if (barriers[b].x == parts[p].x && barriers[b].y == parts[p].y) {
                 return 1; // Path is blocked by a barrier
             }
         }
    }
    return 0; // Path is not blocked
}

void move_car(my_car *car, barrier barriers[], moves target) {
    static int direction_tried[3];
    static int is_reversing;
    moves direction = {0,0};

    if (car->center_front.x == target.x && car->center_front.y == target.y){
        is_reversing = 0;
        for (int i=0;i<3;i++)
        direction_tried[i] = 0;
        return; // reached target
    }
    int original_direction_x = 0;
    int original_direction_y = 0;
    int collision_detected=0;
    

    // Randomly choose a direction towards the target
    int random_choice = rand() % 3; // 0, 1, or 2
    switch (random_choice) {
        case 0: // Move towards x-axis first
            if (car->center_front.x < target.x) {
                direction.x = 1;
            } else if (car->center_front.x > target.x) {
                direction.x = -1;
            }
            break;
        case 1: // Move towards y-axis first
            if (car->center_front.y < target.y) {
                direction.y = 1;
            } else if (car->center_front.y > target.y) {
                direction.y = -1;
            }
            break;
        case 2: // Move diagonally or stay on same axis
            if (car->center_front.x < target.x) {
                direction.x = 1;
            } else if (car->center_front.x > target.x) {
                direction.x = -1;
            }
              if (car->center_front.y < target.y) {
                direction.y = 1;
            } else if(car->center_front.y > target.y){
                direction.y = -1;
            }
            break;
    }

    original_direction_x = direction.x;
    original_direction_y = direction.y;

     collision_detected = is_car_touch_barrier(car, barriers);
     if(collision_detected){
        
        int choice = rand()%3;
        int count = 0;
        while(count <3){
             if(direction_tried[choice] == 0){
                direction_tried[choice] = 1;
                if(choice == 0){//left
                    direction.x = -original_direction_y;
                    direction.y = original_direction_x;
                }else if (choice ==1){ //right
                   direction.x = original_direction_y;
                    direction.y = -original_direction_x;
                }else{//reverse
                   direction.x = -original_direction_x;
                    direction.y = -original_direction_y;
                    is_reversing=1;
                }
                //collision again
                if(!is_car_touch_barrier(car, barriers))
                     break;
                
             }
             count++;
             choice = (choice+1)%3;
        }
        //if all choices have been tried reverse the direction
        if(count >=3){
            direction.x = -original_direction_x;
            direction.y = -original_direction_y;
            is_reversing=1;
             for (int i=0;i<3;i++)
                direction_tried[i] = 0;

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
        for (int i=0;i<3;i++)
             direction_tried[i] = 0;
        is_reversing = 0;
           return;
     }
         is_reversing = 0;
          for (int i=0;i<3;i++) direction_tried[i] = 0;
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
    for (int i = 0; i < 300; i++) {
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
    usleep(100000);
}
