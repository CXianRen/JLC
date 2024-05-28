; ModuleID = 'JLC_llvm'
source_filename = "JLC_llvm"

declare void @printDouble(double)

declare void @printInt(i32)

declare void @printString(ptr)

declare double @readDouble()

declare i32 @readInt()

declare ptr @createNDimArray(ptr, i32, i32)

define i32 @main() {
entry:
  %a = alloca i32, align 4
  store i32 1, ptr %a, align 4
  %dim_array = alloca [1 x i32], align 4
  %dim_ptr = getelementptr i32, ptr %dim_array, i32 0
  store i32 100, ptr %dim_ptr, align 4
  %temp_array = call ptr @createNDimArray(ptr %dim_array, i32 1, i32 ptrtoint (ptr getelementptr (i32, ptr null, i32 1) to i32))
  %arr = alloca ptr, align 8
  store ptr %temp_array, ptr %arr, align 8
  br label %while.cond

while.cond:                                       ; preds = %while.loop, %entry
  %a1 = load i32, ptr %a, align 4
  %le = icmp sle i32 %a1, 100
  br i1 %le, label %while.loop, label %while.end

while.loop:                                       ; preds = %while.cond
  %arr2 = load ptr, ptr %arr, align 8
  %a3 = load i32, ptr %a, align 4
  %ptr = getelementptr i32, ptr %arr2, i32 1
  %e_ptr = getelementptr i32, ptr %ptr, i32 %a3
  %arr_e = load i32, ptr %e_ptr, align 4
  %a4 = load i32, ptr %a, align 4
  store i32 %a4, ptr %e_ptr, align 4
  %a5 = load i32, ptr %a, align 4
  %add = add i32 %a5, 1
  store i32 %add, ptr %a, align 4
  br label %while.cond

while.end:                                        ; preds = %while.cond
  ret i32 0
}
