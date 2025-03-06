#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <functional>
#include <QDoubleValidator>

#define DIGITS_ACCURACY 6

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Устанавливаем валидатор для ввода чисел с плавающей точкой
    QDoubleValidator *validator = new QDoubleValidator(ui->num_line_edit);
    validator->setNotation(QDoubleValidator::StandardNotation);
    ui->num_line_edit->setValidator(validator);

    // Выравнивание поля ввода по правому краю
    ui->num_line_edit->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    connect(ui->num_zero_push_button, &QPushButton::clicked, this, &MainWindow::addSymbol);
    connect(ui->num_one_push_button, &QPushButton::clicked, this, &MainWindow::addSymbol);
    connect(ui->num_two_push_button, &QPushButton::clicked, this, &MainWindow::addSymbol);
    connect(ui->num_three_push_button, &QPushButton::clicked, this, &MainWindow::addSymbol);
    connect(ui->num_four_push_button, &QPushButton::clicked, this, &MainWindow::addSymbol);
    connect(ui->num_five_push_button, &QPushButton::clicked, this, &MainWindow::addSymbol);
    connect(ui->num_six_push_button, &QPushButton::clicked, this, &MainWindow::addSymbol);
    connect(ui->num_seven_push_button, &QPushButton::clicked, this, &MainWindow::addSymbol);
    connect(ui->num_eight_push_button, &QPushButton::clicked, this, &MainWindow::addSymbol);
    connect(ui->num_nine_push_button, &QPushButton::clicked, this, &MainWindow::addSymbol);

    connect(ui->num_dot_push_button, &QPushButton::clicked, this, &MainWindow::addSymbolWithCheck);

    connect(ui->gl_clear_push_button, &QPushButton::clicked, this, &MainWindow::clearGlobal);
    connect(ui->gl_clear_entry_push_button, &QPushButton::clicked, this, &MainWindow::clearEntry);

    auto plusHandler = std::bind(&MainWindow::handleOpMath, this, NumOperations::PLUS);
    auto minusHandler = std::bind(&MainWindow::handleOpMath, this, NumOperations::MINUS);
    auto multHandler = std::bind(&MainWindow::handleOpMath, this, NumOperations::MULT);
    auto divHandler = std::bind(&MainWindow::handleOpMath, this, NumOperations::DIV);

    connect(ui->op_plus_push_button, &QPushButton::clicked, this, plusHandler);
    connect(ui->op_minus_push_button, &QPushButton::clicked, this, minusHandler);
    connect(ui->op_mult_push_button, &QPushButton::clicked, this, multHandler);
    connect(ui->op_div_push_button, &QPushButton::clicked, this, divHandler);
    connect(ui->op_equal_push_button, &QPushButton::clicked, this, &MainWindow::handleOpEqual);

    connect(ui->mem_call_push_button, &QPushButton::clicked, this, &MainWindow::recallFromMemory);
    connect(ui->mem_plus_push_button, &QPushButton::clicked, this, &MainWindow::plusFromMemory);
    connect(ui->mem_minus_push_button, &QPushButton::clicked, this, &MainWindow::minusFromMemory);
    connect(ui->mem_clear_push_button, &QPushButton::clicked, this, &MainWindow::clearMemory);
    connect(ui->mem_save_push_button, &QPushButton::clicked, this, &MainWindow::saveToMemory);
}

float MainWindow::parseToFloat() {
    QString num = ui->num_line_edit->text();
    num.replace(",", ".");
    return num.toFloat();
}

void MainWindow::showFromFloat(float value) {
    QString str = QString::number(value, 'f', DIGITS_ACCURACY);
    str.replace(".", ",");
    ui->num_line_edit->setText(str);
}

void MainWindow::handleOpMath(NumOperations op) {
    this->_curr_cell = parseToFloat();
    this->_last_oper = op;
    clearEntry();
}

void MainWindow::handleOpEqual() {
    float value = parseToFloat();

    switch (this->_last_oper) {
    case NumOperations::PLUS:
        showFromFloat(this->_curr_cell + value);
        break;
    case NumOperations::MINUS:
        showFromFloat(this->_curr_cell - value);
        break;
    case NumOperations::MULT:
        showFromFloat(this->_curr_cell * value);
        break;
    case NumOperations::DIV:
        showFromFloat(this->_curr_cell / value);
        break;
    case NumOperations::NONE:
        return;
    }

    this->_last_oper = NumOperations::NONE;
}

void MainWindow::clearEntry() {
    ui->num_line_edit->clear();
}

void MainWindow::clearGlobal() {
    this->_curr_cell = 0.0f;

    clearMemory();
    clearEntry();
}

void MainWindow::clearMemory() {
    this->_memory_cell.value = 0.0f;
    this->_memory_cell.status = MemoryCellStatus::NOT_EXIST;
}

void MainWindow::saveToMemory() {
    this->_memory_cell.value = parseToFloat();
    this->_memory_cell.status = MemoryCellStatus::EXIST;
}

void MainWindow::recallFromMemory() {
    if (this->_memory_cell.status == MemoryCellStatus::EXIST) {
        showFromFloat(this->_memory_cell.value);
    }
}

void MainWindow::plusFromMemory() {
    if (this->_memory_cell.status == MemoryCellStatus::EXIST) {
        showFromFloat(parseToFloat() + this->_memory_cell.value);
    }
}

void MainWindow::minusFromMemory() {
    if (this->_memory_cell.status == MemoryCellStatus::EXIST) {
        showFromFloat(parseToFloat() - this->_memory_cell.value);
    }
}

void MainWindow::addSymbol() {
    QString symb = dynamic_cast<QPushButton*>(sender())->text();
    ui->num_line_edit->setText(ui->num_line_edit->text() + symb);
}

void MainWindow::addSymbolWithCheck() {
    QString symb = dynamic_cast<QPushButton*>(sender())->text();
    QString curr_text = ui->num_line_edit->text();

    if (curr_text.size() > 0) {
        ui->num_line_edit->setText(curr_text + symb);
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

