#include <QCoreApplication>
#include <QImage>
#include <QString>
#include <cwchar>
#include <windows.h>

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 4;                   // Width of each character in the font
    cfi.dwFontSize.Y = 4;                  // Height
    cfi.FontFamily = FF_MODERN;
    cfi.FontWeight = FW_NORMAL;
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

    QCoreApplication a(argc, argv);

    QString fileName = "../tet";
    QImage img;

    bool success = img.load(fileName, "JPG" );

    cout << "Image load status: " << boolalpha << success << endl;

    for (int i = 0; i < img.height(); i++){
        for (int j = 0; j < img.width(); j++){
            int pB = img.pixelColor(j,i).value(); // pB = pixel britness

            if (pB > 255){
                cout << '.';
            } else if( pB > 230){
                cout << ':';
            }else if( pB > 160){
                cout << ';';
            } else if (pB > 140){
                cout << '>';
            } else if (pB > 125){
                cout << '%';
            }else if (pB > 80){
                cout << '&';
            } else if (pB > 60){
                cout << '$';
            } else if (pB > 40){
                cout << '#';
            } else if (pB > 0){
                cout << '@';
            }

        }
        cout << endl;
    }

    return a.exec();


}
