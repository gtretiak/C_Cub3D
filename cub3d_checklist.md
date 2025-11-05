# cub3D — Specific Roadmap Checklist


## 1) Argument Validation (CLI)

* [ ] Accepts exactly **1 argument**: path to a `*.cub` file
* [ ] Rejects:

  * [ ] No arguments
  * [ ] More than one argument
  * [ ] Extension other than `.cub`
  * [ ] Nonexistent/inaccessible path
  * [ ] Path that is a directory

**Acceptance**

* [ ] On any error, print exactly:

  ```
  Error
  <message>
  ```
* [ ] Clear messages:
  `usage: ./cub3D <map.cub>`,
  `map must end with .cub`,
  `cannot open file`,
  `path is a directory`

---

## 2) `.cub` File Reading and Pre-Parsing

* [ ] Read the file line by line (preserve content)
* [ ] Identify and collect **elements**: `NO`, `SO`, `WE`, `EA`, `F`, `C`
* [ ] Delimit the **map block** (the last block in the file)
* [ ] Allow **empty lines** between elements (never inside the map)
* [ ] Store map lines *exactly as they appear* (including spaces)

**Acceptance**

* [ ] If lines exist after the map → error `map must be last`
* [ ] If map block is empty → error `empty map block`

---

## 3) Element Validation (Textures and Colors)

* [ ] Each identifier appears **exactly once**
* [ ] `NO/SO/WE/EA` → *path* exists and is readable (XPM recommended)
* [ ] `F r,g,b` and `C r,g,b`:

  * [ ] Exactly 3 integers
  * [ ] Each between 0–255
  * [ ] No extra characters (e.g. double commas)
* [ ] Store `floor` and `ceiling` as `uint32_t ARGB`

**Acceptance**

* [ ] Duplicate →

  ```
  Error
  duplicate <ID>
  ```
* [ ] Missing →

  ```
  Error
  missing <ID>
  ```
* [ ] Invalid path → `Error
  texture path invalid`
* [ ] Invalid color → `Error
  invalid color`

---

## 4) Map Validation

* [ ] Allowed characters: `0 1 N S E W` (and spaces)
* [ ] Exactly **one** `N/S/E/W` (player spawn + orientation)
* [ ] Normalize width: pad with `' '` up to `max_width`
* [ ] **Flood-fill** check to ensure the map is **closed by walls**:

  * [ ] Treat `' '` as *outside space*
  * [ ] Start flood from non-wall border cells
  * [ ] If flood touches `0` or spawn → `map not closed`
* [ ] Reject “holes” or empty lines *inside* the map block

**Acceptance**

* [ ] Specific errors:
  `invalid map char`,
  `multiple player spawns`,
  `missing player spawn`,
  `map not closed`

---

## 5) Resource Loading and Window (miniLibX)

* [ ] `mlx_init`, `mlx_new_window`
* [ ] Load 4 textures (`mlx_xpm_file_to_image`): North, South, West, East
* [ ] Create *image buffer* for each frame
* [ ] Convert `F` and `C` to color values and fill ceiling/floor

**Acceptance**

* [ ] Window opens and closes with no leaks
* [ ] Minimizing/switching windows doesn’t break rendering

---

## 6) Player & Camera

* [ ] Initialize position `(x, y)` from spawn
* [ ] Set `dirX/dirY` based on `N/S/E/W`
* [ ] Set `planeX/planeY` (FOV ~66°)
* [ ] Movement speeds: `moveSpeed`, `rotSpeed`

**Acceptance**

* [ ] Initial frame shows ceiling (`C`) and floor (`F`) correctly

---

## 7) Ray-Casting (DDA) + Texturing

* [ ] For each column `x`:

  * [ ] Compute `cameraX` → `rayDir = dir + plane * cameraX`
  * [ ] Prepare DDA (`deltaDist`, `sideDist`, `step`, `mapX/Y`)
  * [ ] Step until wall (`'1'`), store `side`
  * [ ] Compute `perpWallDist` → `lineHeight`
  * [ ] Calculate `wallX` and `texX` (fix mirroring)
  * [ ] Sample correct texture (N/S/E/W) and draw vertical stripe
* [ ] Fill ceiling/floor outside wall stripe

**Acceptance**

* [ ] Correctly textured walls (no “fish-eye”, no texture bleeding)
* [ ] Acceptable FPS and no *tearing*

---

## 8) Input & Collisions

* [ ] Required keys:

  * [ ] **W A S D** to move (check cell before entering)
  * [ ] **← →** to rotate
  * [ ] **ESC** to exit cleanly
  * [ ] **Close button (X)** exits cleanly
* [ ] Simple grid-based collision (can’t walk through `'1'`)

**Acceptance**

* [ ] Smooth movement without wall clipping
* [ ] All exit methods close program cleanly with no leaks

---

## 9) Error Handling & Cleanup

* [ ] On **any** parsing/config failure: print required format and exit
* [ ] Free: images, window, map, strings, `libft`
* [ ] Test with `valgrind` (no *definitely lost* leaks)

**Acceptance**

* [ ] Zero leaks in both success and failure cases

---

## 10) Functional Tests (Minimum)

* [ ] **Valid cases**: minimal example and a larger map with internal spaces
* [ ] **Invalid cases** (each must fail with specific message):

  * [ ] Missing or duplicated texture
  * [ ] `F`/`C` out of range 0–255 or malformed
  * [ ] Invalid characters in map
  * [ ] Multiple or missing spawns
  * [ ] Map not closed / holes / empty lines within map
  * [ ] Lines after map block

**Acceptance**

* [ ] All invalid cases return `Error
  ...`
* [ ] Valid cases launch the game and are playable

