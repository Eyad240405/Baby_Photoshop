#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <bits/stdc++.h>
#include <cmath>
#include <stdbool.h>
#include <ctype.h>
#include "Image_Class.h"
using namespace std;
int main() {
    Image check;
    Image image;
    string load = "0";
    string choice = "21";
    string filename , filename2 , filename3;
    cout<<"_________________________________________________________________________________________________"<<endl
        <<"Please enter the file name for saving the edited picture."<<endl
        <<"With its extension (jpg / jpeg / png / bmp)"
        <<endl<<"Enter:";
    cin >> filename2;

    while(true){
        try {
            check.loadNewImage(filename2);
            break;
        }
        catch( invalid_argument) {
            cout << "Please enter a valid file name and extension:\n" << endl;
            cin>>filename2;
        }
    }

    if (check.loadNewImage(filename2)) {
        cout << "Loaded Successfully , lets start!" << endl;
    }

    while (true) {

        cout << endl << "________________________________________________________________"<<endl;
        string load = "0";
        while ( load != "1" && load != "2" && load != "3" ) {
            cout << endl << "1) New image" << endl
                 << "2) Keep editing" << endl
                 << "3) Exit the program" << endl << endl
                 << "Choose:";

            cin >> load;

            if (load == "1") {
                cout <<endl <<"Please provide the desired input file name."<<endl
                     <<"With its extension (jpg / jpeg / png / bmp)"<<endl<<"Enter:";
                cin>>filename;
                while(true){
                    try {
                        image.loadNewImage(filename);
                        break;
                    }
                    catch( invalid_argument) {
                        cout << "Please enter a valid photo \n" << endl;
                        cin>>filename;
                    }
                }

                if (image.loadNewImage(filename)) {
                    cout << "Loaded Successfully!" << endl;
                }
            }

            else if (load == "2") {
                image.loadNewImage(filename2);
                if (image.loadNewImage(filename2)) {
                    cout << "Loaded Successfully!" << endl;
                }
            }

            else if (load == "3") {
                cout << endl << endl << "Program exited successfully!";
                return 0;
            }
        }
        choice = "21";
        while (stoi(choice)> 20 || stoi(choice)<1 ) {
            cout << endl << "________________________________________________________________" << endl
                 << "1) Greyscale filter" << endl
                 << "2) Black & White filter" << endl
                 << "3) Inverted filter" << endl
                 << "4) Merge Images filter" << endl
                 << "5) Flip filter" << endl
                 << "6) Rotate filter" << endl
                 << "7) Darken and Lighten Image filter" << endl
                 << "8) Crop filter" << endl
                 << "9) Frame filter" << endl
                 << "10) Detect image edges filter" << endl
                 << "11) Resizing filter" << endl
                 << "12) Blur filter" << endl
                 << "13) Sunlight filter" << endl
                 << "14) Oil filter" << endl
                 << "15) Retro filter" << endl
                 << "16) Purple filter" << endl
                 << "17) Infrared filter" << endl
                 << "18) Skewing filter" << endl
                 << "19) Extra #1 filter" << endl
                 << "20) Extra #2 filter" << endl<<endl
                 << "Please choose a number between 1 and 20."
                 <<endl;

            bool cf = false;
            while(!cf) {
                cout <<"Choose:";
                cin>>choice;
                cf  = true;
                for (int x = 0; x < choice.length(); x++) {
                    if (!isdigit(choice[x])) {
                        cf=false;
                        cout<<endl<<"Please enter a valid number!"<<endl;
                        break;
                    }
                }
            }


            if (choice == "1") {
                greyscale(image, filename2);
                cout << endl;
            } else if (choice == "2") {
                Black_White(image, filename2);
                cout << endl;
            } else if (choice == "3") {
                inverted(image, filename2);
                cout << endl;
            } else if (choice == "4") {
                merge(image, filename,filename2);
                cout << endl;
            }else if (choice == "5") {
                flipping(image, filename, filename2);
                cout << endl;
            } else if (choice == "6") {
                Rotate(image, filename, filename2);
                cout << endl;
            } else if (choice == "7") {
                Darken_and_Lighten_Image(image, filename2);
                cout << endl;
            } else if (choice == "8") {
                cropping(image, filename2);
                cout << endl;
            } else if (choice == "9") {

                cout << endl;
            } else if (choice == "10") {
                Detect_Image_Edges(image, filename2);
                cout << endl;
            } else if (choice == "11") {
                resize(image, filename2);
                cout << endl;
            } else if (choice == "12") {
                Image outputImage(image.width, image.height);
                Blur(image, outputImage);
                outputImage.saveImage(filename2);
                cout << endl;
            } else if (choice == "13") {
                sunlight(image, filename2);
                cout << endl;
            } else if (choice == "14") {
                oil( image , filename , filename2);
                cout << endl;
            } else if (choice == "15") {
                retro(image, filename2);
                cout << endl;
            } else if (choice == "16") {
                Purple(image, filename2);
                cout << endl;
            } else if (choice == "17") {
                Infrared(image, filename2);
                cout << endl;
            }
            else if (choice == "19") {

                cout << endl;
            } else if (choice == "20") {

                cout << endl;
            }
        }
        cout<<"Done , Check the " << filename2 << " file!"<<endl;
    }

}