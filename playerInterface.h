#pragma once

#ifndef MOVIEPLAYER_H
#define MOVIEPLAYER_H

#include <QtWidgets\QMainWindow>
#include <QtMultimedia\QMediaplayer.h>
#include <QtMultimediaWidgets\QVideoWidget>
#include <QtWidgets>
#include "ui_AudioV2.h"

#include "spectrumProcess.h"

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

    QMediaPlayer *mediaPlayer = nullptr;

    QAudioOutput *audioWidget = nullptr;

    QString currentVideoDirectory;
    QString currentFilePath;

    QLabel *currentTimeLabel = nullptr;
    QLabel *timeLabel = nullptr;
    QLabel *slashLabel = nullptr;

    QSlider *frameSlider = nullptr;
    QSlider *videoSlider = nullptr;

    QMenu *fileMenuBar = nullptr;

    QAction *fileAction = nullptr;
    QAction *spectumAction = nullptr;

    QToolButton *playButton = nullptr;
    QToolButton *pauseButton = nullptr;
    QToolButton *volumeButton = nullptr;
    QToolButton *seekBackwardButton = nullptr;
    QToolButton *seekForwardButton = nullptr;

    QWidget *widget = nullptr;
    QVideoWidget *videoWidget = nullptr;

    QVBoxLayout *mainLayout = nullptr;
    QHBoxLayout *buttonLayout = nullptr;
    QHBoxLayout *leftButtonsLayout = nullptr;
    QHBoxLayout *rightButtonsLayout = nullptr;
    QHBoxLayout *playerLayout = nullptr;
    QHBoxLayout *sliderLayout = nullptr;

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
};

#endif
