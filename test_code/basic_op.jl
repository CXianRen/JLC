int main(){
    int a = 1;
    int b = 2;
    int c = a + b;
    
    a++;
    a--;

    b = a--;
    b = a++;
    b = b++;
    b = b--;
    b = -b;

    # b = +b; It's not legal in jlc!

    c = a*b;
    c = a/b;
    
    c = a%b;

    boolean e = true;
    e = !e;
    e =  e < 1;
    e = e > 1;
    e = e <= 1;
    e = e >= 1;
    e = e == 1;
    e = e != 1;
    
}