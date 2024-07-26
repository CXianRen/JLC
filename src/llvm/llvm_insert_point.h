#ifndef __LLVM_INSERT_POINT_H__
#define __LLVM_INSERT_POINT_H__

#include <vector>
#include <string>
#include <memory>
#include "llvm/llvm_inst.h"

namespace MLLVM
{

    template <typename T>
    class LLVM_Insertion_Point
    {
    public:
        LLVM_Insertion_Point()
        {
            parent_insertion_point = nullptr;
            label = "";
        }
        LLVM_Insertion_Point(
            std::shared_ptr<LLVM_Insertion_Point> parent,
            std::string label)
        {
            parent_insertion_point = parent;
            this->label = label;
        }

        ~LLVM_Insertion_Point()
        {
        }

        std::shared_ptr<LLVM_Insertion_Point> parent_insertion_point;
        std::string label;
        std::vector<T> instructions;

        void push_back(T instruction)
        {
            instructions.push_back(instruction);
        }

        // [] operator overloading
        T &operator[](int index)
        {
            return instructions[index];
        }
        // back() method
        T back()
        {
            return instructions.back();
        }

        // begin() method
        typename std::vector<T>::iterator begin()
        {
            return instructions.begin();
        }

        // end() method
        typename std::vector<T>::iterator end()
        {
            return instructions.end();
        }

        // size() method
        int size()
        {
            return instructions.size();
        }
    }; // class LLVM_Insertion_Point

} // namespace MLLVM

#endif // __LLVM_INSERT_POINT_H__