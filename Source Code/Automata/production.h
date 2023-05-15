#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <QDialog>
#include <vector>
#include "pda.h"

using namespace std;

namespace Ui {
class Production;
}
class PDA_Window;
class Production : public QDialog
{
    Q_OBJECT

public:
    explicit Production(QWidget *parent = nullptr);
    PDA_Window* graph;
    ~Production();

private slots:
    void on_pushButton_clicked();

    void on_done_clicked();

private:
    Ui::Production *ui;

};

#endif // PRODUCTION_H
