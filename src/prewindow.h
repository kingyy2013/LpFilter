#ifndef PREWINDOW_H
#define PREWINDOW_H

#include <QFileInfo>
#include <QLabel>
#include <QWidget>

class PreWindow : public QLabel {
  Q_OBJECT
public:
  explicit PreWindow();
  void SetImage(QPixmap img);

signals:

protected:
  void paintEvent(QPaintEvent *);

private:
  bool mFlipped;
};

#endif // PREWINDOW_H
