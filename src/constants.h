#ifndef CONSTANTS_H
#define CONSTANTS_H

//boids sizes
#define BOIDS_RAD 10
#define OBST_SMALL_RAD 12.5
#define OBST_BIG_RAD 40
#define OBST_DIST 45
#define HIT_DISTANCE 25

//Obstacle size keywords
#define BIG 1
#define SMALL 2

//relative scaling coefficients
#define ALIGNMENT_FORCE 10
#define SEPARATION_FORCE 300
#define COHESION_FORCE 1
#define ESCAPE_FORCE 1
#define OBSTACLE_FORCE 100000



//Boids speed
#define MAX_PREDATOR_SPEED 7
#define MAX_FLOCK_SPEED 5


//Graphics
#define W_S 1400
#define H_S 1000
#define DIRECTION_ARROW_LENGTH 20

//Initial conditions
#define INITIAL_NUMBER_OF_FLOCK 100
#define INITIAL_NUMBER_OF_PREDATOR 0
#define INITIAL_SPEED 20
#define INITIAL_RADIUS 80
#define INITIAL_GLOBAL_SPEED 1

#define ADD_FLOCK_BUTTON 20

#endif // CONSTANTS_H

