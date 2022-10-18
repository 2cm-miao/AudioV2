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
#include <fftw3.h>

#include "spectrumProcess.h"
#include "sigpack.h"
using namespace sp;
using namespace arma;
using namespace std;

typedef struct WAVEINFO {
	uint8_t  riffHeader[4];  // RIFF Header Magic header
	uint32_t riffChunkSize;  // RIFF Chunk Size
	uint8_t  waveHeader[4];  // WAVE Header
	uint8_t  fmtHeader[4];   // FMT header
	uint32_t fmtChunkSize;   // Size of the fmt chunk
	uint16_t audioFormat;    // Audio format
	uint16_t numOfChannels;  // Number of channels
	uint32_t samplesPerSec;  // Sampling Frequency in Hz  采样率
	uint32_t bytesPerSec;    // bytes per second   音频文件大小
	uint16_t blockAlign;     // 2=16-bit mono, 4=16-bit stereo  判断单声道或是双声道
	uint16_t bitsPerSample;  // Number of bits per sample
	uint8_t  Subchunk2ID[4]; // "data"  string
	uint32_t Subchunk2Size;  // Sampled data length
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

	fftw_complex *in = (fftw_complex*)fftw_malloc(numsOfSamples / 2 * sizeof(fftw_complex));
	fftw_complex *out = (fftw_complex*)fftw_malloc(numsOfSamples / 2 * sizeof(fftw_complex));
	for (int i = 0; i < numsOfSamples / 2; i++)
	{
		in[i][0] = x(0, i);
		in[i][1] = (int16_t)0;
	}

	fftw_plan p = fftw_plan_dft_1d(numsOfSamples / 2, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

	fftw_execute(p);

	// power
	Col<int16_t> dests(numsOfSamples / 2);
	for (int i = 0; i < (numsOfSamples / 2); i++) {
		dests[i] = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
	}

	fftw_destroy_plan(p);
	fftw_cleanup();

	// Calculate the spectrogram size
	const int FFT_SIZE = 1024;
	const int FFT_OVERLAP = 128;
	//mat P = 10 * log10(abs(specgram(dests, FFT_SIZE, FFT_OVERLAP)));  // calculate the power of data
	mat P = specgram(dests, FFT_SIZE, FFT_OVERLAP);
	//mat Q = P.rows(FFT_SIZE / 2, FFT_SIZE - 1); // Cut out the positive parts


	// draw the spectrumprocess image
	QImage image(P.n_cols, P.n_rows, QImage::Format_RGB32);
	uint32_t value;

	for (int y = 0; y < P.n_rows; y++) {
		//value = qRgb(122, 163, 39);
		for (int j = 0; j < P.n_cols; ++j) {
			image.setPixel(j, y, setColor(P(y, j)));
		}
	}

	fileNameLabel->setText(filePath);
	imageLabel->setPixmap(QPixmap::fromImage(image));
}

uint32_t SpectrumProcess::setColor(int16_t level) {
	level *= 0.6625;
	double r = 0.0, g = 0.0, b = 0.0;
	if (level >= 0 && level < 0.15) {
		r = (0.15 - level) / (0.15 + 0.075);
		g = 0.0;
		b = 1.0;
	}
	else if (level >= 0.15 && level < 0.275) {
		r = 0.0;
		g = (level - 0.15) / (0.275 - 0.15);
		b = 1.0;
	}
	else if (level >= 0.275 && level < 0.325) {
		r = 0.0;
		g = 1.0;
		b = (0.325 - level) / (0.325 - 0.275);
	}
	else if (level >= 0.325 && level < 0.5) {
		r = (level - 0.325) / (0.5 - 0.325);
		g = 1.0;
		b = 0.0;
	}
	else if (level >= 0.5 && level < 0.6625) {
		r = 1.0;
		g = (0.6625 - level) / (0.6625 - 0.5f);
		b = 0.0;
	}

	// Intensity correction.
	double cf = 1.0;
	if (level >= 0.0 && level < 0.1) {
		cf = level / 0.1;
	}
	cf *= 255.0;

	// Pack RGB values into a 32-bit uint.
	uint32_t rr = (uint32_t)(r * cf + 0.5);
	uint32_t gg = (uint32_t)(g * cf + 0.5);
	uint32_t bb = (uint32_t)(b * cf + 0.5);

	return (rr << 16) + (gg << 8) + bb;
	//return 32;
}


