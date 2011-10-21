#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>

#include "gui.h"

int main(int argc, char **argv) {
    grid g(0, 0, 7*60, 7*60, "hey");
    g.init();

    g.show(argc,argv);
    return Fl::run();
}
