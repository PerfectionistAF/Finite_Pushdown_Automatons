#include "production.h"
#include "ui_production.h"
#include "pda_window.h"
#include <set>

Production::Production(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Production)
{
    ui->setupUi(this);
}

Production::~Production()
{
    delete ui;
}

void Production::on_pushButton_clicked()
{
    string from = ui->from->text().toStdString();
    string to = ui->to->text().toStdString();

    this->graph->pda.productionRules[from].push_back(to);
//    set<string> s (this->graph->pda.productionRules[from].begin(),this->graph->pda.productionRules[from].end());
//    this->graph->pda.productionRules[from].assign(s.begin(),s.end());




}


void Production::on_done_clicked()
{
    close();
}

