#include <QCoreApplication>
#include <QImage>
#include <QString>
#include <cwchar>
#include <windows.h>

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.FontFamily = FF_MODERN;
    cfi.FontWeight = FW_NORMAL;
    wcscpy(cfi.FaceName, L"Consolas");

    QString fileName = "../img/tree";                   //file name
    QImage img;
    bool success = img.load(fileName, "JPG" );          //file format
    int step;

    if (img.height() <= 512 || img.width() <= 512) {
        cfi.dwFontSize.X = 3;                  // Width of each character in the font
        cfi.dwFontSize.Y = 3;                  // Height
    } else {
        cfi.dwFontSize.X = 2;
        cfi.dwFontSize.Y = 2;
    }

    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

    cout << "Image load status: " << boolalpha << success << endl;


    if (img.height() < 512 || img.width() < 512) {
        step = 1;
    }
    else if (img.height() >= 512 || img.width() > 512) {
        step = 2;
    }
    else if (img.height() <= 2048 || img.width() <= 2048) {
        step = 4;
    }
    else { step = 8; }
       for (int i = 0; i < img.height(); i += step) {
            for (int j = 0; j < img.width(); j += step) {

            int pB = img.pixelColor(j,i).value(); // pB = pixel britness

            if (pB >= 255){
                cout << " ";
            } else if( pB > 230){
                cout << ":";
            } else if( pB > 220){
                cout << ";";
            } else if( pB > 190){
                cout << "/";
            } else if( pB > 160){
                cout << "[";
            } else if (pB > 140){
                cout << '=';
            } else if (pB > 125){
                cout << 'a';
            } else if (pB > 80){
                cout << '$';
            } else if (pB > 60){
                cout << '&';
            } else if (pB > 40){
                cout << '%';
            } else if (pB >= 0){
                cout << '@';
            }
        }
        cout << endl;
    }


    return a.exec();


}
