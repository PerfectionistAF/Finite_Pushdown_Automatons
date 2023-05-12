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

void transition::on_addEdge_clicked()
{
    string from = ui->from->text().toStdString();
    string to = ui->to->text().toStdString();
    string On = ui->on->text().toStdString();
    if(On == "#") graph->isNFA = false;
    vector<string> From; From.push_back(from);
    vector<string> To; To.push_back(to);

    if(graph->NFA.transition_table.find({From,On}) == graph->NFA.transition_table.end())
        graph->NFA.transition_table.insert({{From,On},To});
    else
        graph->NFA.transition_table[{From,On}].push_back(to);
}


void transition::on_done_clicked()
{
    close();
}

