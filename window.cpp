#include <QtWidgets>
#include "window.hpp"

MyWindow::MyWindow()
{
  createWidgets();
  arrangeWidgets();
  setWindowTitle("My Window");
  setMinimumSize(320, 200);
}

void MyWindow::createWidgets()
{
  // Create widgets on the heap using new
}

void MyWindow::arrangeWidgets()
{
  // Create layout for widgets here
  // Remember to call setLayout!
}