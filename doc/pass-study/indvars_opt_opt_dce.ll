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
  br label %while.end

while.end:                                        ; preds = %entry
  call void @printInt(i32 55)
  ret i32 0
}
