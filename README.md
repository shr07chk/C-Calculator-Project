# Scientific Calculator Using C and WebAssembly

## Project Overview

A scientific calculator developed as a C programming laboratory project. It provides a web-based interface while performing mathematical calculations using functions implemented in the C programming language.

## Technologies Used

- **C** – Core mathematical operations and calculation logic.
- **HTML** – Calculator structure.
- **CSS** – Calculator styling.
- **JavaScript** – User interface interaction and expression handling.
- **WebAssembly (WASM)** – Connects C functions to the browser.
- **Emscripten** – Compiles C code into WebAssembly.
- **Git and GitHub** – Version control and team collaboration.
- **GitHub Actions** – Automatically builds the WebAssembly files.

## Features

### Basic Operations
- Addition
- Subtraction
- Multiplication
- Division
- Power
- Modulus

### Scientific Operations
- Trigonometric functions
- Inverse trigonometric functions
- Hyperbolic functions
- Square root and cube root
- Square and cube
- Factorial
- Logarithm and natural logarithm
- Exponential
- Absolute value
- Reciprocal
- Percentage
- Pi and Euler's number

### Additional Features
- Degree and radian modes
- Calculation history
- Keyboard input
- Error handling
- Clear and delete functions

## Project Structure

```text
C-Calculator-Project/
│
├── .github/
│   └── workflows/
│       └── build-wasm.yml
│
├── calculator.h
├── basic.c
├── scientific.c
├── main.c
├── README.md
│
└── public/
    ├── index.html
    ├── style.css
    ├── script.js
    ├── calculator.js
    └── calculator.wasm
```

## How to Run the Web Calculator

The compiled WebAssembly files are already included in the project.

You do not need to install a C compiler or Emscripten to run the website.

### Requirements
- Python 3
- A modern web browser

### Steps

1. Open the project folder in VS Code.
2. Open the terminal.
3. Navigate to the `public` directory:

```bash
cd public
```

4. Start the local server:

```bash
python -m http.server 8000
```

5. Open your browser and visit:

```text
http://localhost:8000
```

The calculator will be ready to use.

## How It Works

1. Mathematical operations are implemented in C using `basic.c` and `scientific.c`.
2. Emscripten compiles these C files into WebAssembly.
3. The generated `calculator.js` and `calculator.wasm` files connect the C functions to the browser.
4. The JavaScript interface calls the C functions whenever the user performs a calculation.

Therefore, the actual mathematical calculations are performed using C, while JavaScript handles the website interface and user interaction.

## Automated Build

The project includes a GitHub Actions workflow located in `.github/workflows/build-wasm.yml`.

Whenever changes are pushed to the main branch, GitHub Actions can automatically compile the C files into WebAssembly.

## Standalone C Program

The project also includes `main.c`, which provides a menu-driven version of the calculator that can be executed in a terminal using a C compiler.

## Team Project

Developed collaboratively as a C programming laboratory project using GitHub for version control and team collaboration.