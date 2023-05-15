#ifndef INDEX_H
#define INDEX_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class nfa;
class PDA_Window;
class Widget : public QWidget

{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_convertNFAtoDFA_clicked();

    void on_convertCFGtoPDA_clicked();

private:
    Ui::Widget *ui;
    nfa* window;
    PDA_Window* win;
};

#endif // INDEX_H
