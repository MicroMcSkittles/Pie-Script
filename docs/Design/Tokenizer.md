# Tokenizer
The Tokenizer is the first step in processing source code.

[Back](../../README.md)

---

![Tokenizer Diagram](../MarkDownAssets/TokenizerDiagram.png)

The tokenizer takes in source code and creates a list of tokens. A example is shown above. These tokens then get passed into the [Parser](https://en.wikipedia.org/wiki/Lexical_analysis)

## Tokens
Tokens represent the source code in a way the [parser](./Parser.md) can understand. Tokens also store a index into the source code at where they start and end.

### Internal Representation
Tokens are represented as a struct with the following variables and types.

#### Variables
| Name          |  Type                 |  Description |
| :-------------| :-------------------: | ---: |
| type          | TokenType enum class  | stores the type of token |
| value         | String                | stores the internal value of token |
| debug_value   | String                | stores value for debuging and errors |
| start         | uint32_t              | stores index to start of token in source code |
| end           | uint32_t              | stores index to end of token in source code |

#### TokenType enum class
| Name |  Description |
| :--- | ---: |
| NumericLiteral | Number |
| StringLiteral | String |
| Identifier | The name of a variable, function, or struct |
| BinaryOperation | The operations mentioned in [Expressions](./Expressions.md) | 
| Equals | = | 
| OpenPeren | ( | 
| ClosePeren | ) | 
| Var | var keyword | 
