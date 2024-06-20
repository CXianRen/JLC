#include "JLCLLVMGenerator.H"

#include "llvm/Support/raw_ostream.h"

#include "util.h"
/*
  this function is used to convert the type_enum to string
  @return: llvm::Type*
  @param: type_enum t
*/
llvm::Type *JLCLLVMGenerator::convertType(JLCType t)
{
	switch (t.type)
	{
	case INT:
		return llvm::Type::getInt32Ty(*LLVM_Context_);
	case DOUB:
		return llvm::Type::getDoubleTy(*LLVM_Context_);
	case BOOL:
		return llvm::Type::getInt1Ty(*LLVM_Context_);
	case VOID:
		return llvm::Type::getVoidTy(*LLVM_Context_);
	case CHAR:
		return llvm::Type::getInt8Ty(*LLVM_Context_);
	case STRING: // the atcually out is ptr not i8*, is it ok? @todo
		return llvm::Type::getInt8PtrTy(*LLVM_Context_);
	case ARRAY: // actual is ptr type, @todo: better design?
		return llvm::Type::getInt32PtrTy(*LLVM_Context_);
	default:
		std::cerr << "Error, Unknown type:" << to_string(t) << std::endl;
		exit(1);
	}
}

void JLCLLVMGenerator::addExternalFunc()
{
	for (auto &func : globalContext.funcs)
	{
		addFuncDeclearation(func.second);
	}
	// adding calloc function declearation

	// @todo: when pointer type is support we can use "addFuncDeclearation"
	std::vector<llvm::Type *> createNDimArray_args;
	createNDimArray_args.push_back(llvm::Type::getInt32PtrTy(*LLVM_Context_)); // dim_array
	createNDimArray_args.push_back(llvm::Type::getInt32Ty(*LLVM_Context_));	   // dim_array_size
	createNDimArray_args.push_back(llvm::Type::getInt32Ty(*LLVM_Context_));	   // element size

	auto createNDimArray_type = llvm::FunctionType::get(
		llvm::Type::getInt8PtrTy(*LLVM_Context_), createNDimArray_args, false);
	auto createNDimArray_func = llvm::Function::Create(
		createNDimArray_type,
		llvm::Function::ExternalLinkage,
		"createNDimArray",
		LLVM_module_.get());

	(void)createNDimArray_func; // make compiler happy

	// add ptr @getElement_N_ptr(ptr %array, i32 * %idx_arr, i32 %idx_count ,i32 %max_dim , i32 %elem_size)
	// std::vector<llvm::Type*> getElementNPtr_args;
	// getElementNPtr_args.push_back(llvm::Type::getInt8PtrTy(*LLVM_Context_)); // array
	// getElementNPtr_args.push_back(llvm::Type::getInt32PtrTy(*LLVM_Context_)); // idx_arr
	// getElementNPtr_args.push_back(llvm::Type::getInt32Ty(*LLVM_Context_)); // idx_count
	// getElementNPtr_args.push_back(llvm::Type::getInt32Ty(*LLVM_Context_)); // max_dim
	// getElementNPtr_args.push_back(llvm::Type::getInt32Ty(*LLVM_Context_)); // elem_size

	// auto getElementNPtr_type = llvm::FunctionType::get(
	//     llvm::Type::getInt8PtrTy(*LLVM_Context_), getElementNPtr_args, false);
	// auto getElementNPtr_func = llvm::Function::Create(
	//     getElementNPtr_type,
	//     llvm::Function::ExternalLinkage,
	//     "getElement_N_ptr",
	//     LLVM_module_.get());
}

void JLCLLVMGenerator::addFuncDeclearation(JLCFunc &frame)
{
	// see the tutorial about llvm:
	std::string func_name = frame.name;
	auto llvm_return_type = convertType(frame.returnType);
	std::vector<llvm::Type *> llvm_args;
	for (auto &arg : frame.args)
	{
		llvm_args.push_back(convertType(arg.second));
	}
	llvm::FunctionType *func_type =
		llvm::FunctionType::get(llvm_return_type, llvm_args, false);
	auto func_dec = llvm::Function::Create(
		func_type,
		llvm::Function::ExternalLinkage,
		func_name,
		LLVM_module_.get());

	std::string ss;
	llvm::raw_string_ostream ss2(ss);
	func_dec->print(ss2);
	DEBUG_PRINT("Add function declearation: " + ss);
}