/**
 * @file 00_tetris.h
 * @brief Public API for Tetris game backend
 * 
 * This header defines the public interface for Tetris game logic.
 * The backend is completely separated from UI, allowing integration
 * with any frontend (ncurses, SDL, Qt, Rust, etc.).
 * 
 * @note Thread safety: NOT thread-safe! Use from single thread only.
 * @note Memory management: All memory is managed internally. Call
 *       userInput(Terminate, false) before exit to free resources.
 */

#ifndef TETRIS_H
#define TETRIS_H

#include <stdbool.h>
#include <stdio.h>

/**
 * @brief Width of the game field in blocks
 */
#define FIELD_WIDTH 10

/**
 * @brief Height of the game field in blocks
 */
#define FIELD_HEIGHT 20

/**
 * @enum UserAction_t
 * @brief User input actions
 * 
 * Represents all possible user actions in the game.
 */
typedef enum {
    Start,      /**< Initialize or restart the game */
    Pause,      /**< Toggle pause state */
    Terminate,  /**< Quit game and free all resources */
    Left,       /**< Move figure left */
    Right,      /**< Move figure right */
    Up,         /**< Release instant drop flag (for next drop) */
    Down,       /**< Instant drop figure to bottom */
    Action      /**< Rotate figure clockwise */
} UserAction_t;

/**
 * @struct GameInfo_t
 * @brief Game state information for rendering
 * 
 * Contains all information needed to render the game state.
 * This structure is returned by updateCurrentState() every frame.
 * 
 * @note Do not free the pointers - memory is managed internally
 */
typedef struct {
    /**
     * @brief 2D game field [FIELD_HEIGHT][FIELD_WIDTH]
     * 
     * Values:
     * - 0: Empty cell
     * - 1: Active (falling) figure
     * - 2: Placed (fixed) blocks
     */
    int **field;
    
    /**
     * @brief Preview of next figure [4][4]
     * 
     * 4x4 matrix containing the next figure shape.
     * Values: 0 (empty) or 1 (figure block)
     */
    int **next;
    
    int score;       /**< Current score */
    int high_score;  /**< Best score (persistent across sessions) */
    int level;       /**< Current level (1-10) */
    int speed;       /**< Current speed multiplier */
    int pause;       /**< Pause state: 0=playing, 1=paused */
} GameInfo_t;

/**
 * @brief Process user input and update game state
 * 
 * This function handles all user actions and updates the internal FSM state.
 * Should be called when user performs an action (key press, button click, etc.).
 * 
 * @param action User action from UserAction_t enum
 * @param hold Reserved for future use (currently ignored)
 * 
 * @note Actions are blocked during pause (except Pause, Terminate, Start)
 * @note Actions are blocked during Attaching state (except Pause, Terminate, Start)
 * @note Down action requires key release between uses to prevent double-drop
 * 
 * @par Example:
 * @code
 * // Handle left arrow key press
 * userInput(Left, false);
 * 
 * // Start new game
 * userInput(Start, false);
 * 
 * // Quit and cleanup
 * userInput(Terminate, false);
 * @endcode
 * 
 * @par FSI Integration (Rust example):
 * @code{.rs}
 * extern "C" {
 *     fn userInput(action: UserAction_t, hold: bool);
 * }
 * 
 * unsafe {
 *     userInput(UserAction_t::Left, false);
 * }
 * @endcode
 */
void userInput(UserAction_t action, bool hold);

/**
 * @brief Update game state and return current game information
 * 
 * This function must be called every game loop iteration (recommended ~10ms).
 * It updates the internal FSM, handles timing, figure movement, collisions,
 * and returns the current state for rendering.
 * 
 * @return GameInfo_t structure with current game state
 * 
 * @note Call frequency: ~100 times per second (every 10ms)
 * @note Timing is handled internally using POSIX clock_gettime(CLOCK_MONOTONIC)
 * @note The returned structure contains pointers to internal memory - do not free!
 * 
 * @par Example:
 * @code
 * // Game loop
 * while (running) {
 *     GameInfo_t state = updateCurrentState();
 *     
 *     // Render game field
 *     for (int i = 0; i < FIELD_HEIGHT; i++) {
 *         for (int j = 0; j < FIELD_WIDTH; j++) {
 *             if (state.field[i][j] == 1) {
 *                 draw_active_block(j, i);
 *             } else if (state.field[i][j] == 2) {
 *                 draw_placed_block(j, i);
 *             }
 *         }
 *     }
 *     
 *     // Display score
 *     printf("Score: %d  Level: %d\n", state.score, state.level);
 *     
 *     sleep_ms(10);
 * }
 * @endcode
 * 
 * @par Timing behavior:
 * - Base fall delay: 1100ms - (speed × 100ms)
 * - Instant drop: 30ms per step
 * - Attach delay: 350ms (prevents instant spawn)
 * - Pause correctly compensates all timings
 */
GameInfo_t updateCurrentState();

#endif /* TETRIS_H */
