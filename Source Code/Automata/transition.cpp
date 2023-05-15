#include "transition.h"
#include "nfa.h"
#include "ui_transition.h"

transition::transition(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::transition)
{
    ui->setupUi(this);
}

transition::~transition()
{
    delete ui;
}

void transition::on_done_clicked()
{
    close();
}


void transition::on_addEdge_clicked()
{
    vector<string> from {ui->from->text().toStdString()};
    string to {ui->to->text().toStdString()};
    string on = ui->on->text().toStdString();
    if(on == "#")
        this->graph->isNFA = false;
    this->graph->NFA.transition_table[{from,on}].push_back(to);
    unique(this->graph->NFA.transition_table[{from,to}]);
}

