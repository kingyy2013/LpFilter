#include "prewindow.h"
#include <QPainter>

PreWindow::PreWindow() {}

// protected member functions
void PreWindow::paintEvent(QPaintEvent *) {

  QPainter painter(this);
  if (pixmap()) {
    if (mFlipped) {
      painter.scale(1, -1);
      painter.translate(0, -this->height());
    }
    QPixmap pixmap_scaled = pixmap()->scaled(size(), Qt::IgnoreAspectRatio);
    painter.drawPixmap(0, 0, pixmap_scaled);
  }
}

void PreWindow::SetImage(QPixmap img) {
  mFlipped = false;
  setPixmap(img);
}
