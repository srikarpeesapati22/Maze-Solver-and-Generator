int* initializeStack(int* stack) {
   stack[0] = 0;
   return stack;
}

int isEmpty(int *stack) {
   if (stack[0] == 0) {
      return 1;
   }
   return 0;
}

void push(int num, int *stack) {
   stack[0] += 1;
   stack[stack[0]] = num;
}

int pop(int *stack) {
   if (isEmpty(stack) == 1) {
      return -1;
   } else {
      int value = stack[stack[0]];
      stack[0] -= 1;
      return value;
   }
}

int search(int num, int *stack) {
   for (int i = 1; i < stack[0] + 1; i++) {
      if (stack[i] == num) {
         return i;
      }
   }
   return -1;
}

int top(int *stack) {
   if (stack[0] == 0) {
      return -1;
   }
   return stack[stack[0]];
}
