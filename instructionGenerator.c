#include <stdio.h>
#include "player.h"

char directionOfNextBlock(int* currentPosition, int* nextPosition) {
   if (currentPosition[0] + 1 == nextPosition[0]) {
      return 'd';
   }
   if (currentPosition[0] - 1 == nextPosition[0]) {
      return 'u';
   }
   if (currentPosition[1] + 1 == nextPosition[1]) {
      return 'r';
   }
   if (currentPosition[1] - 1 == nextPosition[1]) {
      return 'l';
   }
}

int getNoOfTurns(int angle, char direction) {
   if (direction == 'd') {
      if (angle == 0) {return 2;}
      if (angle == 90) {return 1;}
      if (angle == 180) {return 0;}
      if (angle == 270) {return -1;}
   }
   if (direction == 'u') {
      if (angle == 0) {return 0;}
      if (angle == 90) {return -1;}
      if (angle == 180) {return 2;}
      if (angle == 270) {return 1;}
   }
   if (direction == 'r') {
      if (angle == 0) {return 1;}
      if (angle == 90) {return 0;}
      if (angle == 180) {return -1;}
      if (angle == 270) {return 2;}
   }
   if (direction == 'l') {
      if (angle == 0) {return -1;}
      if (angle == 90) {return 2;}
      if (angle == 180) {return 1;}
      if (angle == 270) {return 0;}
   }
}

void makeAndRunInstructions(int simpleVisited[][2], char* mazeArray[], int simpleCount, int* angle) {
   int position[] = {-1, -1};
   for (int i = 0; i < simpleCount; i++) { // REMOVED THE -1
      position[0] = simpleVisited[i][0];
      position[1] = simpleVisited[i][1];
      char direction = directionOfNextBlock(simpleVisited[i], simpleVisited[i + 1]);
      int turns = getNoOfTurns(*angle, direction);
      if (turns >= 0) {
         for (int j = 0; j < turns; j++) {
            right(position, angle);
         }
      } else {
         left(position, angle);
      }
      forward(position, mazeArray, *angle);

   }
}
