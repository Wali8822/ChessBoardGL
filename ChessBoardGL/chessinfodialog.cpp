#include "chessinfodialog.h"
#include "ui_chessinfodialog.h"

#include <qmath.h>

ChessInfoDialog::ChessInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChessInfoDialog)
{
    ui->setupUi(this);

    for(int i=1;i<16;++i)
    {
        ui->m_Size->addItem(QString::number(qPow(2,i)));
    }
    ui->m_Size->setCurrentIndex(0);

    grabKeyboard();
}

ChessInfoDialog::~ChessInfoDialog()
{
    delete ui;
}

int ChessInfoDialog::getSize() const
{
    return ui->m_Size->currentText().toInt();
}

int ChessInfoDialog::getX() const
{
    return ui->m_X->value();
}

int ChessInfoDialog::getY() const
{
    return ui->m_Y->value();
}
