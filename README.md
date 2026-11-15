# Scientific Calculator Using C and WebAssembly

## Project Overview
A scientific calculator developed as a C programming lab project. It provides a web-based interface while performing mathematical calculations using functions written in the C programming language.

## Technologies Used
- C – Core mathematical operations and calculation logic.
- HTML – Calculator structure.
- CSS – Calculator styling.
- JavaScript – User interface interaction and expression handling.
- WebAssembly (WASM) – Connects the C functions to the browser.
- Git and GitHub – Version control and team collaboration.
- Emscripten – Compiles C code into WebAssembly.

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
│
└── public/
    ├── index.html
    ├── style.css
    ├── script.js
    ├── calculator.js
    └── calculator.wasm
```

## How to Run the Calculator

The compiled WebAssembly files are already included.

You do not need to install a C compiler or Emscripten to run the website.

1. Install Python 3 if it is not already installed.
2. Open the project folder in a terminal.
3. Enter the public directory:

```bash
cd public
```

4. Start the local server:

```bash
python -m http.server 8000
```

5. Open a browser and visit:

```text
http://localhost:8000
```

The calculator will be ready to use.

## How It Works

The mathematical operations are implemented in C using `basic.c` and `scientific.c`.

Emscripten compiles these C files into WebAssembly.

The generated `calculator.js` and `calculator.wasm` files allow the browser-based JavaScript interface to call the C functions.

Therefore, the website uses C for its actual mathematical calculations.

## Team Project

Developed as a collaborative C programming laboratory project using GitHub for version control.