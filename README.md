[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/StQAS8iq)

# Continuous Cellular Automaton with Empirical

This project demonstrates a continuous 2D cellular automaton using Conway's Game of Life rules. It runs in the browser using Empirical's `Animate` and `Canvas` tools.

## Features
- Classic Game of Life rules: Implements standard rules for cell birth, survival, and death.

- Toroidal Wrapping: The grid wraps around edges to simulate an infinite 2D space.

- Web-Based Canvas: Uses Empirical's web tools to draw the simulation on an HTML5 canvas.

- Glider Pattern: Starts with the classic glider pattern, which moves diagonally across the grid.

- User Controls: Includes toggle and step buttons to control the animation.


## Patterns

- A **Glider** is added near the top-left.

It is a periodic, self-moving pattern and it demonstrates how wrapping is handled via a toroidal grid.

## Toroidal Wrapping

Implemented by modulus operations to ensure edge wrapping along both axes.

## Sources

- [Conway's Game of Life Patterns](https://conwaylife.com/wiki/Glider)

## Author

Isha Patel
