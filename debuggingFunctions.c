#include <stdio.h>
#include "stack.h"

void printStack(int* stack) {
   printf("Stack: {");
   for (int i = 1; i < stack[0] + 1; i++) {
      printf("%d, ", stack[i]);
   }
   printf("}\n");
   printf("Top of Stack is %d\n", top(stack));
}

void printVisited(int visited[][2], int count) {
   printf("Path: ");
   for (int i = 0; i < count + 1; i++) {
      printf("{%d, %d}, ", visited[i][0], visited[i][1]);
   }
   printf("\n");
}

void printViableBlock(int allViableBlocks[][2], int noOfViableBlocks) {
   printf("ViableBlock: ");
   for (int i = 0; i < noOfViableBlocks; i++) {
      printf("{%d, %d}, ", allViableBlocks[i][0], allViableBlocks[i][1]);
   }
   printf("\n");
}
