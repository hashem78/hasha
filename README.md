# What is hasha?

hasha is an interpreted weakly-typed with a (hopefully) regualr
syntax, intended as a pet project to keep me occupied in my free time.

# What can it do?

---
Currently? almost nothing, but I like to think that it might one be my
goto way to write pet projects.

# Features

---
At the begining I would like to support a small set of core features, 
and make sure these features are fully working then move on to more complex ones
like lambdas, classes and other modern language features.

- [x] Define variables.
- [ ] Expressions
  - [x] Calculation.
  - [x] Inline variables.
  - [ ] Support types other than int.
  - [ ] Generic expressions. 
- [ ] Types
  - [x] Default types (int,float,bool)
  - [ ] Generic types
    - [x] Parsing for '<>' syntax. 
- [ ] Looping
- [x] Functions.
- [x] Code blocks.
- [x] Scoping.
- [ ] Tests.

# Sytnax

---
name: `Naming rules of C`

var-decl: `name` `:` `type`

expression: `simple math expressions with +-*/` 

declaration: `var-decl` `=` `expression`

paramter-list: `list of` `var-decl` `seperated by ,`

statement: `declaration` or `expression` `;`

return-statement: `return` `statement`

block: `{` `list of` `statement` `optional return statement` `}` 

function: `fn` `name` `(parameter-list)` `return-type` `block`

condition: `expression with the result being a boolean`

if: `if` `condition` `block`

elif: `elif` `condition` `block`

else: `else` `block`

# Example
```
fn sum(a : int, b: int) -> int {
  return a + b;
}

fn main() -> int {
    x : int = 10;
    y : int = 10 + 2 * x;
    if true {
      z : int = 14 - sum(1,2);
    }
    return 0;
}
```

# Building from source

---
The project uses CMAKE as the build system, use your favorite C++ compiler with C++20 support,

Place a `source.hasha` file with the code you wish to run at `output` folder.

# Libraries included

---

[nlohmann::json](https://github.com/nlohmann/json)

[fmtlib](https://github.com/fmtlib/fmt)

[magic_enum](https://github.com/Neargye/magic_enum)