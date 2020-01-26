#include <math.h>
#include "image.h"

float nn_interpolate(image im, float x, float y, int c)
{
    // TODO Fill in
    return get_pixel(im,floor(x), floor(y),c);

}

image nn_resize(image im, int w, int h)
{
    // TODO Fill in (also fix that first line)
    image im_r = make_image(w, h, im.c);
    float w_f = (float)w/im.w;
    float h_f = (float)h/im.h;

    if(w_f > 1 && h_f > 1 )
    {
        for(int c = 0; c < im_r.c; c++)
        {
            for(int i = 0; i < im_r.w; i++)
            {
                for(int j = 0; j < im_r.h; j++)
                {
                    float px = nn_interpolate(im, i/w_f, j/h_f, c);
                    set_pixel(im_r, i, j, c, px);

                }
            }
        }
    }
    else
    {
        for(int c = 0; c < im.c; c++)
        {
            for(int i = 0; i < im.w; i++)
            {
                for(int j = 0; j < im.h; j++)
                {
                    float px = nn_interpolate(im, i, j, c);
                    set_pixel(im_r, floor((float)i*w_f), floor((float)j*h_f), c, px);

                }
            }
        }
    }
    save_image(im_r, "output");
    return im_r;
}

float bilinear_interpolate(image im, float x, float y, int c)
{
    // TODO
    return 0;
}

image bilinear_resize(image im, int w, int h)
{
    // TODO
    return make_image(1,1,1);
}

