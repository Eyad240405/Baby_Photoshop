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
void greyscale(Image& image , string& filename2){
    for(int i = 0 ; i < image.width ; i++){
        for(int j = 0  ; j < image.height ; j++){

            unsigned int avg = 0 ;
            for(int k = 0 ; k < image.channels ; k++){
                avg += image(i,j,k);
            }

            avg = avg / 3;
            for(int k = 0 ; k < image.channels ; k++){
                image(i,j,k)=avg;
            }
        }
    }
    image.saveImage(filename2);
}

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




void fixed_cropping(Image& image,string& filename2 , int w , int h){

    Image image_n(w,h);
    for(int i = 0 ; i < w ; ++i){
        for(int j = 0 ; j < h ; ++j){
            for(int k = 0 ; k < image.channels ; ++k){
                image_n(i,j,k) = image(i,j,k);
            }
        }
    }
    image_n.saveImage(filename2);
}

void resize_merge(Image& image , string& filename2 , int w , int h ){

    float fw , fh;
    fw= float (image.width ) / w;
    fh= float (image.height ) / h;

    Image image3(w,h);
    int a , b;
    for(int i = 0 ; i < w ; i++){
        for(int j = 0 ; j < h ; j++){
            for(int k = 0 ; k < image.channels ; ++k){
                a = round (fw * i);
                b = round (fh * j);
                image3(i,j,k) = image(a,b,k);
            }
        }
    }
    image3.saveImage(filename2);
}

void merge(Image& image,string& filename, string& filename2) {
    string f_l2 ;
    string o1="m1.jpg" , o2="m2.jpg";
    Image image2;
    cout <<endl <<"Please provide the desired input file name."<<endl
         <<"With its extension (jpg / jpeg / png / bmp)"<<endl<<"Enter:";
    cin>>f_l2;
    while(true){
        try {
            image2.loadNewImage(f_l2);
            break;
        }
        catch( invalid_argument) {
            cout << "Please enter a valid photo \n" << endl;
            cin>>f_l2;
        }
    }

    if (image2.loadNewImage(f_l2)) {
        cout << "Loaded Successfully!" << endl;
    }
    int x , y;
    string ch="3";
    while(ch!="1" && ch!="2"){
        cout<<endl<<"1) Resize to fit"<<endl<<"2) Merge the common area"<<endl<<"Choose:";
        cin>>ch;
    }
    if(ch=="1") {
        x = max(image.width, image2.width);
        y = max(image.height, image2.height);

        resize_merge(image, o1, x, y);

        resize_merge(image2, o2, x, y);
    }
    else if(ch=="2"){
        x = min(image.width, image2.width);
        y = min(image.height, image2.height);

        fixed_cropping(image, o1, x, y);

        fixed_cropping(image2, o2, x, y);

    }
    image.loadNewImage(o1);
    image2.loadNewImage(o2);

    Image image4(x,y);
    //fixed_cropping(image2 , filename2 , image2.width , image2.height);
    for (int i = 0; i < x ; ++i) {
        for (int j = 0; j < y ; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                image4(i, j, k) = ((image(i,j, k)) + (image2(i,j, k)) ) / 2;
            }
        }
    }
    image4.saveImage(filename2);
}

void Darken_and_Lighten_Image(Image& image , string& filename2){
    string s;
    cout<<endl<<"1) Darker by 50%"<<endl<<"2) Lighter by 50%"<<endl<<"Choose:";
    cin>>s;
    for(int i = 0 ; i < image.width ; i++){
        for(int j = 0  ; j < image.height ; j++){
            for(int k = 0 ; k < image.channels ; k++){
                if(s=="1"){image(i,j,k)=(image(i,j,k))*1/2;}
                else if(s=="2"){
                    if((image(i,j,k))*1.5>=255){
                        image(i,j,k)=255;
                    }
                    else{
                        image(i,j,k)=(image(i,j,k))*1.5;
                    }
                }
            }
        }
    }
    image.saveImage(filename2);
}

void V_flip(Image& image,string& filename,string& filename2) {
    Image image2(filename);
    Image image3(filename);

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
    image.saveImage(filename2);
}



void Purple(Image& image , string& filename2 ){
    double y = 0.6 ;
    for(int i = 0 ; i < image.width ; i++){
        for(int j = 0 ; j < image.height ; j++){
            if((image(i,j,1) * y)<0){image(i,j,1)=0;}
            else {image(i,j,1)*=y;}
        }
    }
    image.saveImage(filename2);
}

void retro(Image& image , string& filename2 ){
    srand(static_cast<unsigned int>(time(0)));

    for(int i = 0 ; i < image.width ; i++){
        for(int j = 0 ; j < image.height ; j++){
            for(int k = 0 ; k < 3 ; k ++) {
                int intensity = 50;
                int noise_value = rand() % (intensity * 2 + 1) - intensity;
                image(i, j, k) = (((0.88) * image(i, j, k)) + (0.33) * noise_value);
            }
        }
    }
    image.saveImage(filename2);

    for(int i = 0 ; i < image.width ; i++) {
        for (int j = 0; j < image.height; j++) {
            for(int k = 0 ; k < 3 ; k++) {
                if (j % 2 == 0) {
                    image(i,j,k)*=0.5;
                }
            }
        }
    }


    image.saveImage(filename2);
}

void Infrared(Image& image , string& filename2){
    greyscale(image , filename2);
    for(int i = 0 ; i < image.width ; i++){
        for(int j = 0 ; j < image.height ; j++){
            image(i,j,0)=0;
            //image(i,j,1)=128;
            //image(i,j,2)=128;
        }
    }
    image.saveImage(filename2);
    inverted(image , filename2);
}

void Detect_Image_Edges(Image& image , string& filename2){
    //greyscale(image , filename2);
    for(int i = 1 ; i < image.width-1 ; i++){
        for(int j = 1  ; j < image.height-1 ; j++) {
            unsigned int avg = 0 ;
            for(int k = 0 ; k < 3 ; k++) {
                if ((abs(image(i, j, k) - image(i, j+1, k)) >= 120
                || abs(image(i, j, k) - image(i+1, j, k)) >= 120
                || abs(image(i, j, k) - image(i+1, j+1, k)) >= 120)){
                    avg = 17 ;
                }
                else {avg = 255 ;}
                image(i,j,0)=avg;
                image(i,j,1)=avg;
                image(i,j,2)=avg;
            }
        }

    }
    image.saveImage(filename2);
}

void inverted(Image& image , string& filename2 ){
    for(int i = 0 ; i < image.width ; i++){
        for(int j = 0 ; j < image.height ; j++){

            unsigned int avg = 0 ;
            for(int k = 0 ; k < image.channels ; k++){
                image(i,j,k)=255 - image(i,j,k) ;
            }
        }
    }
    image.saveImage(filename2);
}
void Rotate(Image& image,string& filename,string& filename2){
    int n;
    cout << "Rotation by:\n" << "1) 90\n" << "2) 180\n" << "3) 270\n" << "Choose[1 , 2 , 3]:";
    cin >> n;
    // Rotate 90 degrees
    if(n == 1){
        Image image2(image.height,image.width);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    image2(image.height-j-1, i, k) = image(i, j, k);
                }
            }
        }
        image2.saveImage(filename2);
    }
    // Rotate 180 degrees
    if(n == 2) {
        Image image2(image.height,image.width);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    image2(image.height - j-1,image.width - i-1, k)=image(i, j, k);
                }
            }
        }
        Image image3(image2.height,image2.width);
        for (int i = 0; i < image2.width; ++i) {
            for (int j = 0; j < image2.height; ++j) {
                for (int k = 0; k < image2.channels; ++k) {
                    image3(image2.height-j-1, i, k) = image2(i, j, k);
                }
            }
        }
        image3.saveImage(filename2);
    }
    // Rotate 270 degrees
    if(n == 3){
        Image image2(image.height,image.width);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    image2(j,image.width-i-1, k)=image(i, j, k);
                }
            }
        }
        image2.saveImage(filename2);
    }
}
int calculate_division_factor(int width, int height) {
    return min(width, height) / 4;
}
void Simple_Frame(Image& image,string& filename2, const string color) {
    int division_factor = calculate_division_factor(image.width, image.height);
    int frameWidth = min(image.width, image.height) / 20;
    int frame_startPoint_1 = image.width / division_factor;
    int frame_startPoint_2 = image.height / division_factor;

    for (int j = 0; j < image.height; ++j) {
        for (int i = 0; i < frameWidth + frame_startPoint_2 / 6; ++i) {
            if (color == "1") {
                image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = 0;
                image(image.width - 1 - i, j, 0) = image(image.width - 1 - i, j, 1) = image(image.width - 1 - i, j, 2) = 0;
            } else if (color == "2") {
                image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = 255;
                image(image.width - 1 - i, j, 0) = image(image.width - 1 - i, j, 1) = image(image.width - 1 - i, j, 2) = 255;
            }else if (color == "3") {
                image(i, j, 0) = 255;
                image(i, j, 1) = 0;
                image(i, j, 2) = 0;
                image(image.width - 1 - i, j, 0) = 255;
                image(image.width - 1 - i, j, 1) = 0;
                image(image.width - 1 - i, j, 2) = 0;
            }
            else if (color == "4") {
                image(i, j, 0) = 0;
                image(i, j, 1) = 255;
                image(i, j, 2) = 0;
                image(image.width - 1 - i, j, 0) = 0;
                image(image.width - 1 - i, j, 1) = 255;
                image(image.width - 1 - i, j, 2) = 0;
            }
            else if (color == "5") {
                image(i, j, 0) = 0;
                image(i, j, 1) = 0;
                image(i, j, 2) = 255;
                image(image.width - 1 - i, j, 0) = 0;
                image(image.width - 1 - i, j, 1) = 0;
                image(image.width - 1 - i, j, 2) = 255;
            }
            else if (color == "6") {
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 0;
                image(image.width - 1 - i, j, 0) = 255;
                image(image.width - 1 - i, j, 1) = 255;
                image(image.width - 1 - i, j, 2) = 0;
            }
            else if (color == "7") {
                image(i, j, 0) = 160;
                image(i, j, 1) = 32;
                image(i, j, 2) = 240;
                image(image.width - 1 - i, j, 0) = 160;
                image(image.width - 1 - i, j, 1) = 32;
                image(image.width - 1 - i, j, 2) = 240;
            }
        }
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < frameWidth + frame_startPoint_1 / 6; ++j) {
            if (color == "1") {
                image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = 0;
                image(i, image.height - 1 - j, 0) = image(i, image.height - 1 - j, 1) = image(i, image.height - 1 - j, 2) = 0;
            }  else if (color == "2") {
                image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = 255;
                image(i, image.height - 1 - j, 0) = image(i, image.height - 1 - j, 1) = image(i, image.height - 1 - j, 2) = 255;
            }else if (color == "3") {
                image(i, j, 0) = 255;
                image(i, j, 1) = 0;
                image(i, j, 2) = 0;
                image(i, image.height - 1 - j, 0) = 255;
                image(i, image.height - 1 - j, 1) = 0;
                image(i, image.height - 1 - j, 2) = 0;
            }
            else if (color == "4") {
                image(i, j, 0) = 0;
                image(i, j, 1) = 255;
                image(i, j, 2) = 0;
                image(i, image.height - 1 - j, 0) = 0;
                image(i, image.height - 1 - j, 1) = 255;
                image(i, image.height - 1 - j, 2) = 0;
            }
            else if (color == "5") {
                image(i, j, 0) = 0;
                image(i, j, 1) = 0;
                image(i, j, 2) = 255;
                image(i, image.height - 1 - j, 0) = 0;
                image(i, image.height - 1 - j, 1) = 0;
                image(i, image.height - 1 - j, 2) = 255;
            }
            else if (color == "6") {
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 0;
                image(i, image.height - 1 - j, 0) = 255;
                image(i, image.height - 1 - j, 1) = 255;
                image(i, image.height - 1 - j, 2) = 0;
            }
            else if (color == "7") {
                image(i, j, 0) = 160;
                image(i, j, 1) = 32;
                image(i, j, 2) = 240;
                image(i, image.height - 1 - j, 0) = 160;
                image(i, image.height - 1 - j, 1) = 32;
                image(i, image.height - 1 - j, 2) = 240;
            }
        }
    }
    image.saveImage(filename2);    
}
void Fancy_Frame(Image& image, string& filename2,const string& color) {
    int frameSize_factor_1 = max(1, image.width / 1900);
    int frameSize_factor_2 = max(1, image.height / 1900);
    int frameWidth = min(image.width, image.height) / 80;
    int frame_startPoint_1 = image.width / (4 * frameSize_factor_1);
    int frame_startPoint_2 = image.height / (4 * frameSize_factor_2);

    if(image.width<1000 && image.height<1000){

        // Apply frame color to the top and bottom borders
        for (int i = 0; i < image.width; ++i) {
            for (int j = frame_startPoint_2/3.9; j < frame_startPoint_2/3.9 + frameWidth; ++j) {
                image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = 255; // Assuming 'white' color
                image(i, image.height - 1 - j, 0) = image(i, image.height - 1 - j, 1) = image(i, image.height - 1 - j, 2) = 255;
            }
        }
        // Apply frame color to the top and bottom borders inside the frame
        for (int i = 0; i < image.width; ++i) {
            for (int j = frame_startPoint_2/3; j < frame_startPoint_2/3 + frameWidth; ++j) {
                image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = 128; // Assuming 'gray' color
                image(i, image.height - 1 - j, 0) = image(i, image.height - 1 - j, 1) = image(i, image.height - 1 - j, 2) = 128;
            }
        }
        // Apply frame color to the left and right borders
        for (int j = 0; j < image.height; ++j) {
            for (int i = frame_startPoint_1/3.5; i < frame_startPoint_1/3.5 + frameWidth; ++i) {
                image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = 255;
                image(image.width - 1 - i, j, 0) = image(image.width - 1 - i, j, 1) = image(image.width - 1 - i, j, 2) = 255;
            }
        }
        // Apply frame color to the left and right borders inside the frame
        for (int j = 0; j < image.height; ++j) {
            for (int i = frame_startPoint_1 / 2.7; i < frame_startPoint_1 / 2.7 + frameWidth; ++i) {
                image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = 128;
                image(image.width - 1 - i, j, 0) = image(image.width - 1 - i, j, 1) = image(image.width - 1 - i, j, 2) = 128;
            }
        }
    }
    else if(image.width>1000 && image.height>1000){
        // Apply frame color to the top and bottom borders
        for (int i = 0; i < image.width; ++i) {
            for (int j = frame_startPoint_2/4; j < frame_startPoint_2/4 + frameWidth; ++j) {
                image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = 255; // Assuming 'white' color
                image(i, image.height - 1 - j, 0) = image(i, image.height - 1 - j, 1) = image(i, image.height - 1 - j, 2) = 255;
            }
        }
        // Apply frame color to the top and bottom borders inside the frame
        for (int i = 0; i < image.width; ++i) {
            for (int j = frame_startPoint_2/3.1; j < frame_startPoint_2/3.1 + frameWidth; ++j) {
                image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = 128; // Assuming 'gray' color
                image(i, image.height - 1 - j, 0) = image(i, image.height - 1 - j, 1) = image(i, image.height - 1 - j, 2) = 128;
            }
        }
        // Apply frame color to the left and right borders
        for (int j = 0; j < image.height; ++j) {
            for (int i = frame_startPoint_1/3.1; i < frame_startPoint_1/3.1 + frameWidth; ++i) {
                image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = 255;
                image(image.width - 1 - i, j, 0) = image(image.width - 1 - i, j, 1) = image(image.width - 1 - i, j, 2) = 255;
            }
        }
        // Apply frame color to the left and right borders inside the frame
        for (int j = 0; j < image.height; ++j) {
            for (int i = frame_startPoint_1 / 2.3; i < frame_startPoint_1 / 2.3 + frameWidth; ++i) {
                image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = 128;
                image(image.width - 1 - i, j, 0) = image(image.width - 1 - i, j, 1) = image(image.width - 1 - i, j, 2) = 128;
            }
        }
    }
    else{
        // Apply frame color to the top and bottom borders
        for (int i = 0; i < image.width; ++i) {
            for (int j = frame_startPoint_2/3.3; j < frame_startPoint_2/3.3 + frameWidth; ++j) {
                image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = 255; // Assuming 'white' color
                image(i, image.height - 1 - j, 0) = image(i, image.height - 1 - j, 1) = image(i, image.height - 1 - j, 2) = 255;
            }
        }
        // Apply frame color to the top and bottom borders inside the frame
        for (int i = 0; i < image.width; ++i) {
            for (int j = frame_startPoint_2/2.5; j < frame_startPoint_2/2.5 + frameWidth; ++j) {
                image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = 128; // Assuming 'gray' color
                image(i, image.height - 1 - j, 0) = image(i, image.height - 1 - j, 1) = image(i, image.height - 1 - j, 2) = 128;
            }
        }
        // Apply frame color to the left and right borders
        for (int j = 0; j < image.height; ++j) {
            for (int i = frame_startPoint_1/6; i < frame_startPoint_1/6 + frameWidth; ++i) {
                image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = 255;
                image(image.width - 1 - i, j, 0) = image(image.width - 1 - i, j, 1) = image(image.width - 1 - i, j, 2) = 255;
            }
        }
        // Apply frame color to the left and right borders inside the frame
        for (int j = 0; j < image.height; ++j) {
            for (int i = frame_startPoint_1 / 4.7; i < frame_startPoint_1 / 4.7 + frameWidth; ++i) {
                image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = 128;
                image(image.width - 1 - i, j, 0) = image(image.width - 1 - i, j, 1) = image(image.width - 1 - i, j, 2) = 128;
            }
        }
    }
    image.saveImage(filename2);
}
int Pixel(Image& image, int col, int row, int k, int width, int height) {
    int sum = 0;
    int sumKernel = 0;
    int kernelSize = 35; // We can adjust the kernel to apply different blur levels


    for (int j = -kernelSize/2; j <= kernelSize/2; j++) {
        for (int i = -kernelSize/2; i <= kernelSize/2; i++) {
            if ((row + j) >= 0 && (row + j) < height && (col + i) >= 0 && (col + i) < width) {
                int color = image.getPixel(col + i, row + j, k);

                sum += color;
                sumKernel++;
            }
        }
    }
    return sum / sumKernel;
}
void Blur(Image& image, Image& result) {
    for (int row = 0; row < image.height; row++) {
        for (int col = 0; col < image.width; col++) {
            for (int k = 0; k < 3; k++) {
                result.setPixel(col, row, k, Pixel(image, col, row, k, image.width, image.height));
            }
        }
    }
}
void sunlight(Image& image, string& filename2){
    Image photo(image.width, image.height);
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) 
        {
            photo(i, j, 0) = image(i, j, 0);
            photo(i, j, 1) = image(i, j, 1);
            photo(i, j, 2) = image(i, j, 2);


            photo(i, j, 0) = min(photo(i, j, 0) + 30, 255);
            photo(i, j, 1) = min(photo(i, j, 1) + 20, 255);
            photo(i, j, 2) = max(photo(i, j, 2) - 50, 0);
        }
    }
    photo.saveImage(filename2);
}
void sepia(Image& image, string& filename2){
    Image image2(image.width,image.height);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            int r =image(i, j, 0);
            int g =image(i, j, 1);
            int b =image(i, j, 2);

            int sepia_r = (r*0.393)+(g*0.769)+(b*0.189);
            int sepia_g = (r*0.349)+(g*0.686)+(b*0.168);
            int sepia_b = (r*0.272)+(g*0.534)+(b*0.131);

            sepia_r = min(255, max(0, sepia_r));
            sepia_g = min(255, max(0, sepia_g));
            sepia_b = min(255, max(0, sepia_b));

            image2(i,j,0)= sepia_r;
            image2(i,j,1)= sepia_g;
            image2(i,j,2)= sepia_b;

        }
    }
    image2.saveImage(filename2);
}

void emboss(Image& image, string& filename2){
    Image image2(image.width,image.height);
    // Define the embossing kernel
    int embossKernel[3][3] = {{-2, -1, 0},
                               {-1,  1, 1},
                               { 0,  1, 2}};
                               
    // Iterate over each pixel and apply stamp-like embossing effect
    for (int y = 1; y < image.height - 1; ++y) {
        for (int x = 1; x < image.width - 1; ++x) {
            int embossValue = 0;

            // Convolve image with the embossing kernel
            for (int j = -1; j <= 1; ++j) {
                for (int i = -1; i <= 1; ++i) {
                    embossValue += image(x + i, y + j, 0) * embossKernel[j + 1][i + 1];
                }
            }

            // Add intensity and clamp emboss value to the range [0, 255]
            embossValue = min(max(embossValue +128, 0), 255);

            

            // Set the pixels to the new values
            image2(x, y, 0) = embossValue;
            image2(x, y, 1) = embossValue;
            image2(x, y, 2) = embossValue;
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
                 << "19) Sepia filter" << endl
                 << "20) Emboss filter" << endl<<endl
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
                int x = 0;
                while (x == 0) {
                    cout << "What frame do you want to add to your photo" << endl;
                    cout << "1- simple frame" << endl;
                    cout << "2- fancy frame" << endl;
                    string choice;
                    cin >> choice;
                    string color;
                    if (choice == "1" || choice == "2") {
                        int y = 0;
                        while (y == 0) {
                            cout << "Choose a color for the frame:\n";
                            cout << "1. Black\n2. White\n3. Red\n4. Green\n5. Blue\n6. Yellow\n7. Purple\n";
                            cout << "Which color do you want: ";
                            cin >> color;
                            if (color == "1" || color == "2" || color == "3" || color == "4" || color == "5" || color == "6" || color == "7") {
                                if (choice == "1") Simple_Frame(image,filename2, color);
                                else {
                                    Fancy_Frame(image,filename2, color);
                                    Simple_Frame(image,filename2, color);
                                }
                                y = 1;
                            } else {
                                cout << "Invalid color choice. Please choose again." << endl;
                                y = 0;
                            }
                        }
                        x = 1;
                    } else {
                        cout << "Invalid choice. Please choose again." << endl;
                    }
                }
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
                sepia(image, filename2);
                cout << endl;
            } else if (choice == "20") {
                emboss(image, filename);
                cout << endl;
            }
        }
        cout<<"Done , Check the " << filename2 << " file!"<<endl;
    }

}
