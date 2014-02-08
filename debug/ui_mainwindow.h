/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue Jun 18 04:39:09 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWebView *webView;
    QLabel *label_2;
    QSlider *horizontalSlider;
    QLabel *label;
    QLabel *label_3;
    QWebView *webView_2;
    QWebView *webView_3;
    QLabel *label_4;
    QSlider *horizontalSlider_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1860, 945);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        webView = new QWebView(centralwidget);
        webView->setObjectName(QString::fromUtf8("webView"));
        webView->setGeometry(QRect(30, 10, 651, 481));
        webView->setUrl(QUrl(QString::fromUtf8("about:blank")));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 590, 151, 17));
        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(20, 620, 391, 29));
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setTickPosition(QSlider::TicksBelow);
        horizontalSlider->setTickInterval(10);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 650, 16, 17));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(400, 650, 31, 17));
        webView_2 = new QWebView(centralwidget);
        webView_2->setObjectName(QString::fromUtf8("webView_2"));
        webView_2->setGeometry(QRect(700, 10, 621, 631));
        webView_2->setUrl(QUrl(QString::fromUtf8("about:blank")));
        webView_3 = new QWebView(centralwidget);
        webView_3->setObjectName(QString::fromUtf8("webView_3"));
        webView_3->setGeometry(QRect(1330, 10, 541, 631));
        webView_3->setUrl(QUrl(QString::fromUtf8("about:blank")));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(620, 820, 171, 17));
        horizontalSlider_2 = new QSlider(centralwidget);
        horizontalSlider_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
        horizontalSlider_2->setGeometry(QRect(620, 850, 351, 29));
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1860, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Set K for Anonymizing", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "99", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Time Series Visualization", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
