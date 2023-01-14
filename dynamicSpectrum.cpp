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
}

void AudioV2::setInputDevice() {

}



