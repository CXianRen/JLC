# step:
+ 1. scan all topdefines' (enum, struct, typedef, class, function)
  decleration and save them into context

+ 2. scan all topdefines' definition.

+ 3. the functions decleartion should be checked after other topdefinition because their return type and parameters's type might 
depende on context.

# how to handle class member and member function:
+ rename the function for different classes 
  to avoid functions having a same name

+ using "this" pointer as that in cpp as the first parameter 
  passing to a member function

+ using virtual table to implement runtime polymorphism!