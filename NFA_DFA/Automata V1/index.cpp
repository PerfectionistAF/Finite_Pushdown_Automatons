#include "index.h"
#include "nfa.h"
#include "ui_index.h"


Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPixmap pixmap("icons8-bot-48.png");
    ui->logo->setPixmap(pixmap);
    //ui->logo->setScaledContents(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_convertNFAtoDFA_clicked()
{
    window = new nfa();
    window->show();
    close();
}

