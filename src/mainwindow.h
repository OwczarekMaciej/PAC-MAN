#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include <QFontDatabase>
#include "game_view.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_play_btn_clicked();
    void on_exit_btn_clicked();

private:
    Ui::MainWindow *ui;

    void set_start_screen();

    int btn_font_size = 16;
    int lbl_font_size = 32;
    const QString font_family = "Emulogic";
};
#endif // MAINWINDOW_H
