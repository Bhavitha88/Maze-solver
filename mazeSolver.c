/*ASSIGNMENT NUMBER :1
NAME:KAKKIRALA BHAVITHA
EMAIL-ID:co22btech11005@iit.ac.in
CLASS:2ND YEAR OF BTECH COMPUTATIONAL ENGINEERING
DATE :3RD SEP 2023*/

#include <stdio.h>
#include <stdlib.h>

int deque[1000];
int head = -1, rear = -1;
/*IsEmpty is the function which tells wheather the 
the deque is empty are not*/

int IsEmpty() {
    if (head == -1 && rear == -1) {
        return 1;
    } else {
        return 0;
    }
}
/*IsFull is the function which tells wheather the deque
is full or not*/

int IsFull() {
    if (head == (rear + 1) % 1000) {
        return 1;
    } else {
        return 0;
    }
}
/*deletes the front most element in the deque*/
int deletefront() {
    int z;
    if (!IsEmpty()) {
        if (head == rear) {
            z = deque[head];
            head = -1;
            rear = -1;
        } else {
            z = deque[head];
            head = (head + 1) % 1000;
        }
        return z;
    } else {
        return -1; // Return -1 to indicate failure
    }
}
/*addfront helps in adding the element at the front
of the deque*/
void addfront(int y) {
    if (!IsFull()) {
        if (head == -1 && rear == -1) {
            head = 0;
            rear = 0;
            deque[head] = y;
        } else {
            head = (head + 1000 - 1) % 1000;
            deque[head] = y;
        }
    }
}
/*add back tells to add the element at the back of the deque*/
void addback(int y) {
    if (!IsFull()) {
        if (head == -1 && rear == -1) {
            head = 0;
            rear = 0;
            deque[rear] = y;
        } else {
            rear = (rear + 1) % 1000;
            deque[rear] = y;
        }
    }
}

int main() {
    char maze[1000][1000];
    /*this row and column are the variables for the particular
    index of the 2d maze*/
    int row, column;
    /*L=location
    end=end position
    start=start position*/
    int L, end, start;
    FILE* input;
    FILE* output;
    /*input is the file which I have to input*/
    /*output is the file which output is printed*/
    /*NUMBER OF ROWS AND COLUMNS DOES THE MAZE HAS*/
    int ROWS = 0;
    int COLUMNS = 0;

    input = fopen("maze.txt", "r");
    while (fscanf(input, "%c", &maze[ROWS][COLUMNS]) != EOF) {
        if (maze[ROWS][COLUMNS] == '\n') {
            ROWS++;
            COLUMNS = 0;
        } else {
            COLUMNS++;
        }
    }
    
    fclose(input);

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (maze[i][j] == 'S') {
                start = COLUMNS * i + j;
                addfront(start);
            }
            if (maze[i][j] == 'E') {
                end = COLUMNS * i + j;
            }
        }
    }

    while (1) {
        L = deletefront();
        row = L / COLUMNS;
        column = L % COLUMNS;
        if (L == end) {
            break;
        }

        if (maze[row][column] == '.' || maze[row][column] == '#') {
            continue;
        } else {
            if (maze[row][column] != 'S') {
                maze[row][column] = '.';
            }
            if (abs(end - (L + COLUMNS)) < abs(end - L)) {
                addfront(L + COLUMNS);
            } else {
                addback(L + COLUMNS);
            }

            if (abs(end - (L - COLUMNS)) < abs(end - L)) {
                addfront(L - COLUMNS);
            } else {
                addback(L - COLUMNS);
            }

            if (abs(end - (L + 1)) < abs(end - L)) {
                addfront(L + 1);
            } else {
                addback(L + 1);
            }

            if (abs(end - (L - 1)) < abs(end - L)) {
                addfront(L - 1);
            } else {
                addback(L - 1);
            }
            
        }
        if (IsEmpty())
        {
            break;
        }
        
    }
    // Print the solved maze
    for (int i = 0; i <= ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }

    if (L == end) {
        printf("Reached the end\n");
    } else {
        printf("Couldn't find the end\n");
    }
    output =fopen("outputs maze3.txt" ,"w");
   fprintf(output,"%s","Maze file name? maze1.txt\n");
   fprintf(output,"%s","Searching for a path ...\n");
   fprintf(output,"%s","Here is your solved maze :\n");

for(int i = 0 ; i <= ROWS ; i++)
 {
  for(int j = 0 ; j < COLUMNS ; j++)
  {
    fputc( maze[i][j],output);
  }
    fprintf(output,"\n");
 }
fclose(output);

    return 0;
}