# Control flow
This doc describes the design of the following control flow features:
+ return 
+ if 
+ if else
+ while loop
+ for loop for arrays
+ logical operations short circuit
+ fully branch return check


## Return 
Generally, there are 3 types of return cases as listed above.
+ Return a specific type. 
+ Return void.
+ No return. 

It should also be noted that main function returns an int type. 


### Return a specific type.
<!-- a normal case -->
```c
int f(){
    return 1;
}
```

### Return void 
```c

void f(){
    return
}
```

### No return
Only void type function can omit the return statement.
```c
void f(){

}
```
### error cases
+ return unmatch type
```c
int f(){
    return false;
}
```
```shell
In Function f:
Function f return type bool is not the same as the expected return type int: 
        return false;
```

+ miss a return
```c
int f(){

}
```
```shell
ERROR, Type check error:
 Function f is not returned
```

+ main function return unmatch type
```c
void main(){
  
}
```
```shell
ERROR, Type check error:
 Main function must have return type INT
```


# if statement
it is easy to implement an 'if' statement, as it consists just two parts
+ A condition statment 
+ An 'if' body block

For the condition statement, it accepts any expression that returns a boolean type.

There are two cases.
```c
// case 1
if (true)
    a = 1;

// case 2
if (true){
    a =1;
}
```
An 'if' statement is followed by a new block or an expression. 
However, we can handle both cases in the same way by adding 
an extrac block for both cases to keep code consistent. 

```c
// code in AST 
// case 1
if (true){
    a = 1;
}
// case 2
if (true){
    {
    a =1;
    }
}
```
And when condition expression returns false, we also need an end lable to skip the if body. 
Additionally, the end of the if body will also requires a jump to the end block
(llvm grammar feature).

Thus the code above will be translated into:
```ll
; partial code.
; if(true ){
  br i1 1, label %cond_2, label %end_3
cond_2:
  ; a = 1;
  store i32 1, ptr %a1
  br label %end_3
  ; }
end_3:
  ; if(true ){
  br i1 1, label %cond_4, label %end_5
cond_4:
  ; a = 1;
  store i32 1, ptr %a1
  br label %end_5
  ; }
end_5:
```

# if-else statment

Similar handling process as that of the 'if' statement, just with an additional 'else' block. 

the translation of code
```c
if (true){
    a = 1;
}else{
    a= 0;
}
```
will be like:
```ll
; if(true ){
  br i1 1, label %cond_2, label %else_3
cond_2:
  ; a = 1;
  store i32 1, ptr %a1
  br label %end_4
  ; } else {
else_3:
  ; a = 0;
  store i32 0, ptr %a1
  br label %end_4
  ; }
end_4:

```

And for nested if-else statments, like 
```c
if (true){
    a = 1;
}else if (true){

}
```
It will actually be parsed as an 'if-else' statement followed by another 'if' statement. 
