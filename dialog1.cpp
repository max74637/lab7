#include "dialog1.h"
#include "ui_dialog1.h"

Dialog1::Dialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1)
{
    ui->setupUi(this);
}

Dialog1::~Dialog1()
{
    delete ui;
}

void Dialog1::setResultText(QString s)
{
    QPlainTextEdit* plainTextEdit = findChild<QPlainTextEdit*>("plainTextEdit");
    plainTextEdit->document()->setPlainText(s);
    plainTextEdit->moveCursor(QTextCursor::Up);
    plainTextEdit->moveCursor(QTextCursor::Start);
}
