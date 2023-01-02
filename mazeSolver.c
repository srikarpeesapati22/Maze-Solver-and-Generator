#include <stdio.h>
#include "graphics.h"
#include "player.h"
#include "stack.h"
#include "shapeGenerator.h"
#include "coordinateFunctions.h"
#include "instructionGenerator.h"
#include "debuggingFunctions.h"
#include "mazeGenerator.h"
#include "positionFunctions.h"

void allPossibleBlocks(char* mazeArray[], int mazeSize, int allAvailableBlocks[][2], int* noOfAvailableBlocks) {
   for (int row = 0; row < mazeSize; row++) {
      for (int column = 0; column < mazeSize; column++) {
         if (mazeArray[row][column] != '1') {
            allAvailableBlocks[*noOfAvailableBlocks][0] = row;
            allAvailableBlocks[*noOfAvailableBlocks][1] = column;
            *noOfAvailableBlocks += 1;
         }
      }
   }
}

int indexOfAdjBlock(int* position, int allAvailableBlocks[][2], int noOfAvailableBlocks) {
   for (int i = 0; i < noOfAvailableBlocks; i++) {
      if (position[0] == allAvailableBlocks[i][0] && position[1] == allAvailableBlocks[i][1]) {
         return i;
      }
   }
}

void validAdjacentBlocks(int* position, int* temp, int adjPosition[][2], char* mazeArray[], int mazeSize) {
   if (position[0] - 1 != 0 && (mazeArray[position[0] - 1][position[1]] != '1')) { // up
      temp[0] = 1;
      adjPosition[0][0] = position[0] - 1;
      adjPosition[0][1] = position[1];
   }
   if (position[0] + 1 != mazeSize - 1 && (mazeArray[position[0] + 1][position[1]] != '1')) { //down
      temp[1] = 1;
      adjPosition[1][0] = position[0] + 1;
      adjPosition[1][1] = position[1];
   }
   if (position[1] - 1 != 0 && (mazeArray[position[0]][position[1] - 1] != '1')) { // left
      temp[2] = 1;
      adjPosition[2][0] = position[0];
      adjPosition[2][1] = position[1] - 1;
   }
   if (position[1] + 1 != mazeSize - 1 && (mazeArray[position[0]][position[1] + 1] != '1')) { // right
      temp[3] = 1;
      adjPosition[3][0] = position[0];
      adjPosition[3][1] = position[1] + 1;
   }
}

int checkIfInVisited(int* position, int visited[][2], int visitedCount) {
   for (int i = 0; i < visitedCount; i++) {
      if (visited[i][0] == position[0] && visited[i][1] == position[1]) {
         return 1;
      }
   }
   return 0;
}

int resetPath(int* path, int start, int count) {
   for (int i = start; i < count; i++) {
      path[i] = -1;
   }
}

int isAdjacentBlocks(int* currentPosition, int* nextPosition) {
   if (currentPosition[0] - 1 == nextPosition[0] && currentPosition[1] == nextPosition[1]) { //up
      return 1;
   }
   if (currentPosition[0] + 1 == nextPosition[0] && currentPosition[1] == nextPosition[1]) { //down
      return 1;
   }
   if (currentPosition[0] == nextPosition[0] && currentPosition[1] - 1 == nextPosition[1]) { //left
      return 1;
   }
   if (currentPosition[0] == nextPosition[0] && currentPosition[1] + 1 == nextPosition[1]) { //right
      return 1;
   }
   return 0;

}

void simplifyVisited(int* path, int visited[][2], int count) {
   int marker = 0;
   int visitCounter = 0;
   int pathCounter = 0;
   path[0] = visitCounter;
   int currentPosition[2], nextPosition[2];
   while (marker != 1) {
      currentPosition[0] = visited[path[pathCounter]][0];
      currentPosition[1] = visited[path[pathCounter]][1];
      nextPosition[0] = visited[visitCounter + 1][0];
      nextPosition[1] = visited[visitCounter + 1][1];
      if (isAdjacentBlocks(currentPosition, nextPosition) == 1) {
         pathCounter++;
         visitCounter++;
         path[pathCounter] = visitCounter;
      } else {
         int previousPosition[] = {-1, -1};
         while (isAdjacentBlocks(previousPosition, nextPosition) != 1) {
            pathCounter--;
            previousPosition[0] = visited[path[pathCounter]][0];
            previousPosition[1] = visited[path[pathCounter]][1];
         }
         pathCounter++;
         visitCounter++;
         path[pathCounter] = visitCounter;
         resetPath(path, pathCounter + 1, count);
      }
      if (visitCounter == count - 1) {
         marker = 1;
      }
   }
}

void mazeSolve(char* mazeArray[], int* angle, int mazeSize) {
   int stack[mazeSize * mazeSize];
   initializeStack(stack);
   int allAvailableBlocks[mazeSize * mazeSize][2];
   int noOfAvailableBlocks = 0;
   int visited[mazeSize * mazeSize][2];
   int visitedCount = 0;
   allPossibleBlocks(mazeArray, mazeSize, allAvailableBlocks, &noOfAvailableBlocks);
   int positionStart[] = {0, 0};
   getStartPosition(&positionStart[0], &positionStart[1], mazeArray, mazeSize);
   int positionEnd[] = {0, 0};
   getEndPosition(positionEnd, mazeArray, mazeSize);
   int checkEnd[] = {positionEnd[0] - 1,  positionEnd[1]};
   visited[0][0] = positionStart[0];visited[0][1] = positionStart[1];
   int pushIndex = -1;
   int popStore = -1;
   int dfsRecursive() {
      int temp[] = {0, 0, 0, 0};
      int adjPosition[][2] = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};
      validAdjacentBlocks(visited[visitedCount], temp, adjPosition, mazeArray, mazeSize);
      if (checkIfInAdjBlocks(checkEnd, temp, adjPosition) == 1) {
         visitedCount++;
         visited[visitedCount][0] = checkEnd[0];
         visited[visitedCount][1] = checkEnd[1];
         visitedCount++;
         visited[visitedCount][0] = positionEnd[0];
         visited[visitedCount][1] = positionEnd[1];
         return 1;
      } else {
         if (isEmpty(stack) == 1) {
            for (int i = 0; i < 4; i++) {
               if (temp[i] == 1 && checkIfInVisited(adjPosition[i], visited, visitedCount) == 0) {
                  pushIndex = indexOfAdjBlock(adjPosition[i], allAvailableBlocks, noOfAvailableBlocks);
                  push(pushIndex, stack);
               }
            }
            dfsRecursive();
         } else {
            popStore = pop(stack);
            if (checkIfInVisited(allAvailableBlocks[popStore], visited, visitedCount) == 0) {
               visitedCount++;
               visited[visitedCount][0] = allAvailableBlocks[popStore][0];
               visited[visitedCount][1] = allAvailableBlocks[popStore][1];
            }
            validAdjacentBlocks(visited[visitedCount], temp, adjPosition, mazeArray, mazeSize);
            for (int i = 0; i < 4; i++) {
               if (temp[i] == 1 && checkIfInVisited(adjPosition[i], visited, visitedCount) == 0) {
                  pushIndex = indexOfAdjBlock(adjPosition[i], allAvailableBlocks, noOfAvailableBlocks);
                  push(pushIndex, stack);
               }
            }
            dfsRecursive();
         }
      }
   }
   dfsRecursive();
   int path[visitedCount];
   resetPath(path, 0, visitedCount);
   simplifyVisited(path, visited, visitedCount);
   int simpleVisited[visitedCount][2];
   int simpleCount = 0;
   for (int i = 0; i < visitedCount; i++) {
      if (path[i] != -1) {
         simpleVisited[i][0] = visited[path[i]][0];
         simpleVisited[i][1] = visited[path[i]][1];
         simpleCount++;
      }
   }
   simpleVisited[simpleCount][0] = positionEnd[0];
   simpleVisited[simpleCount][1] = positionEnd[1];
   makeAndRunInstructions(simpleVisited, mazeArray, simpleCount, angle);
}
