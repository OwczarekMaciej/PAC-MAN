#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); 
    set_start_screen();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::set_start_screen()
{
    setWindowTitle("WELCOME TO PAC-MAN");
    setStyleSheet("background-color: black");

    QMovie *movie = new QMovie(":/res/welcome_gif.gif");
    ui->gif_lbl->setMovie(movie);
    movie->start();

    QFontDatabase::addApplicationFont(":/res/font.ttf");
    ui->name_lbl->setFont(QFont(font_family, lbl_font_size));
    ui->play_btn->setFont(QFont(font_family, btn_font_size));
    ui->exit_btn->setFont(QFont(font_family, btn_font_size));
}

void MainWindow::on_play_btn_clicked()
{
    close();
    Game_view *game = new Game_view();
    game->show();
}


void MainWindow::on_exit_btn_clicked()
{
    close();
}

