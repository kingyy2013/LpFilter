#include "ctrlwindow.h"
#include <QFileDialog>
#include <QGridLayout>
#include <QMessageBox>
#include <QtCore>
//#include <QSpinBox>

CtrlWindow::CtrlWindow(QWidget *parent) : QWidget(parent) {

  mRenderWindow = new qtglRenderRes();

  setWindowTitle("Shape Map Control Panel");
  // set slider
  mFileWidget = new QListWidget();
  connect(mFileWidget, SIGNAL(currentRowChanged(int)), this,
          SLOT(SetDisplayImage(int)));

  // set mini map labe
  mMiniMap = new PreWindow();

  QGridLayout *mainLayout = new QGridLayout();
  // set all buttons
  // image related
  mButtonSetBG = new QPushButton("Set BG Image");
  connect(mButtonSetBG, SIGNAL(clicked()), this, SLOT(GetBG()));
  mButtonSetFolder = new QPushButton("Set Image Folder");
  connect(mButtonSetFolder, SIGNAL(clicked()), this, SLOT(SetFolder()));

  // project related
  mButtonRefFolder = new QPushButton("   Refresh Folder   ");
  connect(mButtonRefFolder, SIGNAL(clicked()), this, SLOT(BuildFileList()));
  mButtonSave = new QPushButton("Save Image");
  connect(mButtonSave, SIGNAL(clicked()), this, SLOT(SaveImage()));
  mReloadShader = new QPushButton("Reload Shader/Filter");
  connect(mReloadShader, SIGNAL(clicked()), mRenderWindow,
          SLOT(ReloadShader()));
  //  mReloadFilter = new QPushButton("Reload Filter");
  connect(mReloadShader, SIGNAL(clicked()), mRenderWindow,
          SLOT(ReloadFilter()));
  mButtonAbout = new QPushButton("About");
  connect(mButtonAbout, SIGNAL(clicked()), this, SLOT(About()));

  // set slider
  mDepthSliderSpinbox = new QSliderSpinBox();
  mDepthSliderSpinbox->SetRatio(40);
  mDepthSliderSpinbox->SetChangeRange(-400, 400);
  mDepthSliderSpinbox->SetChangeStep(0.25);
  mDepthValue = new QLabel("LP:");

  connect(mDepthSliderSpinbox, SIGNAL(SliderSpinboxValueChange(double)),
          mRenderWindow, SLOT(SetDepthValue(double)));
  //  QTabWidget *tabWidget = new QTabWidget;
  //  tabWidget->addTab(CreateRenderControlTab(), tr("Render"));
  //  //  tabWidget->addTab(CreateVideoControlTab(), tr("Video"));
  //  tabWidget->setTabPosition(QTabWidget::East);

  /// attach to widget
  mainLayout->addWidget(mFileWidget, 0, 0, 6, 1);
  mainLayout->addWidget(mButtonSetFolder, 0, 1, 1, 3);
  mainLayout->addWidget(mButtonSetBG, 1, 1, 1, 3);
  mainLayout->addWidget(mButtonSave, 2, 1, 1, 3);
  mainLayout->addWidget(mButtonRefFolder, 3, 1, 1, 3);
  mainLayout->addWidget(mReloadShader, 4, 1, 1, 3);
  mainLayout->addWidget(mButtonAbout, 5, 1, 1, 3);

  //  mainLayout->addWidget(mButtonAbout, 5, 1, 1, 3);
  mainLayout->addWidget(mDepthSliderSpinbox->m_Slider, 6, 0, 1, 1);
  mainLayout->addWidget(mDepthValue, 6, 2, 1, 1);
  mainLayout->addWidget(mDepthSliderSpinbox, 6, 3, 1, 1);

  // set main layout
  setLayout(mainLayout);

  mRenderWindow->show();
  connect(this, SIGNAL(SetBG(QPixmap)), mRenderWindow,
          SLOT(SetBGTexture(QPixmap)));
  connect(this, SIGNAL(SetLense(QPixmap)), mRenderWindow,
          SLOT(SetLenseTexture(QPixmap)));
  connect(this, SIGNAL(SetEnv(QPixmap)), mRenderWindow,
          SLOT(SetEnvTexture(QPixmap)));
  connect(this, SIGNAL(SetDIDark(QPixmap)), mRenderWindow,
          SLOT(SetDIDarkTexture(QPixmap)));
  connect(this, SIGNAL(SetDIBright(QPixmap)), mRenderWindow,
          SLOT(SetDIBrightTexture(QPixmap)));
  connect(this, SIGNAL(SetFG(QPixmap)), mRenderWindow,
          SLOT(SetFGTexture(QPixmap)));
  connect(this, SIGNAL(SetFG(QPixmap)), mRenderWindow,
          SLOT(SetFGTexture(QPixmap)));

  // set initial value of slider controllers
  mDepthSliderSpinbox->setValue(0);
  mFileDir = NULL;

  // adjust positions
  move(100, 50);
  adjustSize();
  mRenderWindow->setWindowTitle("Rendered Scene");
  mRenderWindow->move(pos().x() + size().width() + 15, pos().y());
  mMiniMap->setWindowTitle("Image Preview");
  mMiniMap->move(pos().x(), pos().y() + size().height() + 40);
  mMiniMap->setPixmap(QPixmap(size().width(), sizeHint().width()));
  mMiniMap->adjustSize();
  mRenderWindow->sizeHint();
  mRenderWindow->resize(mMiniMap->height() + size().height() + 40,
                        mMiniMap->height() + size().height() + 40);
  QSizePolicy pol;
  pol.setHeightForWidth(true);
  mRenderWindow->setSizePolicy(pol);
  mMiniMap->setScaledContents(true);
  mMiniMap->show();
}

void CtrlWindow::SetFolder() {
  if (mFileDir != NULL)
    delete mFileDir;
  mFileDir = new QDir(QFileDialog::getExistingDirectory(
      this, tr("Open Directory"), QDir::currentPath(),
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks));
  BuildFileList();
}

QWidget *CtrlWindow::CreateRenderControlTab() {
  QWidget *RenderTab = new QWidget();
  int SliderStart_pos = 0;
  QGridLayout *RenderLayout = new QGridLayout();

  RenderLayout->addWidget(mDepthSliderSpinbox->m_Slider, SliderStart_pos, 0, 1,
                          1);
  RenderLayout->addWidget(mDepthSliderSpinbox, SliderStart_pos, 2, 1, 1);
  RenderLayout->addWidget(mDepthValue, SliderStart_pos, 1, 1, 1);
  connect(mDepthSliderSpinbox, SIGNAL(SliderSpinboxValueChange(double)),
          mRenderWindow, SLOT(SetDepthValue(double)));

  RenderTab->setLayout(RenderLayout);
  return RenderTab;
}

void CtrlWindow::BuildFileList() {
  if (mFileDir != NULL) {
    mFileWidget->blockSignals(true);
    mFileWidget->clear();
    QStringList nameFilter;
    nameFilter << "*.png"
               << "*.jpg"
               << "*.gif"
               << "*.bmp"
               << "*.jpeg"
               << "*.pbm"
               << "*.pgm"
               << "*.ppm"
               << "*.wmv"
               << "*.avi"
               << "*.mp4"
               << "*.mov"
               << "*.mpg";
    QStringList list = mFileDir->entryList(nameFilter);
    mFileWidget->addItems(list);
    mFileWidget->blockSignals(false);
  } else {
    QMessageBox::warning(this, "Empty", "No folder is selected");
  }
}

void CtrlWindow::GetBG() {
  QPixmap img = GetPixmap(mFileWidget->currentRow(), m_BGFileName);

  mRenderWindow->SetBGTexture(img);
}

void CtrlWindow::SetDisplayImage(int) {
  QFileInfo cur_name;
  QPixmap img = GetPixmap(mFileWidget->currentRow(), cur_name);

  mMiniMap->SetImage(img);
  mMiniMap->show();
}

void CtrlWindow::SaveImage() {
  QString fileName = QFileDialog::getSaveFileName(
      this, tr("Save File"), "/home/untitled.png",
      tr("Images (*.png *.jpg *.gif *.bmp *.jpeg *.pbm *.pgm *.ppm)"));
  if (!fileName.isNull()) {
    QImage image = (mRenderWindow->grabFrameBuffer());
    if (!image.save(fileName)) {
      QMessageBox::warning(this, "Save Image", "Error saving image.");
    }
  }
}

void CtrlWindow::About() {
  QMessageBox::about(
      this, tr("Shape Map"),
      QString(
          "<p><b>Control Penal</b></p>"
          "<pre><b>Buttons:</b>\n"
          "<b>Set Image Folder:</b> Set the folder for all images. All images "
          "in the set folder will show in the list.\n"
          "<b>Set BG Image:</b> Refracted image.\n"
          "<b>Set Shape Map:</b> Aspect ratio will change accordingly, and all "
          "other images will be resized to fit current shape map.\n"
          "<b>Set Diffusion(Dark):</b> The DI0 image in paper.\n"
          "<b>Set Diffusion(Bright):</b> The DI1 image in paper.\n"
          "<b>Set Enviroment Map:</b> Reflected images.\n"
          "<b>Set Image Folder:</b> Set the folder for all images.\n"
          "<b>Refresh Folder:</b> Refresh current image folder.\n"
          "<b>Load Project:</b> Load a project file.\n"
          "<b>Save Project:</b> Save a project file.\n"
          "A project file is a text file that contains all the current "
          "parameters as well as images(names).\n"
          "A project with extension of '.smp' will only save the absolute "
          "path/name of images.\n"
          "A project with extension of '.smf' will save the actual image files "
          "to a folder that has the same name as project name.\n"
          "Within project file, if an image name is left empty, then a "
          "black(rgba = 0,0,0,0) image will be set instead\n"
          "If the given image name is not readable, a warning will be given, "
          "but no image will be set\n"
          "<b>Save Image:</b> Save current image in the rendering window.</pre>"
          "<pre><b>Check Boxes</b>\n"
          "Choose to see whether a certain effect should be turnned.\n"
          "<b>Toggle Light:</b> Show/off lighting position.\n"
          "<b>Toggle Cos:</b> Add/remove Shading effect.\n"
          "<b>Toggle Amb:</b> Add/remove Ambient occlusion.\n"
          "<b>Toggle Sha:</b> Add/remove Shadow effect.\n"
          "<b>Toggle Point:</b> Switch bettwen parallel light and point "
          "light.</pre>"
          "<pre><b>Sliders</b>\n"
          "Refraction:</b> Amount of distortion during refraction.\n"
          "<b>Alpha:</b> Transparency of current shape map.\n"
          "<b>Filter Size:</b> Filter Size for calculating ambient occlusion "
          "and shadow.\n"
          "<b>Shadow Size:</b> Threshold to decisde whether a pixel is in "
          "shadow or not.\n"
          "<b>Cartoon:</b> Sharpness between shadow and non-shadow area.\n"
          "<b>Transluceny:</b> Amount of transluceny for refration.\n"
          "<b>SM Quality:</b> Flatness of Current shape map, a small value "
          "will make current shape map flat in order to eliminate some "
          "errors.</pre>"
          "<p><b>Rendering Window</b></p>"
          "<pre><b>Left_Button:</b> change lighting postion.\n"
          "<b>Right_Button:</b> change lighting intensity.\n"
          "<b>Ctrl+Left_Button:</b> Translate image\n"
          "<b>Ctrl+Right_Button:</b> Zoomming image\n"
          "<b>Drag on window</b>: Resize image\n"
          "<b>Space</b>: Restore to default size\n"
          "<b>Tab</b>: Turn on/off light auto motion\n"));
}

QPixmap CtrlWindow::GetPixmap(int index, QFileInfo &img_name) {
  if (index < 0 || index >= mFileWidget->count()) {
    QMessageBox::critical(this, tr("Image Setting"),
                          tr("Cannot load selected image"));
    return QPixmap();
  }
  img_name =
      QFileInfo(mFileDir->path() + "/" + mFileWidget->currentItem()->text());
  //    qDebug()<<imageFormat;
  QPixmap img(img_name.absoluteFilePath());
  return img;
}

void CtrlWindow::closeEvent(QCloseEvent *event) {
  mMiniMap->close();
  mRenderWindow->close();
}
