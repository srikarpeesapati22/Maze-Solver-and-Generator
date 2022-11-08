# Maze Generator and Solver

## Description

First draws a basic maze and solves it using a hardcoded solution (Stages 1 and 2)
![image](https://user-images.githubusercontent.com/112534138/200616121-f47b9b91-ab76-4fa9-859f-39023e33eddf.png)

Next, draws a slightly more complex maze and solves it using a depth-first-search algorithm (Stage 3)
![image](https://user-images.githubusercontent.com/112534138/200616539-2937c5ef-26dc-426e-9fdc-b3f61a1dc2e1.png)

Lastly, draws a complex maze with a size between 30x30 to 150x150 and solves it using a depth-first-search algorithm (Stages 4 and 5)
![image](https://user-images.githubusercontent.com/112534138/200617207-3fc57100-93b4-4f04-a60a-07a3373b6b56.png)

## Usage
### Compiling
```bash
gcc -o maze coordinateFunctions.c debuggingFunctions.c graphics.c instructionGenerator.c mazeGenerator.c mazeSolver.c player.c positionFunctions.c shapeGenerator.c stack.c main.c

```
### Running
```bash
./maze | java -jar drawapp-2.0.jar
```
## Known Errors
Sometimes drawapp-2.0.jar does not generate the stage 3, 4, 5 code properly. To fix this issue quit the drawing app and run the maze program again.

## Changing Dimensions of Maze and size of Maze

To change the range for the dimensions of the maze, navigate to mazeGenerator.c and edit the MIN_SIZE and MAX_SIZE constants.
To change the size of the maze edit the SIDE_LENGTH constant in the coordinateFunctions.c, shapeGenerator.c, and player.c files.
