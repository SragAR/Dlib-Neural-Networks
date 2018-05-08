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
        using my_relu_net_type = relu<input<array2d<rgb_pixel>>>;
        my_relu_net_type relu_net;
        using my_max_pool_type = max_pool<2,2,2,2,input<array2d<rgb_pixel>>>;
        my_max_pool_type max_pool_net;
        array2d<rgb_pixel> img_mine, out_img_mine;
        load_image(img_mine, argv[1]);
        cout<<"Net details"<<relu_net(img_mine).nr()<<" "<<relu_net(img_mine).nc();
        image_window my_window(mat(relu_net(img_mine),150,150 ), "Convolved Image");
        long n_rows, n_columns;
        n_rows = max_pool_net(img_mine).nr();
        n_columns = max_pool_net(img_mine).nc();
        cout<<"Maxpool  details"<<max_pool_net(img_mine).nr()<<" "<<max_pool_net(img_mine).nc();
        image_window my_window2(mat(max_pool_net(img_mine),n_rows,n_columns), "MaxPool Image");
        image_window my_window1(mat(img_mine), "Original Image");
        my_window.wait_until_closed();
        my_window1.wait_until_closed();
        my_window2.wait_until_closed();

    }
    catch (exception &e)
    {
        cout << "exception thrown: " << e.what() << endl;
    }
}