#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QPlainTextEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow() override;

private:
    // build the window
    void createLayout();
    void createActions();
    void createMenus();

    void loadConfigFile();
    void saveConfigFile();

    // misc
    QPlainTextEdit *textEdit;
    QFont textFont;
    QString fileName;

    // file menu
    QMenu *fileMenu;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;

    // edit menu
    QMenu *editMenu;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *undoAct;
    QAction *redoAct;

    // help menu
    QMenu *helpMenu;
    QAction *aboutAct;
    QAction *aboutQtAct;

    // configuration menu
    QMenu *configurationMenu;
    QAction *fontChangeAct;
    QAction *autoSaveAct;

private slots:
    // window
    void resizeEvent(QResizeEvent* event) override;

    // file menu
    void newFile();
    void open();
    void save();
    void saveAs();
    void exitApplication();

    // edit menu
    void cut();
    void copy();
    void paste();
    void undo();
    void redo();

    // help menu
    void about();
    void aboutQt();

    // font menu
    void fontChange();
    void autoSave();

};

#endif // MAINWINDOW_H
