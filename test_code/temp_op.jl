

boolean f1(){
  printInt(1);
  return true;
}

boolean f2(){
  printInt(2);
  return false;
}

int main(){
 
 printString("&& 1,2:");
  if(f1()&& f2()){
    printInt(3);
  }

  printString("&& 2:");
  if(f2() && f1()){
    printInt(4);
  }

  printString("|| 1,5:");
  if(f1()|| f2()){
    printInt(5);
  }

  printString("|| 2,1,6:");
  if(f2()|| f1()){
    printInt(6);
  }

  return 0;
}
