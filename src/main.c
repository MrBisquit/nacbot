/*
    NACBOT made by William Dawson (MrBisquit on GitHub)
    https://wtdawson.info

    --------------------------------------------------------------------------------------------

    This is a 2nd version of my noughts and crosses bot,
    and this one is in the console instead. Entirely written in C.

    The ONLY dependencies are:
    *   memory.h
    *   stdio.h
    *   stdint.h
    
    Which are all standard libraries, no external dependencies.

    Key points within this file:
    *   The main function               (Ctrl+F to find "int main(int argc, char* argv[])")
    *   The bot function for simulation (CTRL+F to find "void run_bot(board_t* b)")

    This uses ansi_console.h, which is defined below.

    --------------------------------------------------------------------------------------------

 *  GitHub:     https://github.com/MrBisquit/nacbot
 *  File:       https://github.com/MrBisquit/nacbot/tree/master/src/main.c
 *  License:    SPDX-License-Identifier: MIT
 *              See LICENSE file in the project root for full license text or see below.

    --------------------------------------------------------------------------------------------

    MIT License

    Copyright (c) 2025 William Dawson

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include <memory.h>

/** ansi_console.h made by William Dawson (MrBisquit on GitHub)
 *  GitHub:     https://github.com/MrBisquit/ansi_console
 *  File:       https://github.com/MrBisquit/ansi_console/tree/main/ansi_console.h
 *  License:    SPDX-License-Identifier: MIT
 *              See LICENSE file in the project root for full license text.
 */

#include <stdio.h>
#include <stdint.h>

#ifndef CONSOLE_H

/**
    Information on ANSI escape codes are available here:    https://gist.github.com/ConnerWill/d4b6c776b509add763e17f9f113fd25b
    See examples:                                           https://stackoverflow.com/a/54062826
    Truecolor:                                              https://en.wikipedia.org/wiki/Color_depth#True_color_.2824-bit.29
  
    Name            FG  BG
	Black           30  40
	Red             31  41
	Green           32  42
	Yellow          33  43
	Blue            34  44
	Magenta         35  45
	Cyan            36  46
	White           37  47
	Bright Black    90  100
	Bright Red      91  101
	Bright Green    92  102
	Bright Yellow   93  103
	Bright Blue     94  104
	Bright Magenta  95  105
	Bright Cyan     96  106
	Bright White    97  107

    This file uses the American spelling of colour (color).
*/

#pragma region // Definitions
// Color definitions
// Foreground
#define CONSOLE_FG_BLACK                (uint8_t)30
#define CONSOLE_FG_RED                  (uint8_t)31
#define CONSOLE_FG_GREEN                (uint8_t)32
#define CONSOLE_FG_YELLOW               (uint8_t)33
#define CONSOLE_FG_BLUE                 (uint8_t)34
#define CONSOLE_FG_MAGENTA              (uint8_t)35
#define CONSOLE_FG_CYAN                 (uint8_t)36
#define CONSOLE_FG_WHITE                (uint8_t)37
#define CONSOLE_FG_BRIGHT_BLACK         (uint8_t)90
#define CONSOLE_FG_BRIGHT_RED           (uint8_t)91
#define CONSOLE_FG_BRIGHT_GREEN         (uint8_t)92
#define CONSOLE_FG_BRIGHT_YELLOW        (uint8_t)93
#define CONSOLE_FG_BRIGHT_BLUE          (uint8_t)94
#define CONSOLE_FG_BRIGHT_MAGENTA       (uint8_t)95
#define CONSOLE_FG_BRIGHT_CYAN          (uint8_t)96
#define CONSOLE_FG_BRIGHT_WHITE         (uint8_t)97
// Background
#define CONSOLE_BG_BLACK                (uint8_t)40
#define CONSOLE_BG_RED                  (uint8_t)41
#define CONSOLE_BG_GREEN                (uint8_t)42
#define CONSOLE_BG_YELLOW               (uint8_t)43
#define CONSOLE_BG_BLUE                 (uint8_t)44
#define CONSOLE_BG_MAGENTA              (uint8_t)45
#define CONSOLE_BG_CYAN                 (uint8_t)46
#define CONSOLE_BG_WHITE                (uint8_t)47
#define CONSOLE_BG_BRIGHT_BLACK         (uint8_t)100
#define CONSOLE_BG_BRIGHT_RED           (uint8_t)101
#define CONSOLE_BG_BRIGHT_GREEN         (uint8_t)102
#define CONSOLE_BG_BRIGHT_YELLOW        (uint8_t)103
#define CONSOLE_BG_BRIGHT_BLUE          (uint8_t)104
#define CONSOLE_BG_BRIGHT_MAGENTA       (uint8_t)105
#define CONSOLE_BG_BRIGHT_CYAN          (uint8_t)106
#define CONSOLE_BG_BRIGHT_WHITE         (uint8_t)107

// Colors/Graphics mode
#define CONSOLE_GRAPHICS_RESET                  (uint8_t)0
#define CONSOLE_GRAPHICS_BOLD                   (uint8_t)1
#define CONSOLE_GRAPHICS_DIM                    (uint8_t)2
#define CONSOLE_GRAPHICS_ITALIC                 (uint8_t)3
#define CONSOLE_GRAPHICS_UNDERLINE              (uint8_t)4
#define CONSOLE_GRAPHICS_BLINKING               (uint8_t)5
#define CONSOLE_GRAPHICS_INVERSE_REVERSE        (uint8_t)7
#define CONSOLE_GRAPHICS_HIDDEN_INVISIBLE       (uint8_t)8
#define CONSOLE_GRAPHICS_STRIKETHROUGH          (uint8_t)9
// Reset sequences
#define CONSOLE_GRAPHICS_RESET_BOLD             (uint8_t)22
#define CONSOLE_GRAPHICS_RESET_DIM              (uint8_t)22
#define CONSOLE_GRAPHICS_RESET_ITALIC           (uint8_t)23
#define CONSOLE_GRAPHICS_RESET_UNDERLINE        (uint8_t)24
#define CONSOLE_GRAPHICS_RESET_BLINKING         (uint8_t)25
#define CONSOLE_GRAPHICS_RESET_INVERSE_REVERSE  (uint8_t)27
#define CONSOLE_GRAPHICS_RESET_HIDDEN_INVISIBLE (uint8_t)28
#define CONSOLE_GRAPHICS_RESET_STRIKETHROUGH    (uint8_t)29

// Screen modes
#define CONSOLE_MODE_40x25_MONOCHROME           (uint8_t)0
#define CONSOLE_MODE_40x25_COLOR                (uint8_t)1
#define CONSOLE_MODE_80x25_MONOCHROME           (uint8_t)2
#define CONSOLE_MODE_80x25_COLOR                (uint8_t)3
#define CONSOLE_MODE_320x200_4_COLOR            (uint8_t)4
#define CONSOLE_MODE_320x200_MONOCHROME         (uint8_t)5
#define CONSOLE_MODE_640x200_MONOCHROME         (uint8_t)6
#define CONSOLE_MODE_LINE_WRAPPING              (uint8_t)7      // I have no idea why this is in the middle of here and not at one end
#define CONSOLE_MODE_320x200_COLOR              (uint8_t)13
#define CONSOLE_MODE_640x200_16_COLOR           (uint8_t)14
#define CONSOLE_MODE_640x350_MONOCHROME         (uint8_t)15
#define CONSOLE_MODE_640x350_16_COLOR           (uint8_t)16
#define CONSOLE_MODE_640x480_MONOCHROME         (uint8_t)17
#define CONSOLE_MODE_640x480_16_COLOR           (uint8_t)18
#define CONSOLE_MODE_320x200_256_COLOR          (uint8_t)19

#pragma endregion
#pragma region // Colors
/// @brief This can set both the foreground and background color
/// @param color The color (definitions beginning with `CONSOLE_FG` or `CONSOLE_BG`)
void console_set_color(uint8_t color) {
    printf("\x1B[%dm", color);
}

/// @brief This can set both the foreground and background colour
/// @param stream The stream to write the ANSI escape code to
/// @param color The color (definitions beginning with `CONSOLE_FG` or `CONSOLE_BG`)
void fconsole_set_color(FILE* stream, uint8_t color) {
    fprintf(stream, "\x1B[%dm", color);
}

/// @brief Set the console foreground color with RGB (If your terminal supports Truecolor)
/// @param r Red
/// @param g Green
/// @param b Blue
void console_set_foreground_rgb(uint8_t r, uint8_t g, uint8_t b) {
    printf("\x1B[38;2;{%d};{%d};{%d}m", r, g, b);
}

/// @brief Set the console foreground color with RGB (If your terminal supports Truecolor)
/// @param stream The stream to write the ANSI escape code to
/// @param r Red
/// @param g Green
/// @param b Blue
void fconsole_set_foreground_rgb(FILE* stream, uint8_t r, uint8_t g, uint8_t b) {
    fprintf(stream, "\x1B[38;2;{%d};{%d};{%d}m", r, g, b);
}

/// @brief Set the console background color with RGB (If your terminal supports Truecolor)
/// @param r Red
/// @param g Green
/// @param b Blue
void console_set_background_rgb(uint8_t r, uint8_t g, uint8_t b) {
    printf("\x1B[48;2;{%d};{%d};{%d}m", r, g, b);
}

/// @brief Set the console background color with RGB (If your terminal supports Truecolor)
/// @param stream The stream to write the ANSI escape code to
/// @param r Red
/// @param g Green
/// @param b Blue
void fconsole_set_background_rgb(FILE* stream, uint8_t r, uint8_t g, uint8_t b) {
    fprintf(stream, "\x1B[48;2;{%d};{%d};{%d}m", r, g, b);
}

/// @brief Resets console color
void console_reset_color() {
    printf("\033[0m");
}

/// @brief Resets console color
/// @param stream The stream to write the ANSI escape code to
void fconsole_reset_color(FILE* stream) {
    fprintf(stream, "\033[0m");
}

#pragma endregion
#pragma region // Cursor
/// @brief Resets the console cursor back to (0,0)
void console_reset_cursor() {
    printf("\x1B[H");
}

/// @brief Resets the console cursor back to (0,0)
/// @param stream The stream to write the ANSI escape code to
void fconsole_reset_cursor(FILE* stream) {
    fprintf(stream, "\x1B[H");
}

/// @brief Moves the console cursor to the specified line and column
/// @param line The line to move the console cursor to
/// @param column The column to move the console cursor to
void console_move_cursor(int line, int column) {
    printf("\x1B[%d;%dH", line, column);
    printf("\x1B[%d;%df", line, column);
}

/// @brief Moves the console cursor to the specified line and column
/// @param stream The stream to write the ANSI escape code to
/// @param line The line to move the console cursor to
/// @param column The column to move the console cursor to
void fconsole_move_cursor(FILE* stream, int line, int column) {
    fprintf(stream, "\x1B[%d;%dH", line, column);
    fprintf(stream, "\x1B[%d;%df", line, column);
}

#pragma endregion
#pragma region // Clearing
/// @brief Clears the screen
void console_clear_screen() {
    printf("\x1B[2J");
}

/// @brief Clears the screen
/// @param stream The stream to write the ANSI escape code to
void fconsole_clear_screen(FILE* stream) {
    fprintf(stream, "\x1B[2J");
}

/// @brief Clears the current line
/// @note You may want to move the cursor to the start of the line with `\r`
void console_clear_line() {
    printf("\x1B[2K");
}

/// @brief Clears the current line
/// @note You may want to move the cursor to the start of the line with `\r`
/// @param stream The stream to write the ANSI escape code to
void fconsole_clear_line(FILE* stream) {
    fprintf(stream, "\x1B[2K");
}

#pragma endregion
#pragma region // Graphics
/// @brief Sets the graphics mode
/// @param graphics The graphics mode (definitions beginning with `CONSOLE_GRPAHICS`)
void console_graphics_set(uint8_t graphics) {
    printf("\x1B[%dm", graphics);
}

/// @brief Sets the graphics mode
/// @param stream The stream to write the ANSI escape code to
/// @param graphics The graphics mode (definitions beginning with `CONSOLE_GRPAHICS`)
void fconsole_graphics_set(FILE* stream, uint8_t graphics) {
    fprintf(stream, "\x1B[%dm", graphics);
}

#pragma endregion
#pragma region // Mode

#endif // CONSOLE_H

/*
    Pre definitions
*/
typedef struct uPoint8 { uint8_t x; uint8_t y; } uPoint8;
static uPoint8 uP8(uint8_t x, uint8_t y) { uPoint8 point = { x, y }; return point; };

typedef struct board board_t;
typedef enum plr plr_t;
typedef enum err err_t;
typedef enum bool bool;
typedef enum winner winner_t;

static bool cuP8(uPoint8 p) { return p.x <= 2 && p.y <= 2; }

void run_bot(board_t* b);
uPoint8 bot_suggest(board_t* b);

/*
    Below is the actual game, and the main functionality.
*/

/// @brief Prints 10 new lines, then moves the cursor to the top
void clr_game_area() {
    for(uint8_t i = 0; i < 100; i++) printf("\n");
    console_reset_cursor(); // Reset cursor to (0,0)
}

/// @brief Prints grid information
void prnt_info() {
    console_set_color(CONSOLE_FG_WHITE);
    printf("On the grid, ");
    console_set_color(CONSOLE_BG_WHITE);
    printf(" ");
    console_set_color(CONSOLE_BG_BLACK);
    printf(" means blank ");
    console_set_color(CONSOLE_BG_RED);
    printf(" ");
    console_set_color(CONSOLE_BG_BLACK);
    printf(" means X, and ");
    console_set_color(CONSOLE_BG_BLUE);
    printf(" ");
    console_set_color(CONSOLE_BG_BLACK);
    printf(" means O");
    console_reset_color();
    printf("\n");
}

struct board {
    uint8_t board[3][3];
};

/// @brief Generates a new empty board
/// @return A new empty board
board_t new_board() {
    board_t b = {
        .board = {
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 }
        }
    };

    return b;
}

static board_t game_board;
enum plr {
    PLR_BLANK,
    PLR_X,
    PLR_O
};
static plr_t active_player;

enum err {
    ERR_SUCCESS,
    ERR_INVALID_PLACE,
    ERR_PLACE_TAKEN
};

enum bool {
    true,
    false
};

enum winner {
    NO_WINNER,  // This is used sort of like an offset (see `plr`)
    WINNER_X,
    WINNER_O,
    WINNER_TIE
};

/// @brief Prints the board to the screen
/// @param b The board
void prnt_board(board_t b) {
    // It does a line 6 times

    // Top line
    printf(" A");
    for (uint8_t i = 0; i < 6; i++)
    {
        printf(" ");
    }
    printf("B");
    for (uint8_t i = 0; i < 6; i++)
    {
        printf(" ");
    }
    printf("C");

    printf("\n");

    // Top 3
    for (uint8_t j = 0; j < 3; j++)
    {
        if(j == 0) printf("1");
        else printf(" ");

        for (uint8_t i = 0; i < 3; i++)
        {
            for (uint8_t k = 0; k < 6; k++)
            {
                switch (b.board[0][i])
                {
                case PLR_BLANK:
                    console_set_color(CONSOLE_BG_WHITE);
                    break;
                case PLR_X:
                    console_set_color(CONSOLE_BG_RED);
                    break;
                case PLR_O:
                    console_set_color(CONSOLE_BG_BLUE);
                    break;
                default:
                    console_set_color(CONSOLE_BG_GREEN);    // Make it obvious that something isn't right
                    break;
                }
                printf(" ");
                console_reset_color();
            }
            printf(" ");
        }
        printf("\n");
    }
    printf("\n");
    // Middle 3
    for (uint8_t j = 0; j < 3; j++)
    {
        if(j == 0) printf("2");
        else printf(" ");

        for (uint8_t i = 0; i < 3; i++)
        {
            for (uint8_t k = 0; k < 6; k++)
            {
                switch (b.board[1][i])
                {
                case PLR_BLANK:
                    console_set_color(CONSOLE_BG_WHITE);
                    break;
                case PLR_X:
                    console_set_color(CONSOLE_BG_RED);
                    break;
                case PLR_O:
                    console_set_color(CONSOLE_BG_BLUE);
                    break;
                default:
                    console_set_color(CONSOLE_BG_GREEN);    // Make it obvious that something isn't right
                    break;
                }
                printf(" ");
                console_reset_color();
            }
            printf(" ");
        }
        printf("\n");
    }
    printf("\n");
    // Bottom 3
    for (uint8_t j = 0; j < 3; j++)
    {
        if(j == 0) printf("3");
        else printf(" ");

        for (uint8_t i = 0; i < 3; i++)
        {
            for (uint8_t k = 0; k < 6; k++)
            {
                switch (b.board[2][i])
                {
                case PLR_BLANK:
                    console_set_color(CONSOLE_BG_WHITE);
                    break;
                case PLR_X:
                    console_set_color(CONSOLE_BG_RED);
                    break;
                case PLR_O:
                    console_set_color(CONSOLE_BG_BLUE);
                    break;
                default:
                    console_set_color(CONSOLE_BG_GREEN);    // Make it obvious that something isn't right
                    break;
                }
                printf(" ");
                console_reset_color();
            }
            printf(" ");
        }
        printf("\n");
    }

    // Reset colour
    console_reset_color();
}

/// @brief Select a place
/// @return The place
uPoint8 place_select() {
    printf("Select a place (E.g. \"A1\"): ");
    char col = ' ';
    uint8_t row = 0;
    scanf("%c %d", &col, &row);
    uint8_t cold = 4;
    switch (col)
    {
    case 'A':
        cold = 0;
        break;
    case 'B':
        cold = 1;
        break;
    case 'C':
        cold = 2;
        break;
    default:
        break;
    }
    return uP8(row - 1, cold);
}

/// @brief Place the place on the board
/// @param b A pointer to the board object
/// @param p The player
/// @param pnt The point
/// @return Error code (0 = success)
err_t place_plr(board_t* b, plr_t p, uPoint8 pnt) {
    if(pnt.x > 2 || pnt.y > 2) return ERR_INVALID_PLACE;
    if(b->board[pnt.x][pnt.y] == PLR_BLANK)
        b->board[pnt.x][pnt.y] = p;
    else return ERR_PLACE_TAKEN;
    return ERR_SUCCESS;
}

static uint8_t pos[8][3][2] = {
        { { 0, 0 }, { 1, 0 }, { 2, 0 } }, // Top line       (A)
        { { 0, 1 }, { 1, 1 }, { 2, 1 } }, // Middle line    (A)
        { { 0, 2 }, { 1, 2 }, { 2, 2 } }, // Bottom line    (A)
        { { 0, 0 }, { 0, 1 }, { 0, 2 } }, // Left line      (D)
        { { 1, 0 }, { 1, 1 }, { 1, 2 } }, // Middle line    (D)
        { { 2, 0 }, { 2, 1 }, { 2, 2 } }, // Right line     (D)
        { { 0, 0 }, { 1, 1 }, { 2, 2 } }, // Top left  -> Bottom right
        { { 2, 0 }, { 1, 1 }, { 0, 2 } }  // Top right -> Bottom left
    };

/// @brief Check for any winners
/// @param b The pointer to the board
winner_t check_winner(board_t* b) {
    plr_t player = PLR_BLANK;

    for (uint8_t i = 0; i < 8; i++)
    {
        player = b->board[pos[i][0][0]][pos[i][0][1]];
        bool win = true;
        for (uint8_t j = 0; j < 3; j++)
        {
            plr_t now_player = b->board[pos[i][j][0]][pos[i][j][1]];
            if(player != now_player) win = false;
            player = now_player;
        }
        if(win == true && player != PLR_BLANK) return player;
    }

    // Check if all of the places are placed
    for (uint8_t i = 0; i < 3; i++)
    {
        for (uint8_t j = 0; j < 3; j++)
        {
            if(b->board[i][j] == PLR_BLANK) return NO_WINNER;
        }
    }
    return WINNER_TIE;
}

void prnt_winner(winner_t winner) {
    console_reset_color();
    printf("Winner: ");
    switch (winner)
    {
    case WINNER_TIE:
        console_set_color(CONSOLE_FG_GREEN);
        printf("Tie");
        break;
    case WINNER_X:
        console_set_color(CONSOLE_FG_RED);
        printf("X");
        break;
    case WINNER_O:
        console_set_color(CONSOLE_FG_BLUE);
        printf("O");
        break;
    default:
        break;
    }
    console_reset_color();
    printf("!");
}

void prnt_suggestion(board_t* b) {
    uPoint8 p = bot_suggest(b);
    printf("Bot suggestion: %c%d\n", 'A' + p.x, p.y + 1);
}

/// @brief The main function
/// @param argc Args count
/// @param argv Args
/// @return Return code (0 = Success, anything else = issue/error - e.g. 1)
int main(int argc, char* argv[]) {
    game_board = new_board();
    active_player = PLR_X;
    while(1) {
        clr_game_area();
        prnt_info();
        prnt_board(game_board);
        if(active_player == PLR_X) {
            prnt_suggestion(&game_board);
            uPoint8 place = place_select();
            err_t err;
            if((err = place_plr(&game_board, PLR_X, place)) != ERR_SUCCESS) {
                active_player = PLR_X; // Maintain active player, invalid move
            } else {
                active_player = PLR_O;
            }
        } else {
            // Send board to the bot, and await a response
            run_bot(&game_board);
            active_player = PLR_X;
        }

        // Check for a winner
        winner_t winner = check_winner(&game_board);
        if(winner != NO_WINNER) {
            clr_game_area();
            prnt_info();
            prnt_board(game_board);

            prnt_winner(winner);

            break;
        }
    }
}

/*
    This is the algorithm behind the bot.

    There are 3 main stages when choosing the next move:
    - See any possible ways that the opposing player could win, and block them.
      Conflicts within this are dealt with which is the most likely for the player to notice
    - See any possible ways that the bot could win, easy.
    - Calculate the likelyness of the next move being a win (Determine which place has the highest likelyhood of a win)

    The first 2 checks can be disabled with a flag (check above).

    Previous versions of this included a pre-generation algorithm, which takes time and about 20 MB.
    This one however takes off from the current board, and generates every possible outcome from it.

    It uses a stepping algorithm to determine the likelyness (as a float) that placing in that specific spot will win.
    Basically, it goes over every possible available spot, and then places there, it'll then run that same algorithm
    going back and forth between the player until it either wins, loses, or ties. Losses and ties and grouped together
    as losses, and are calculated as wins / total to get a decimal.

    The algorithm then goes over every one of the results, and picks the highest. If there is a conflict with more than
    one having the highest (Two have the same number), it will pick the first option.
*/

typedef struct bot_board bot_board_t;

struct bot_board {
    uint64_t wins;
    uint64_t losses;
    uint64_t ties;
};

void bot_simulate_game(board_t* b, bot_board_t* board, plr_t active_player, uPoint8 start);
uPoint8 bot_check_blocks(board_t* b);
uPoint8 bot_check_win(board_t* b);

/// @brief Run the bot algorithm
/// @param b The pointer to the board
void run_bot(board_t* b) {
    // Check for any easy way to win first
    uPoint8 p = bot_check_win(b);
    if(cuP8(p)) {
        place_plr(b, PLR_O, p);
        return;
    }
    p = bot_check_blocks(b);
    if(cuP8(p)) {
        place_plr(b, PLR_O, p);
        return;
    }

    float probs[3][3] = {
        { 0.0, 0.0, 0.0 },
        { 0.0, 0.0, 0.0 },
        { 0.0, 0.0, 0.0 }
    };

    bot_board_t boards[3][3];

    // Look at the board first, there's no point in simulating a move that isn't possible
    for (uint8_t i = 0; i < 3; i++)
    {
        for (uint8_t j = 0; j < 3; j++)
        {
            if(b->board[i][j] == PLR_BLANK) {
                bot_simulate_game(b, &boards[i][j], PLR_O, uP8(j, i));
            }
        }
    }

    for (uint8_t i = 0; i < 3; i++)
    {
        for (uint8_t j = 0; j < 3; j++)
        {
            probs[i][j] = (float)boards[i][j].wins / ((float)boards[i][j].wins + (float)boards[i][j].losses + (float)boards[i][j].ties);
        }
    }

    uPoint8 point = uP8(0, 0);
    float top = 0.0;
    for (uint8_t i = 0; i < 3; i++)
    {
        for (uint8_t j = 0; j < 3; j++)
        {
            if(probs[i][j] > top && b->board[i][j] == PLR_BLANK) {
                top = probs[i][j];
                point = uP8(i, j);
            }
        }
    }

    place_plr(b, PLR_O, point);
    return;
}

/// @brief Simulates the next move by duplicating the board
/// @param b The pointer to the board
/// @param board The pointer to the bot board
/// @param active_player The active player
/// @param start The starting position
void bot_simulate_game(board_t* b, bot_board_t* board, plr_t active_player, uPoint8 start) {
    // Duplicate the board
    board_t b_cpy;
    memcpy(&b_cpy, b, sizeof(board_t));

    // Place the active player on the board
    b_cpy.board[start.y][start.x] = active_player;
    
    // Check for any winner
    winner_t winner = check_winner(&b_cpy);
    if(winner != NO_WINNER) {
        if(winner == WINNER_X) board->losses++;
        if(winner == WINNER_O) board->wins++;
        else board->ties++;
        
        return;
    }

    // Fork again
    for (uint8_t i = 0; i < 3; i++)
    {
        for (uint8_t j = 0; j < 3; j++)
        {
            if(b_cpy.board[i][j] == PLR_BLANK) {
                bot_simulate_game(&b_cpy, board, PLR_O, uP8(j, i));
            }
        }
    }

    return;
}

/*
    Below are 2 very important checks, these are the checks that can easily
    block the player, or get an easy win.

    They work in similar ways, by detecting if the player (or bot) are in 2
    of the 3 positions needed to win. It will then fill the 3rd, blocking or
    winning easily.
*/

/// @brief Checks every possible way that the opposing player could win
/// @param b The pointer to the board
/// @return A way to block the opposing player (Returns an invalid move if so)
uPoint8 bot_check_blocks(board_t* b) {
    for (uint8_t i = 0; i < 8; i++)
    {
        uint8_t used = 0;
        uPoint8 unused;
        for (uint8_t j = 0; j < 3; j++)
        {
            if(b->board[pos[i][j][0]][pos[i][j][1]] == PLR_X) used++;
            else unused = uP8(pos[i][j][0], pos[i][j][1]);
        }
        if(used == 2 && b->board[unused.y][unused.x] == PLR_BLANK) return unused;
    }
    return uP8(5, 5);
}

/// @brief Checks every possible way that the bot could win (easily)
/// @param b The pointer to the board
/// @return A way to easily win (Returns an invalid move if so)
uPoint8 bot_check_win(board_t* b) {
    for (uint8_t i = 0; i < 8; i++)
    {
        uint8_t used = 0;
        uPoint8 unused;
        for (uint8_t j = 0; j < 3; j++)
        {
            if(b->board[pos[i][j][0]][pos[i][j][1]] == PLR_O) used++;
            else unused = uP8(pos[i][j][0], pos[i][j][1]);
        }
        if(used == 2 && b->board[unused.y][unused.x] == PLR_BLANK) return unused;
    }
    return uP8(5, 5);
}

/// @brief Uses the same bot algorithms to suggest a move to the player
/// @param b The pointer ot the board
/// @return A suggestion as a point
uPoint8 bot_suggest(board_t* b) {
    // Check for any easy way to win first
    uPoint8 p = bot_check_win(b);
    if(cuP8(p)) {
        return p;
    }
    p = bot_check_blocks(b);
    if(cuP8(p)) {
        return p;
    }

    float probs[3][3] = {
        { 0.0, 0.0, 0.0 },
        { 0.0, 0.0, 0.0 },
        { 0.0, 0.0, 0.0 }
    };

    bot_board_t boards[3][3];

    // Look at the board first, there's no point in simulating a move that isn't possible
    for (uint8_t i = 0; i < 3; i++)
    {
        for (uint8_t j = 0; j < 3; j++)
        {
            if(b->board[i][j] == PLR_BLANK) {
                bot_simulate_game(b, &boards[i][j], PLR_O, uP8(j, i));
            }
        }
    }

    for (uint8_t i = 0; i < 3; i++)
    {
        for (uint8_t j = 0; j < 3; j++)
        {
            probs[i][j] = (float)boards[i][j].wins / ((float)boards[i][j].wins + (float)boards[i][j].losses + (float)boards[i][j].ties);
        }
    }

    uPoint8 point = uP8(0, 0);
    float top = 0.0;
    for (uint8_t i = 0; i < 3; i++)
    {
        for (uint8_t j = 0; j < 3; j++)
        {
            if(probs[i][j] > top && b->board[i][j] == PLR_BLANK) {
                top = probs[i][j];
                point = uP8(i, j);
            }
        }
    }

    return point;
}