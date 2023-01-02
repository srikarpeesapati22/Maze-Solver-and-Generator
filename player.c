#include "graphics.h"
#include "shapeGenerator.h"
#include "mazeGenerator.h"
#include "mazeSolver.h"
#include "coordinateFunctions.h"
#include "positionFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIDE_LENGTH 5
#define MAZE_START_X 50
#define MAZE_START_Y 50

void getNewAngle(int* angle, char direction) {
   if (direction == 'r') {
      *angle += 90;
   }
   if (direction == 'l') {
      if (*angle - 90 < 0) {
         *angle = 270;
         return;
      }
      *angle -= 90;
   }
   if (*angle == 360) {*angle = 0;}
}

int canMoveForward(int* position, char* mazeArray[], int angle) {
   if (angle == 0) {
      if (mazeArray[*(position) - 1][*(position + 1)] == '1') { // Checks if black block is present above
         return 0;
      }
   } else if (angle == 90) {
      if (mazeArray[*(position)][*(position + 1) + 1] == '1') { // Checks if black block is present to the right
         return 0;
      }
   } else if (angle == 180) {
      if (mazeArray[*(position) + 1][*(position + 1)] == '1') { // Checks if black block is present below
         return 0;
      }
   } else if (angle == 270) {
      if (mazeArray[*(position)][*(position + 1) - 1] == '1') { // Checks if black block is present to the left
         return 0;
      }
   } else {
      return 1;
   }
}

int atMarker(int* position, char* mazeArray[]) {
   if (mazeArray[*(position)][*(position + 1)] == '3') {
      return 1;
   }
   return 0;
}

int checks(int* position, char* mazeArray[], int angle) {
   if (atMarker(position, mazeArray) == 1) {
      setColour(blue);
      drawString("DONE", 1400, 100);
      return 0;
   }
   if (canMoveForward(position, mazeArray, angle) == 0) {
      return 0;
   }
}

void forward(int* position, char* mazeArray[], int angle) {
   int checkvalue = checks(position, mazeArray, angle);
   if (checkvalue == 0) {
      return;
   } else {
      int oldPoints[6];
      getTriangleCoordinates(position, angle, oldPoints);
      drawSpecificTriangle(oldPoints, 'w');
      int newPoints[6];
      getForwardTriangleCoordinates(angle, oldPoints, newPoints);
      updatePosition(position, angle);
      drawSpecificTriangle(newPoints, 'd');
   }
   checks(position, mazeArray, angle);

}

void left(int* position, int* angle) {
   int oldPoints[6];
   getTriangleCoordinates(position, *angle, oldPoints);
   drawSpecificTriangle(oldPoints, 'w');
   getNewAngle(angle, 'l');
   int newPoints[6];
   getTriangleCoordinates(position, *angle, newPoints);
   drawSpecificTriangle(newPoints, 'd');
}

void right(int* position, int* angle) {
   int oldPoints[6];
   getTriangleCoordinates(position, *angle, oldPoints);
   drawSpecificTriangle(oldPoints, 'w');
   getNewAngle(angle, 'r');
   int newPoints[6];
   getTriangleCoordinates(position, *angle, newPoints);
   drawSpecificTriangle(newPoints, 'd');
}

void backward(int* position, char* mazeArray[], int* angle) {
   right(position, angle);
   right(position, angle);
   forward(position, mazeArray, *angle);
}

void instructionsStage1(int* position, char* mazeArray[], int* angle) {
   right(position, angle);
   for (int i = 0; i < 2; i++) {forward(position, mazeArray, *angle);}
   left(position, angle);
   for (int i = 0; i < 4; i++) {forward(position, mazeArray, *angle);}
   right(position, angle);
   for (int i = 0; i < 2; i++) {forward(position, mazeArray, *angle);}
   left(position, angle);
   for (int i = 0; i < 2; i++) {forward(position, mazeArray, *angle);}
   left(position, angle);
   for (int i = 0; i < 4; i++) {forward(position, mazeArray, *angle);}
   right(position, angle);
   for (int i = 0; i < 2; i++) {forward(position, mazeArray, *angle);}
   right(position, angle);
   for (int i = 0; i < 8; i++) {forward(position, mazeArray, *angle);}
   left(position, angle);
   forward(position, mazeArray, *angle);
}

void start() { // For stages 4 and 5
   mazeGenerator();
}

void startStage1_2(char* mazeArray[]) {
   int sizeOfMaze = strlen(mazeArray[0]);
   drawMaze(mazeArray, sizeOfMaze);
   foreground();
   int position[] = {0, 0};
   int coordinate[] = {0, 0};
   getStartPosition(&position[0], &position[1], mazeArray, sizeOfMaze);
   getCoordinates(position[0], position[1], coordinate);
   drawTriangle(coordinate[0], coordinate[1]);
   int angle = 90;
   instructionsStage1(position, mazeArray, &angle);
}

void startStage3(char* mazeArray[]) {
   int sizeOfMaze = strlen(mazeArray[0]);
   drawMaze(mazeArray, sizeOfMaze);
   foreground();
   int position[] = {0, 0};
   int coordinate[] = {0, 0};
   getStartPosition(&position[0], &position[1], mazeArray, sizeOfMaze);
   getCoordinates(position[0], position[1], coordinate);
   drawTriangle(coordinate[0], coordinate[1]);
   int angle = 90;
   mazeSolve(mazeArray, &angle, sizeOfMaze);
}
