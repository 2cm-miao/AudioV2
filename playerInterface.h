#pragma once

#ifndef MOVIEPLAYER_H
#define MOVIEPLAYER_H

#include <QtWidgets/QMainWindow>
#include <QtMultimedia/QMediaplayer.h>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QtWidgets>
#include <QtMultimedia/Qaudiodevice.h>
#include <QtMultimedia/qmediadevices.h>
#include <qbuffer.h>
#include <fftw3.h>
#include "ui_AudioV2.h"

#include "spectrumProcess.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
class QCheckBox;
class QGridLayout;
class QHBoxLayout;
class QLabel;
class QSlider;
class QToolButton;
class QVBoxLayout;
class QDialogButtonBox;
class QComboBox;
class QDialogButtonBox;
class QGridLayout;
class QGroupBox;
class QLabel;
class QPushButton;
class QMediaPlayer;
class QAudioOutput;
class QVideoWidget;
class QtWidgets;
class QBuffer;
QT_END_NAMESPACE

class AudioV2 : public QMainWindow
{
    Q_OBJECT

public:
    AudioV2(QWidget *parent = nullptr);
    ~AudioV2();

private:
    Ui::AudioV2Class ui;

    QMediaPlayer::PlaybackState m_playerState = QMediaPlayer::StoppedState;

    QMediaPlayer* mediaPlayer = nullptr;

    QAudioOutput* audioWidget = nullptr;

    QBuffer inputBuffer;

    QAudioFormat* audioFormat = nullptr;

    QWidget* widget = nullptr;

    QCustomPlot* customPlot = nullptr;

    QVideoWidget* videoWidget = nullptr;

    QActionGroup* playSpeechItemGroup = nullptr;

    QPushButton* playSpeechList = nullptr;

    QVector<double> audioSample;

    QString currentVideoDirectory;
    QString currentFilePath;

    QLabel* currentTimeLabel = nullptr;
    QLabel* timeLabel = nullptr;
    QLabel* slashLabel = nullptr;
    QLabel* dynamicSpectrumLabel = nullptr;

    QSlider* frameSlider = nullptr;
    QSlider* videoSlider = nullptr;
    QSlider* volumeSlider = nullptr;

    QMenu* fileMenuBar = nullptr;
    QMenu* playSpeech = nullptr;

    QAction* fileAction = nullptr;
    QAction* spectumAction = nullptr;

    QToolButton* playButton = nullptr;
    QToolButton* pauseButton = nullptr;
    QToolButton* volumeButton = nullptr;
    QToolButton* seekBackwardButton = nullptr;
    QToolButton* seekForwardButton = nullptr;

    QVBoxLayout* mainLayout = nullptr;
    QHBoxLayout* buttonLayout = nullptr;
    QHBoxLayout* leftButtonsLayout = nullptr;
    QHBoxLayout* rightButtonsLayout = nullptr;
    QHBoxLayout* playerLayout = nullptr;
    QHBoxLayout* sliderLayout = nullptr;
    QHBoxLayout* dynamicSpectrumLayout = nullptr;

    QVector<double> mIndices;
    QVector<double> mFftIndices;

    fftw_plan mFftPlan;
    double* mFftIn;
    double* mFftOut;

    bool volumeButtonFlag;

private slots:
    void open(const QString& fileName);
    void openFileAction();
    void playFunction();
    void mediaStateChanged(QMediaPlayer::PlaybackState state);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void setPosition(int position);
    void spectumProcessAction();
    void getDuration(qint64 durationTime);
    void convertPlaytimeToString(qint64 durationTime);
    void setPlaySpeechFunction(QAction* action);
    void seekPlayBackFunction();
    void seekPlayForwardFunction();
    void turnOffVolume();
    void volumeSetting();
    void drawDynamicSpectrumBar();
    void audioBufferProcess();
    void audioFFTProcess();
};

#endif
