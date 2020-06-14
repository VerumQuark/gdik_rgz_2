#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFont font("MyFont");
    font.setPointSize(2);
    font.setStyleHint(QFont::TypeWriter);
    font.setLetterSpacing (QFont::AbsoluteSpacing,1);
    ui->label->setFont(font);
}

MainWindow::~MainWindow() {
    delete ui;
}

int setStep(int h, int w) {
    if (h < 512 || w < 512)
        return 1;
    else if (h <= 1024 || w < 1024)
        return 4;
    else if (h <= 2048 || w <= 2048)
        return 6;
    else return 8;
}

char getChar (int pb) {
    if (pb >= 255)
        return ' ';
    if (pb > 230)
        return ':';
    if (pb > 220)
        return ';';
    if (pb > 190)
        return '/';
    if (pb > 160)
        return '[';
    if (pb > 140)
        return '=';
    if (pb > 125)
        return 'a';
    if (pb > 80)
        return '$';
    if (pb > 60)
        return '&';
    if (pb > 40)
        return '%';
    return '@';
}

QString getArt(QImage img) {
    QString art;
    int height = img.height();
    int width = img.width();
    int step=setStep(height,width);
    for (int i = 0; i < height; i += step) {
        for (int j = 0; j < width; j += step) {
            int sumPB = 0;  // sumPB = sum of area pixel brightness

            for (int y = i; y < i+step; y++) {
                if (y >= height)
                    continue;
                for (int x = j; x < j+step; x++) {
                    if(x >= width)
                        continue;
                    sumPB += img.pixelColor(x,y).value();
                }
            }
            sumPB /= step * step;
            art+=getChar(sumPB);
        }
        art+="\n";
    }
    return art;
}

void MainWindow::on_pushButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Upload Image"), "", "*.jpg");
    QImage image;
    if (!image.load(fileName, "JPG" ))
        QMessageBox::critical(0,"Error", "Can't upload image");
    ui->label->setText(getArt(image));
}
