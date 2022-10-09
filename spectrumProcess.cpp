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

typedef struct WAV_HEADER {
	uint8_t RIFF[4];        // RIFF Header Magic header
	uint32_t chunkSize;     // RIFF Chunk Size
	uint8_t WAVE[4];        // WAVE Header
	uint8_t fmt[4];         // FMT header
	uint32_t subchunk1Size; // Size of the fmt chunk
	uint16_t audioFormat;   // Audio format
	uint16_t numOfChan;     // Number of channels
	uint32_t samplesPerSec; // Sampling Frequency in Hz
	uint32_t bytesPerSec;   // bytes per second
	uint16_t blockAlign;    // 2=16-bit mono, 4=16-bit stereo
	uint16_t bitsPerSample; // Number of bits per sample
	uint8_t subchunk2ID[4]; // "data"  string
	uint32_t subchunk2Size; // Sampled data length
} wav_header;


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

void SpectrumProcess::exampleFunction(const QString& filePath) {
	// open file
	//QByteArray cacheFilePath = filePath.toLatin1();
	//char* charFilePath = cacheFilePath.data();
	//FILE* wavFile = fopen(charFilePath, "r");
	FILE* wavFile = fopen("D:/apps/thx-sound-test/thx-sound-test.wav", "r");

	// read info about the file
	wav_header wavHeader;
	fread(&wavHeader, 1, sizeof(wav_header), wavFile);

	//// Read the data
	//uint16_t Nb = wavHeader.bitsPerSample / 8;     // Number of bytes per sample
	//uint32_t Ns = (wavHeader.chunkSize - 36) / Nb; // Number of samples
	//arma::Mat<int16_t> x(wavHeader.numOfChan, Ns / wavHeader.numOfChan);
	//fread(x.memptr(), Nb, Ns, wavFile);
	//fclose(wavFile);

	//// Get the left channel
	//arma::Col<int16_t> x_left = x.row(0).t();

	//// Calculate the spectrogram
	//const int FFT_SIZE = 1024;
	//const int FFT_OVERLAP = 128;
	//arma::mat P = 10 * log10(abs(specgram(x_left, FFT_SIZE, FFT_OVERLAP)));

	//system("pause");

	//// Plot
	//arma::mat Q = P.rows(FFT_SIZE / 2, FFT_SIZE - 1); // Cut out the positive parts
	//gplot gp0;
	//gp0.window("Deep note spectrogram", 100, 100, 1200, 400);
	//gp0.send2gp("unset tics");
	//gp0.send2gp("unset colorbox");
	//gp0.image(Q);
	//return;



	QImage image(100, 100, QImage::Format_RGB32);
	QRgb value;

	value = qRgb(189, 149, 39); // 0xffbd9527
	image.setPixel(1, 1, value);

	value = qRgb(122, 163, 39); // 0xff7aa327
	image.setPixel(0, 1, value);
	image.setPixel(1, 0, value);

	value = qRgb(237, 187, 51); // 0xffedba31
	image.setPixel(2, 1, value);

	fileNameLabel->setText(fileName);
	imageLabel->setPixmap(QPixmap::fromImage(image));

	//myLabel.show();
}
