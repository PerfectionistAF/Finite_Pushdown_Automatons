#ifndef NFA_H
#define NFA_H

#include <QWidget>
#include <QPixmap>
#include <QRegularExpression>
#include "graph.h"
//#include "transition.h"

namespace Ui {
class nfa;
}
class transition;
class Widget;
class nfa : public QWidget
{
    Q_OBJECT

public:
    explicit nfa(QWidget *parent = nullptr);
    FA NFA;
    FA DFA;
    bool isNFA;
    ~nfa();

private slots:
    void on_backButton_clicked();

    void on_drawDFA_clicked();

    void on_addTable_clicked();

private:

    transition* transitionWindow;
    Widget* mainWindow;
    Ui::nfa *ui;
};

#endif // NFA_H
