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
void Black_White(Image& image , string& filename2){
    greyscale( image , filename2);
    for(int i = 0 ; i < image.width ; i++){
        for(int j = 0  ; j < image.height ; j++){
            for(int k = 0 ; k < image.channels ; k++){
                if(image(i,j,k)>=128) {
                    image(i, j, k) = 255;
                }
                else{
                    image(i, j, k) = 0;
                }
            }
        }
    }
    image.saveImage(filename2);
}
void flipping(Image& image,string& filename,string& filename2) {
    Image image2(filename);
    Image image3(filename);
    cout << endl << "1) Vertical flip" << endl
         << "2) Horizontal flip" << endl
         <<"Choose:";
    string s;
    cin>>s;


//  Vertical flip
    if(s=="1") {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height / 2; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    image2(i, j, k) = image(i, image.height / 2 - j, k);
                    image3(i, j, k) = image(i, image.height - 1 - j, k);


                }
            }
        }
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height / 2; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    image(i, j, k) = image3(i, j, k);
                    image(i, j + image.height / 2, k) = image2(i, j, k);
                }
            }
        }
    }
//Horizontal flip
    else if(s=="2") {
        for (int i = 0; i < image.width / 2; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    image2(i, j, k) = image(image.width / 2 - i, j, k);
                    image3(i, j, k) = image(image.width - 1 - i, j, k);


                }
            }
        }
        for (int i = 0; i < image.width / 2; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    image(i, j, k) = image3(i, j, k);
                    image(i + image.width / 2, j, k) = image2(i, j, k);
                }
            }
        }
    }


    image.saveImage(filename2);
}
void repair_crop(int D , int& sd , int& d , int y , int y2){
    while (D-sd < d){
        int s;
        cout<<"1) Manually change the starting point."<<endl<<"2) Manually change the dimensions. "<<endl<<"3) Apply recommended changes."<<endl<<"Choose:";
        cin>>s;

        if(s==1){
            cout<<endl<<"Enter the new starting point:";
            cin>>sd;
        }
        else if(s==2){
            cout<<endl<<"Enter the new dimension:";
            cin>>d;
            while (d==0){
                cout<<endl<<"Enter the new dimension:";
                cin>>d;
            }
        }
        else if(s==3){
            cout<<"1) Automatically change the starting point to ("<<D - d <<" , "<<y<<")"<<endl
                <<"2) Automatically change the dimensions to ("<<D -sd<<"x"<<y2<<")"<<endl<<"Choose:";
            int z;
            cin>>z;
            if(z==1){
                sd=D - d;
            }
            else if (z==2){
                d=D -sd;
            }
        }
    }
}
void repair_crop2(int D1 , int D2 , int& sd1 , int& sd2 , int& d1 , int& d2 ){
    while (D1-sd1 < d1 || D2-sd2 < d2){
        int s;
        cout<<"1) Manually change the starting point."<<endl<<"2) Manually change the dimensions. "<<endl<<"3) Apply recommended changes."<<endl<<"Choose:";
        cin>>s;

        if(s==1){
            cout<<endl<<"Enter the new starting points:";
            cin>>sd1>>sd2;
        }
        else if(s==2){
            cout<<endl<<"Enter the new dimensions:";
            cin>>d1>>d2;
            while (d1==0 || d2==0){
                cout<<endl<<"Enter the new dimensions:";
                cin>>d1>>d2;
            }
        }
        else if(s==3){
            cout<<"1) Automatically change the starting point to ("<<D1 - d1<<" , "<<D2 - d2 <<")"<<endl
            <<"2) Automatically change the dimensions to ("<<D1 -sd1<<"x"<<D2 -sd2<<")"<<endl<<"Choose:";
            int z;
            cin>>z;
            if(z==1){
                sd1=D1 - d1 ;
                sd2=D2 - d2 ;
            }
            else if (z==2){
                d1=D1 -sd1 ;
                d2=D2 -sd2 ;
            }
        }
    }
}

void cropping(Image& image,string& filename2){
    cout<<"Dimensions:"<<image.width<<" "<<image.height<<endl;

    int n , b , w , h;
    cout << "Enter the start point:" ;
    cin >> n >> b;

    while (n >= image.width || h >= image.height){
        cout << "Enter the start point:" ;
        cin >> n >> b;
    }

    cout<<endl << "Enter the dimensions:" ;
    cin >> w >> h;
    if(image.width-n < w && image.height-b < h ){
        repair_crop2(image.width , image.height ,  n , b , w , h );
    }

    else if (image.height - b < h){
        repair_crop(image.height , b , h , n , w);
    }

    else if(image.width - n < w){
        repair_crop(image.width , n , w , b , h);
    }

    Image image2(w,h);
    for(int i = n ; i < n+w ; ++i){
        for(int j = b ; j < b+h ; ++j){
            for(int k = 0 ; k < image.channels ; ++k){
                image2(i-n,j-b,k) = image(i,j,k);
            }
        }
    }
    image2.saveImage(filename2);
}
void resize(Image& image , string& filename2){
    cout<<"Dimensions:"<<image.width<<" "<<image.height<<endl;

    int w , h ;
    float fw , fh;
    cout<<endl << "Enter the dimensions:" ;
    cin >> w >> h;
    fw= float (image.width ) / w;
    fh= float (image.height ) / h;
    cout<<endl<<fw<<endl<<fh<<endl;

    Image image2(w,h);
    int a , b;
    for(int i = 0 ; i < w ; i++){
        for(int j = 0 ; j < h ; j++){
            for(int k = 0 ; k < image.channels ; ++k){
                a = round (fw * i);
                b = round (fh * j);
                image2(i,j,k) = image(a,b,k);
            }
        }
    }
    image2.saveImage(filename2);
}
void oil(Image& image,string& filename,string& filename2){
    Image image2(filename);
    int radius;
    cout << "Enter the radius:";
    cin >> radius;
    int intestylevel;
    cout << "Enter the intensity:";
    cin >> intestylevel;

    int maxindex = 0;
    for(int i = radius ; i < image.width-radius ; i++){
        for(int j = radius ; j < image.height-radius ; j++){
            int curmax = 0;
            int l = 0;
            int avgR[intestylevel]={0};
            int avgG[intestylevel]={0};
            int avgB[intestylevel]={0};
            int count[intestylevel]={0};
            for(int i_O = i-radius ; i_O < i ; ++i_O){
                for(int j_O = j-radius ; j_O < j ; ++j_O){
                    int R = image(i_O,j_O,0);
                    int G = image(i_O,j_O,1);
                    int B = image(i_O,j_O,2);
                    int curintensity = int(round(double((double(R + G + B)/3.0)*intestylevel)/255.0f));
                    count[curintensity]++;
                    avgR[curintensity]+=R;
                    avgG[curintensity]+=G;
                    avgB[curintensity]+=B;
                    if(curintensity > l){
                        l=curintensity;

                    }
                }
            }
            for(int n = 0 ; n <= l ; n++){
                if(count[n] > curmax){
                    curmax = count[n];
                    maxindex = n;
                }
            }
            int fR = min(255,max(0,int(round(double(double(avgR[maxindex])/curmax)))));
            if (fR >255)
                fR = 255;
            else if (fR < 0)
                fR = 0;
            int fG = min(255,max(0,int(round(double(double(avgG[maxindex])/curmax)))));
            if (fG >255)
                fG = 255;
            else if (fG < 0)
                fG = 0;
            int fB = min(255,max(0,int(round(double(double(avgB[maxindex])/curmax)))));
            if (fB >255)
                fB = 255;
            else if (fB < 0)
                fB = 0;
            image2(i,j,0) = fR;
            image2(i,j,1) = fG;
            image2(i,j,2) = fB;
        }
    }
    image2.saveImage(filename2);
}
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
