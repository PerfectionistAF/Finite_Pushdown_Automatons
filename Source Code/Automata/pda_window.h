#ifndef PDA_WINDOW_H
#define PDA_WINDOW_H

#include <QDialog>
#include <QRegularExpression>
#include <vector>
#include "pda.h"
#include "graph.h"
#include "index.h"

using namespace std;

namespace Ui {
class PDA_Window;
}

class Production;
class index;

class PDA_Window : public QDialog
{
    Q_OBJECT

public:
    explicit PDA_Window(QWidget *parent = nullptr);
    PDA pda;
    Widget* in;
    ~PDA_Window();

private slots:

    void on_drawPDA_clicked();
    void on_addProductions_clicked();

    void on_backButton_clicked();

private:
    Ui::PDA_Window *ui;
    Production* win;
};

#endif // PDA_WINDOW_H
