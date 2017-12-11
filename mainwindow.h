#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/highgui/highgui.hpp>
#include <QFileInfo>
#include <QTranslator>

class QGraphicsScene;
class QWheelEvent;
class QFileInfo;
class QundoCommand;
class QUndoStack;
class QTranslator;
class QActionGroup;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //void wheelEvent(QWheelEvent *event);
    //void closeEvent(QCloseEvent* event);

private slots:
    void on_actionAbout_triggered();

    void on_actionopen_triggered();
    
    void on_actionsave_triggered();

    void on_actionexit_triggered();

    void on_actionsave_as_triggered();

    void on_actionCartoon_triggered();

private:
    Ui::MainWindow *ui;
    cv::Mat loadedImage;
    QGraphicsScene *scene;
    cv::Mat savedImage;
    QFileInfo fileInfo;
    QUndoStack *undoStack;
    QAction *undoAction;
    QAction *redoStack;
    QTranslator appTranslator;
    QTranslator qtTranslator;
    QString langPath;
    QActionGroup *languageActionGroup;
private:
    void displayMat(cv::Mat displayImage);
    void updatwImage(cv::Mat img);
};

#endif // MAINWINDOW_H
