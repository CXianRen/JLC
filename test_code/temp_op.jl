typedef struct A_t{
  int a;
  int b;
}* A;

class B{
  int a;
  int b;
}

void f(){
  int[] a = new int[10];
  int[][] b = new int[10][10];
  A[] c = new A[10];
  B[] d = new B[10];
  double[][][][] e = new double[1][2][3][4];
}