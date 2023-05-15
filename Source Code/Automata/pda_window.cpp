#include "pda_window.h"
#include "production.h"
#include "ui_pda_window.h"
#include "index.h"
#include <QDebug>


PDA_Window::PDA_Window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PDA_Window)
{
    ui->setupUi(this);
}

PDA_Window::~PDA_Window()
{
    delete ui;
}

void PDA_Window::on_drawPDA_clicked()
{
    QStringList query;

    static QRegularExpression rx("\\,");

    // extract states
    QString qStart = ui->start->text();
    this->pda.start = qStart.toStdString();

    QString qTerminals = ui->terminals->text();
    query = qTerminals.split(rx);

    vector<string> vecTerminals;
    foreach(QString str, query)
        vecTerminals.push_back(str.toStdString());
    this->pda.terminals.assign(vecTerminals.begin(),vecTerminals.end());

    QString qNonTerminals = ui->nonTerminals->text();
    query = qNonTerminals.split(rx);

    vector<string> vecNonTerminals;
    foreach(QString str, query)
        vecNonTerminals.push_back(str.toStdString());
    this->pda.nonTerminals.assign(vecNonTerminals.begin(),vecNonTerminals.end());

    convertCFGToPDA(this->pda);

    buildPDA(this->pda);
    printPDA(this->pda);

    QPixmap pixmap("graph.png");
    ui->image->setPixmap(pixmap);
    ui->image->setScaledContents(true);
    //ui->image->show();
}


void PDA_Window::on_addProductions_clicked()
{
    win = new Production();
    win->graph = this;
    win->show();
}


void PDA_Window::on_backButton_clicked()
{
    in = new Widget();
    in->show();
    close();
}

