
// (c) Copyright Texas A&M University Department of Computer Scinece&Engineering
// ALL RIGHTS RESERVED
//
///
#include <QApplication>
#include <QDesktopWidget>

#include "ctrlwindow.h"

class CtrlWindow;

int main(int argc, char *argv[]) {
  QCoreApplication::addLibraryPath("./");

  QApplication app(argc, argv);
  CtrlWindow window;
  window.show();
  app.exec();
}
