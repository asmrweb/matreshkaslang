#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    editor = new CodeEditor(this);
    repl = new ReplWidget(this);

    QSplitter* splitter = new QSplitter(Qt::Vertical);
    splitter->addWidget(editor);
    splitter->addWidget(repl);

    setCentralWidget(splitter);
    createActions();
    createMenus();
    createStatusBar();

    setWindowTitle("MatreshkaScript IDE");
    resize(800, 600);
}

void MainWindow::createActions() {
    openAct = new QAction(tr("&Открыть..."), this);
    openAct->setShortcut(QKeySequence::Open);
    connect(openAct, &QAction::triggered, this, &MainWindow::openFile);

    saveAct = new QAction(tr("&Сохранить"), this);
    saveAct->setShortcut(QKeySequence::Save);
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);

    exitAct = new QAction(tr("В&ыйти"), this);
    exitAct->setShortcut(QKeySequence::Quit);
    connect(exitAct, &QAction::triggered, this, &QWidget::close);
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&Файл"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
}

void MainWindow::createStatusBar() {
    statusBar()->showMessage(tr("Готов"));
}

void MainWindow::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            editor->setPlainText(file.readAll());
            currentFile = fileName;
            statusBar()->showMessage(tr("Файл открыт: %1").arg(fileName));
        }
    }
}

void MainWindow::saveFile() {
    if (currentFile.isEmpty()) {
        QString fileName = QFileDialog::getSaveFileName(this);
        if (fileName.isEmpty())
            return;
        currentFile = fileName;
    }

    QFile file(currentFile);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << editor->toPlainText();
        statusBar()->showMessage(tr("Файл сохранён: %1").arg(currentFile));
    }
}