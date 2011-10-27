#define DIM 5

enum state {
    UNCHECKED,
    FORSLASH,
    BACKSLASH
};

enum dir {
    TOP,
    RIGHT,
    BOT,
    LEFT
};

class grid : public Fl_Double_Window {
private:
    enum state *g;
    void draw();
    int handle(int event);
    void laser_into(int x, int y, enum dir dir, char letter, Fl_Color c);

public:
    grid(int x,int y,int w,int h,const char *l=0) : Fl_Double_Window(x,y,w,h,l) { }
    void init();
};

