#include "replwidget.hpp"
#include <QScrollBar>

ReplWidget::ReplWidget(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);
    output = new QTextEdit(this);
    input = new QLineEdit(this);

    output->setReadOnly(true);
    input->setPlaceholderText("Введите команду...");

    layout->addWidget(output);
    layout->addWidget(input);

    connect(input, &QLineEdit::returnPressed, this, &ReplWidget::handleInput);
}

void ReplWidget::handleInput() {
    QString command = input->text();
    if (command.isEmpty()) return;

    appendOutput(">>> " + command);

    // TODO: вызов интерпретатора MatreshkaScript здесь

    input->clear();
}

void ReplWidget::appendOutput(const QString& text) {
    output->moveCursor(QTextCursor::End);
    output->insertPlainText(text + "\n");
    output->verticalScrollBar()->setValue(output->verticalScrollBar()->maximum());
}