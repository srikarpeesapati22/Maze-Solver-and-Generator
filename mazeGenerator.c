#include "graphics.h"
#include "shapeGenerator.h"
#include "coordinateFunctions.h"
#include "player.h"
#include "mazeSolver.h"
#include "positionFunctions.h"
#include "debuggingFunctions.h"
#include "instructionGenerator.h"
#include "stack.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MIN_SIZE 50
#define MAX_SIZE 150

int randCount = 0;

void sleep_function() {
   time_t t1 = time(&t1) + 1;
   time_t t;
   while (time(&t) != t1 + 1) {
      t = time(&t);
   }
}

int getRandomNumber(int start, int end) {
   time_t t = time(&t);
   int marker = 0;
   int num = 0;
   srand(t + randCount);
   while (marker != 1) {
      num = rand() % end;
      if (num >= start) {
         return num;
      }
   }
   randCount++;
}

void drawMaze(char* mazeArray[], int sizeOfMaze) {
   setWindowSize(1500, 1500);
   int coordinateArr[] = {0, 0};
   for (int row = 0; row < sizeOfMaze; row++) {
      for (int column = 0; column < sizeOfMaze; column++) {
         getCoordinates(row, column, coordinateArr);
         drawSquare(coordinateArr[0], coordinateArr[1], getBlockColour(mazeArray[row][column]));
         }
      }
}

void resetTemp(char* tempRow, int mazeSize) {
   for (int i = 0; i < mazeSize; i++) {
      tempRow[i] = 'c';
   }
   tempRow[mazeSize + 1] = '\0';
}

void initializeMazeArray(char* mazeArray[], int mazeSize, char individualMazeArray[][mazeSize]) {
   int start = getRandomNumber(1, mazeSize - 1);
   int end = getRandomNumber(1, mazeSize - 1);
   char tempRow[mazeSize];
   resetTemp(tempRow, mazeSize);
   for (int row = 0; row < mazeSize; row++) {
      for (int column = 0; column < mazeSize; column++) {
         if (row == 0 || column == mazeSize - 1) {
            tempRow[column] = '1';
         } else if (column == 0) {
            if (row == start) {
               tempRow[column] = '2';
            } else {
               tempRow[column] = '1';
            }
         } else if (row == mazeSize - 1) {
            if (column == end) {
               tempRow[column] = '3';
            } else {
               tempRow[column] = '1';
            }
         } else {
            int randNum = getRandomNumber(0, 2);
            randCount++;
            if (randNum == 0) {
               tempRow[column] = '0';
            } else{
               tempRow[column] = '1';
            }
         }
      }
      for (int j = 0; j < mazeSize; j++) {
         individualMazeArray[row][j] = tempRow[j];
      }
   }
}

void getAdjacentBlocks(int path[][2], int pathCount, int* temp, int adjPosition[][2], int mazeSize) {
   if (path[pathCount][0] - 1 != 0) { // up
      temp[0] = 1;
      adjPosition[0][0] = path[pathCount][0] - 1;
      adjPosition[0][1] = path[pathCount][1];
   }
   if (path[pathCount][0] + 1 != mazeSize - 1) { //down
      temp[1] = 1;
      adjPosition[1][0] = path[pathCount][0] + 1;
      adjPosition[1][1] = path[pathCount][1];
   }
   if (path[pathCount][1] - 1 != 0) { // left
      temp[2] = 1;
      adjPosition[2][0] = path[pathCount][0];
      adjPosition[2][1] = path[pathCount][1] - 1;
   }
   if (path[pathCount][1] + 1 != mazeSize - 1) { // right
      temp[3] = 1;
      adjPosition[3][0] = path[pathCount][0];
      adjPosition[3][1] = path[pathCount][1] + 1;
   }
}

int checkIfInPath(int* position, int path[][2], int pathCount) {
   for (int i = 0; i < pathCount; i++) {
      if (path[i][0] == position[0] && path[i][1] == position[1]) {return 1;}
   }
   return 0;
}

int checkIfInAdjBlocks(int* end, int* temp, int adjPosition[][2]) {
   for (int i = 0; i < 4; i++) {
      if (temp[i] == 1) {
         if (adjPosition[i][0] == end[0] && adjPosition[i][1] == end[1]) {return 1;}
      }
   }
   return 0;
}

void clearPath(char* mazeArray[], int path[][2], int pathCount) {
   for (int i = 0; i < pathCount; i++) {
      mazeArray[path[i][0]][path[i][1]] = '0';
   }
}

int allAdjInPath(int path[][2], int pathCount, int* temp, int adjPosition[][2]) {
   int count = 0;
   int compCount = 0;
   for (int i = 0; i < 4; i++) {
      if (temp[i] == 1) {
         int value = checkIfInPath(adjPosition[i], path, pathCount);
         if (value == 1) {
            count++;
         }
         compCount++;
      }
   }
   if (count == compCount) {
      return 1;
   }
   return 0;
}

void makePath(char* mazeArray[], int mazeSize) {
   int blacklist[mazeSize * mazeSize][2];
   int blacklistCount = 0;
   int positionStart[] = {0, 0};
   getStartPosition(&positionStart[0], &positionStart[1], mazeArray, mazeSize);
   int positionEnd[] = {0, 0};
   getEndPosition(positionEnd, mazeArray, mazeSize);
   int checkEnd[] = {positionEnd[0] - 1,  positionEnd[1]};
   int path[(mazeSize - 2) * (mazeSize - 2) + 1][2];
   path[0][0] = positionStart[0];
   path[0][1] = positionStart[1] + 1;
   int pathCount = 0;
   checkIfInPath(path[0], path, pathCount);
   int makePathRecursive(int path[][2]) {
      int temp[] = {0, 0, 0, 0};
      int adjPosition[][2] = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};
      getAdjacentBlocks(path, pathCount, temp, adjPosition, mazeSize);
      for (int i = 0; i < 4; i++) {
         if (temp[i] == 1) {
            if (checkIfInPath(adjPosition[i], path, pathCount) == 1 || checkIfInPath(adjPosition[i], blacklist, blacklistCount)) {
               temp[i] = 0;
            }
         }
      }
      if (checkIfInAdjBlocks(checkEnd, temp, adjPosition) == 1) {
         path[pathCount + 1][0] = checkEnd[0];
         path[pathCount + 1][1] = checkEnd[1];
         pathCount++;
         return 1;
      } else {
         int marker = 0;
         int randomIndex = -1;
         while (marker == 0) {
            randomIndex = getRandomNumber(0, 4);
            randCount++;
            if (temp[0] == 0 && temp[1] == 0 && temp[2] == 0 && temp[3] == 0) {
               pathCount--;
               blacklist[blacklistCount][0] = path[pathCount + 1][0];
               blacklist[blacklistCount][1] = path[pathCount + 1][1];
               blacklistCount++;
               marker = 1;
            }
            if (temp[randomIndex] == 1) {
               pathCount++;
               path[pathCount][1] = adjPosition[randomIndex][1];
               path[pathCount][0] = adjPosition[randomIndex][0];
               marker = 1;
            }

         }
      }
      makePathRecursive(path);
      }
      makePathRecursive(path);
      path[pathCount + 1][0] = positionEnd[0];
      path[pathCount + 1][1] = positionEnd[1];
      pathCount++;
      int angle = 90;
      clearPath(mazeArray, path, pathCount);
      drawMaze(mazeArray, mazeSize);
      mazeSolve(mazeArray, &angle, mazeSize);
}

void mazeGenerator() {

   int start = MIN_SIZE;
   int end = MAX_SIZE;
   int mazeSize = getRandomNumber(start, end);
   char* mazeArray[mazeSize];
   int angle = 90;
   char individualMazeArray[mazeSize][mazeSize];
   initializeMazeArray(mazeArray, mazeSize, individualMazeArray);
   for (int row = 0; row < mazeSize; row++) {mazeArray[row] = individualMazeArray[row];}
   makePath(mazeArray, mazeSize);
}
