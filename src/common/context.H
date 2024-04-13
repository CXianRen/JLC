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

class JLCType{
public:
	type_enum type;
	// for array
	type_enum base_type;
	int brackets_count; // dimension of the array

	JLCType(type_enum type, type_enum base_type = UNDEFINED, int brackets_count = 0)
		: type(type), base_type(base_type), brackets_count(brackets_count) {}
	JLCType() = default;
	~JLCType() = default;
	// reload operator ==
	bool operator==(const JLCType &t) const;
	bool operator==(const type_enum &t) const { 
		return type == t; 
	}
	bool operator!=(const JLCType &t) const { 
		return !(*this == t); 
	}
	
	bool operator!=(const type_enum &t) const { 
		return type != t; 
	}
	

	// copy constructor
	//JLCType(const JLCType &t) : 
	//	type(t.type), base_type(t.base_type), 
	//	brackets_count(t.brackets_count) {}

};
std::string to_string(const JLCType & t);

// for each parameter, declared CVARiable, we create a new CVAR object
class CVAR
{
public:
	CVAR() = default;
	~CVAR() = default;
	std::string name;
	JLCType type;
};

// for each block, we create a new CBlk object
// a block is a sequence of statements
// a block can contain other blocks
// most of time a block mean a new scope, at least in "javalette"
class CBlk
{
public:
	CBlk() = default;
	CBlk(CBlk *parent) : parent(parent) {}

	~CBlk() = default;
	std::map<std::string, CVAR> CVARiables; // map of CVARiables
	CBlk *parent = nullptr;					// parent block

	// base_type and brackets_count are used for array
	void addVar(const std::string &name, JLCType type)
	{
		CVAR CVARiable;
		CVARiable.name = name;
		CVARiable.type = type;
		CVARiables[name] = CVARiable;
	}

	bool isExistVar(const std::string &name)
	{
		return CVARiables.find(name) != CVARiables.end();
	}
};

// when there is a new fuction, we create a new frame
class Frame
{
public:
	Frame() = default;
	Frame(std::string name) : name(name), returnType() {}
	~Frame() = default;
	std::string name;									 // name of the function
	JLCType returnType;								 // return type of the function
	std::vector<std::pair<std::string, JLCType>> args; // save the arguments of the function

	CBlk *blk = nullptr; // block of the function

	// chcek if the argument is declared
	bool isExistArg(const std::string &name);

	void addArg(const std::string &name, JLCType type)
	{
		args.push_back(std::make_pair(name, type));
	}

	void newBlock()
	{
		blk = new CBlk(blk);
	}

	void releaseBlock()
	{
		CBlk *temp = blk;
		blk = blk->parent;
		delete temp;
	}

	void addVar(const std::string &name, JLCType type)
	{

		blk->addVar(name, type);
	}


	bool isExistVar(const std::string &name)
	{
		CBlk *temp = blk;
		while (temp)
		{
			if (temp->isExistVar(name))
			{
				return true;
			}
			temp = temp->parent;
		}
		// check if in the arguments
		for (const auto &arg : args)
		{
			if (arg.first == name)
			{
				return true;
			}
		}
		return false;
	}

	JLCType getVarType(const std::string &name)
	{
		CBlk *temp = blk;
		while (temp)
		{
			if (temp->isExistVar(name))
			{
				return temp->CVARiables[name].type;
			}
			temp = temp->parent;
		}
		// check if in the arguments
		for (const auto &arg : args)
		{
			if (arg.first == name)
			{
				return arg.second;
			}
		}
		return JLCType(UNDEFINED);
	}	
};

// Context is a class that holds the current state of the program.
class Context
{
public:
	Context(){
		// internal functions
		{
			addFrame("printInt");
			auto &frame = getFrame("printInt");
			frame.returnType = JLCType(VOID);
			frame.addArg("a", JLCType(INT));
		}
		{
			addFrame("printDouble");
			auto &frame = getFrame("printDouble");
			frame.returnType = JLCType(VOID);
			frame.addArg("a", JLCType(DOUB));
		}
		{
			addFrame("printString");
			auto &frame = getFrame("printString");
			frame.returnType = JLCType(VOID);
			frame.addArg("a", JLCType(STRING));
		}
		{
			addFrame("readInt");
			auto &frame = getFrame("readInt");
			frame.returnType = JLCType(INT);
		}
		{
			addFrame("readDouble");
			auto &frame = getFrame("readDouble");
			frame.returnType = JLCType(DOUB);
		}
}

~Context() = default;
std::map<std::string, Frame> funcs;
// rules for checking the function

std::string currentFrameName;

Frame &currentFrame()
{
	return funcs[currentFrameName];
}

void addFrame(const std::string &name)
{
	Frame frame(name);
	funcs[name] = frame;
}
Frame &getFrame(const std::string &name)
{
	return funcs[name];
}

bool isExistFunction(const std::string &name)
{
	return funcs.find(name) != funcs.end();
}
};

#endif