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
using namespace arma;

typedef struct WAVEINFO {
	uint8_t riffHeader[4];  // RIFF Header Magic header
	uint32_t riffChunkSize; // RIFF Chunk Size
	uint8_t waveHeader[4];  // WAVE Header
	uint8_t fmtHeader[4];   // FMT header
	uint32_t fmtChunkSize;  // Size of the fmt chunk
	uint16_t audioFormat;   // Audio format
	uint16_t numOfChannels; // Number of channels
	uint32_t samplesPerSec; // Sampling Frequency in Hz  采样率
	uint32_t bytesPerSec;   // bytes per second   音频文件大小
	uint16_t blockAlign;    // 2=16-bit mono, 4=16-bit stereo  判断单声道或是双声道
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

	// process the data of audio
	uint16_t bytesPerSample = waveInformation.bitsPerSample / 8; // Number of bytes per sample
	uint32_t numsOfSamples = (waveInformation.riffChunkSize - 36) / bytesPerSample; // Number of samples

	Mat<int16_t> x(waveInformation.numOfChannels, numsOfSamples / waveInformation.numOfChannels);
	fread(x.memptr(), bytesPerSample, numsOfSamples, wavFile);
	fclose(wavFile);

	// Get the left channel
	Col<int16_t> x_left = x.row(0).t();  // .t()的作用是转置

	// Calculate the spectrogram
	const int FFT_SIZE = 1024;
	const int FFT_OVERLAP = 128;
	mat P = 10 * log10(abs(specgram(x_left, FFT_SIZE, FFT_OVERLAP)));
	mat Q = P.rows(FFT_SIZE / 2, FFT_SIZE - 1); // Cut out the positive parts

	// draw the spectrumprocess image
	QImage image(Q.n_cols, Q.n_rows, QImage::Format_RGB32);
	//QImage image(width() - 60 - 90, 500, QImage::Format_RGB32);
	QRgb value;

	mat A_row = Q.submat(span(1, 3), span(1, 3));

	for (int y = 0; y < Q.n_rows; y++) {
		value = qRgb(122, 163, 39);
		for (int j = 0; j < Q.n_cols; ++j) {
			image.setPixel(j, Q.n_rows - y - 1, value);
		}
	}

	fileNameLabel->setText(filePath);
	imageLabel->setPixmap(QPixmap::fromImage(image));
}
