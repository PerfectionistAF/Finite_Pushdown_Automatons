#include "index.h"
#include "nfa.h"
#include "pda_window.h"
#include "ui_index.h"


Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
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


void Widget::on_convertCFGtoPDA_clicked()
{
    win = new PDA_Window();
    win->show();
    close();
}

