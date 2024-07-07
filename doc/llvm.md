# define a struct

```llvm
%Mystruct = type {i32, float}
```

# allocate a struct 

```llvm
%myStruct = alloca %mystruct
```

# access struct field 

```
; i32
%field1_ptr = getelementptr %Mystruct, ptr %myStruct, i32 0, i32 0 
store i32 1, ptr %field1_ptr

; float 
%field2_ptr = getelementptr %Mystruct, ptr %myStruct, i32 0, i32 1 
store float 1, ptr %field2_ptr
```
