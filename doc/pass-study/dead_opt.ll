; ModuleID = '<stdin>'
source_filename = "JLC_llvm"

declare void @printDouble(double)

declare void @printInt(i32)

declare void @printString(ptr)

declare double @readDouble()

declare i32 @readInt()

declare ptr @createNDimArray(ptr, i32, i32)

define i32 @main() {
entry:
  %add = add i32 15, 20
  %add5 = add i32 5, 10
  call void @printInt(i32 %add5)
  ret i32 0
}
