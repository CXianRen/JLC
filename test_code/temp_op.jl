

boolean f1(){
  printInt(1);
  return true;
}

boolean f2(){
  printInt(2);
  return false;
}

int main(){
 
  if(!f1()&& f2()){
    printInt(3);
  }

  return 0;
}
