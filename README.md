# Javalette Compiler

# For test
we don't use git submodule here, just clone: https://github.com/TDA283-compiler-construction/project.git

```
# for just parsing and type checking.
python3 testing.py path/to/submission 
```


# FRONT END
+ If you considering running BNFC to regenerate the parser, take a moment to consider: do you really need to do so, and why?

+ For further details on the front-end basic code generated by BNFC: https://bnfc.digitalgrammars.com/


+ why do we seperate the checker into N checkers: for example, case good/core002.jl, all called functions in main function are defined after the main, then in the tree, those nodes will be visted only after the main node is visted. (making things complex if we check everything using a single vistor (checker), even if we save the context.)

# TODO 
- [x] bad003: func declearation check
- [x] bad064: func declearation check
- [x] bad072: func declearation check

- [x] bad017: called func parameter check
- [x] bad016: called func parameter check
- [x] bad015: called func parameter check
- [x] bad019: called func parameter check
- [x] bad018: called func parameter check

- [x] bad022: invalid operation
- [x] bad023: invalid operation

- [x] bad026: invalid operation

<!-- op -->
- [x] bad052: invalid operation
- [x] bad053: invalid operation
- [x] bad054: invalid operation
- [x] bad055: invalid operation
- [x] bad056: invalid operation
- [x] bad070: invalid operation
- [x] bad013: invalid operation


- [x] bad027: invalid operation
- [x] bad009: invalid operation

<!-- func -->
- [x] bad073: invalid operation


- [x] bad006: access variable before decleration
- [x] bad059: access variable before decleration
- [x] bad060: access variable

- [x] bad007: variable declearation
- [x] bad074: variable declearation
- [x] bad063: variable declearation

- [x] bad020: Compare double with boolean

- [x] bad035: while(b) return 0; 
- [x] bad021: invalid return
- [x] bad069: return check
- [x] bad068: return check

- [x] bad033: same as bad035
- [x] bad025: return check
- [x] bad032: return check
- [x] bad008: return check
- [x] bad031: return check
- [x] bad067: return check
- [x] bad065: return check
- [x] bad011: return check
- [x] bad029: return check
- [x] bad071: return check
- [x] bad058: return check
- [x] bad010: return check
- [x] bad012: return check


# LLVM Backend
- [x] variable definition and initialization
- [x] sting
- [x] add basic operation
  - [x] add, sub
  - [x] mul, mod, div
  - [x] Neg
  - [x] Not ?@TODO, have to double check the result. 
  - [x] Incre, Decre
  - [x] logic op
    - [x] others 
    - [x] and , or : short-circui evaluation @TODO
- [x] add function call
- [x] add return 
  - [x] return
  - [x] void return
- [x] if, if/else, while
  - [x] if
  - [x] if else
  - [x] while

- [x] add debug script to generate linked bc file

# QA:

## undefined operation: 
- [ ] printInt(x++);
- [x] what about variable name is same as a function name -> see core020.jl

- [x] Short-circui evaluation:
```c
int main () {
  int a =1,b =2;
  if(a<0 && b>0){
    a = 1;
  }
}
```