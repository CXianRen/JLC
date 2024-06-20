# global define 
## struct

```c
// define a new struct 
typedef struct Foo_t{
  int bar;
} * Foo;

// or 
typedef struct Foo_t * Foo;
struct Foo_t{
   int bar;
};

// or 
typedef struct A* A;

struct A {
    int a;
    A b;
};

// define a struct variable 
Foo f01 = new Foot; 

// access memeber 
f01->bar = 1;

```

## enum 
```c
enum Color {
  RED,
  GREEN,
  BLUE
};

Color color = Color.RED;
if(color == Color.RED)

```

## class
```c
// define 
class Counter {
  int val;

  void incr () {val++; return;}

  int value () {return val;}

}

class Node {
  int elem;
  Node next; // so its a pointer?
  // yes, in case queue.jl (Node)null

  void a(){

  }
}

// call member function

Node n = new Node;
n.a();
// a memebr is not accessible directly?

// extend
class Point2 {
  int x;
  int y;
}

class Point3 extends Point2 {
  int z;
}

// member funcion overide

```


## array
```c
int[] arr;
printInt(arr.length);

int[] a = new int[10];

// The grammar should accept any expression to the left of the
// dot, and any expression inside [ ].
printInt(new int[foo(7)].length);

array(3)[2] = 1;
printInt(array(3)[0]);

printInt((new int[3])[2]);

```
## inner type
## function
```c
//lambada 
  fn(int) -> int addXZ() {
    int z = 3;
    return \(int y) -> int: y + x + z;
  }
  printInt(addXZ()(2));
```

# op level

```c

(new A)->b = new A;

printInt((new int[3])[2]);
```