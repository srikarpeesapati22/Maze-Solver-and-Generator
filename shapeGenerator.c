#include "graphics.h"
#include <stdio.h>

#define SIDE_LENGTH 5
#define PLAYER_COLOUR green
#define SLEEP_TIME 100

colour getBlockColour(char shapeId) {
   if (shapeId == '0' || shapeId == '2') {return white;}
   if (shapeId == '1') {return black;}
   if (shapeId == '3') {return lightgray;}
}

void drawSquare(int x, int y, colour c) {
   setColour(c);
   fillRect(x, y, SIDE_LENGTH, SIDE_LENGTH);
}

void drawTriangle(int x, int y) {
   int pointsX[] = {x, x, x + SIDE_LENGTH};
   int pointsY[] = {y, y + SIDE_LENGTH, y + SIDE_LENGTH / 2};
   setColour(PLAYER_COLOUR);
   fillPolygon(3, pointsX, pointsY);
   sleep(SLEEP_TIME);
}

void drawSpecificTriangle(int* points, char c) {
   if (c == 'w') {
      setColour(white);
   } else {
      setColour(PLAYER_COLOUR);
   }
   foreground();
   int pointsX[] = {points[0], points[2], points[4]};
   int pointsY[] = {points[1], points[3], points[5]};
   fillPolygon(3, pointsX, pointsY);
   if (c != 'w') {
      sleep(SLEEP_TIME);
   }
}
