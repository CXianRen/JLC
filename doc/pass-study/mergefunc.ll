; ModuleID = 'JLC_llvm'
source_filename = "JLC_llvm"

declare void @printDouble(double)

declare void @printInt(i32)

declare void @printString(ptr)

declare double @readDouble()

declare i32 @readInt()

declare ptr @createNDimArray(ptr, i32, i32)

define i32 @add(i32 %a, i32 %b) {
entry:
  %a1 = alloca i32, align 4
  store i32 %a, ptr %a1, align 4
  %b2 = alloca i32, align 4
  store i32 %b, ptr %b2, align 4
  %a3 = load i32, ptr %a1, align 4
  %b4 = load i32, ptr %b2, align 4
  %add = add i32 %a3, %b4
  ret i32 %add
}

define i32 @sum(i32 %x, i32 %y) {
entry:
  %x1 = alloca i32, align 4
  store i32 %x, ptr %x1, align 4
  %y2 = alloca i32, align 4
  store i32 %y, ptr %y2, align 4
  %x3 = load i32, ptr %x1, align 4
  %y4 = load i32, ptr %y2, align 4
  %add = add i32 %x3, %y4
  ret i32 %add
}

define i32 @main() {
entry:
  %add = call i32 @add(i32 3, i32 4)
  %result1 = alloca i32, align 4
  store i32 %add, ptr %result1, align 4
  %sum = call i32 @sum(i32 3, i32 4)
  %result2 = alloca i32, align 4
  store i32 %sum, ptr %result2, align 4
  %result11 = load i32, ptr %result1, align 4
  call void @printInt(i32 %result11)
  %result22 = load i32, ptr %result2, align 4
  call void @printInt(i32 %result22)
  ret i32 0
}
