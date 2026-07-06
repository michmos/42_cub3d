# raycaster

<table>
  <tr>
    <img width="400" height="200" alt="cub3d1-ezgif com-optimize(1)" src="https://github.com/user-attachments/assets/a0999271-7a99-48a9-9c2d-799fc671c1d8" />
    <img width="400" height="200" alt="cub3d2-ezgif com-optimize" src="https://github.com/user-attachments/assets/211e3306-a773-46fe-a675-4dc323f0c10b" />
  </tr>
</table>

## About
This project is the 42 project `cub3d`. The goal of this project is to build a raycasting engine inspired by
Wolfenstein 3D, rendering a first-person view of a maze from a 2D map. The program reads a `.cub` configuration file 
defining textures, colors, and the map layout, then uses DDA raycasting to project textured 3D walls in real-time.

## Features
- Raycasting with DDA (Digital Differential Analyzer) algorithm for grid intersection detection
- Textured walls (4 directional textures: NO, SO, WE, EA)
- Graphics via [MLX42](https://github.com/codam-coding-college/MLX42)
- Configurable floor & ceiling colors (RGB)
- Smooth movement (WASD) and rotation (arrow keys)
- Collision system with configurable hitbox
- Distance-based shading for depth effectPlan
- Real-time minimap
- Robust `.cub` file parsing with descriptive error messages

## Algorithm
Raycasting is a pipeline of trigonometry problems solved for each of the 1024 vertical screen columns for each frame:
1. **DDA**: find the closest ray intersection with a wall
2. **Fish-eye correction**: compute the actual distance to remove the spherical distortion
3. **Wall-height scaling**: compute the wall height based on the distance of the wall
4. **Texture selection**: select the correct texture (N/S/E/W) based on the intersection and the viewing angle
5. **Texture slicing**: scale the texture to fill the wall
6. **Shading**: darken rgba of computed pixel based on the distance 

## Utilization
1. **Cloning**:
   ```bash
   git clone https://github.com/michmos/raycaster.git && cd raycaster && make
   ```

2. **Running**:
   Run the executable with a `.cub` map file as argument:
   ```
   ./cub3d maps/all_walls.cub
   ```
   Choose any map from the `maps/` directory or create your own.

3. **Controls**:
   | Key | Action |
   |---|---|
   | `W/A/S/D` | Move forward / strafe left / backward / strafe right |
   | `← →` | Rotate view left / right |
   | `ESC` | Quit the game |
