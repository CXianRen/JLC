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
define ptr @gen_nda(ptr %dim_arr, i32 %dims, i32 %elem_size) {
entry:
	%da_0a = getelementptr i32, ptr %dim_arr, i32 0	; get dim_arr[0] address
	%da_0 = load i32, ptr %da_0a 					; dim_arr[0]
	%t0 = icmp eq i32 %dims, 1
	br i1 %t0, label %if_then, label %if_else

if_then:											; if (dims == 1)
													;    return calloc(dim_arr[0]*elem_size + 4 , 1)   
													; 4 is for the size of length field

	%t3 = mul i32 %da_0, %elem_size					; dim_arr[0]*elem_size
	%t4 = add i32 %t3, 4 							; + 4
	%t5 = call ptr @calloc(i32 %t4, i32 1)		
	store i32 %da_0, ptr %t5						; store length field
	ret ptr %t5

if_else:											; else 
													;    void** array = 
													;    (void**)calloc(dim_arr[0] * sizeof(void*) + 4, 1);				
	%p = getelementptr ptr, ptr null, i32 1			; size = sizeof(ptr)
	%s = ptrtoint ptr %p to i32

	%t9 = mul i32 %da_0, %s 							; dim_arr[0]*sizeof(ptr)
	%t10 = add i32 %t9, 4 							; + 4

	%t11 = call ptr @calloc(i32 %t10, i32 1) 		; array = calloc(size, 1)

	store i32 %da_0, ptr %t11						; store length field
	br label %for_cond

; for (i = 0; i < dim_arr[0]; i++)
for_cond:
	%ti = phi i32 [ 0, %if_else ], [ %ti_new, %for_body ] 		; i
	%t14 = icmp slt i32 %ti, %da_0						  		; i < dim_arr[0]
	br i1 %t14, label %for_body, label %for_end 

for_body:											; to generate next dimension
	%ti_new = add i32 %ti, 1 							  		; i++

	%t16 = getelementptr i32, ptr %dim_arr, i32 1 				; dim_arr + 1
	
	%tarr = getelementptr i32, ptr %t11, i32 1					; + 4 offset
	%t17 = getelementptr ptr, ptr %tarr, i32 %ti 				; array[i] 
	
	%t18 =  sub i32 %dims, 1 									; dims - 1

	%t19 = call ptr @gen_nda(ptr %t16, i32 %t18, i32 %elem_size)
	store ptr %t19, ptr %t17 	; array[i] = gen_nda(dim_arr + 1, dims - 1, elem_size)

	br label %for_cond

for_end:
	ret ptr %t11
}
