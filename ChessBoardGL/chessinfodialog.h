#ifndef CHESSINFODIALOG_H
#define CHESSINFODIALOG_H

#include <QDialog>

namespace Ui {
class ChessInfoDialog;
}

class ChessInfoDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ChessInfoDialog(QWidget *parent = 0);
    ~ChessInfoDialog();
    
    int getSize()const;
    int getX()const;
    int getY()const;

private:
    Ui::ChessInfoDialog *ui;
};

#endif // CHESSINFODIALOG_H
