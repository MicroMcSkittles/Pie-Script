## Expressions
---
Expressions represent values such as numbers, bools, and strings.
[Back](../../README.md)

When creating Pie Script I thought of what the most important part of a programming language is. This is why I started with expressions which are used every were from variables to functions to conditions.


### Numeric Expressions

| Supported symbols     | Name              |
| :------:              | ------:           |
| +                     | Addition          |
| -                     | Subtraction       |
| *                     | Multiplication    |
| /                     | Division          |
| &                     | And               |
| &#124;                | Or                |
| %                     | Modulus           |
| ^                     | Exponent          |
| !                     | Factorial         |

These operations can only be used with numeric values. Most operations require two numbers except for the factorial and subtract operations. The subtract operation can be placed behind a numeric value to show that it's negative or used to subtract to numbers. The factorial operation can be placed after a numaric value to find it's factorial.

It is important to note that numaric expressions don't
need to use operations.

#### Examples
The following shows examples of Numeric Expressions

``` Python
10 + 2 * (3 / 4) - 2
20!
10^2
```

### Boolean Expressions

| Supported symbols     | Name                  |
| :------:              | ------:               |
| &&                    | And                   |
| &#124;&#124;          | Or                    |
| ==                    | Equal                 |
| !=                    | Not Equal             |
| >                     | Greater than          |
| <                     | Less that             |
| >=                    | Greater Than or Equal |
| <=                    | Less Than or Equal    |

All of these operations require two values to functions. Boolean operation can use both boolean values and numaric values. Boolean operations only return boolean values. If a numaric value is compairedto a boolean value with a boolean operation then the numaric value will be converted to a boolean value based on if the numaric value is grater than zero. Ex: 0 = false, 3 = true, 10 = true

Boolean expressions can be represented as the key words `True` or `False`.

#### Examples
The following shows examples of Boolean Expressions

``` Python
True
False

4 > 1
10 != 2
11 == 11
```

### String Expression

| Supported symbols     | Name                  |
| :------:              | ------:               |
| +                     | Addition              |

A string needs to be the left value to use the add operation. Adding a string to a string combinesthe strings into one new string. Adding a number to the string puts the number on the end of the string. Adding a boolean to the string puts ether true or false of the end of the string based on the boolean.

#### Examples
The following shows examples of String Expressions

``` Python
"Hello, World"
"Hello," + " World"
"Number: " + 1234
"Boolean: " + True
```

### Internal Representation
Each expression and operation of expressions will be represented as a node on the [Abstract Syntax Tree](./AST.md)