/********************************************************************************
** Form generated from reading UI file 'AudioV2.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUDIOV2_H
#define UI_AUDIOV2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AudioV2Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AudioV2Class)
    {
        if (AudioV2Class->objectName().isEmpty())
            AudioV2Class->setObjectName(QString::fromUtf8("AudioV2Class"));
        AudioV2Class->resize(600, 400);
        menuBar = new QMenuBar(AudioV2Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        AudioV2Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AudioV2Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        AudioV2Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(AudioV2Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        AudioV2Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(AudioV2Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        AudioV2Class->setStatusBar(statusBar);

        retranslateUi(AudioV2Class);

        QMetaObject::connectSlotsByName(AudioV2Class);
    } // setupUi

    void retranslateUi(QMainWindow *AudioV2Class)
    {
        AudioV2Class->setWindowTitle(QCoreApplication::translate("AudioV2Class", "AudioV2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AudioV2Class: public Ui_AudioV2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUDIOV2_H