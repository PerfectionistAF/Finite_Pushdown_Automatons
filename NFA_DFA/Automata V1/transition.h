#ifndef TRANSITION_H
#define TRANSITION_H

#include <QWidget>

namespace Ui {
class transition;
}

class nfa;
class transition : public QWidget
{
    Q_OBJECT

public:
    explicit transition(QWidget *parent = nullptr);
    nfa* graph;
    ~transition();

private slots:
    void on_addEdge_clicked();

    void on_done_clicked();

private:
    Ui::transition *ui;

};

#endif // TRANSITION_H
