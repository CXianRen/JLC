int main(){

    int[][] a = new int [2][2];
    a[0][0] = 1;
    a[0][1] = 2;
    a[1][0] = 3;
    a[1][1] = 4;

    for( int[] e_a : a){
        for( int e : e_a){
            printInt (e);
        }
    }
    
  return 0;
}