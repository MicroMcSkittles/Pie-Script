# Abstract Syntax Tree
A abstract syntax tree represents the program in the form of a tree see ([Abstract Syntax Tree](https://en.wikipedia.org/wiki/Abstract_syntax_tree)) for more information.
[Back](../../README.md)

---

## Implementation
The AST nodes will be implemented with a programming technique called [Object Oriented Programming](https://en.wikipedia.org/wiki/Object-oriented_programming).

## Nodes
The folowing is all nodes their use and their variables.

### Statements
Every node is a statement but statements mostly refer to nodes that don't return a value.

#### Program
Program statements hold a list of Statements. They are used to contain the program and body statements, which are used in other statements like functions and if statements.

### Expressions
Expressions fall under statements but expression nodes return a value.

#### NumericLiteral

W.I.P.