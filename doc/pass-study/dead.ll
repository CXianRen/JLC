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
  %x = alloca i32, align 4
  store i32 5, ptr %x, align 4
  %y = alloca i32, align 4
  store i32 10, ptr %y, align 4
  %z = alloca i32, align 4
  store i32 15, ptr %z, align 4
  %a = alloca i32, align 4
  store i32 20, ptr %a, align 4
  %z1 = load i32, ptr %z, align 4
  %a2 = load i32, ptr %a, align 4
  %add = add i32 %z1, %a2
  store i32 %add, ptr %z, align 4
  %x3 = load i32, ptr %x, align 4
  %y4 = load i32, ptr %y, align 4
  %add5 = add i32 %x3, %y4
  %result = alloca i32, align 4
  store i32 %add5, ptr %result, align 4
  %result6 = load i32, ptr %result, align 4
  call void @printInt(i32 %result6)
  ret i32 0
}
