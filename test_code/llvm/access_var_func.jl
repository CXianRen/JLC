typedef struct A_t{
    int a;
    int b;
  }* A;
  
  class B{
    int a;
    int b;
  }
  
  int f(){
    return 2;
  }
  
  int main(){
    int a;
    a = 1;
    int b = a;
    printInt(b);
    printString("hello");
    printString("world");
    printString("hello");
    printDouble(1.0);
    printInt(f());
    return 0;
  }