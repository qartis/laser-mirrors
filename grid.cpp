#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>

#include "grid.h"

const char *top[]   = {"F","B","I","J","E"};
const char *right[] = {"J","I","H","G","H"};
const char *bot[]   = {"E","F","D","G","C"};
const char *left[]  = {"A","B","A","C","D"};

int grid::handle(int event){
    int x, y;
    enum state *s;
    int width = w() / (DIM + 2);
    switch(event){
    case FL_MOVE:
        break;
    case FL_PUSH:
        if (Fl::event_button() != FL_LEFT_MOUSE) return 1;
        x = Fl::event_x() / width - 1;
        y = Fl::event_y() / width - 1;
        if (x >= DIM || x < 0){
            return 0;
        }
        if (y >= DIM || y < 0){
            return 0;
        }
        s = &g[y*DIM + x];
        if (*s == UNCHECKED){
            *s = BACKSLASH;
        } else if (*s == BACKSLASH){
            *s = FORSLASH;
        } else {
            *s = UNCHECKED;
        }
        damage(1);
        break;
    default:
        return Fl_Double_Window::handle(event);
    }
}


void grid::draw() {
    Fl_Double_Window::draw();
    fl_rectf(0,0,w(),h(), FL_WHITE);
    int i,j;
    int width = w() / (DIM + 2);
    fl_color(0,0,0);
    fl_line_style(FL_DASH, 2);
    for(i=0;i<DIM-1;i++){
        fl_line((i+2) * width, 0, (i+2) * width, h());
    }
    for(i=0;i<DIM-1;i++){
        fl_line(0, (i+2) * width, w(), (i+2) * width);
    }
    fl_line_style(FL_SOLID, 2);
    fl_line(0, width, w(), width);
    fl_line(0, h() - width, w(), h() - width);
    fl_line(width, 0, width, h());
    fl_line(w() - width, 0, w() - width, h());
    for(i=0;i<DIM;i++){
        for(j=0;j<DIM;j++){
            if (g[i*DIM + j] == FORSLASH){
                fl_line((j+1) * width, (i+2) * width, (j+2) * width, (i+1) * width);
            } else if (g[i*DIM + j] == BACKSLASH){
                fl_line((j+1) * width, (i+1) * width, (j+2) * width, (i+2) * width);
            }
        }
    }
    fl_font(FL_HELVETICA, (Fl_Fontsize)(width * 0.75));

    for(i=0;i<DIM;i++){
        fl_draw(top[i], width + width * i, 0,
                        width, width,
                        FL_ALIGN_CENTER);
    }
    for(i=0;i<DIM;i++){
        fl_draw(right[i], width * DIM + width, width + width * i,
                          width, width,
                          FL_ALIGN_CENTER);
    }
    for(i=0;i<DIM;i++){
        fl_draw(bot[i], width + width * i, width * DIM + width,
                        width, width,
                        FL_ALIGN_CENTER);
    }
    for(i=0;i<DIM;i++){
        fl_draw(left[i], 0, width + width * i,
                         width, width,
                         FL_ALIGN_CENTER);
    }

    laser_into(0, 0, LEFT, 'A', FL_RED);
    laser_into(0, 1, LEFT, 'B', FL_BLUE);
    laser_into(0, 3, LEFT, 'C', FL_YELLOW);
    laser_into(0, 4, LEFT, 'D', FL_MAGENTA);
    laser_into(0, 4, BOT,  'E', FL_DARK_CYAN);
    laser_into(1, 4, BOT,  'F', FL_CYAN);
    laser_into(3, 4, BOT,  'G', FL_DARK_RED);
    laser_into(4, 4, RIGHT,'H', FL_DARK_YELLOW);
    laser_into(2, 0, TOP,  'I', FL_DARK_BLUE);
    laser_into(3, 0, TOP,  'J', FL_DARK_GREEN);
}

void grid::laser_into(int x, int y, enum dir dir, char letter, Fl_Color color){
    fl_line_style(FL_SOLID, 3);
    if (x < 0 || x >= DIM ||
        y < 0 || y >= DIM){
        if (color == FL_GREEN){
            return;
        }
        if (x == -1 && left[y][0] == letter){
            laser_into(0, y, LEFT, letter, FL_GREEN);
        } else if (x == DIM && right[y][0] == letter){
            laser_into(DIM-1, y, RIGHT, letter, FL_GREEN);
        } else if (y == -1 && top[x][0] == letter){
            laser_into(x, 0, TOP, letter, FL_GREEN);
        } else if (y == DIM && bot[x][0] == letter){
            laser_into(x, DIM-1, BOT, letter, FL_GREEN);
        }
        return;
    }
    int width = w() / (DIM + 2);
    fl_color(color);
    switch (g[y*DIM + x]){
    case UNCHECKED:
        switch (dir){
        case TOP:
            fl_line(width + x * width + width/2, width + width * y,
                    width + x * width + width/2, width + width*y + width);
            laser_into(x, y+1, TOP, letter, color);
            break;
        case BOT:
            fl_line(width + x * width + width/2, width + width * y,
                    width + x * width + width/2, width + width*y + width);
            laser_into(x, y-1, BOT, letter, color);
            break;
        case LEFT:
            fl_line(width + x * width, width + y * width + width/2,
                    width + x * width + width, width + y * width + width/2);
            laser_into(x+1, y, LEFT, letter, color);
            break;
        case RIGHT:
            fl_line(width + x * width, width + y * width + width/2,
                    width + x * width + width, width + y * width + width/2);
            laser_into(x-1, y, RIGHT, letter, color);
            break;
        }
        break;
    case FORSLASH:
        switch (dir){
        case TOP:
            fl_line(width + x * width + width/2, width + width * y,
                    width + x * width + width/2, width + width*y + width/2);
            fl_line(width + x * width, width + width * y + width/2,
                    width + x * width + width/2, width + width*y + width/2);
            laser_into(x-1, y, RIGHT, letter, color);
            break;
        case BOT:
            fl_line(width + x * width + width/2, width + width * y + width,
                    width + x * width + width/2, width + width*y + width/2);
            fl_line(width + x * width + width, width + width * y + width/2,
                    width + x * width + width/2, width + width*y + width/2);
            laser_into(x+1, y, LEFT, letter, color);
            break;
        case LEFT:
            fl_line(width + x * width + width/2, width + width * y,
                    width + x * width + width/2, width + width*y + width/2);
            fl_line(width + x * width, width + width * y + width/2,
                    width + x * width + width/2, width + width*y + width/2);
            laser_into(x, y-1, BOT, letter, color);
            break;
        case RIGHT:
            fl_line(width + x * width + width/2, width + width * y + width,
                    width + x * width + width/2, width + width*y + width/2);
            fl_line(width + x * width + width, width + width * y + width/2,
                    width + x * width + width/2, width + width*y + width/2);
            laser_into(x, y+1, TOP, letter, color);
            break;
        }
        break;
    case BACKSLASH:
        switch(dir){
        case TOP:
            fl_line(width + x * width + width/2, width + width * y,
                    width + x * width + width/2, width + width*y + width/2);
            fl_line(width + x * width + width, width + width * y + width/2,
                    width + x * width + width/2, width + width*y + width/2);
            laser_into(x+1, y, LEFT, letter, color);
            break;
        case BOT:
            fl_line(width + x * width + width/2, width + width * y + width,
                    width + x * width + width/2, width + width*y + width/2);
            fl_line(width + x * width, width + width * y + width/2,
                    width + x * width + width/2, width + width*y + width/2);
            laser_into(x-1, y, RIGHT, letter, color);
            break;
        case LEFT:
            fl_line(width + x * width, width + width * y + width/2,
                    width + x * width + width/2, width + width*y + width/2);
            fl_line(width + x * width + width/2, width + width * y + width,
                    width + x * width + width/2, width + width*y + width/2);
            laser_into(x, y+1, TOP, letter, color);
            break;
        case RIGHT:
            fl_line(width + x * width + width, width + width * y + width/2,
                    width + x * width + width/2, width + width*y + width/2);
            fl_line(width + x * width + width/2, width + width * y,
                    width + x * width + width/2, width + width*y + width/2);
            laser_into(x, y-1, BOT, letter, color);
            break;
        }
        break;
    }
}


void grid::init(void) {
    this->g = (enum state *)malloc(DIM * DIM * sizeof(enum state));
    int i, j;
    for(i=0;i<DIM;i++){
        for(j=0;j<DIM;j++){
            g[i*DIM + j] = UNCHECKED;
        }
    }
    this->end();
}
