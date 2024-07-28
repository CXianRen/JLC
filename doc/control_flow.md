# Control flow
This doc describes the design of the following control flow features:
+ return 
+ if 
+ if else
+ while loop
+ for loop for arrays


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