#include "nfa.h"
#include "index.h"
#include "transition.h"
#include "ui_nfa.h"
#include "graph.h"

nfa::nfa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nfa)
{
    this->isNFA = true;
    ui->setupUi(this);
}

nfa::~nfa()
{
    delete ui;
}

void nfa::on_backButton_clicked()
{
    close();
    mainWindow = new Widget();
    mainWindow->show();
}



void nfa::on_addTable_clicked()
{
    transitionWindow = new transition();
    transitionWindow->graph = this;
    transitionWindow->show();
}


void nfa::on_drawDFA_clicked()
{
    QStringList query;

    static QRegularExpression rx("\\,");

    // extract states
    QString qStates = ui->states->text();
    query = qStates.split(rx);

    vector<string> vecStates;
    foreach(QString str, query)
    {
        //vecStates.push_back(str.toLocal8Bit().constData());
        vector<string> s;
        s.push_back(str.toStdString());
        this->NFA.states.push_back(s);
    }


    // extract start state
    string start = (ui->start->text()).toLocal8Bit().constData();
    this->NFA.start = start;

    // extract input symbols
    QString qLang = ui->input->text();
    query = qLang.split(rx);

    vector<string> vecLang;
    foreach(QString str, query)
        vecLang.push_back(str.toLocal8Bit().constData());
    this->NFA.lang.assign(vecLang.begin(),vecLang.end());

    // extract accepting states
    QString qAccept = ui->accept->text();
    query = qAccept.split(rx);

    vector<string> vecAccept;
    foreach(QString str, query)
    {
        //vecAccept.push_back(str.toLocal8Bit().constData());
        vector<string> s;
        s.push_back(str.toStdString());
        this->NFA.accept.push_back(s);
    }
    //printDFA(this->NFA);
    if(this->isNFA)
        this->DFA = convertNFAToDFA(this->NFA);
    else
        this->DFA = convertEpsilonNFAToDFA(this->NFA);
    buildGraph(this->DFA);
    printDFA(this->DFA,this->isNFA);

    QPixmap pixmap("graph.png");
    ui->image->setPixmap(pixmap);
    ui->image->setScaledContents(true);

}

