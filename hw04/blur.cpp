#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <map>
#include <queue>
#include "graphics.h"
using namespace std;

/* Image code borrowed from our USA map demo... */

struct Pixel {
    unsigned char r, g, b;
};

int width, height;
Pixel *image;

Pixel white = { 255, 255, 255 };
Pixel black = { 0, 0, 0 };

Pixel &get_pixel(int x, int y) {
    return image[y*width + x];
}

void read_image(const char *filename) {
    FILE *fp = fopen (filename, "r");
    int dummy = fscanf (fp, "P6\n%d %d\n255%*c", &width, &height);
    image = new Pixel[width * height];
    dummy = fread (image, width*height, sizeof(Pixel), fp);
    fclose (fp);
}

void write_image(const char *filename) {
    FILE *fp = fopen (filename, "w");
    fprintf (fp, "P6\n%d %d\n255\n", width, height);
    int dummy = fwrite (image, width*height, sizeof(Pixel), fp);
    fclose (fp);
}

/* To be completed from here on... */

void calculate_blur(void) {
    // Modify image to add blur effect
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (image[i].r == 255 && image[i].g == 255 && image[i].b == 255) {

            }
            else if (image[i+1].r == 255 && image[i+1].g == 255 && image[i+1].b == 255) {
                //Pixel is white

            }
            else if (image[i-1].r == 255 && image[i-1].g == 255 && image[i-1].b == 255) {

            }
            else if (image[j].r == 255 && image[j].g == 255 && image[j].b == 255) {

            }
            else if (image[j+1].r == 255 && image[j+1].g == 255 && image[j+1].b == 255) {

            }
            else if (image[j-1].r == 255 && image[j-1].g == 255 && image[j-1].b == 255) {

            }

        }
    }
}

int main(void) {
    read_image("paw.ppm");
    calculate_blur();
    write_image("paw2.ppm");
}
