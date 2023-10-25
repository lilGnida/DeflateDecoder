/********************************************************************************
** Form generated from reading UI file 'errorfixerwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ERRORFIXERWINDOW_H
#define UI_ERRORFIXERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_ErrorFixerWindow
{
public:

    void setupUi(QDialog *ErrorFixerWindow)
    {
        if (ErrorFixerWindow->objectName().isEmpty())
            ErrorFixerWindow->setObjectName(QString::fromUtf8("ErrorFixerWindow"));
        ErrorFixerWindow->resize(400, 300);

        retranslateUi(ErrorFixerWindow);

        QMetaObject::connectSlotsByName(ErrorFixerWindow);
    } // setupUi

    void retranslateUi(QDialog *ErrorFixerWindow)
    {
        ErrorFixerWindow->setWindowTitle(QCoreApplication::translate("ErrorFixerWindow", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ErrorFixerWindow: public Ui_ErrorFixerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ERRORFIXERWINDOW_H
