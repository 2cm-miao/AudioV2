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

#include "spectrumProcess.h"
#include "sigpack.h"
using namespace sp;

typedef struct WAVEINFO {
	uint8_t riffHeader[4];        // RIFF Header Magic header
	uint32_t riffChunkSize;     // RIFF Chunk Size
	uint8_t waveHeader[4];        // WAVE Header
	uint8_t fmtHeader[4];         // FMT header
	uint32_t fmtChunkSize; // Size of the fmt chunk
	uint16_t audioFormat;   // Audio format
	uint16_t numOfChannels;     // Number of channels
	uint32_t samplesPerSec; // Sampling Frequency in Hz
	uint32_t bytesPerSec;   // bytes per second
	uint16_t blockAlign;    // 2=16-bit mono, 4=16-bit stereo
	uint16_t bitsPerSample; // Number of bits per sample
	uint8_t subchunk2ID[4]; // "data"  string
	uint32_t subchunk2Size; // Sampled data length
} waveInfo;


SpectrumProcess::SpectrumProcess(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setWindowTitle(tr("Spectrum Image"));

	//image label
	fileNameLabel = new QLabel();
	imageLabel = new QLabel();

	//main layout
	widget = new QWidget();
	mainLayout = new QVBoxLayout(widget);
	mainLayout->addWidget(fileNameLabel);
	mainLayout->addWidget(imageLabel);

	//set main layout
	this->setCentralWidget(widget);
	setLayout(mainLayout);
}

SpectrumProcess::~SpectrumProcess() {
}

static int bits_to_bands(int bits) {
	return (1 << (bits - 1)) + 1;
}

void SpectrumProcess::exampleFunction(const QString& filePath) {
	//if (filePath.isEmpty()) {
	//	QMessageBox m(this);
	//	m.setWindowTitle("ERROR");
	//	m.setText("Please Choose a file.");
	//	m.show();
	//	m.exec();
	//}

	// open file
	//QByteArray cacheFilePath = filePath.toLatin1();
	//char* charFilePath = cacheFilePath.data();
	//FILE* wavFile = fopen(charFilePath, "r");
	FILE* wavFile = fopen("D:/apps/thx-sound-test/thx-sound-test.wav", "r");

	// read info about the file
	waveInfo waveInformation;
	fread(&waveInformation, 1, sizeof(waveInfo), wavFile);
	fclose(wavFile);

	// process the data of audio
	uint16_t bytesPerSample = waveInformation.bitsPerSample / 8; // Number of bytes per sample
	uint32_t numsOfSamples = (waveInformation.riffChunkSize - 36) / bytesPerSample; // Number of samples

	// draw the spectrumprocess image
	QImage image(numsOfSamples, bits_to_bands(waveInformation.bitsPerSample), QImage::Format_RGB32);
	//QImage image(width() - 60 - 90, 500, QImage::Format_RGB32);
	QRgb value;

	for (int y = 0; y < bits_to_bands(waveInformation.bitsPerSample); y++) {
		value = qRgb(122, 163, 39);
		for (int j = 0; j < numsOfSamples; ++j) {
			image.setPixel(j, bits_to_bands(waveInformation.bitsPerSample) - y - 1, value);
		}
	}

	//value = qRgb(122, 163, 39); // 0xff7aa327
	//image.setColor(0, value);

	//value = qRgb(237, 187, 51); // 0xffedba31
	//image.setColor(1, value);

	//value = qRgb(189, 149, 39); // 0xffbd9527
	//image.setColor(2, value);

	//image.setPixel(0, 1, 0);
	//image.setPixel(1, 0, 0);
	//image.setPixel(1, 1, 2);
	//image.setPixel(2, 1, 1);

	fileNameLabel->setText(filePath);
	imageLabel->setPixmap(QPixmap::fromImage(image));


}
