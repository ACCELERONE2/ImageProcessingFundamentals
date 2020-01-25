#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{
    // TODO Fill this in

    if(x > im.w || x < 0 || y > im.h || y < 0 || c > im.c || c < 0  )
    {
       if(x < 0)
       {
           x = 0;
       }
       else if(x > im.w)
       {
           x = im.w;
       }
       if(y < 0)
       {
           y = 0;
       }
       else if(y > im.h)
       {
         y = im.h;
       }
       if(c < 0)
       {
         c = 0;
       }
       else if(c > im.c)
       {
           c = im.c;
       }
    }
    int val = x + (y*im.w)+ (c*im.w*im.h);

    return im.data[val];
}

void set_pixel(image im, int x, int y, int c, float v)
{
    // TODO Fill this in
     if(x > im.w || x < 0 || y > im.h || y < 0 || c > im.c || c < 0  ){
        return;
     }
     int val = x + (y*im.w)+ (c*im.w*im.h);
     im.data[val] = v;

}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    // TODO Fill this in
      for(int c = 0; c < im.c; c++)
      {
        for(int i = 0; i < im.w; i++)
            {
                for(int j = 0; j < im.h; j++)
                {
                    float val = get_pixel(im,i,j,c);
                    set_pixel(copy, i, j, c, val);

                }
        }
      }


    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    // TODO Fill this in
    for(int i = 0; i < im.w; i++)
    {
        for(int j = 0; j < im.h; j++)
        {
           float val = 0.299*get_pixel(im,i,j,0) + 0.587*get_pixel(im,i,j,1) + 0.114*get_pixel(im,i,j,2);
           set_pixel(gray, i, j, 0, val);
        }
    }
    return gray;
}

void shift_image(image im, int c, float v)
{
    // TODO Fill this in
    for(int i = 0; i < im.w; i++)
    {
        for(int j = 0; j < im.h; j++)
        {
            float val = get_pixel(im,i,j,c);
            set_pixel(im, i, j, c, (v+val));
        }
    }
}

void clamp_image(image im)
{
    // TODO Fill this in
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    // TODO Fill this in
    image copy = copy_image(im);

    for(int i = 0; i < im.w; i++)
    {
        for(int j = 0; j < im.h; j++)
        {
            float val = three_way_max(get_pixel(copy,i,j,0),get_pixel(copy,i,j,1),get_pixel(copy,i,j,2));
            set_pixel(im,i,j,2, val);
            float min = three_way_min(get_pixel(copy,i,j,0),get_pixel(copy,i,j,1),get_pixel(copy,i,j,2));
            float c = val - min;
            float sat;
            if(val == 0)
            {
                sat = 0;
            }
            else
            {
                sat = c/val;

            }
             set_pixel(im,i,j,1, sat);
             float hue, hue_;

             if(c == 0)
             {
                 hue = 0;
             }else if(val == get_pixel(copy,i,j,0))
             {
                 hue_ = ((get_pixel(copy,i,j,1) - get_pixel(copy,i,j,2))/c);

             }else if(val == get_pixel(copy,i,j,1))
             {
                 hue_ = (((get_pixel(copy,i,j,2) - get_pixel(copy,i,j,0))/c)+2);

             }else if(val == get_pixel(copy,i,j,2))
             {
                 hue_ = (((get_pixel(copy,i,j,0) - get_pixel(copy,i,j,1))/c)+4);
             }

             if(hue_ < 0)
             {
                 hue = (hue_/6) + 1;
             }
             else
             {
                 hue = hue/6;
             }
             set_pixel(im,i,j,0, hue);
        }
    }

}
