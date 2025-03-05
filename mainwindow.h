#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    enum NumOperations {
        PLUS,
        MINUS,
        MULT,
        DIV,

        NONE
    };

    enum MemoryCellStatus {
        NOT_EXIST,
        EXIST
    };

    struct MemoryCell {
        float value;
        MemoryCellStatus status;
    };

    // ------------------------------

    Ui::MainWindow *ui;

    MemoryCell _memory_cell;
    float _curr_cell;
    NumOperations _last_oper;

    // ------------------------------

    float parseToFloat();
    void showFromFloat(float value);

    void handleOpMath(NumOperations op);
    void handleOpEqual();

    void addSymbol();
    void addSymbolWithCheck();

    void saveToMemory();
    void clearMemory();
    void recallFromMemory();
    void plusFromMemory();
    void minusFromMemory();

    void clearEntry();
    void clearGlobal();
};
#endif // MAINWINDOW_H
