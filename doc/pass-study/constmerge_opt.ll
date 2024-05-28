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
  call void @printInt(i32 26)
  ret i32 0
}
