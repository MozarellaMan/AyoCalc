# AyoCalc

A calculator repl that uses Polish notation.

## How to use

- Clone repo
- run `gcc parsing.c mpc-0.9.0/mpc.c -ledit -lm -o parsing && ./parsing` in terminal
- enter equation and press enter

### Dependencies

- gcc (mingw or WSL if you are on windows)
- editline (OSX and Linux)

## Polish Notation

- `1 + 2 + 6`  is `+ 1 2 6`
- `6 + (2 * 9)`	is `+ 6 (* 2 9)`
- `(10 * 2) / (4 + 2)` is `/ (* 10 2) (+ 4 2)`

## Libraries + Credits

- [Micro Parser Combinators](https://github.com/orangeduck/mpc) for parser
- Code mainly from www.buildyourownlisp.com (at the moment!)
