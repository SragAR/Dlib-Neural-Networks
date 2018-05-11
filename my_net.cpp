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
        using my_max_pool_type = max_pool<2, 2, 2, 2, input<array2d<rgb_pixel>>>;
        my_max_pool_type max_pool_net;
        using fully_connected_type = fc_no_bias<128, input<array2d<rgb_pixel>>>;
        fully_connected_type full_net;

        template <int N, typename SUBNET>
        using ares = relu<residual<block, N, affine, SUBNET>>;
        template <int N, typename SUBNET>
        using ares_down = relu<residual_down<block, N, affine, SUBNET>>;
        template <int N, template <typename> class BN, int stride, typename SUBNET>
        using block = BN<con<N, 3, 3, 1, 1, relu<BN<con<N, 3, 3, stride, stride, SUBNET>>>>>;

        using mock_resnet_type = max_pool<3, 3, 2, 2, relu<affine<con<32, 7, 7, 2, 2, input<array2d<rgb_pixel>>>>>>;
        mock_resnet_type mock_resnet;

        array2d<rgb_pixel> img_mine, out_img;
        load_image(img_mine, argv[1]);
        long n_rows, n_columns;
        resizable_tensor resnet_output;
        resnet_output = mock_resnet(img_mine);
        n_rows = resnet_output.nr();
        n_columns = resnet_output.nc();
        cout << n_rows << " " << n_columns;
        image_window my_window2(mat(resnet_output, n_rows, n_columns), "Resnet Output");
        image_window my_window1(mat(img_mine), "Original Image");
        my_window1.wait_until_closed();
        my_window2.wait_until_closed();
    }
    catch (exception &e)
    {
        cout << "exception thrown: " << e.what() << endl;
    }
}