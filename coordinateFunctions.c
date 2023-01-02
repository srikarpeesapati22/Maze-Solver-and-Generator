#include <string.h>
#include <stdio.h>
#include "graphics.h"
#include "shapeGenerator.h"

#define SIDE_LENGTH 5
#define MAZE_START_X 50
#define MAZE_START_Y 50

void getCoordinates(int rowId, int columnId, int* coordinateArray) {
   coordinateArray[0] = SIDE_LENGTH * columnId + MAZE_START_X;
   coordinateArray[1] = SIDE_LENGTH * rowId + MAZE_START_Y;
}

void getTriangleCoordinates(int* position, int angle, int* points) {
   int topLeft[2] = {0, 0};
   getCoordinates(*(position), *(position + 1), topLeft);
   if (angle == 0) { // bottomLeft and bottomRight
      points[0] = topLeft[0];
      points[1] = topLeft[1] + SIDE_LENGTH;
      points[2] = topLeft[0] + SIDE_LENGTH;
      points[3] = topLeft[1] + SIDE_LENGTH;
      points[4] = topLeft[0] + SIDE_LENGTH / 2;
      points[5] = topLeft[1];
   } else if (angle == 90) { // topLeft and bottomLeft
      points[0] = topLeft[0];
      points[1] = topLeft[1];
      points[2] = topLeft[0];
      points[3] = topLeft[1] + SIDE_LENGTH;
      points[4] = topLeft[0] + SIDE_LENGTH;
      points[5] = topLeft[1] + SIDE_LENGTH / 2;
   } else if (angle == 180) { // topLeft and topRight
      points[0] = topLeft[0];
      points[1] = topLeft[1];
      points[2] = topLeft[0] + SIDE_LENGTH;
      points[3] = topLeft[1];
      points[4] = topLeft[0] + SIDE_LENGTH / 2;
      points[5] = topLeft[1] + SIDE_LENGTH;
   } else { // Angle 270 topRight and bottomRight
      points[0] = topLeft[0] + SIDE_LENGTH;
      points[1] = topLeft[1];
      points[2] = topLeft[0] + SIDE_LENGTH;
      points[3] = topLeft[1] + SIDE_LENGTH;
      points[4] = topLeft[0];
      points[5] = topLeft[1] + SIDE_LENGTH / 2;
   }
}

void getForwardTriangleCoordinates(int angle, int* oldPoints, int* newPoints) {
   if (angle == 0) { // Move Up One Square
      newPoints[0] = oldPoints[0];
      newPoints[1] = oldPoints[1] - SIDE_LENGTH;
      newPoints[2] = oldPoints[2];
      newPoints[3] = oldPoints[3] - SIDE_LENGTH;
      newPoints[4] = oldPoints[4];
      newPoints[5] = oldPoints[5] - SIDE_LENGTH;
   } else if (angle == 90) { // Move Right One Square
      newPoints[0] = oldPoints[0] + SIDE_LENGTH;
      newPoints[1] = oldPoints[1];
      newPoints[2] = oldPoints[2] + SIDE_LENGTH;
      newPoints[3] = oldPoints[3];
      newPoints[4] = oldPoints[4] + SIDE_LENGTH;
      newPoints[5] = oldPoints[5];
   } else if (angle == 180) { // Move Down One Square
      newPoints[0] = oldPoints[0];
      newPoints[1] = oldPoints[1] + SIDE_LENGTH;
      newPoints[2] = oldPoints[2];
      newPoints[3] = oldPoints[3] + SIDE_LENGTH;
      newPoints[4] = oldPoints[4];
      newPoints[5] = oldPoints[5] + SIDE_LENGTH;
   } else { // Move Left One Square
      newPoints[0] = oldPoints[0] - SIDE_LENGTH;
      newPoints[1] = oldPoints[1];
      newPoints[2] = oldPoints[2] - SIDE_LENGTH;
      newPoints[3] = oldPoints[3];
      newPoints[4] = oldPoints[4] - SIDE_LENGTH;
      newPoints[5] = oldPoints[5];
   }
}
