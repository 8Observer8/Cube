#include <QApplication>
#include "scene3D.h"

int main(int argc, char** argv)
{
   QApplication app(argc, argv);

   Scene3D scene1;
   scene1.setWindowTitle("Cube");
   scene1.resize(500, 500);
   scene1.show();

   return app.exec();
}
