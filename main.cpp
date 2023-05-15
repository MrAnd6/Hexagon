#include "Window.cpp"

int main(){
    Window window;
    while (window.working()){
        window.update();
        window.render();
    }
}

