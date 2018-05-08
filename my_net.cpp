#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/image_transforms.h>
#include <iostream>

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
        array2d<rgb_pixel> img;
        load_image(img, argv[1]);
        array2d<unsigned char> blurred_img;
        gaussian_blur(img, blurred_img);
        image_window my_window(blurred_img, "Blurred Image");
        my_window.wait_until_closed();
    }
    catch (exception &e)
    {
        cout << "exception thrown: " << e.what() << endl;
    }
}