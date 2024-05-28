; ModuleID = '<stdin>'
source_filename = "JLC_llvm"

declare void @printDouble(double)

declare void @printInt(i32)

declare void @printString(ptr)

declare double @readDouble()

declare i32 @readInt()

declare ptr @createNDimArray(ptr, i32, i32)

define void @foo() {
entry:
  %add = add i32 10, 20
  ret void
}

define i32 @main() {
entry:
  call void @foo()
  ret i32 0
}
