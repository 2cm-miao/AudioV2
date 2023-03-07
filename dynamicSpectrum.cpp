#include "playerInterface.h"
#include "spectrumProcess.h"
#include "qcustomplot.h"

void AudioV2::drawDynamicSpectrumBar()
{
	//QPainter spectrumPainter(dynamicSpectrumLabel);
	//spectrumPainter.fillRect(rect(), Qt::black);
	//spectrumPainter.setPen((QPen(Qt::blue)));
	//
	//for (int i = 1; i < 1199; i+=12) {
	//	QRect bar = rect();
	//	bar.setLeft(i);
	//	bar.setWidth(10);
	//	bar.setTop(100);
	//	bar.setBottom(20);
	//
	//	spectrumPainter.fillRect(bar, Qt::blue);
	//}
	//
	//QVector<double> x(101), y(101);
	//for (int i = 0; i < 101; i++) {
	//	x[i] = i / 50.0 - 1;
	//	y[i] = x[i] * x[i];
	//}
	customPlot->addGraph();
	customPlot->setFixedSize(1200, 200);
	//customPlot->graph(0)->setData(x, y);
	customPlot->xAxis->setLabel("Frequency");
	customPlot->yAxis->setLabel("dB");
	customPlot->yAxis->setRange(-60, 0);
	customPlot->xAxis->setRange(0, 22000);
	customPlot->replot();
	customPlot->graph()->setPen(QPen(Qt::black));
}

void AudioV2::audioBufferProcess() {
	inputBuffer.seek(0);
	QByteArray ba = inputBuffer.readAll();

	int num_samples = ba.length() / 2;
	int b_pos = 0;
	for (int i = 0; i < num_samples; i++) {
		int16_t s;
		s = ba.at(b_pos++);
		s |= ba.at(b_pos++) << 8;
		if (s != 0) {
			audioSample.append((double)s / 32768.0);
		}
		else {
			audioSample.append(0);
		}
	}
	inputBuffer.buffer().clear();
	inputBuffer.seek(0);

	audioFFTProcess();
}

void AudioV2::audioFFTProcess() {
	int n = audioSample.length();
	if (n > 96000) audioSample = audioSample.mid(n - 96000, -1);

	memcpy(mFftIn, audioSample.data(), 96000 * sizeof(double));

	fftw_execute(mFftPlan);

	QVector<double> fftVec;

	for (int i = (96000 / 48000) * 20; i < (96000 / 48000) * 20000; i++) {
		fftVec.append(abs(mFftOut[i]));
	}

	customPlot->graph(0)->setData(mFftIndices.mid(0, fftVec.length()), fftVec);
	customPlot->replot();
}

