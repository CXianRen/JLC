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

  arr[0] = 1;

  printInt(arr[0]);
  printInt(arr[1]);
  printInt(arr.length);
 
  
  printInt(arr2[0].length);
  printInt(arr2[1].length);
  printInt(arr2.length);

  B[] b_arr = new B[10];
  b_arr[0] = new B;
  b_arr[0].a = 1;
  printInt(b_arr[0].a);
  printInt(b_arr.length);

  A[] a_arr = new A[7];
  a_arr[0] = new A_t;
  a_arr[0]->a = 2;
  printInt(a_arr[0]->a);
  printInt(a_arr.length);


  return 0;
}

