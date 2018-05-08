#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/image_transforms.h>
// #include "dlib/matrix.h"
#include <iostream>
#include <dlib/dnn.h>
#include <iostream>
#include <dlib/data_io.h>

using namespace std;
using namespace dlib;

int main(int argc, char **argv)
{

    try
    {
        // make sure the user entered an argument to this program
        if (argc != 2)
        {
            cout << "error, you have to enter a BMP file as an argument to this program" << endl;
            return 1;
        }
        using my_net_type = relu<input<array2d<rgb_pixel>>>;
        my_net_type net;
        array2d<rgb_pixel> img_mine, out_img_mine;
        load_image(img_mine, argv[1]);
        cout<<"Net details"<<net(img_mine).nr()<<" "<<net(img_mine).nc();
        image_window my_window(mat(net(img_mine),150,150 ), "Convolved Image");
        image_window my_window1(mat(img_mine), "Original Image");
        my_window.wait_until_closed();
        my_window1.wait_until_closed();

    }
    catch (exception &e)
    {
        cout << "exception thrown: " << e.what() << endl;
    }
}