# AyoCalc
A calculator repl that uses Polish notation

# How to use

- Clone repo
- run `gcc parsing.c mpc-0.9.0/mpc.c -ledit -lm -o parsing && ./parsing` in terminal
- enter equation and press enter

# Polish Notation
- 1 + 2 + 6	is	`+ 1 2 6`
- 6 + (2 * 9)	is	`+ 6 (* 2 9)`
- (10 * 2) / (4 + 2)	is	`/ (* 10 2) (+ 4 2)`

# Libraries + Credits
- [Micro Parser Combinators](https://github.com/orangeduck/mpc) for parser
- Code mainly from www.buildyourownlist.com (at the moment!)
