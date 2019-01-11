#include "mainwindow.h"

#include <QContextMenuEvent>
#include <QFileDialog>
#include <QFontDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QTextStream>
#include <QVBoxLayout>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

MainWindow::MainWindow()
{
    resize(300, 300);
    setMinimumWidth(265);

    createLayout();
    loadConfigFile();
    createActions();
    createMenus();
}

MainWindow::~MainWindow()
{

}

void MainWindow::newFile()
{
    fileName = "";
    this->setWindowTitle("Sin título");
    textEdit->setPlainText("");
}

void MainWindow::open()
{
    QString file = QFileDialog::getOpenFileName(this, "Abrir archivo de texto");
    if(!file.isEmpty()){
        QFile sFile(file);
        if(sFile.open(QFile::ReadOnly | QFile::Text )){
            fileName = file;
            QTextStream input(&sFile);
            QString text = input.readAll();
            sFile.flush();
            sFile.close();
            textEdit->setPlainText(text);

            // set window title
            QStringList split = file.split("/");
            this->setWindowTitle(split[split.length() - 1]);
        }
    }
}

void MainWindow::save()
{
    if(fileName.isEmpty()){
        this->saveAs();
    } else {
        QFile sFile(fileName);
        if(sFile.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream output(&sFile);
            output << textEdit->toPlainText();
            sFile.flush();
            sFile.close();
        }
    }
}

void MainWindow::saveAs()
{
    QString file = QFileDialog::getSaveFileName(this, "Guardar archivo de texto");
    if(!file.isEmpty())
    {
        fileName = file;
        this->save();

        // set window title
        QStringList split = file.split("/");
        this->setWindowTitle(split[split.length() - 1]);
    }
}

void MainWindow::exitApplication()
{
    exit(0);
}

void MainWindow::cut()
{
    textEdit->cut();
}

void MainWindow::copy()
{
    textEdit->copy();
}

void MainWindow::paste()
{
    textEdit->paste();
}

void MainWindow::undo()
{
    textEdit->undo();
}

void MainWindow::redo()
{
    textEdit->redo();
}

void MainWindow::fontChange()
{
    bool fontok;
    textFont = QFontDialog::getFont(&fontok);
    if(fontok)
    {
        textEdit->setFont(textFont);
        saveConfigFile();
    }
}

void MainWindow::autoSave()
{
}

void MainWindow::about()
{
    QString aboutTextPad;
    aboutTextPad.append("Bienvenido a TextPad")
            .append("\n\nSoftware desarrollado por Alejandro Carrasco Rodríguez <acarrasco8@misena.edu.co>")
            .append("\nAprendiz SENA de tecnología en Análisis y Desarrollo de sistemas de Información");

    QMessageBox::about(this, tr("TextPad"), aboutTextPad);
}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    saveConfigFile();
}

void MainWindow::createLayout()
{
    QVBoxLayout *containerLayout = new QVBoxLayout();
    containerLayout->setMargin(0);
    containerLayout->addWidget(textEdit = new QPlainTextEdit());

    QWidget *containerWidget = new QWidget();
    containerWidget->setLayout(containerLayout);

    setCentralWidget(containerWidget);

    setWindowTitle(tr("Sin título"));
}

void MainWindow::createActions()
{

    // new
    newAct = new QAction(tr("Nuevo"), this);
    newAct->setShortcuts(QKeySequence::New);
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    // open
    openAct = new QAction(tr("Abrir"), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    // save
    saveAct = new QAction(tr("Guardar"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    // save as
    saveAsAct = new QAction(tr("Guardar como"), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveAs);

    // exit
    exitAct = new QAction(tr("Salir"), this);
    connect(exitAct, &QAction::triggered, this, &MainWindow::exitApplication);

    // cut
    cutAct = new QAction(tr("Cortar"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    connect(cutAct, &QAction::triggered, this, &MainWindow::cut);

    // copy
    copyAct = new QAction(tr("Copiar"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    connect(copyAct, &QAction::triggered, this, &MainWindow::copy);

    // paste
    pasteAct = new QAction(tr("Pegar"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    connect(pasteAct, &QAction::triggered, this, &MainWindow::paste);

    // undo
    undoAct = new QAction(tr("Deshacer"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    connect(undoAct, &QAction::triggered, this, &MainWindow::undo);

    // redo
    redoAct = new QAction(tr("Rehacer"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    connect(redoAct, &QAction::triggered, this, &MainWindow::redo);

    // font
    fontChangeAct = new QAction(tr("Formato"), this);
    connect(fontChangeAct, &QAction::triggered, this, &MainWindow::fontChange);

    // autosave
    autoSaveAct = new QAction(tr("Guardar automáticamente"), this);
    autoSaveAct->setCheckable(true);
    connect(autoSaveAct, &QAction::triggered, this, &MainWindow::autoSave);

    // about app
    aboutAct = new QAction(tr("Acerca de TextPad"), this);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    // about QT
    aboutQtAct = new QAction(tr("Acerca de QT"), this);
    connect(aboutQtAct, &QAction::triggered, this, &MainWindow::aboutQt);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("Archivo"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("Edición"));
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);

    configurationMenu = menuBar()->addMenu(tr("Configuración"));
    configurationMenu->addAction(fontChangeAct);
    configurationMenu->addAction(autoSaveAct);

    helpMenu = menuBar()->addMenu(tr("Ayuda"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::loadConfigFile()
{
    // create font and provide default values
    textEdit->setFont(textFont = QFont("arial", 10));

    // open file
    QFile qFile("textpad.xml");
    if(qFile.open(QFile::ReadOnly | QFile::Text))
    {
        QXmlStreamReader stream(&qFile);

        if(stream.readNextStartElement() && stream.name() == "textpad")
        {

            // save the elements in xml to map
            QMap<QString, QString> elements;
            while(stream.readNextStartElement() && stream.name() != "textpad"){
                elements[stream.name().toString()] = stream.readElementText();
            }

            // load the data in map to application
            if (elements.contains("text_bold"))
            {
                textFont.setBold(elements["text_bold"].toInt());
            }
            if (elements.contains("text_family"))
            {
                textFont.setFamily(elements["text_family"]);
            }
            if (elements.contains("text_italic"))
            {
                textFont.setItalic(elements["text_italic"].toInt());
            }
            if (elements.contains("text_size"))
            {
                textFont.setPointSize(elements["text_size"].toInt());
            }
            if (elements.contains("window_height") && elements.contains("window_width"))
            {
                resize(elements["window_width"].toInt(), elements["window_height"].toInt());
            }
            else if (elements.contains("window_height"))
            {
                resize(width(), elements["window_height"].toInt());
            }
            else if (elements.contains("window_width"))
            {
                resize(elements["window_width"].toInt(), height());
            }
        }

        // finally set font (default or loaded)
        textEdit->setFont(textFont);

    }
}

void MainWindow::saveConfigFile()
{
    // open file
    QFile qFile("textpad.xml");
    if(qFile.open(QFile::WriteOnly | QFile::Text))
    {
        QXmlStreamWriter stream(&qFile);
        stream.writeStartDocument();
        stream.writeStartElement("textpad");

        // window data
        stream.writeTextElement("window_width", QString::number(width()));
        stream.writeTextElement("window_height", QString::number(height()));

        // text data
        stream.writeTextElement("text_family", textFont.family());
        stream.writeTextElement("text_size", QString::number(textFont.pointSize()));
        stream.writeTextElement("text_bold", QString::number(textFont.bold()));
        stream.writeTextElement("text_italic", QString::number(textFont.italic()));

        // close file
        stream.writeEndElement();
        stream.writeEndDocument();
        qFile.flush();
        qFile.close();
    }
}
