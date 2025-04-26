# Timber Man Game Project based on *Beginning C++ Game Programming* by John Horton

This project is a game called **Timber Man**, developed using **SFML (Simple and Fast Multimedia Library)** in C++. The structure of the project follows the first 6 chapters of the book *Beginning C++ Game Programming* by John Horton. Each part of the game corresponds to a chapter, showcasing the concepts learned.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Game Structure](#game-structure)
- [Installation](#installation)
- [Build and Run Instructions](#build-and-run-instructions)
- [How to Play](#how-to-play)
- [Acknowledgments](#acknowledgments)

---

## Introduction

**Timber Man** is a simple and fun game where you play as a lumberjack chopping wood while avoiding falling branches. This project was developed as a learning exercise while following the book *Beginning C++ Game Programming* by John Horton. It uses **SFML** for rendering graphics and handling user input.

The game demonstrates core C++ programming concepts and builds upon them chapter by chapter.

---

## Features

- **C++ Core Concepts**: Demonstrates object-oriented programming, functions, and basic game mechanics.
- **Graphics with SFML**: Implements a simple graphical interface using SFML.
- **Interactive Gameplay**: Allows the player to chop wood while avoiding obstacles.
- **Modular Design**: Each part of the game corresponds to a chapter in the book, making it modular and easy to follow.

---

## Game Structure

The game is divided into parts, each corresponding to a chapter in the book:

1. **Chapter 1: Setting up SFML and the Environment**
   - Setting up SFML and creating a basic game window.

2. **Chapter 2: Adding the Background**
   - Adding a static background image to the game.

3. **Chapter 3: Displaying the Player and Other Game Objects**
   - Rendering the player, the tree, branches, and other objects.

4. **Chapter 5: Handling Player Input**
   - Allowing the player to control the lumberjack and chop wood on the left or right side of the tree.

5. **Chapter 6: Adding Game Logic**
   - Introducing game logic, scoring, and losing conditions (e.g., branches falling on the player).

---

## Installation

To run this game, you will need:
- A C++ compiler (e.g., `g++`).
- **SFML** installed on your system. Follow the official [SFML installation guide](https://www.sfml-dev.org/tutorials/2.5/).

---

## Build and Run Instructions

Each chapter's source code is located in its respective folder (e.g., `Chapter_1`, `Chapter_2`, etc.). Use the following commands to compile and run the game for each chapter:

### General Steps:
1. Navigate to the `src` folder of the respective chapter:
   ```bash
   cd Chapter_<n>/src
   ```

2. Compile the code:
   ```bash
   c++ chapter<n>.cpp -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -o ../build/a.out
   ```

3. Navigate to the `build` folder:
   ```bash
   cd ../build
   ```

4. Run the game:
   ```bash
   ./a.out
   ```

### Example: Running Chapter 6
```bash
cd Chapter_6/src
c++ chapter6.cpp -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -o ../build/a.out
cd ../build
./a.out
```

---

## How to Play

- **Objective**: Chop wood as fast as you can while avoiding branches.
- **Controls**:
  - `Left Arrow` or `A`: Chop wood on the left side of the tree.
  - `Right Arrow` or `D`: Chop wood on the right side of the tree.

- **Scoring**: Gain points for each successful chop.
- **Game Over**: The game ends if a falling branch hits the player.

---

## Acknowledgments

This project was inspired by the book *Beginning C++ Game Programming* by John Horton. Special thanks to the authors of SFML for providing a powerful library for multimedia applications.

---

Happy Chopping!
