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
  br label %while.cond

while.cond:                                       ; preds = %while.loop, %entry
  %a.0 = phi i32 [ 1, %entry ], [ %add5, %while.loop ]
  %x.0 = phi i32 [ 0, %entry ], [ %add, %while.loop ]
  %le = icmp sle i32 %a.0, 10
  br i1 %le, label %while.loop, label %while.end

while.loop:                                       ; preds = %while.cond
  %add = add i32 %x.0, %a.0
  %add5 = add i32 %a.0, 1
  br label %while.cond

while.end:                                        ; preds = %while.cond
  call void @printInt(i32 %x.0)
  ret i32 0
}
