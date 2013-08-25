/********************************************************************************
** Form generated from reading UI file 'chessinfodialog.ui'
**
** Created: Mon Mar 5 16:48:21 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHESSINFODIALOG_H
#define UI_CHESSINFODIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_ChessInfoDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *m_Size;
    QSpinBox *m_X;
    QSpinBox *m_Y;

    void setupUi(QDialog *ChessInfoDialog)
    {
        if (ChessInfoDialog->objectName().isEmpty())
            ChessInfoDialog->setObjectName(QString::fromUtf8("ChessInfoDialog"));
        ChessInfoDialog->resize(216, 134);
        buttonBox = new QDialogButtonBox(ChessInfoDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(20, 100, 181, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(ChessInfoDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 71, 21));
        label_2 = new QLabel(ChessInfoDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 40, 71, 21));
        label_3 = new QLabel(ChessInfoDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 70, 71, 21));
        m_Size = new QComboBox(ChessInfoDialog);
        m_Size->setObjectName(QString::fromUtf8("m_Size"));
        m_Size->setGeometry(QRect(90, 10, 111, 22));
        m_X = new QSpinBox(ChessInfoDialog);
        m_X->setObjectName(QString::fromUtf8("m_X"));
        m_X->setGeometry(QRect(90, 40, 111, 22));
        m_Y = new QSpinBox(ChessInfoDialog);
        m_Y->setObjectName(QString::fromUtf8("m_Y"));
        m_Y->setGeometry(QRect(90, 70, 111, 22));

        retranslateUi(ChessInfoDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ChessInfoDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ChessInfoDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ChessInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *ChessInfoDialog)
    {
        ChessInfoDialog->setWindowTitle(QApplication::translate("ChessInfoDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ChessInfoDialog", "\347\273\264\346\225\260", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ChessInfoDialog", "\347\211\271\346\256\212\347\202\271\345\235\220\346\240\207X", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ChessInfoDialog", "\347\211\271\346\256\212\347\202\271\345\235\220\346\240\207Y", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ChessInfoDialog: public Ui_ChessInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHESSINFODIALOG_H
