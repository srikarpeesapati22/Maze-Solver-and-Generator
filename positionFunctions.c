void updatePosition(int* position, int angle) {
   if (angle == 0) { // Move Up One Square
      position[0] -= 1;
   } else if (angle == 90) { // Move Right One Square
      position[1] += 1;
   } else if (angle == 180) { // Move Down One Square
      position[0] += 1;
   } else { // Move Left One Square
      position[1] -= 1;
   }
}

void getStartPosition(int* x, int * y, char* mazeArray[], int sizeOfMaze) {
   int* xAddress = x;
   int* yAddress = y;
   int coordinateArr[] = {0, 0};
   for (int row = 0; row < sizeOfMaze; row++) {
      for (int column = 0; column < sizeOfMaze; column++) {
         if (mazeArray[row][column] == '2') {
            *xAddress = row;
            *yAddress = column;
         }
      }
   }
}

void getEndPosition(int* position, char* mazeArray[], int sizeOfMaze) {
   for (int row = 0; row < sizeOfMaze; row++) {
      for (int column = 0; column < sizeOfMaze; column++) {
         if (mazeArray[row][column] == '3') {
            position[0] = row;
            position[1] = column;
         }
      }
   }
}
