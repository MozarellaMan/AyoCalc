# AyoCalc

A calculator repl that uses Polish notation. This implementation is from the book [Build Your Own Lisp](www.buildyourownlisp.com). My version has the following added features:

- double precision floating point values
- min operator
- max operator
- % operator
- negation with `-`
- more to come...

## How to use

- Clone repo
- run `clear && gcc parsing.c mpc-0.9.0/mpc.c -ledit -lm -o parsing && ./parsing` in terminal
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
- www.buildyourownlisp.com
