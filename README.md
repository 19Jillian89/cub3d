![Language](https://img.shields.io/badge/language-C-blue)
![School](https://img.shields.io/badge/school-42-black)

# cub3d

A 3D graphics engine written in C, simulating a first-person view inside a maze using the raycasting technique — the same technology behind Wolfenstein 3D (1992).
Project developed as part of the 42 School curriculum.
---

## 🎯 Project Goals

- Build a 3D graphics engine from scratch in C
- Simulate a first-person perspective using raycasting math
- Handle real-time keyboard input
- Parse and validate `.cub` scene description files
- Work with the MiniLibX graphics library

---

## ⚙️ Features

| Feature | Description |
|---|---|
| 🔦 3D Raycasting | First-person rendering via DDA algorithm |
| 🧱 Wall Textures | Different textures for each wall side (N / S / E / W) |
| 🎨 Floor & Ceiling | Customizable colors for floor and ceiling |
| 🕹️ FPS Movement | WASD + arrow keys |
| 💥 Collision Detection | Player cannot walk through walls |
| 🗺️ `.cub` Map Parsing | Scene file parsing and validation |
| ❌ Error Handling | Clean exit with descriptive error messages |

---

## 🗺️ `.cub` File Format

The program takes a `.cub` configuration file as its only argument.

### File Structure

```
NO ./textures/north.xpm      # North wall texture
SO ./textures/south.xpm      # South wall texture
WE ./textures/west.xpm       # West wall texture
EA ./textures/east.xpm       # East wall texture

F 220,100,0                  # Floor color (R,G,B)
C 225,30,0                   # Ceiling color (R,G,B)

1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
1111111111N00000000000001
1111111111111111111111111
```

### Map Legend

### Map Legend

| Character | Meaning |
|---|---|
| `1` | Wall |
| `0` | Empty space |
| `N` | Player spawn, facing **North** |
| `S` | Player spawn, facing **South** |
| `E` | Player spawn, facing **East** |
| `W` | Player spawn, facing **West** |

### Validation Rules

- The map **must be closed** by walls on all sides
- The map must be the **last element** in the file
- There must be **exactly one player spawn** point
- RGB color values must be in the range `[0, 255]`

---

## 🕹️ Controls

| Key | Action |
|---|---|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` `→` | Rotate view |
| `ESC` | Close the program |
| `[X]` | Close from window frame |

---

## 🚀 Build & Run

### Requirements

- GCC / Clang
- Make
- MiniLibX (included in `minilibx-linux/`)

### Run

```bash
./cub3D maps/test.cub
```

### Cleanup

```bash
make clean    # remove object files
make fclean   # remove objects + executable
make re       # full recompile
```

---

## 📁 Project Structure

```
cub3D/
├── src/                    # Main source files
│   ├── main.c
│   ├── parsing/            # .cub file reading & validation
│   ├── raycasting/         # 3D engine (DDA)
│   ├── rendering/          # Screen drawing
│   └── utils/              # Helper functions
├── maps/                   # .cub test files
├── textures/               # XPM textures
├── libft/                  # 42 custom library
├── include/                # header
├── minilibx-linux/         # Graphics library
├── Makefile
└── README.md
```

---

## 🧠 How It Works: Raycasting

### Core Concept

Raycasting transforms a 2D map into a simulated 3D view. For each **column of pixels** on the screen, a ray is cast from the player's position. When a ray hits a wall, the distance is measured and a vertical line is drawn — the closer the wall, the taller the line.

```
                  Screen
     2D Map        │ │ │ │ │ │ │ │
    ┌──────────┐   █ █ █ █ █ █ █ █   ← Rendered columns
    │ 1 1 1 1  │   │ │ │   │ │ │ │
    │ 1 0 0 1  │   █ █     █ █ █ █
    │ 1 P 0 1  │       empty space
    │ 1 1 1 1  │
    └──────────┘
```

### DDA Algorithm (Digital Differential Analyzer)

The DDA algorithm steps through the map grid by grid, advancing the ray in the most efficient direction (horizontal or vertical) until it hits a wall (`1`).

```
Key principle: wall_height ∝ 1 / distance_to_wall
  → Close  = tall column  = big wall
  → Far    = short column = small wall
```

### Texture Mapping

When a ray hits a wall, the exact point of impact is calculated to determine which pixel of the XPM texture to apply. All four sides (N/S/E/W) have distinct textures.

### Main Data Structures

```c
typedef struct s_player {
    double  pos_x;      // X position
    double  pos_y;      // Y position
    double  dir_x;      // Direction vector X
    double  dir_y;      // Direction vector Y
    double  room_plane_x;    // Camera plane X
    double  room_plane_y;    // Camera plane Y
} t_player;
```

---


## 📚 Key Concepts Learned

- **Graphics in C** — pixels, buffers, MiniLibX library
- **3D Math** — vectors, trigonometry, projections
- **DDA Algorithm** — efficient grid traversal
- **Robust Parsing** — file validation with error handling
- **Memory Management** — allocation/deallocation with no leaks
- **Game Loop** — input → update → render

---

## 👥 Authors

| Name | GitHub |
|---|---|
| *Ilaria Nassi* | [@19Jillian89](https://github.com/19Jillian89)|
| *Viorica Gabriela Hacman* | [@vhacman](https://github.com/vhacman) |

---

## 📄 License

Project developed for educational purposes as part of the **42 School** curriculum.
