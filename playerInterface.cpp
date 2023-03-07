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
#include <Qtmultimedia\qaudiodevice.h>
#include <Qdir>
#include <qpainter.h>

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
    * video player
    */
    inputBuffer.open(QBuffer::ReadWrite);

    QAudioFormat audioFMT;
    audioFMT.setSampleRate(44000);

    QAudioDevice audioDevice;

    mediaPlayer = new QMediaPlayer();
    videoWidget = new QVideoWidget();
    audioWidget = new QAudioOutput(&inputBuffer);
    mediaPlayer->setAudioOutput(audioWidget);
    mediaPlayer->setVideoOutput(videoWidget);

    connect(mediaPlayer, &QMediaPlayer::playbackStateChanged, this, &AudioV2::mediaStateChanged);
    connect(mediaPlayer, &QMediaPlayer::positionChanged, this, &AudioV2::positionChanged);
    connect(mediaPlayer, &QMediaPlayer::durationChanged, this, &AudioV2::durationChanged);
    connect(mediaPlayer, SIGNAL(durationChanged(qint64)),this, SLOT(getDuration(qint64)));
    connect(mediaPlayer, &QMediaPlayer::playbackStateChanged, this, &AudioV2::audioBufferProcess);

    /*
    * buttons and labels
    */
    QSize iconSize(30, 30);

    // play button
    playButton = new QToolButton;
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    playButton->setIconSize(iconSize);
    playButton->setToolTip(tr("Play"));
    playButton->setEnabled(false);

    connect(playButton, &QAbstractButton::clicked, this, &AudioV2::playFunction);

    // time label
    currentTimeLabel = new QLabel;
    currentTimeLabel->setText("00:00:00");
    currentTimeLabel->setFixedSize(43, 10);

    slashLabel = new QLabel;
    slashLabel->setText("/");
    slashLabel->setFixedSize(5, 10);

    timeLabel = new QLabel;
    timeLabel->setText("00:00:00");
    timeLabel->setFixedSize(43, 10);

    // volume button
    volumeButton = new QToolButton;
    volumeButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    volumeButton->setIconSize(iconSize);
    volumeButtonFlag = false;

    connect(volumeButton, &QToolButton::clicked, this, &AudioV2::turnOffVolume);

    // volume slider
    volumeSlider = new QSlider(Qt::Horizontal);
    volumeSlider->setRange(0, 100);
    volumeSlider->setFixedWidth(100);
    volumeSlider->setSliderPosition(50);
    audioWidget->setVolume(0.5);

    connect(volumeSlider, &QAbstractSlider::sliderReleased, this, &AudioV2::volumeSetting);

    // play speech list
    playSpeech = new QMenu;
    playSpeechList = new QPushButton;
    playSpeechList->setCheckable(true);
    playSpeechItemGroup = new QActionGroup(this);
    QStringList playspeechItemList;
    playspeechItemList << tr("0.5x") << tr("0.7x") << tr("1.0x") << tr("1.5x") << tr("1.7x") << tr("2.0x");
    float speeds[] = { 0.5, 0.7, 1.0, 1.5, 1.7, 2.0 };

    for (int i = 0; i < playspeechItemList.size(); i++)
    {
        QAction* pSpeedItem = playSpeech->addAction(playspeechItemList.at(i));
        pSpeedItem->setData(QVariant::fromValue(speeds[i]));
        pSpeedItem->setCheckable(true);
        playSpeechItemGroup->addAction(pSpeedItem);
        if (i == 10)  pSpeedItem->setChecked(true);
    }

    connect(playSpeechItemGroup, SIGNAL(triggered(QAction*)), this, SLOT(setPlaySpeechFunction(QAction*)));

    playSpeechList = new QPushButton;
    playSpeechList->setText("1.0x");
    playSpeechList->setFixedSize(60, 30);
    playSpeechList->setMenu(playSpeech);

    // seekBackward button
    seekBackwardButton = new QToolButton;
    seekBackwardButton->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    seekBackwardButton->setIconSize(iconSize);

    connect(seekBackwardButton, &QToolButton::clicked, this, &AudioV2::seekPlayBackFunction);

    // seekForward button
    seekForwardButton = new QToolButton;
    seekForwardButton->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    seekForwardButton->setIconSize(iconSize);

    connect(seekForwardButton, &QToolButton::clicked, this, &AudioV2::seekPlayForwardFunction);

    // video slider
    videoSlider = new QSlider(Qt::Horizontal);
    videoSlider->setRange(0, 0);

    connect(videoSlider, &QAbstractSlider::sliderMoved, this, &AudioV2::setPosition);

    // dynamic spectrum
    customPlot = new QCustomPlot;
    drawDynamicSpectrumBar();

    /*
    * layouts
    */
    // left button layout
    leftButtonsLayout = new QHBoxLayout;
    leftButtonsLayout->addWidget(seekBackwardButton);
    leftButtonsLayout->addWidget(playButton);
    leftButtonsLayout->addWidget(seekForwardButton);
    leftButtonsLayout->addWidget(currentTimeLabel);
    leftButtonsLayout->addWidget(slashLabel);
    leftButtonsLayout->addWidget(timeLabel);
    leftButtonsLayout->setAlignment(Qt::AlignLeft);

    // right button layout
    rightButtonsLayout = new QHBoxLayout;
    rightButtonsLayout->addWidget(playSpeechList);
    rightButtonsLayout->addWidget(volumeButton);
    rightButtonsLayout->addWidget(volumeSlider);
    rightButtonsLayout->setAlignment(Qt::AlignRight);

    // button layout
    buttonLayout = new QHBoxLayout;
    buttonLayout->addLayout(leftButtonsLayout);
    buttonLayout->addLayout(rightButtonsLayout);

    // slider layout
    sliderLayout = new QHBoxLayout;
    sliderLayout->addWidget(videoSlider);

    // player layout
    playerLayout = new QHBoxLayout; 
    playerLayout->addWidget(videoWidget);

    // dynamic spectrum layout
    dynamicSpectrumLayout = new QHBoxLayout;
    //dynamicSpectrumLayout->addWidget(dynamicSpectrumLabel);
    dynamicSpectrumLayout->addWidget(customPlot);

    // main layout
    widget = new QWidget();
    mainLayout = new QVBoxLayout(widget);
    mainLayout->addLayout(playerLayout);
    mainLayout->addLayout(sliderLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(dynamicSpectrumLayout);

    this -> setCentralWidget(widget);
    setLayout(mainLayout);

    setWindowTitle(tr("Video Player"));
    resize(1200, 900);

    for (int i = 0; i < 96000; i++) {
        mIndices.append((double)i);
        audioSample.append(0);
    }

    double freqStep = (double)48000 / (double)96000;
    double f = 20;
    while (f < 20000) {
        mFftIndices.append(f);
        f += freqStep;
    }

    mFftIn = fftw_alloc_real(96000);
    mFftOut = fftw_alloc_real(96000);
    mFftPlan = fftw_plan_r2r_1d(96000, mFftIn, mFftOut, FFTW_R2HC, FFTW_ESTIMATE);
}

AudioV2::~AudioV2() {
    fftw_free(mFftIn);
    fftw_free(mFftOut);
    fftw_destroy_plan(mFftPlan);
}

// open file function
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

// open file action
void AudioV2::openFileAction()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open a Video"), currentVideoDirectory);
    currentFilePath = fileName;
    if (!fileName.isEmpty())
        open(fileName);
}

// play the video function
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

// change state of video
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

// set position of slide
void AudioV2::setPosition(int position)
{
    mediaPlayer->setPosition(position);
}

// change position of slide
void AudioV2::positionChanged(qint64 value)
{
    videoSlider->setValue(value);
    currentTimeLabel->setText(QTime(0, 0, 0).addMSecs(int(value)).toString(QString::fromLatin1("HH:mm:ss")));
}

// convert playtime to string
void AudioV2::convertPlaytimeToString(qint64 durationTime)
{
    int h, m, s;
    durationTime /= 1000;
    h = (int)durationTime / 3600;
    m = ((int)durationTime - h * 3600) / 60;
    s = (int)durationTime - h * 3600 - m * 60;
    timeLabel->setText(QString("%1:%2:%3").arg(h).arg(m).arg(s));
}

// get duration of the video
void AudioV2::getDuration(qint64 durationTime)
{
    durationTime = mediaPlayer->duration();
    convertPlaytimeToString(durationTime);
}

// change the current duration
void AudioV2::durationChanged(qint64 duration)
{
    videoSlider->setRange(0, duration);
}

// play speech setting function
void AudioV2::setPlaySpeechFunction(QAction* action)
{
    action->setChecked(true);
    playSpeechList->setToolTip(action->text());
    playSpeechList->setText(action->text());

    mediaPlayer->setPlaybackRate(qreal(action->data().toFloat()));
}

// play back function
void AudioV2::seekPlayBackFunction()
{
    int currentPosition = mediaPlayer->position();
    currentPosition -= 5000;
    mediaPlayer->setPosition(currentPosition);
}

// play forward function
void AudioV2::seekPlayForwardFunction()
{
    int currentPosition = mediaPlayer->position();
    currentPosition += 5000;
    mediaPlayer->setPosition(currentPosition);
}

//set the volume to zero
void AudioV2::turnOffVolume() {
    if (volumeButtonFlag) {
        volumeButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
        volumeButtonFlag = false;

        int volumeNumber = volumeSlider->value();
        audioWidget->setVolume((float)volumeNumber / 100.0);
    }
    else {
        volumeButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        volumeButtonFlag = true;

        audioWidget->setVolume(0);
    }
}

// volume function
void AudioV2::volumeSetting() {
    int volumeNumber = volumeSlider->value();
    audioWidget->setVolume((float)volumeNumber / 100.0);
}

// dynamic spectrum
//bool AudioV2::eventFilter(QObject* obj, QEvent* event)
//{
//    if (obj == dynamicSpectrumLabel && event->type() == QEvent::Paint)
//    {
//        drawDynamicSpectrumBar();
//    }
//    return QWidget::eventFilter(obj, event);
//}

// spectum process function
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



