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

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int dim;

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
    dim = atoi(argv[1]);
    if (dim < DIM_MIN || dim > DIM_MAX)
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
        for (int i = 0; i < dim; i++)
        {
            for (int j = 0; j < dim; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < dim - 1)
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
            usleep(50000);
        }

        // sleep thread for animation's sake
        usleep(50000);
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
    usleep(2000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int ntiles = dim * dim - 1;

    int num = ntiles;
    for (int i = 0; i < dim; i++) 
    {
        for (int j = 0; j < dim; j++) 
        {
            board[i][j] = num;
            num--;
        }
    }

    // if d is even swap 2 and 1
    int modulo = dim % 2;
    if (modulo == 0) 
    {
        board[dim - 1][dim - 3] = 1;
        board[dim - 1][dim - 2] = 2;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++) 
        {
            if (board[i][j] == 0) 
            {
                printf(" _");
            } 
            else 
            {
                printf("%2d ", board[i][j]);
            }
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
    // check if tile number is valid
    int min_tile_num = 1;
    int max_tile_num = dim * dim - 1;

    if (tile < min_tile_num || tile > max_tile_num) 
    {
        return false;
    }

    // linear search for the tile's index, O(n^2)
    for (int i = 0; i < dim; i++) 
    {
        for (int j = 0; j < dim; j++) 
        {
            if (tile == board[i][j]) 
            {

                // empty tile is marked 0 (zero)
                // check left
                if (j - 1 >= 0 && board[i][j - 1] == 0) 
                {
                    board[i][j - 1] = tile;
                    board[i][j] = 0;
                    return true;
                }

                // check right
                if (j + 1 <= dim - 1 && board[i][j + 1] == 0) 
                {
                    board[i][j + 1] = tile;
                    board[i][j] = 0;
                    return true;
                }

                // check up
                if (i - 1 >= 0 && board[i - 1][j] == 0) 
                {
                    board[i - 1][j] = tile;
                    board[i][j] = 0;
                    return true;
                }

                // check down
                if (i + 1 <= dim - 1 && board[i + 1][j] == 0) 
                {
                    board[i + 1][j] = tile;
                    board[i][j] = 0;
                    return true;
                }
            }
        }
    }

    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // omega(1) , check if last tile value is zero
    if (board[dim - 1][dim - 1] != 0) 
    {
        return false;
    }

    int num = 1;
    int maxtiles = dim * dim;

    // O(n^2)
    for (int i = 0; i < dim; i++) 
    {
        for (int j = 0; j < dim; j++) 
        {
            if (num != maxtiles) 
            {
                if (board[i][j] != num) 
                {
                    printf("\n %d == %d", board[i][j], num);
                    return false;
                }
            }
            num++;
        }
    }

    return true;
}