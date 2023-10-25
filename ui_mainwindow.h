/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_15;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_14;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *pathLineEdit;
    QPushButton *fileOpenButton;
    QLabel *sizeLabel;
    QLabel *creationLabel;
    QLabel *modificationLabel;
    QLabel *packCountLabel;
    QLabel *maxLenLabel;
    QLabel *minLenLabel;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *binaryButton;
    QPushButton *decButton;
    QPushButton *hexButton;
    QPushButton *textButton;
    QSpacerItem *horizontalSpacer;
    QTableWidget *sigViewer;
    QVBoxLayout *verticalLayout_13;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QTextBrowser *textBrowser;
    QProgressBar *decompressionProgressBar;
    QHBoxLayout *horizontalLayout_7;
    QLabel *readedBitCountLabel;
    QPushButton *clearTextBrowserButton;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *charAlfBox;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_3;
    QProgressBar *charAlfProgress;
    QLabel *charAlfStatus;
    QLabel *charAlfCount;
    QPushButton *charAlfPresentButton;
    QGroupBox *lenAlfBox;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_4;
    QProgressBar *lenAlfProgress;
    QLabel *lenAlfStatus;
    QLabel *lenAlfCount;
    QPushButton *lenAlfPresentButton;
    QGroupBox *moveAlfBox;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QProgressBar *moveAlfProgress;
    QLabel *moveAlfStatus;
    QLabel *moveAlfCount;
    QPushButton *moveAlfPresentButton;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_10;
    QRadioButton *decodeFlow;
    QRadioButton *decodeBlocs;
    QHBoxLayout *horizontalLayout_9;
    QLabel *seekPositionLabel;
    QSpinBox *seekSpinBox;
    QVBoxLayout *verticalLayout_11;
    QCheckBox *staticBlocks;
    QCheckBox *dynamicBlocks;
    QCheckBox *noCompressionBlocks;
    QPushButton *pushButton;
    QPushButton *errorFixerButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1025, 775);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_15 = new QVBoxLayout(centralwidget);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pathLineEdit = new QLineEdit(groupBox_2);
        pathLineEdit->setObjectName(QString::fromUtf8("pathLineEdit"));

        horizontalLayout->addWidget(pathLineEdit);

        fileOpenButton = new QPushButton(groupBox_2);
        fileOpenButton->setObjectName(QString::fromUtf8("fileOpenButton"));

        horizontalLayout->addWidget(fileOpenButton);


        verticalLayout->addLayout(horizontalLayout);

        sizeLabel = new QLabel(groupBox_2);
        sizeLabel->setObjectName(QString::fromUtf8("sizeLabel"));

        verticalLayout->addWidget(sizeLabel);

        creationLabel = new QLabel(groupBox_2);
        creationLabel->setObjectName(QString::fromUtf8("creationLabel"));

        verticalLayout->addWidget(creationLabel);

        modificationLabel = new QLabel(groupBox_2);
        modificationLabel->setObjectName(QString::fromUtf8("modificationLabel"));

        verticalLayout->addWidget(modificationLabel);

        packCountLabel = new QLabel(groupBox_2);
        packCountLabel->setObjectName(QString::fromUtf8("packCountLabel"));

        verticalLayout->addWidget(packCountLabel);

        maxLenLabel = new QLabel(groupBox_2);
        maxLenLabel->setObjectName(QString::fromUtf8("maxLenLabel"));

        verticalLayout->addWidget(maxLenLabel);

        minLenLabel = new QLabel(groupBox_2);
        minLenLabel->setObjectName(QString::fromUtf8("minLenLabel"));

        verticalLayout->addWidget(minLenLabel);


        horizontalLayout_2->addLayout(verticalLayout);


        verticalLayout_14->addWidget(groupBox_2);

        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout_9 = new QVBoxLayout(groupBox_4);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        binaryButton = new QPushButton(groupBox_4);
        binaryButton->setObjectName(QString::fromUtf8("binaryButton"));
        binaryButton->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_6->addWidget(binaryButton);

        decButton = new QPushButton(groupBox_4);
        decButton->setObjectName(QString::fromUtf8("decButton"));
        decButton->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_6->addWidget(decButton);

        hexButton = new QPushButton(groupBox_4);
        hexButton->setObjectName(QString::fromUtf8("hexButton"));
        hexButton->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_6->addWidget(hexButton);

        textButton = new QPushButton(groupBox_4);
        textButton->setObjectName(QString::fromUtf8("textButton"));
        textButton->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_6->addWidget(textButton);

        horizontalSpacer = new QSpacerItem(70, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);


        verticalLayout_9->addLayout(horizontalLayout_6);

        sigViewer = new QTableWidget(groupBox_4);
        sigViewer->setObjectName(QString::fromUtf8("sigViewer"));
        sigViewer->setMinimumSize(QSize(460, 159));

        verticalLayout_9->addWidget(sigViewer);


        verticalLayout_14->addWidget(groupBox_4);


        horizontalLayout_10->addLayout(verticalLayout_14);

        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_3 = new QHBoxLayout(groupBox);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        textBrowser = new QTextBrowser(groupBox);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout_2->addWidget(textBrowser);

        decompressionProgressBar = new QProgressBar(groupBox);
        decompressionProgressBar->setObjectName(QString::fromUtf8("decompressionProgressBar"));
        decompressionProgressBar->setValue(0);

        verticalLayout_2->addWidget(decompressionProgressBar);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        readedBitCountLabel = new QLabel(groupBox);
        readedBitCountLabel->setObjectName(QString::fromUtf8("readedBitCountLabel"));

        horizontalLayout_7->addWidget(readedBitCountLabel);

        clearTextBrowserButton = new QPushButton(groupBox);
        clearTextBrowserButton->setObjectName(QString::fromUtf8("clearTextBrowserButton"));
        clearTextBrowserButton->setMaximumSize(QSize(101, 16777215));

        horizontalLayout_7->addWidget(clearTextBrowserButton);


        verticalLayout_2->addLayout(horizontalLayout_7);


        horizontalLayout_3->addLayout(verticalLayout_2);


        verticalLayout_13->addWidget(groupBox);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        horizontalLayout_5 = new QHBoxLayout(groupBox_3);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        charAlfBox = new QGroupBox(groupBox_3);
        charAlfBox->setObjectName(QString::fromUtf8("charAlfBox"));
        charAlfBox->setMinimumSize(QSize(150, 140));
        verticalLayout_8 = new QVBoxLayout(charAlfBox);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        charAlfProgress = new QProgressBar(charAlfBox);
        charAlfProgress->setObjectName(QString::fromUtf8("charAlfProgress"));
        charAlfProgress->setValue(0);

        verticalLayout_3->addWidget(charAlfProgress);

        charAlfStatus = new QLabel(charAlfBox);
        charAlfStatus->setObjectName(QString::fromUtf8("charAlfStatus"));

        verticalLayout_3->addWidget(charAlfStatus);

        charAlfCount = new QLabel(charAlfBox);
        charAlfCount->setObjectName(QString::fromUtf8("charAlfCount"));

        verticalLayout_3->addWidget(charAlfCount);

        charAlfPresentButton = new QPushButton(charAlfBox);
        charAlfPresentButton->setObjectName(QString::fromUtf8("charAlfPresentButton"));

        verticalLayout_3->addWidget(charAlfPresentButton);


        verticalLayout_8->addLayout(verticalLayout_3);


        horizontalLayout_4->addWidget(charAlfBox);

        lenAlfBox = new QGroupBox(groupBox_3);
        lenAlfBox->setObjectName(QString::fromUtf8("lenAlfBox"));
        lenAlfBox->setMinimumSize(QSize(150, 140));
        verticalLayout_7 = new QVBoxLayout(lenAlfBox);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        lenAlfProgress = new QProgressBar(lenAlfBox);
        lenAlfProgress->setObjectName(QString::fromUtf8("lenAlfProgress"));
        lenAlfProgress->setValue(0);

        verticalLayout_4->addWidget(lenAlfProgress);

        lenAlfStatus = new QLabel(lenAlfBox);
        lenAlfStatus->setObjectName(QString::fromUtf8("lenAlfStatus"));

        verticalLayout_4->addWidget(lenAlfStatus);

        lenAlfCount = new QLabel(lenAlfBox);
        lenAlfCount->setObjectName(QString::fromUtf8("lenAlfCount"));

        verticalLayout_4->addWidget(lenAlfCount);

        lenAlfPresentButton = new QPushButton(lenAlfBox);
        lenAlfPresentButton->setObjectName(QString::fromUtf8("lenAlfPresentButton"));

        verticalLayout_4->addWidget(lenAlfPresentButton);


        verticalLayout_7->addLayout(verticalLayout_4);


        horizontalLayout_4->addWidget(lenAlfBox);

        moveAlfBox = new QGroupBox(groupBox_3);
        moveAlfBox->setObjectName(QString::fromUtf8("moveAlfBox"));
        moveAlfBox->setMinimumSize(QSize(150, 140));
        verticalLayout_6 = new QVBoxLayout(moveAlfBox);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        moveAlfProgress = new QProgressBar(moveAlfBox);
        moveAlfProgress->setObjectName(QString::fromUtf8("moveAlfProgress"));
        moveAlfProgress->setValue(0);

        verticalLayout_5->addWidget(moveAlfProgress);

        moveAlfStatus = new QLabel(moveAlfBox);
        moveAlfStatus->setObjectName(QString::fromUtf8("moveAlfStatus"));

        verticalLayout_5->addWidget(moveAlfStatus);

        moveAlfCount = new QLabel(moveAlfBox);
        moveAlfCount->setObjectName(QString::fromUtf8("moveAlfCount"));

        verticalLayout_5->addWidget(moveAlfCount);

        moveAlfPresentButton = new QPushButton(moveAlfBox);
        moveAlfPresentButton->setObjectName(QString::fromUtf8("moveAlfPresentButton"));

        verticalLayout_5->addWidget(moveAlfPresentButton);


        verticalLayout_6->addLayout(verticalLayout_5);


        horizontalLayout_4->addWidget(moveAlfBox);


        horizontalLayout_5->addLayout(horizontalLayout_4);


        verticalLayout_13->addWidget(groupBox_3);

        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        verticalLayout_12 = new QVBoxLayout(groupBox_5);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        decodeFlow = new QRadioButton(groupBox_5);
        decodeFlow->setObjectName(QString::fromUtf8("decodeFlow"));

        verticalLayout_10->addWidget(decodeFlow);

        decodeBlocs = new QRadioButton(groupBox_5);
        decodeBlocs->setObjectName(QString::fromUtf8("decodeBlocs"));

        verticalLayout_10->addWidget(decodeBlocs);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        seekPositionLabel = new QLabel(groupBox_5);
        seekPositionLabel->setObjectName(QString::fromUtf8("seekPositionLabel"));

        horizontalLayout_9->addWidget(seekPositionLabel);

        seekSpinBox = new QSpinBox(groupBox_5);
        seekSpinBox->setObjectName(QString::fromUtf8("seekSpinBox"));
        seekSpinBox->setMaximum(9999);

        horizontalLayout_9->addWidget(seekSpinBox);


        verticalLayout_10->addLayout(horizontalLayout_9);


        horizontalLayout_8->addLayout(verticalLayout_10);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        staticBlocks = new QCheckBox(groupBox_5);
        staticBlocks->setObjectName(QString::fromUtf8("staticBlocks"));

        verticalLayout_11->addWidget(staticBlocks);

        dynamicBlocks = new QCheckBox(groupBox_5);
        dynamicBlocks->setObjectName(QString::fromUtf8("dynamicBlocks"));

        verticalLayout_11->addWidget(dynamicBlocks);

        noCompressionBlocks = new QCheckBox(groupBox_5);
        noCompressionBlocks->setObjectName(QString::fromUtf8("noCompressionBlocks"));

        verticalLayout_11->addWidget(noCompressionBlocks);


        horizontalLayout_8->addLayout(verticalLayout_11);


        verticalLayout_12->addLayout(horizontalLayout_8);

        pushButton = new QPushButton(groupBox_5);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_12->addWidget(pushButton);


        verticalLayout_13->addWidget(groupBox_5);


        horizontalLayout_10->addLayout(verticalLayout_13);


        verticalLayout_15->addLayout(horizontalLayout_10);

        errorFixerButton = new QPushButton(centralwidget);
        errorFixerButton->setObjectName(QString::fromUtf8("errorFixerButton"));

        verticalLayout_15->addWidget(errorFixerButton);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1025, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\320\236\321\201\320\275\320\276\320\262\320\275\321\213\320\265 \321\201\320\262\320\265\320\264\320\265\320\275\320\270\321\217", nullptr));
        pathLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\240\320\260\321\201\320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\320\265 \321\204\320\260\320\271\320\273\320\260", nullptr));
        fileOpenButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        sizeLabel->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200 \321\204\320\260\320\271\320\273\320\260:", nullptr));
        creationLabel->setText(QCoreApplication::translate("MainWindow", "\320\224\320\260\321\202\320\260 \320\270 \320\262\321\200\320\265\320\274\321\217 \321\201\320\276\320\267\320\264\320\260\320\275\320\270\321\217 \321\204\320\260\320\271\320\273\320\260:", nullptr));
        modificationLabel->setText(QCoreApplication::translate("MainWindow", "\320\224\320\260\321\202\320\260 \320\270 \320\262\321\200\320\265\320\274\321\217 \320\277\320\276\321\201\320\273\320\265\320\264\320\275\320\265\320\263\320\276 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217:", nullptr));
        packCountLabel->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\277\320\260\320\272\320\265\321\202\320\276\320\262:", nullptr));
        maxLenLabel->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\320\272\321\201\320\270\320\274\320\260\320\273\321\214\320\275\320\260\321\217 \320\264\320\273\320\270\320\275\320\260 \320\277\320\260\320\272\320\265\321\202\320\260:", nullptr));
        minLenLabel->setText(QCoreApplication::translate("MainWindow", "\320\234\320\270\320\275\320\270\320\274\320\260\320\273\321\214\320\275\320\260\321\217 \320\264\320\273\320\270\320\275\320\260 \320\277\320\260\320\272\320\265\321\202\320\260:", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265 \320\277\320\260\320\272\320\265\321\202\320\275\321\213\321\205 \321\201\321\202\321\200\321\203\320\272\321\202\321\203\321\200", nullptr));
        binaryButton->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        decButton->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        hexButton->setText(QCoreApplication::translate("MainWindow", "16", nullptr));
        textButton->setText(QCoreApplication::translate("MainWindow", "T", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265 \320\275\320\260\320\271\320\264\320\265\320\275\320\275\321\213\321\205 \321\201\320\270\320\274\320\262\320\276\320\273\320\276\320\262 \320\270 \320\272\320\276\320\264\320\276\320\262", nullptr));
        readedBitCountLabel->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\321\207\320\270\321\202\320\260\320\275\320\276 \320\261\320\270\321\202:", nullptr));
        clearTextBrowserButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\262\320\276\320\264 \320\260\320\273\321\204\320\260\320\262\320\270\321\202\320\276\320\262", nullptr));
        charAlfBox->setTitle(QCoreApplication::translate("MainWindow", "\320\220\320\273\321\204\320\260\320\262\320\270\321\202 \321\201\320\270\320\274\320\262\320\276\320\273\320\276\320\262", nullptr));
        charAlfStatus->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\321\203\321\201", nullptr));
        charAlfCount->setText(QCoreApplication::translate("MainWindow", "\320\255\320\273\320\265\320\274\320\265\320\275\321\202\321\213: ", nullptr));
        charAlfPresentButton->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\262\320\265\321\201\321\202\320\270", nullptr));
        lenAlfBox->setTitle(QCoreApplication::translate("MainWindow", "\320\220\320\273\321\204\320\260\320\262\320\270\321\202 \320\264\320\273\320\270\320\275", nullptr));
        lenAlfStatus->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\321\203\321\201", nullptr));
        lenAlfCount->setText(QCoreApplication::translate("MainWindow", "\320\255\320\273\320\265\320\274\320\265\320\275\321\202\321\213:", nullptr));
        lenAlfPresentButton->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\262\320\265\321\201\321\202\320\270", nullptr));
        moveAlfBox->setTitle(QCoreApplication::translate("MainWindow", "\320\220\320\273\321\204\320\260\320\262\320\270\321\202 \321\201\320\274\320\265\321\211\320\265\320\275\320\270\320\271", nullptr));
        moveAlfStatus->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\321\203\321\201", nullptr));
        moveAlfCount->setText(QCoreApplication::translate("MainWindow", "\320\255\320\273\320\265\320\274\320\265\320\275\321\202\321\213:", nullptr));
        moveAlfPresentButton->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\262\320\265\321\201\321\202\320\270", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\276\320\261\321\200\320\260\320\261\320\276\321\202\320\272\320\270", nullptr));
        decodeFlow->setText(QCoreApplication::translate("MainWindow", "\320\224\320\265\320\272\320\276\320\264\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\262\320\265\321\201\321\214 \320\277\320\276\321\202\320\276\320\272", nullptr));
        decodeBlocs->setText(QCoreApplication::translate("MainWindow", "\320\224\320\265\320\272\320\276\320\264\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\277\320\276 \320\261\320\273\320\276\320\272\320\260\320\274", nullptr));
        seekPositionLabel->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\267\320\270\321\206\320\270\321\217 \320\275\320\260\321\207\320\260\320\273\321\214\320\275\320\276\320\263\320\276 \320\261\320\270\321\202\320\260:", nullptr));
        staticBlocks->setText(QCoreApplication::translate("MainWindow", "\320\230\321\201\320\272\320\260\321\202\321\214 \321\201\321\202\320\260\321\202\320\270\321\207\320\265\321\201\320\272\320\270\320\265 \320\272\320\276\320\264\321\213", nullptr));
        dynamicBlocks->setText(QCoreApplication::translate("MainWindow", "\320\230\321\201\320\272\320\260\321\202\321\214 \320\264\320\270\320\275\320\260\320\274\320\270\321\207\320\265\321\201\320\272\320\270\320\265 \320\272\320\276\320\264\321\213", nullptr));
        noCompressionBlocks->setText(QCoreApplication::translate("MainWindow", "\320\230\321\201\320\272\320\260\321\202\321\214 \320\261\320\273\320\276\320\272\320\270 \320\261\320\265\320\267 \321\201\320\266\320\260\321\202\320\270\321\217", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\265\320\272\320\276\320\264\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        errorFixerButton->setText(QCoreApplication::translate("MainWindow", "\320\230\321\201\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\276\321\210\320\270\320\261\320\276\320\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
