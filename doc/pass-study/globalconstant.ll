; ModuleID = 'JLC_llvm'
source_filename = "JLC_llvm"

@str0 = private constant [14 x i8] c"Hello, LLVM!\0A\00"

declare void @printDouble(double)

declare void @printInt(i32)

declare void @printString(ptr)

declare double @readDouble()

declare i32 @readInt()

declare ptr @createNDimArray(ptr, i32, i32)

define void @printMessage1() {
entry:
  call void @printString(ptr @str0)
  ret void
}

define void @printMessage2() {
entry:
  call void @printString(ptr @str0)
  ret void
}

define i32 @main() {
entry:
  call void @printMessage1()
  call void @printMessage2()
  ret i32 0
}
