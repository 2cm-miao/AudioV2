#pragma once
#include "ui_spectrumProcess.h"

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

class SpectrumProcess : public QMainWindow {
	Q_OBJECT
public:
	SpectrumProcess(QWidget* parent = nullptr);
	~SpectrumProcess();

	void exampleFunction(const QString& fileName);
	uint32_t setColor(int16_t level);

private:
	Ui::MainWindow ui;

	QWidget* widget = nullptr;
	QVBoxLayout* mainLayout = nullptr;
	QLabel* imageLabel = nullptr;
	QLabel* fileNameLabel = nullptr;
	QImage* image = nullptr;


private slots:
	
};

