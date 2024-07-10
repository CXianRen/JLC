
class A{
  int a;
  int b;
}

int main(){
  int a = 0;
  printInt(a++);
  printInt(a--);

  A aa = new A;
  aa.a = aa.a++;

  printInt(aa.a);

  printInt(-1);

  printDouble(1.0);
  printDouble(-1.0);

  # int mul div mod
  printInt(2*3);
  printInt(2/3);
  printInt(2%3);
  printInt(-2*3);
  printInt(-2*(-3));

  # double mul div
  printDouble(2.0*3.0);
  printDouble(2.0/3.0);
  printDouble(-2.0*3.0);

  # +,- 
  printInt(2+3);
  printInt(2-3);

  # not 
  printInt((int)true);
  printInt((int)false);
  boolean b1 = false;
  b1 = !b1;

  return 0;
}

