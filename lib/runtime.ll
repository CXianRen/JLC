@dnl = internal constant [4 x i8] c"%d\0A\00"
@fnl = internal constant [6 x i8] c"%.1f\0A\00"
@d   = internal constant [3 x i8] c"%d\00"
@lf  = internal constant [4 x i8] c"%lf\00"

declare i32 @printf(i8*, ...)
declare i32 @scanf(i8*, ...)
declare i32 @puts(i8*)

define void @printInt(i32 %x) {
entry: %t0 = getelementptr [4 x i8], [4 x i8]* @dnl, i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %t0, i32 %x)
	ret void
}

define void @printDouble(double %x) {
entry: %t0 = getelementptr [6 x i8], [6 x i8]* @fnl, i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %t0, double %x)
	ret void
}

define void @printString(i8* %s) {
entry:  call i32 @puts(i8* %s)
	ret void
}

define i32 @readInt() {
entry:	%res = alloca i32
        %t1 = getelementptr [3 x i8], [3 x i8]* @d, i32 0, i32 0
	call i32 (i8*, ...) @scanf(i8* %t1, i32* %res)
	%t2 = load i32, i32* %res
	ret i32 %t2
}

define double @readDouble() {
entry:	%res = alloca double
        %t1 = getelementptr [4 x i8], [4 x i8]* @lf, i32 0, i32 0
	call i32 (i8*, ...) @scanf(i8* %t1, double* %res)
	%t2 = load double, double* %res
	ret double %t2
}

; declare calloc 
declare i8* @calloc(i32, i32)

; @todo :maybe provide createOneDimArray, createTwoDimArray, createThreeDimArry, for optimization
; create NDimensionalArray
define ptr @createNDimArray(i32* %dim_arr, i32 %dims, i32 %elem_size) {
entry:
	%t0 = icmp eq i32 %dims, 1
	br i1 %t0, label %if_then, label %if_else

; if (dims == 1)
if_then:
	; return calloc(dim_arr[0]*elem_size + 4 , 1) ; 4 is for the size of length field
	%t1 = getelementptr i32, i32* %dim_arr, i32 0
	%t2 = load i32, i32* %t1 ; dim_arr[0]
	%t3 = mul i32 %t2, %elem_size; dim_arr[0]*elem_size
	%t4 = add i32 %t3, 4 ; + 4
	
	%t5 = call i8* @calloc(i32 %t4, i32 1)
	; store length field
	%t6 = bitcast i8* %t5 to i32*
	store i32 %t2, i32* %t6

	;call void @printInt(i32 %t2); ; length

	ret ptr %t5

; else 
if_else:
	; void** array = (void**)calloc(dim_arr[0] * sizeof(void*) + 4, 1);
	%t7 = getelementptr i32, i32* %dim_arr, i32 0 ;
	%t8 = load i32, i32* %t7 ; dim_arr[0]
	; size = sizeof(ptr)
	%p = getelementptr ptr, ptr null, i32 1
	%s = ptrtoint ptr %p to i32
	; calloc 
	; total size = dim_arr[0]*sizeof(ptr) + 4
	%t9 = mul i32 %t8, %s ; dim_arr[0]*sizeof(ptr)
	%t10 = add i32 %t9, 4 ; + 4

	%t11 = call ptr @calloc(i32 %t10, i32 1) ; array = calloc(dim_arr[0]*sizeof(ptr) + 4, 1)

	; store length field
	;%t12 = bitcast i8* %t11 to i32*
	store i32 %t8, ptr %t11	
	; debug 
	;%ptrint = ptrtoint ptr %t12 to i32
	;call void @printInt(i32 %t8) ; length
	;call void @printInt(i32 %ptrint)
	;call void @printInt(i32 %t9)
	;call void @printInt(i32 %t10)
	br label %for_cond

; for (i = 0; i < dim_arr[0]; i++)
for_cond:
	%ti = phi i32 [ 0, %if_else ], [ %ti_new, %for_body ] ; i
	%t14 = icmp slt i32 %ti, %t8	; i < dim_arr[0]
	br i1 %t14, label %for_body, label %for_end 

for_body:
	%ti_new = add i32 %ti, 1 ; i++

	; array[i] = createNDimArray(dim_arr + 1, dims - 1, elem_size);
	%t16 = getelementptr i32, i32* %dim_arr, i32 1 ; dim_arr + 1
	
	;debug
	;%d = load i32, ptr %t16
	;call void @printInt(i32 %d)

	%tarr = getelementptr i32, ptr %t11, i32 1 ; + 4 offset
	%t17 = getelementptr ptr, ptr %tarr, i32 %ti ; array[i] 
	
	%t18 =  sub i32 %dims, 1 ; dims - 1
	;call void @printInt(i32 %t18) ; dims
	%t19 = call i8* @createNDimArray(i32* %t16, i32 %t18, i32 %elem_size)
	store ptr %t19, ptr %t17 ; array[i] = createNDimArray(dim_arr + 1, dims - 1, elem_size)

	br label %for_cond

for_end:
	ret ptr %t11
}


; @todo: similar above provide more specific api for better performance
; 