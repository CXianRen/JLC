typedef struct A_t{
  int a;
  int b;
}* A;

class B{
  int a;
  int b;
}

enum C{
  A,
  B,
  C
};

int main(){
  B b = new B;
  b.a = 1;
  b.b = 2;
  printInt(b.a);
  printInt(b.b);

  int[] arr = new int[10];
  printInt(arr.length);
  int[][] arr2 = new int[5][10];
  printInt(arr2.length);


  C c = C.A;
  printInt((int)c);

  A a = new A_t;
  a->a = 1;
  a->b = 2;
  printInt(a->b);
  a->a = 3;
  printInt(a->a);


  return 0;
}