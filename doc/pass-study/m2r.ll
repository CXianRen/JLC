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
  %c1 = alloca i32, align 4
  store i32 11, ptr %c1, align 4
  %c2 = alloca i32, align 4
  store i32 15, ptr %c2, align 4
  %c11 = load i32, ptr %c1, align 4
  %c22 = load i32, ptr %c2, align 4
  %add = add i32 %c11, %c22
  %c3 = alloca i32, align 4
  store i32 %add, ptr %c3, align 4
  %c33 = load i32, ptr %c3, align 4
  call void @printInt(i32 %c33)
  ret i32 0
}
