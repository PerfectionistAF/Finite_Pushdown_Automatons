#ifndef NFA_H
#define NFA_H

#include <QWidget>
#include <QPixmap>
#include <QRegularExpression>
#include <QWidget>
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
    void on_draw_clicked();
    void on_addTransition_clicked();
    void on_backButton_clicked();

private:
    Ui::nfa *ui;
    transition* transitionWindow;
    Widget* mainWindow;
};

#endif // NFA_H
