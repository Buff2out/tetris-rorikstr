# Tetris Game API Documentation

## Overview

This is a Tetris game implementation following FSM (Finite State Machine) pattern.
The backend is completely separated from frontend, allowing easy integration with any UI.

## Public API

### `void userInput(UserAction_t action, bool hold)`

Processes user input and updates game state accordingly.

**Parameters:**

- `action`: User action from enum `UserAction_t`
  - `Start`: Initialize/restart game
  - `Pause`: Toggle pause state
  - `Terminate`: Quit game and free resources
  - `Left`: Move figure left
  - `Right`: Move figure right
  - `Up`: Release instant drop flag (for next drop)
  - `Down`: Instant drop figure
  - `Action`: Rotate figure
- `hold`: Reserved for future use (currently ignored)

**Behavior:**

- Blocked during pause (except Pause/Terminate/Start)
- Blocked during Attaching state (except Pause/Terminate/Start)
- Down action requires key release between uses (prevents double-drop)

**Example (Rust FFI):**

```rust
extern "C" {
    fn userInput(action: UserAction_t, hold: bool);
}

// In your Rust code:
unsafe {
    userInput(UserAction_t::Left, false);
}
```

---

### `GameInfo_t updateCurrentState()`

Updates game state machine and returns current game information for rendering.

**Returns:**

- `GameInfo_t` structure containing:
  - `field`: 2D array `[FIELD_HEIGHT][FIELD_WIDTH]` representing game field
    - `0`: Empty cell
    - `1`: Active (falling) figure
    - `2`: Placed (fixed) blocks
  - `next`: 2D array `[4][4]` with next figure preview
  - `score`: Current score
  - `high_score`: Best score (persistent)
  - `level`: Current level (1-10)
  - `speed`: Current speed multiplier
  - `pause`: Pause state (0=playing, 1=paused)

**Call frequency:**
Should be called every game loop iteration (~10ms recommended).
The function handles timing internally using `clock_gettime(CLOCK_MONOTONIC)`.

**Example (Rust FFI):**

```rust
#[repr(C)]
struct GameInfo_t {
    field: *mut *mut c_int,
    next: *mut *mut c_int,
    score: c_int,
    high_score: c_int,
    level: c_int,
    speed: c_int,
    pause: c_int,
}

extern "C" {
    fn updateCurrentState() -> GameInfo_t;
}

// In your game loop:
loop {
    let state = unsafe { updateCurrentState() };
    render_game(state);
    std::thread::sleep(Duration::from_millis(10));
}
```

---

## Game Constants

```c
#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
```

## FSM States (Internal)

- **Init**: Initialize game field and stats
- **Spawn**: Create new figure at top
- **Move**: Automatic figure falling
- **Moving**: User-controlled movement/rotation
- **Attaching**: Figure placement with delay
- **GameOver**: Game ended, waiting for restart

## Timing

- Base fall delay: 1100ms - (speed × 100ms)
- Instant drop delay: 30ms per step
- Attach delay: 350ms (prevents double-spawn)
- Pause compensates all timings correctly

## Score System

- 1 line: 100 points
- 2 lines: 300 points
- 3 lines: 700 points
- 4 lines: 1500 points
- Level up: every 600 points
- Speed increases with level (max level 10)

## Memory Management

All memory is managed internally. Call `userInput(Terminate, false)` before exit
to properly free resources.

## Thread Safety

**Not thread-safe!** Use from single thread only or add external synchronization.

---

## Integration Example (Full Rust Frontend)

```rust
use std::ffi::c_int;
use std::time::Duration;

#[repr(C)]
#[derive(Copy, Clone)]
enum UserAction_t {
    Start = 0,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action,
}

#[repr(C)]
struct GameInfo_t {
    field: *mut *mut c_int,
    next: *mut *mut c_int,
    score: c_int,
    high_score: c_int,
    level: c_int,
    speed: c_int,
    pause: c_int,
}

#[link(name = "tetris", kind = "static")]
extern "C" {
    fn userInput(action: UserAction_t, hold: bool);
    fn updateCurrentState() -> GameInfo_t;
}

fn main() {
    // Initialize game
    unsafe { userInput(UserAction_t::Start, false); }
    
    // Game loop
    loop {
        // Get input (your input handling)
        let action = get_user_input();
        if let Some(a) = action {
            unsafe { userInput(a, false); }
        }
        
        // Update and render
        let state = unsafe { updateCurrentState() };
        render_with_your_ui(state);
        
        std::thread::sleep(Duration::from_millis(10));
    }
}
```

---

## Building for FFI

```sh
# Build static library
make

# Use in your project
gcc your_frontend.c -L./build -ltetris -lncurses -lm -lrt -lpthread -o game
# or with Rust
cargo build --release
```

## Notes for Frontend Developers

1. **Field coordinates**: [y][x] where y=0 is top, x=0 is left
2. **Next preview**: Always 4×4 matrix, figure may not fill entire space
3. **High score**: Automatically saved to `build/high_score.txt`
4. **No need to free** GameInfo_t - it's internal storage
5. **Call sequence**: Start → (updateCurrentState + userInput)* → Terminate
