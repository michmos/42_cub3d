# 42 cub3d

<table>
  <tr>
    <img width="400" height="200" alt="cub3d1-ezgif com-optimize(1)" src="https://github.com/user-attachments/assets/a0999271-7a99-48a9-9c2d-799fc671c1d8" />
    <img width="400" height="200" alt="cub3d2-ezgif com-optimize" src="https://github.com/user-attachments/assets/211e3306-a773-46fe-a675-4dc323f0c10b" />
  </tr>
</table>

## About the project
### Task
The goal of this project was to build a raycasting engine inspired by
Wolfenstein 3D, rendering a first-person view of a maze from a 2D map.
The program reads a `.cub` configuration file defining textures, colors,
and the map layout, then uses DDA raycasting to project textured 3D walls
in real-time.

### Features
- Raycasting with DDA (Digital Differential Analyzer) algorithm for grid intersection detection
- Textured walls (4 directional textures: NO, SO, WE, EA)
- Graphics via [MLX42](https://github.com/codam-coding-college/MLX42)
- Configurable floor & ceiling colors (RGB)
- Smooth movement (WASD) and rotation (arrow keys)
- Collision system with configurable hitbox
- Distance-based shading for depth effectPlan
- Real-time minimap
- Robust `.cub` file parsing with descriptive error messages

## Utilization
### Cloning
```bash
git clone https://github.com/michmos/42_cub3d.git && cd 42_cub3d && make
```

### Running
Run the executable with a `.cub` map file as argument:
```
./cub3d maps/all_walls.cub
```
Choose any map from the `maps/` directory or create your own.

### Controls
| Key | Action |
|---|---|
| `W/A/S/D` | Move forward / strafe left / backward / strafe right |
| `← →` | Rotate view left / right |
| `ESC` | Quit the game |
