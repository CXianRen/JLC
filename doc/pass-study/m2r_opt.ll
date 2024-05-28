; ModuleID = 'test.ll'
source_filename = "JLC_llvm"

declare void @printDouble(double)

declare void @printInt(i32)

declare void @printString(ptr)

declare double @readDouble()

declare i32 @readInt()

declare ptr @createNDimArray(ptr, i32, i32)

define i32 @main() {
entry:
  %add = add i32 11, 15
  call void @printInt(i32 %add)
  ret i32 0
}
