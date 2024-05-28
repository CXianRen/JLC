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
  store i32 0, ptr %x, align 4
  %a = alloca i32, align 4
  store i32 1, ptr %a, align 4
  br label %while.cond

while.cond:                                       ; preds = %while.loop, %entry
  %a1 = load i32, ptr %a, align 4
  %le = icmp sle i32 %a1, 10
  br i1 %le, label %while.loop, label %while.end

while.loop:                                       ; preds = %while.cond
  %x2 = load i32, ptr %x, align 4
  %a3 = load i32, ptr %a, align 4
  %add = add i32 %x2, %a3
  store i32 %add, ptr %x, align 4
  %a4 = load i32, ptr %a, align 4
  %add5 = add i32 %a4, 1
  store i32 %add5, ptr %a, align 4
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %x6 = load i32, ptr %x, align 4
  call void @printInt(i32 %x6)
  ret i32 0
}
