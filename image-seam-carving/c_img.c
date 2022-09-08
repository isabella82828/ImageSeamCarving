#include "c_img.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void create_img(struct rgb_img **im, size_t height, size_t width){
    *im = (struct rgb_img *)malloc(sizeof(struct rgb_img));
    (*im)->height = height;
    (*im)->width = width;
    (*im)->raster = (uint8_t *)malloc(3 * height * width);
}


int read_2bytes(FILE *fp){
    uint8_t bytes[2];
    fread(bytes, sizeof(uint8_t), 1, fp);
    fread(bytes+1, sizeof(uint8_t), 1, fp);
    return (  ((int)bytes[0]) << 8)  + (int)bytes[1];
}

void write_2bytes(FILE *fp, int num){
    uint8_t bytes[2];
    bytes[0] = (uint8_t)((num & 0XFFFF) >> 8);
    bytes[1] = (uint8_t)(num & 0XFF);
    fwrite(bytes, 1, 1, fp);
    fwrite(bytes+1, 1, 1, fp);
}

void read_in_img(struct rgb_img **im, char *filename){
    FILE *fp = fopen(filename, "rb");
    size_t height = read_2bytes(fp);
    size_t width = read_2bytes(fp);
    create_img(im, height, width);
    fread((*im)->raster, 1, 3*width*height, fp);
    fclose(fp);
}

void write_img(struct rgb_img *im, char *filename){
    FILE *fp = fopen(filename, "wb");
    write_2bytes(fp, im->height);
    write_2bytes(fp, im->width);
    fwrite(im->raster, 1, im->height * im->width * 3, fp);
    fclose(fp);
}

uint8_t get_pixel(struct rgb_img *im, int y, int x, int col){
    return im->raster[3 * (y*(im->width) + x) + col];
}

void set_pixel(struct rgb_img *im, int y, int x, int r, int g, int b){
    im->raster[3 * (y*(im->width) + x) + 0] = r;
    im->raster[3 * (y*(im->width) + x) + 1] = g;
    im->raster[3 * (y*(im->width) + x) + 2] = b;
}

void destroy_image(struct rgb_img *im)
{
    free(im->raster);
    free(im);
}


void print_grad(struct rgb_img *grad){
    int height = grad->height;
    int width = grad->width;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            printf("%d\t", get_pixel(grad, i, j, 0));
        }
    printf("\n");    
    }
}

int max(int a, int b){
    if (a >= b){
        return a;
    }
    return b;
}

// int main(void){
//     struct rgb_img *image;
//     char s[6];

//     for(int i = 0; i<=5;i++){
//         read_in_img(&image, "UofTPresident.bin");
//         for(int x = 0; x < (image->width); x++){
//             for(int y = 0; y < (image->height); y++){
//                 int r = get_pixel(image, y, x, 0);   // 0 is red 1 is green 2 is blue
//                 //printf("%d\n", r);
//                 int g = get_pixel(image, y, x, 1);
//                 int b = get_pixel(image, y, x, 2);

//                 if (max(max(r*i, g*i), b*i) > 255){
//                     float s = ((float)max(max(r, g), b))/255.0;
//                     r = (int)((float)r*s);
//                     g = (int)((float)g*s);
//                     b = (int)((float)b*s);
//                     set_pixel(image, y, x, r, g, b);
//                 }
//                 else{
//                     set_pixel(image, y, x, r*i, g*i, b*i);
//                 }
//             }
//         }
//         sprintf(s, "%d.bin", i);
//         write_img(image, s);
//     }
//     //write_img(struct rgb_img *im, char *filename);   convert back to png
//     return 0;
// }