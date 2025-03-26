#include <GL/freeglut.h>
#include "/src/GlutApp.h"
#include "/src/Controller.h"

using namespace std;


int main(int argc,char** argv) {

    GlutApp* app = new GlutApp(argc, argv);

    Controller* myController = new Controller();

    app->setController(myController);

    app->setTitle("UC Merced Paint");

    app->run();
    
    return 0;
}