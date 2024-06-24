# int case_1()
# {
#     int length = 3;
#     int[] x = new int[length];
#     return x[x.length - 1];
# }

# typedef struct node *tree;
# struct node
# {
#     tree[] children;
#     int value;
# };

# int main()
# {
#     tree f = new node;
#     f->children = new tree[4];

#     f->children[3] = new node;
#     f->children[3]->value = 1234;

#     for (tree elem : f->children)
#     {
#         if (elem == (tree)null)
#         {
#             printString("null");
#         }
#         else
#         {
#             printString("not null");
#         }
#     }

#     printInt(f->children[3]->value);

#     return 0;
# }


typedef struct Pixel_t{
    int r, g, b;
  } * Pixel;
  
  typedef struct Screen_t{
    Pixel[][] pixels;
    boolean active;
  } * Screen;
  
  void initPixel(Pixel[][] pixels){
    int i = 0;
    while(i < pixels.length){
      int j = 0;
      while(j < pixels[i].length){
        Pixel p = new Pixel_t;
        p->r = i;
        p->g = j;
        p->b = i*j;
        pixels[i][j] = p;
        j++;
      }
      i++;
    }
  }
  
  Screen createScreen(){
    Screen screen = new Screen_t;
    screen->pixels = new Pixel[640][480];
    initPixel(screen->pixels);
    screen->active = true;
    return screen;
  }
  
  int main(){
    Screen screen = createScreen();
    printInt(screen->pixels[4][2]->r);
    printInt(screen->pixels[4][2]->g);
    printInt(screen->pixels[4][2]->b);
    // prints 4
    //        2
    //        8
    return 0;
  }
  
  