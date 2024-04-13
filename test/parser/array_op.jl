# int foo(int a)
# {
#   return a;
# }

int[] array(int a)
{
  int[] arr = new int[a];
  return arr;
}

int[][] array2(int a)
{
  int[][] arr = new int[a][a];
  return arr;
}

int main()
{
  #
  int[] arr;
  # printInt(arr.length);
  
  #
  # int j = 0;
  # while (j<arr.length){
  #   ;
  # }
  
  # int [] res = new int [arr . length];
  
  # #
  # int i = 0;
  # arr [i] = arr [i + 1];
  
  # # 
  # arr[arr.length - 1]= 1 ;
  
  # #
  # int [] a = new int [10];
  # int [] b = new int [10];
  # int resb = 0;
  # resb = resb + a[i] * b[i];
  
  # #
  # printInt(new int[foo(7)].length);
  
  # # 
  # array(3)[2] = 1;
  # printInt(array(3).length);
  # printInt(array(3)[0]);

  # printInt(array2(3).length);
  # printInt(array2(3)[0].length);
  
  # #
  # printInt((new int[3])[2]);
  # printInt(new int[3].length);
  
  printInt(- array(3).length);
  printInt(- array(3)[0]);
  return 0;
}
