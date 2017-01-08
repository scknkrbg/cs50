/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;
int empty_h;
int empty_r;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(10000);
        }

        // sleep thread for animation's sake
        usleep(10000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int numbers = d*d;
    for(int height = 0; height < d; height++)
    {
        for(int row = 0; row < d; row++)
        {
            numbers--;  
            board[height][row] = numbers;
        }
    }
    
    if((d*d-1)%2 != 0)
    {
        board[d-1][d-2] = 2;
        board[d-1][d-3] = 1;
    }
    
    empty_h = d-1;
    empty_r = d-1;
    
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for(int height = 0; height < d; height++)
    {
        for(int row = 0; row < d; row++)
        {
            if(board[height][row] > 0)
                printf("%3i ", board[height][row]);
            else
                printf("%3c ", '_');
        }
        printf("\n");
    }
    
    
    printf("\n");
    for(int height = 0; height < d; height++)
    {
        for(int row = 0; row < d; row++)
        {
            printf("(%i, %i) = %i ", height, row, board[height][row]);
        }
        printf("\n");
    }
    
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // printf("DEBUG: d = %i\n", d);
    int h, r;
    for(h = 0; h < d; h++)
    {
        for(r = 0; r < d; r++)
        {
            if(board[h][r] == tile) 
                break;
        }
        if(board[h][r] == tile) 
            break;
    }
    
    // h++;
    // r++;
    // printf("DEBUG: h = %i, r = %i\n", h, r);
    // printf("DEBUG: empty_h = %i, empty_r = %i\n", empty_h, empty_r);
    
   
    
    if(((h == empty_h+1 && empty_r == r) ||
        (h == empty_h-1 && empty_r == r) ||
        (r == empty_r-1 && empty_h == h) ||
        (r == empty_r+1 && empty_h == h)))
    {
        int temp = board[h][r];
        board[h][r] = board[empty_h][empty_r];
        board[empty_h][empty_r] = temp; 
        empty_h = h;
        empty_r = r;
        return true;
    }
    else
        return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int num = 0;
    bool result = true;
    for(int h = 0; h < d; h++)
    {
        for(int r = 0; r < d; r++)
        {
            num++;
            if(board[d-1][d-1] > 0) 
            {
                result = false;
                break;
            }
            else if (!(h == d-1 && r == d-1) && board[h][r] != num )
            {
                result = false;
                break;
            }
            else
                result = true;
             
        }
    }
    return result;
}