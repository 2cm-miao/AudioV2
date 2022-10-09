#include "playerInterface.h"
#include "spectrumProcess.h"

#include <qpushbutton.h>
#include <QMessageBox>
#include <QCheckBox>
#include <QFileDialog>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QStyle>
#include <QToolButton>
#include <QVBoxLayout>
#include <QDialog>
#include <QDialogButtonBox>
#include <QtMultimediaWidgets\QVideoWidget>
#include <QtWebEngineWidgets\QWebEngineView>
#include <QtMultimedia\QMediaPlayer>
#include <QtMultimedia\QAudioOutput>
#include <Qdir>

AudioV2::AudioV2(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    currentVideoDirectory = QDir::homePath();
    currentFilePath = nullptr;

    /*
    * action
    */
    //open file
    fileAction = new QAction(this);
    fileAction->setText("open");
    connect(fileAction, SIGNAL(triggered()), this, SLOT(openFileAction()));

    //show spectum
    spectumAction = new QAction(this);
    spectumAction->setText("spectum");
    connect(spectumAction, SIGNAL(triggered()), this, SLOT(spectumProcessAction()));

    /*
    * menu bar
    */
    fileMenuBar = menuBar()->addMenu("file");
    fileMenuBar->addAction(fileAction);
    fileMenuBar->addAction(spectumAction);

    /*
    * buttons
    */
    QSize iconSize(36, 36);

    //play button
    playButton = new QToolButton;
    playButton -> setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    playButton -> setIconSize(iconSize);
    playButton -> setToolTip(tr("Play"));
    playButton -> setEnabled(false);
    connect(playButton, &QAbstractButton::clicked, this, &AudioV2::playFunction);

    //video slider
    videoSlider = new QSlider(Qt::Horizontal);
    videoSlider->setRange(0, 0);
    connect(videoSlider, &QAbstractSlider::sliderMoved, this, &AudioV2::setPosition);

    /*
    * video player
    */
    mediaPlayer = new QMediaPlayer();
    videoWidget = new QVideoWidget();
    audioWidget = new QAudioOutput();
    mediaPlayer->setAudioOutput(audioWidget);
    mediaPlayer->setVideoOutput(videoWidget);

    connect(mediaPlayer, &QMediaPlayer::playbackStateChanged, this, &AudioV2::mediaStateChanged);
    connect(mediaPlayer, &QMediaPlayer::positionChanged, this, &AudioV2::positionChanged);
    connect(mediaPlayer, &QMediaPlayer::durationChanged, this, &AudioV2::durationChanged);


    /*
    * layouts
    */
    //button layout
    buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(playButton);
    //buttonsLayout->addWidget(pauseButton);
    buttonsLayout->addWidget(videoSlider);

    //player layout
    playerLayout = new QHBoxLayout;
    playerLayout -> addWidget(videoWidget);

    //main layout
    widget = new QWidget();
    mainLayout = new QVBoxLayout(widget);
    mainLayout -> addLayout(playerLayout);
    mainLayout -> addLayout(buttonsLayout);


    this -> setCentralWidget(widget);
    setLayout(mainLayout);

    setWindowTitle(tr("Video Player"));
    resize(1100, 700);
}

AudioV2::~AudioV2()
{}

void AudioV2::open(const QString& fileName)
{
    currentVideoDirectory = QFileInfo(fileName).path();

    if (mediaPlayer->isAvailable()) {
        mediaPlayer->setSource(QUrl::fromLocalFile(fileName));
        mediaPlayer->play();
    }
    else {
        QMessageBox m(this);
        m.setWindowTitle("ERROR");
        m.setText("This media is not available.");
        m.show();
        m.exec();
    }
    playButton->setEnabled(true);
}

void AudioV2::openFileAction()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open a Video"), currentVideoDirectory);
    currentFilePath = fileName;
    if (!fileName.isEmpty())
        open(fileName);
}

void AudioV2::playFunction()
{
    switch (mediaPlayer->playbackState()) {
    case QMediaPlayer::PlayingState:
        mediaPlayer->pause();
        break;
    default:
        mediaPlayer->play();
        break;
    }
}

void AudioV2::mediaStateChanged(QMediaPlayer::PlaybackState state)
{
    switch (state) {
    case QMediaPlayer::PlayingState:
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        break;
    default:
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        break;
    }
}

void AudioV2::setPosition(int position)
{
    mediaPlayer->setPosition(position);
}

void AudioV2::positionChanged(qint64 position)
{
    videoSlider->setValue(position);
}

void AudioV2::durationChanged(qint64 duration)
{
    videoSlider->setRange(0, duration);
}

void AudioV2::spectumProcessAction()
{
    //QMessageBox m(this);
    //m.setWindowTitle("spectumProcess");
    //int aa = 2;
    //m.setText("This is a messagebox for my spectumProcess.");
    //m.show();
    //m.exec();

    SpectrumProcess* spectPro;
    spectPro = new SpectrumProcess();
    spectPro->show();

    spectPro->exampleFunction(currentFilePath);
}



