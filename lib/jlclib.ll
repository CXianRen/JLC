; JLC inner functions for array
; it may be inlined by LLVM
; for boolean array

%bool_array = type { i32, [0 x i32] }
%int_array = type { i32, [0 x i32] }
%double_array = type { i32, [0 x double] }
%ptr_array = type { i32, [0 x ptr] }

define i1* @get_Bool_element_ptr(%bool_array* %array, i32 %index) {
entry:
	%t0 = getelementptr %bool_array, %bool_array* %array, i32 0, i32 1, i32 %index
	ret i1* %t0
}

define i32* @get_Int_element_ptr(%int_array* %array, i32 %index) {
entry:
	%t0 = getelementptr %int_array, %int_array* %array, i32 0, i32 1, i32 %index
	ret i32* %t0
}

define ptr @get_Ptr_element_ptr(%ptr_array* %array, i32 %index) {
entry:
	%t0 = getelementptr %ptr_array, %ptr_array* %array, i32 0, i32 1, i32 %index
	ret ptr %t0
}