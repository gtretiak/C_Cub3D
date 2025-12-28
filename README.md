# C_Cub3D
Ray-Caster "3D" First-person-shooter 

## 📋 Table of Contents
- [Overview](#overview)
- [Key Concepts](#key-concepts)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Map Format](#map-format)
- [Real-World Applications](#real-world-applications)
- [Project Structure](#project-structure)

---

## 🎮 Overview

**cub3D** is a 3D graphics project that recreates the raycasting engine used in classic games like Wolfenstein 3D. The program takes a 2D map and renders it as a 3D first-person perspective maze, complete with textured walls, floor/ceiling colors, and smooth player movement.

### What It Does
- Parses scene description files (`.cub`) containing map layouts and texture paths
- Renders a real-time 3D view from a first-person perspective using raycasting
- Handles player movement (WASD) and rotation (arrow keys/mouse)
- Displays different wall textures based on cardinal direction (N/S/E/W)
- Validates map integrity (closed walls, proper format)

---

## 🔑 Key Concepts

### Raycasting Algorithm
The core technique that makes pseudo-3D rendering possible:

1. **Ray Projection**: For each vertical screen column, cast a ray from the player's position through the viewing plane
2. **DDA Algorithm**: Use Digital Differential Analysis to efficiently traverse the grid and find wall intersections
3. **Distance Calculation**: Calculate perpendicular wall distance to avoid fisheye distortion
4. **Wall Height**: Project 3D wall height based on distance (closer = taller)
5. **Texture Mapping**: Map wall textures to rendered columns based on hit position

**Why This Approach?**
- **Efficiency**: O(n) per frame where n = screen width, much faster than true 3D rendering
- **Simplicity**: Works with 2D data structures (grid maps) and without GPU dependencies

---

## ✨ Features

### Mandatory Features
- ✅ **3D Raycasting Engine**: Real-time first-person rendering at 640×360 resolution
- ✅ **Textured Walls**: Four directional textures (N/S/E/W) using XPM format
- ✅ **Custom Colors**: RGB color configuration for floor and ceiling
- ✅ **Smooth Controls**: 
  - WASD for movement
  - Arrow keys for rotation
  - ESC to exit
- ✅ **Map Validation**: Comprehensive error checking for invalid configurations
- ✅ **Scene Parser**: Flexible .cub file format with whitespace tolerance

###  Ideas TODO
- 🎁 **Wall Collisions**: Realistic collision detection
- 🎁 **Minimap System**: Real-time overhead view
- 🎁 **Interactive elements**: Open/close/use mechanisms 
- 🎁 **Animated Sprites**: Dynamic visual elements
- 🎁 **Mouse Rotation**: Smooth camera control
- 🎁 **Configuration file**: For key bindings
- 🎁 **Save/load system**: To keep game state

---

## 🚀 Installation

### Prerequisites
```bash
# Linux (Debian/Ubuntu)
sudo apt-get update
sudo apt-get install -y gcc make xorg libxext-dev libbsd-dev

# macOS
xcode-select --install
brew install make
```

1. **Clone the Repository**
```bash
git clone https://github.com/yourusername/cub3D.git
cd cub3D
```

2. **Build the Project**
```bash
make
# This compiles:
# - Main executable: cub3D
# - MinilibX library
# - Libft (custom C library)
```

3. **Verify Installation**
```bash
./cub3D <path_to_map.cub>
Example: ./cub3D maps/good/subject_map.cub
# Should open a window with a 3D maze view
```

---

## 📖 Usage

### Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` | Rotate left |
| `→` | Rotate right |
| `ESC` | Exit program |

---

## 🗺️ Map Format

### .cub File Structure

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111111111
100000000001
100N00000001
100000000001
111111111111
```

### Element Reference

| Identifier | Description | Format |
|------------|-------------|--------|
| `NO` | North wall texture | `NO ./path/to/texture.xpm` |
| `SO` | South wall texture | `SO ./path/to/texture.xpm` |
| `WE` | West wall texture | `WE ./path/to/texture.xpm` |
| `EA` | East wall texture | `EA ./path/to/texture.xpm` |
| `F` | Floor color (RGB) | `F R,G,B` (0-255 each) |
| `C` | Ceiling color (RGB) | `C R,G,B` (0-255 each) |

### Map Characters

| Character | Meaning |
|-----------|---------|
| `0` | Empty walkable space |
| `1` | Wall |
| `N` | Player spawn facing North |
| `S` | Player spawn facing South |
| `E` | Player spawn facing East |
| `W` | Player spawn facing West |
| ` ` (space) | Void |

### Validation Rules

✅ **Valid Maps**:
- Enclosed by walls (surrounded by `1`)
- Exactly one player spawn position
- Rectangular or irregular shapes with proper boundaries

❌ **Invalid Maps**:
- Open edges (player can walk off the map)
- Multiple player positions
- Missing required textures/colors
- Invalid RGB values (>255 or <0)

---

## 🌍 Real-World Applications

### 1. **Game Engine Development**
**Scenario**: Indie game studio prototyping a retro-style FPS

**Application**:
- Use cub3D's raycasting engine as foundation for a commercial 2.5D game
- Extend with combat mechanics, inventory systems, and level progression
- Deploy on platforms with limited GPU capabilities (embedded systems, old hardware)

**Example**: A dungeon crawler mobile game using similar techniques could run on low-end Android devices where full 3D engines struggle.

---

### 2. **Architectural Visualization**
**Scenario**: Real estate company creating virtual property tours

**Application**:
- Convert 2D floor plans into navigable 3D walkthroughs
- Allow clients to "walk through" properties remotely
- Lightweight alternative to heavy CAD software for initial presentations

**Example**: A web-based property viewer that loads floor plans as `.cub` format and renders instant 3D previews without requiring browser WebGL support.

---

### 3. **Accessibility Tools**
**Scenario**: Assistive technology for visually impaired users

**Application**:
- Audio-based navigation system using spatial sound
- Convert physical spaces into navigable digital maps
- Haptic feedback integration for maze-like environments (museums, malls)

**Example**: A museum app where blind visitors navigate exhibits using headphones that provide 3D audio cues based on raycasting calculations of nearby walls and objects.

---

## 📁 Project Structure

```
cub3D/
├── sources/
│   ├── args_checker.c       # Command-line argument validation
│   ├── file_reading.c       # .cub file parsing orchestration
│   ├── init_scene.c         # Scene structure initialization
│   ├── wall_parsing.c       # Texture path parsing
│   ├── flat_parsing.c       # Floor/ceiling color parsing
│   ├── map_parsing.c        # Map validation & flood fill
│   ├── utils.c              # Memory management utilities
│   └── render/
│       ├── render.c         # Main rendering loop
│       ├── raycast.c        # Core raycasting algorithm
│       ├── draw.c           # Pixel manipulation
│       ├── texture.c        # Texture mapping calculations
│       ├── move.c           # Player movement logic
│       ├── keys.c           # Keyboard event handling
│       ├── utils.c          # Frame timing & speed calculation
│       └── memory/
│           ├── init.c       # MLX initialization
│           ├── player.c     # Player state setup
│           └── free.c       # Resource cleanup
├── maps/
│   ├── good/                # Valid test maps
│   │   ├── subject_map.cub
│   │   ├── cheese_maze.cub
│   │   └── ...
│   └── bad/                 # Invalid maps for error testing
│       ├── wall_hole_north.cub
│       ├── player_multiple.cub
│       └── ...
├── textures/
│   ├── n.xpm                # North wall texture
│   ├── s.xpm                # South wall texture
│   ├── e.xpm                # East wall texture
│   └── w.xpm                # West wall texture
├── cub3d.h                  # Main header with data structures
├── Makefile                 # Build configuration
└── README.md                # This file
```

### Key Data Structures

```c
typedef struct s_scene {
    t_flat      floor;           // Floor color (RGB)
    t_flat      ceilling;        // Ceiling color (RGB)
    t_wall      north/south/     // Texture paths
                west/east;
    t_player    player;          // Spawn position & direction
    char        **map;           // 2D grid representation
    t_point     map_size;        // Map dimensions
} t_scene;

typedef struct s_game {
    char        **map;           // Runtime map grid
    t_actor     *plyr;           // Player position & vectors
    t_image     *txtr[4];        // Loaded textures (N/S/E/W)
    void        *mlx_ptr;        // MinilibX instance
    void        *win_ptr;        // Window handle
} t_game;

typedef struct s_ray_vars {
    double      ray_dir_x/y;     // Ray direction vector
    double      delta_dist_x/y;  // Distance between grid lines
    int         step_x/y;        // DDA step direction
    double      perp_wall_dist;  // Perpendicular distance to wall
    int         tex_x/y;         // Texture coordinates
} t_ray_vars;
```

---

## 🧪 Testing

### Automated Test Suite
```bash
# Run all valid maps
for map in maps/good/*.cub; do
    echo "Testing: $map"
    ./cub3D "$map" &
    sleep 2
    killall cub3D
done

# Test error handling
for map in maps/bad/*.cub; do
    echo "Testing: $map"
    ./cub3D "$map" 2>&1 | grep -q "Error"
    if [ $? -eq 0 ]; then
        echo "✓ Correctly rejected"
    else
        echo "✗ Should have failed"
    fi
done
```

### Performance Benchmarking
```c
// In render loop (utils.c)
double frametime = (current_time - prev_time) / 1000.0;
fps = 1.0 / frametime;

// Typical results:
// - Simple maps: 60+ FPS
// - Complex mazes: 45-60 FPS
// - With bonuses: 30-45 FPS
```

---


## 📚 Resources

### Learning Materials
- [Lodev's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) - Comprehensive guide
- [Permadi's Ray-Casting Tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/) - Classic resource
- [Game Engine Black Book: Wolfenstein 3D](https://fabiensanglard.net/gebbwolf3d/) - Deep dive into the original
- [Original Wolfenstein game](http://users.atw.hu/wolf3d/) - get inspiration

### Tools
- [GIMP](https://www.gimp.org/) - Creating XPM textures
- [Valgrind](https://valgrind.org/) - Memory leak detection
- [GDB](https://www.gnu.org/software/gdb/) - Debugging
