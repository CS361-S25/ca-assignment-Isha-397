[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/StQAS8iq)

# Continuous Cellular Automaton - Glider

## Description

This project implements a continuous version of Conway's Game of Life using Empirical's web-based animation tools.

This simulation uses continuous state values ranging from 0.0 to 1.0 for each cell. Alive cells are shown in red using RGB color, while dead or inactive cells smoothly fade through greyscale tones using HSV values. This creates a visually rich and dynamic effect where patterns don’t just appear or disappear instantly, but transition over time.

The simulation begins with a classic **glider** pattern and demonstrates toroidal edge wrapping, ensuring movement continues fluidly across boundaries.

## Pattern Demonstrated

- **Glider**:
  - A 5-cell pattern that travels diagonally across the grid.
  - A well-known demonstration of motion and persistence in cellular automata.
  - In this implementation, the glider is visualized in **red**, with fading trails in **greyscale**, enhancing the aesthetic of continuous change.

  ## Visual Behavior

- **Alive Cells**:
  - Rendered in **red** using RGB (255, 0, 0).
- **Inactive/Dead Cells**:
  - Fade in and out in greyscale using HSV, where the value component is based on recent activity.

This style simulates organic, fluid transitions between cell states and highlights continuous change over abrupt updates.

## Sources Consulted

- **Empirical Library Documentation**: https://dev.empirical.codes
- **Lecture Materials Week of April 15, 2025** (covering continuous CA using ColorHSV and ColorRGB)
- **Wikipedia: Conway's Game of Life** – [https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)
- **Stack Overflow** for minor syntax clarification on nested vectors and greyscale HSV values.

## Author

Isha Patel
