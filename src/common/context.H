#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include <map>
#include <string>
#include <vector>
#include <memory>

enum op_enum
{
	eADD,
	eSUB,
	eMUL,
	eDIV,
	eMOD,
	eLT,
	eLE,
	eGT,
	eGE,
	eEQ,
	eNE
};

enum type_enum
{
	INT = 0,
	DOUB,
	BOOL,
	VOID,
	FUN,
	CHAR,
	STRING,
	ARRAY,
	UNDEFINED
};
std::string to_string(type_enum t);

class JLCType
{
public:
	type_enum type;
	// for array
	type_enum base_type;
	int dimension; // dimension of the array

	JLCType(type_enum type, type_enum base_type = UNDEFINED, int dimension = 0)
		: type(type), base_type(base_type), dimension(dimension) {}
	JLCType() = default;
	~JLCType() = default;
	// reload operator ==
	bool operator==(const JLCType &t) const;

	bool operator==(const type_enum &t) const
	{
		return type == t;
	}

	bool operator!=(const JLCType &t) const
	{
		return !(*this == t);
	}

	bool operator!=(const type_enum &t) const
	{
		return type != t;
	}
};

std::string to_string(const JLCType &t);

// for each parameter, declared JLCVARiable, we create a new JLCVAR object
class JLCVAR
{
public:
	JLCVAR() = default;
	~JLCVAR() = default;
	std::string name;
	JLCType type;
};

// for each block, we create a new JLCBLK object
// a block is a sequence of statements
// a block can contain other blocks
// most of time a block mean a new scope, at least in "javalette"
class JLCBLK
{
public:
	JLCBLK() = default;
	JLCBLK(JLCBLK *parent) : parent(parent) {}

	~JLCBLK() = default;
	std::map<std::string, JLCVAR> JLCVariables; // map of JLCVariables
	JLCBLK *parent = nullptr;					// parent block

	void addVar(const std::string &name, JLCType type)
	{
		JLCVAR JLCVARiable;
		JLCVARiable.name = name;
		JLCVARiable.type = type;
		JLCVariables[name] = JLCVARiable;
	}

	bool isExistVar(const std::string &name)
	{
		return JLCVariables.find(name) != JLCVariables.end();
	}
};

// when there is a new fuction, we create a new frame
class JLCFunc
{
public:
	JLCFunc() = default;
	JLCFunc(std::string name) : name(name), returnType() {}
	~JLCFunc() = default;
	std::string name;								   // name of the function
	JLCType returnType;								   // return type of the function
	std::vector<std::pair<std::string, JLCType>> args; // save the arguments of the function

	JLCBLK *blk = nullptr; // block of the function

	// chcek if the argument is declared
	bool isExistArg(const std::string &name);

	void addArg(const std::string &name, JLCType type)
	{
		args.push_back(std::make_pair(name, type));
	}

	void newBlock()
	{
		blk = new JLCBLK(blk);
	}

	void releaseBlock()
	{
		JLCBLK *temp = blk;
		blk = blk->parent;
		delete temp;
	}

	bool isExistVar(const std::string &name);

	void addVar(const std::string &name, JLCType type)
	{

		blk->addVar(name, type);
	}

	JLCType getVarType(const std::string &name);
};

// JLCContext is a class that holds the current state of the program.
class JLCContext
{
public:
	JLCContext();

	~JLCContext() = default;
	std::map<std::string, JLCFunc> funcs;

	std::string currentFuncName;

	JLCFunc &currentFunc()
	{
		return funcs[currentFuncName];
	}

	void addFunc(const std::string &name)
	{
		JLCFunc frame(name);
		funcs[name] = frame;
	}
	JLCFunc &getFunc(const std::string &name)
	{
		return funcs[name];
	}

	bool isExistFunc(const std::string &name)
	{
		return funcs.find(name) != funcs.end();
	}
};

#endif