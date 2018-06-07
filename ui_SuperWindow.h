/********************************************************************************
** Form generated from reading UI file 'SuperWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUPERWINDOW_H
#define UI_SUPERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SuperWindow
{
public:
    QWidget *centralWidget;
    QLabel *ChessBoardLabel;
    QLCDNumber *BlackNumber;
    QLCDNumber *WhiteNumber;
    QLabel *BlackPieceImage;
    QLabel *WhitePieceImage;
    QPushButton *Undo;
    QPushButton *Redo;
    QPushButton *Restart;
    QPushButton *AI;
    QComboBox *BlackAI;
    QComboBox *WhiteAI;
    QLCDNumber *Timer;

    void setupUi(QMainWindow *SuperWindow)
    {
        if (SuperWindow->objectName().isEmpty())
            SuperWindow->setObjectName(QStringLiteral("SuperWindow"));
        SuperWindow->resize(361, 527);
        SuperWindow->setStyleSheet(QLatin1String("QPushButton{\n"
"	border : 1px solid black;\n"
"}\n"
"\n"
"#centralWidget{\n"
"	background-image : url(:/Image/ChessBoard.jpg);\n"
"}\n"
"\n"
"#Restart, #Undo, #Redo, #AI{\n"
"	border : none;\n"
"	border-radius : 5px;\n"
" 	background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                       stop:0 rgb(0, 0, 255), stop:1 rgb(0, 0, 155));\n"
"	color : white;\n"
"	font-family : 'Consolas';\n"
"}\n"
"\n"
"#Restart:hover, #Undo:hover, #Redo:hover, #AI:hover{\n"
"	background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                       stop:0 rgb(0, 0, 200), stop:1 rgb(0, 0, 100));\n"
"}"));
        centralWidget = new QWidget(SuperWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ChessBoardLabel = new QLabel(centralWidget);
        ChessBoardLabel->setObjectName(QStringLiteral("ChessBoardLabel"));
        ChessBoardLabel->setGeometry(QRect(20, 30, 320, 320));
        BlackNumber = new QLCDNumber(centralWidget);
        BlackNumber->setObjectName(QStringLiteral("BlackNumber"));
        BlackNumber->setGeometry(QRect(59, 480, 61, 30));
        QFont font;
        font.setPointSize(15);
        BlackNumber->setFont(font);
        WhiteNumber = new QLCDNumber(centralWidget);
        WhiteNumber->setObjectName(QStringLiteral("WhiteNumber"));
        WhiteNumber->setGeometry(QRect(240, 480, 61, 30));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WhiteNumber->sizePolicy().hasHeightForWidth());
        WhiteNumber->setSizePolicy(sizePolicy);
        WhiteNumber->setMinimumSize(QSize(0, 0));
        WhiteNumber->setFont(font);
        BlackPieceImage = new QLabel(centralWidget);
        BlackPieceImage->setObjectName(QStringLiteral("BlackPieceImage"));
        BlackPieceImage->setGeometry(QRect(80, 440, 40, 40));
        BlackPieceImage->setTextFormat(Qt::AutoText);
        WhitePieceImage = new QLabel(centralWidget);
        WhitePieceImage->setObjectName(QStringLiteral("WhitePieceImage"));
        WhitePieceImage->setGeometry(QRect(230, 440, 40, 40));
        Undo = new QPushButton(centralWidget);
        Undo->setObjectName(QStringLiteral("Undo"));
        Undo->setGeometry(QRect(140, 430, 75, 23));
        Redo = new QPushButton(centralWidget);
        Redo->setObjectName(QStringLiteral("Redo"));
        Redo->setGeometry(QRect(140, 460, 75, 23));
        Restart = new QPushButton(centralWidget);
        Restart->setObjectName(QStringLiteral("Restart"));
        Restart->setGeometry(QRect(140, 490, 75, 23));
        AI = new QPushButton(centralWidget);
        AI->setObjectName(QStringLiteral("AI"));
        AI->setGeometry(QRect(140, 400, 75, 23));
        BlackAI = new QComboBox(centralWidget);
        BlackAI->setObjectName(QStringLiteral("BlackAI"));
        BlackAI->setGeometry(QRect(20, 400, 104, 26));
        WhiteAI = new QComboBox(centralWidget);
        WhiteAI->setObjectName(QStringLiteral("WhiteAI"));
        WhiteAI->setGeometry(QRect(230, 400, 104, 26));
        Timer = new QLCDNumber(centralWidget);
        Timer->setObjectName(QStringLiteral("Timer"));
        Timer->setGeometry(QRect(150, 360, 61, 31));
        QFont font1;
        font1.setKerning(true);
        Timer->setFont(font1);
        Timer->setSegmentStyle(QLCDNumber::Outline);
        SuperWindow->setCentralWidget(centralWidget);

        retranslateUi(SuperWindow);

        QMetaObject::connectSlotsByName(SuperWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SuperWindow)
    {
        SuperWindow->setWindowTitle(QApplication::translate("SuperWindow", "SuperWindow", Q_NULLPTR));
        ChessBoardLabel->setText(QString());
        BlackPieceImage->setText(QString());
        WhitePieceImage->setText(QString());
        Undo->setText(QApplication::translate("SuperWindow", "Undo", Q_NULLPTR));
        Redo->setText(QApplication::translate("SuperWindow", "Redo", Q_NULLPTR));
        Restart->setText(QApplication::translate("SuperWindow", "Restart", Q_NULLPTR));
        AI->setText(QApplication::translate("SuperWindow", "Start", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SuperWindow: public Ui_SuperWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUPERWINDOW_H
