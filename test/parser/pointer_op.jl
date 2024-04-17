
typedef struct Big *big;

struct Big{
    int x01;
};

typedef struct A* A;

struct A {
    int a;
    A b;
};

struct Foo_t{
    int bar;
};

typedef struct Foo_t * Foo;

        
int main(){
    big b01 = new Big;
    b01->x01 = 1;
    printInt(b01->x01);
    
    if(b01 == (big)null)
        printInt(0);
    else
        printInt(1);

    printInt((new A)->a);
    new A->b = new A;

    int c = p -> cool + 5;
    # Foo[] foos = new Foo[10];
    # foos[1] = new Foo_t;
    # foos[1]->bar = 1;
    
    # printInt(foos.length);
    # for(Foo foo : foos){
    #    printInt(foo->bar);
    # }

    return 0;

}

