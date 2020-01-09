#ifndef CTRLWINDOW_H
#define CTRLWINDOW_H

#include "prewindow.h"
#include "qsliderspinbox.h"
#include "qtglrenderres.h"
#include <QCheckBox>
#include <QDir>
#include <QLabel>
#include <QListWidget>
#include <QPixmap>
#include <QPushButton>
#include <QWidget>

class qtglRenderRes;
class CtrlWindow : public QWidget {
  Q_OBJECT
public:
  explicit CtrlWindow(QWidget *parent = 0);
  QPushButton *mButtonSetFolder;
  QPushButton *mButtonSetBG;

  QPushButton *mButtonRefFolder;
  QPushButton *mButtonSave;
  QPushButton *mReloadShader;
  QPushButton *mReloadFilter;

  QPushButton *mButtonAbout;

  QSliderSpinBox *mDepthSliderSpinbox;
  QLabel *mDepthValue;

signals:
  void SetBG(QPixmap);
  void SetLense(QPixmap);
  void SetEnv(QPixmap);
  void SetDIDark(QPixmap);
  void SetDIBright(QPixmap);
  void SetFG(QPixmap);

public slots:
  void SetFolder();
  void BuildFileList();
  void GetBG();

  void SetDisplayImage(int);
  void SaveImage();
  void About();

private:
  QDir *mFileDir;
  QStringList *mFileNames;
  QListWidget *mFileWidget;
  QPixmap GetPixmap(int index, QFileInfo &image);
  QWidget *CreateRenderControlTab();
  QWidget *CreateVideoControlTab();

  PreWindow *mMiniMap;
  qtglRenderRes *mRenderWindow;
  QPixmap applySobelFiltering(QPixmap pixmap);

  bool m_ShaderSaveCheck;
  bool m_ImageSaveCheck;

  QFileInfo m_BGFileName;
  QFileInfo m_SMFileName;
  QFileInfo m_DIDarkFileName;
  QFileInfo m_DIBrightFileName;
  QFileInfo m_ENVFileName;
  QFileInfo m_SIFileName;

  QFileInfo m_FShaderName;
  QFileInfo m_VShaderName;

protected:
  void closeEvent(QCloseEvent *event);
};

#endif // CTRLWINDOW_H
