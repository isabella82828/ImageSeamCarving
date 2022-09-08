#include "seamcarving.h"
#include "c_img.h"
// #include "c_img.c"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int min3(int a, int b, int c){
    if(a <= b && a <= c){
        return a;
    }
    if(b <= a && b <= c){
        return b;
    }
    if(c <= b && c <= a){
        return c;
    }
}

int min2(int a, int b){
    if(a <= b){
        return a;
    }
    else{
        return b;
    }
}

void calc_energy(struct rgb_img *im, struct rgb_img **grad){
    //read_in_img(&im, "3x4.bin");
    int max_x = (im->width)-1;
    int max_y = (im->height)-1;

    int xcol;
    int ycol;

    create_img(grad, im->height, im->width);
    //(*grad)->raster = (uint8_t *)malloc(3 * (im->height) * (im->width) * sizeof(int)); 

    for(int x = 0; x < (im->width); x++){
        for(int y = 0; y < (im->height); y++){
            if(x == 0 && y == 0){  // top left corner
                int rx = get_pixel(im, y, x+1, 0) - get_pixel(im, y, max_x, 0);
                int gx = get_pixel(im, y, x+1, 1) - get_pixel(im, y, max_x, 1);
                int bx = get_pixel(im, y, x+1, 2) - get_pixel(im, y, max_x, 2);
                int xcol = (rx*rx) + (gx*gx) + (bx*bx);

                int ry = get_pixel(im, y+1, x, 0) - get_pixel(im, max_y, x, 0);  // calculating x for colours
                int gy = get_pixel(im, y+1, x, 1) - get_pixel(im, max_y, x, 1);
                int by = get_pixel(im, y+1, x, 2) - get_pixel(im, max_y, x, 2);
                int ycol = (ry*ry) + (gy*gy) + (by*by);
                uint8_t energy = (uint8_t)((sqrt(xcol + ycol))/10); 
                set_pixel(*grad, y, x, energy, energy, energy);
            }

            else if(x == max_x && y == 0){   //top right corner
                int rx = get_pixel(im, y, x-1, 0) - get_pixel(im, y, 0, 0);
                int gx = get_pixel(im, y, x-1, 1) - get_pixel(im, y, 0, 1);
                int bx = get_pixel(im, y, x-1, 2) - get_pixel(im, y, 0, 2);
                int xcol = rx*rx + gx*gx + bx*bx;

                int ry = get_pixel(im, y+1, x, 0) - get_pixel(im, max_y, x, 0);  // calculating x for colours
                int gy = get_pixel(im, y+1, x, 1) - get_pixel(im, max_y, x, 1);
                int by = get_pixel(im, y+1, x, 2) - get_pixel(im, max_y, x, 2);
                int ycol = ry*ry + gy*gy + by*by;

                uint8_t energy = (uint8_t)((sqrt(xcol + ycol))/10); 
                set_pixel(*grad, y, x, energy, energy, energy);
            }

            else if(x == 0 && y == max_y){   //bottom left corner
                int rx = get_pixel(im, y, x+1, 0) - get_pixel(im, y, max_x, 0);
                int gx = get_pixel(im, y, x+1, 1) - get_pixel(im, y, max_x, 1);
                int bx = get_pixel(im, y, x+1, 2) - get_pixel(im, y, max_x, 2);
                int xcol = rx*rx + gx*gx + bx*bx;

                int ry = get_pixel(im, y-1, x, 0) - get_pixel(im, 0, x, 0);  // calculating x for colours
                int gy = get_pixel(im, y-1, x, 1) - get_pixel(im, 0, x, 1);
                int by = get_pixel(im, y-1, x, 2) - get_pixel(im, 0, x, 2);
                int ycol = ry*ry + gy*gy + by*by;

                uint8_t energy = (uint8_t)((sqrt(xcol + ycol))/10); 
                set_pixel(*grad, y, x, energy, energy, energy);
            }

            else if(y == max_y && x == max_x){   //bottom right corner
                int rx = get_pixel(im, y, 0, 0) - get_pixel(im, y, x-1, 0);
                int gx = get_pixel(im, y, 0, 1) - get_pixel(im, y, x-1, 1);
                int bx = get_pixel(im, y, 0, 2) - get_pixel(im, y, x-1, 2);
                int xcol = rx*rx + gx*gx + bx*bx;

                int ry = get_pixel(im, y-1, x, 0) - get_pixel(im, 0, x, 0);
                int gy = get_pixel(im, y-1, x, 1) - get_pixel(im, 0, x, 1);
                int by = get_pixel(im, y-1, x, 2) - get_pixel(im, 0, x, 2);
                int ycol = ry*ry + gy*gy + by*by;

                uint8_t energy = (uint8_t)((sqrt(xcol + ycol))/10); 
                set_pixel(*grad, y, x, energy, energy, energy);
            }

            else if(x==0){
                int rx = get_pixel(im, y, x+1, 0) - get_pixel(im, y, max_x, 0);
                int gx = get_pixel(im, y, x+1, 1) - get_pixel(im, y, max_x, 1);
                int bx = get_pixel(im, y, x+1, 2) - get_pixel(im, y, max_x, 2);
                int xcol = rx*rx + gx*gx + bx*bx;

                int ry = get_pixel(im, y-1, x, 0) - get_pixel(im, y+1, x, 0);  // calculating x for colours
                int gy = get_pixel(im, y-1, x, 1) - get_pixel(im, y+1, x, 1);
                int by = get_pixel(im, y-1, x, 2) - get_pixel(im, y+1, x, 2);
                int ycol = ry*ry + gy*gy + by*by;

                uint8_t energy = (uint8_t)((sqrt(xcol + ycol))/10); 
                set_pixel(*grad, y, x, energy, energy, energy);
            }

            else if(x == max_x){
                int rx = get_pixel(im, y, x-1, 0) - get_pixel(im, y, 0, 0);
                int gx = get_pixel(im, y, x-1, 1) - get_pixel(im, y, 0, 1);
                int bx = get_pixel(im, y, x-1, 2) - get_pixel(im, y, 0, 2);
                int xcol = rx*rx + gx*gx + bx*bx;

                int ry = get_pixel(im, y-1, x, 0) - get_pixel(im, y+1, x, 0);  // calculating x for colours
                int gy = get_pixel(im, y-1, x, 1) - get_pixel(im, y+1, x, 1);
                int by = get_pixel(im, y-1, x, 2) - get_pixel(im, y+1, x, 2);
                int ycol = ry*ry + gy*gy + by*by;

                uint8_t energy = (uint8_t)((sqrt(xcol + ycol))/10); 
                set_pixel(*grad, y, x, energy, energy, energy);
            }

            else if(y == 0){
                int rx = get_pixel(im, y, x+1, 0) - get_pixel(im, y, x-1, 0);  //calculating x of colours
                int gx = get_pixel(im, y, x+1, 1) - get_pixel(im, y, x-1, 1);
                int bx = get_pixel(im, y, x+1, 2) - get_pixel(im, y, x-1, 2);
                int xcol = rx*rx + gx*gx + bx*bx;
                
                int ry = get_pixel(im, y+1, x, 0) - get_pixel(im, max_y, x, 0);  // calculating x for colours
                int gy = get_pixel(im, y+1, x, 1) - get_pixel(im, max_y, x, 1);
                int by = get_pixel(im, y+1, x, 2) - get_pixel(im, max_y, x, 2);
                int ycol = ry*ry + gy*gy + by*by;

                uint8_t energy = (uint8_t)((sqrt(xcol + ycol))/10); 
                set_pixel(*grad, y, x, energy, energy, energy);
            }

            else if(y == max_y){
                int rx = get_pixel(im, y, x+1, 0) - get_pixel(im, y, x-1, 0);  //calculating x of colours
                int gx = get_pixel(im, y, x+1, 1) - get_pixel(im, y, x-1, 1);
                int bx = get_pixel(im, y, x+1, 2) - get_pixel(im, y, x-1, 2);
                int xcol = rx*rx + gx*gx + bx*bx;

                int ry = get_pixel(im, y-1, x, 0) - get_pixel(im, 0, x, 0);  // calculating x for colours
                int gy = get_pixel(im, y-1, x, 1) - get_pixel(im, 0, x, 1);
                int by = get_pixel(im, y-1, x, 2) - get_pixel(im, 0, x, 2);
                int ycol = ry*ry + gy*gy + by*by;

                uint8_t energy = (uint8_t)((sqrt(xcol + ycol))/10); 
                set_pixel(*grad, y, x, energy, energy, energy);
            }
            
            else{
                int rx = get_pixel(im, y, x+1, 0) - get_pixel(im, y, x-1, 0);  //calculating x of colours
                int gx = get_pixel(im, y, x+1, 1) - get_pixel(im, y, x-1, 1);
                int bx = get_pixel(im, y, x+1, 2) - get_pixel(im, y, x-1, 2);
                int xcol = rx*rx + gx*gx + bx*bx;

                int ry = get_pixel(im, y-1, x, 0) - get_pixel(im, y+1, x, 0);  // calculating x for colours
                int gy = get_pixel(im, y-1, x, 1) - get_pixel(im, y+1, x, 1);
                int by = get_pixel(im, y-1, x, 2) - get_pixel(im, y+1, x, 2);
                int ycol = ry*ry + gy*gy + by*by;

                uint8_t energy = (uint8_t)((sqrt(xcol + ycol))/10); 
                set_pixel(*grad, y, x, energy, energy, energy);
            }
        }
    }
}
 

void dynamic_seam(struct rgb_img *grad, double **best_arr){
    int height = (grad->height);
    int width = (grad->width);

    double *min_energyarr = (double *)malloc(height * width * sizeof(double)); // need single pointer 

    for(int k = 0; k < width; k++){ //initializing the first row
        min_energyarr[k] = get_pixel(grad, 0, k, 0); // use get_pixel bc it doesnt matter what colour not raster
    }
    for(int t = 0; t < width*(height-1); t++){//initializing the empty spots to 0
        min_energyarr[width + t] = 0;
    }
    int y = 1;
    for(int h = width; h< height*width; h = h + width){
        min_energyarr[h] = get_pixel(grad, y, 0, 0) + min2(min_energyarr[h-width], min_energyarr[h-width+1]); // left cases
        for(int w = 1; w<width-1; w++){
            min_energyarr[h+w] = get_pixel(grad, y, w, 0) + min3(min_energyarr[h+w-width], min_energyarr[h+w-width-1], min_energyarr[h+w-width+1]);
        }
        min_energyarr[h + width-1] = get_pixel(grad, y, width-1, 0) + min2(min_energyarr[h-1], min_energyarr[h-2]);  //right cases
        y++;
    }
    *best_arr = min_energyarr;

    // for (int i = 0; i<height; i++){
    //     for(int j=0; j<width; j++){
    //         int index = i*width +j;
    //         printf("%f, ", min_energyarr[index]);
    //     }
    //     printf("\n");
    // }

    // for (int n = 0; n<height*width; n++){
    //     printf("%f\n", (*best_arr)[n]);
    // }
}

void recover_path(double *best, int height, int width, int **path){

    int *seam = (int *)malloc(height * sizeof(int));    //should we keep the (int *) casting?
    int min_index = 0;
    double min_energy = best[(height*width) - width];

    // for (int b = 0; b < (sizeof(*seam)/sizeof(seam[0])); b++){
    //     seam[b] = 0;
    // }

    for(int j = 0; j< width; j++){
        if(best[(height*width) - width + j] < min_energy){
            min_index = j;
            min_energy = best[(height*width) - width + j];
            seam[height-1] = min_index; // putting it at end of list
        }
    }
    int k = height-2;
    for(int i = height*width - width; i>=width; i = i-width){
        if(min_index == 0){ // left case
            min_energy = min2(best[i-width], best[i-width + 1]);
            if(best[i-width] == min_energy){ //parent directly above
                seam[k] = 0;
                k--;
            }else if(best[i-width + 1] == min_energy){
                seam[k] = 1;
                min_index = 1;
                k--;
            }
        }
        else if(min_index == width-1){ //right case
            min_energy = min2(best[i-1], best[i-2]);
            if(best[i-1] == min_energy){ //parent directly above
                seam[k] = width-1;
                k--;
            }else if(best[i-2] == min_energy){
                seam[k] = width-2;
                min_index = width-2;
                k--;
            }
        }
        else{ // middle case
            min_energy = min3(best[i - width + min_index], best[i - width + min_index - 1], best[i - width + min_index + 1]);
            if(best[i - width + min_index] == min_energy){
                seam[k] = min_index;
                k--;
            }else if(best[i - width + min_index - 1] == min_energy){
                seam[k] = min_index-1;
                min_index = min_index - 1;
                k--;
            }else if(best[i - width + min_index + 1] == min_energy){
                seam[k] = min_index+1;
                min_index = min_index + 1;
                k--;
            }
        }
    }
    *path = seam;
    // for (int k=0; k<sizeof(best)/sizeof(best[0]);k++){
    //     printf("%i\n", best[k]);
    // }
}

//path = [2, 1, 2, 3, 4, 5, 4]
void remove_seam(struct rgb_img *src, struct rgb_img **dest, int *path){

    int src_height = src->height;
    int src_width = src->width;

    create_img(dest, src_height, src_width - 1);

    int p = 0;
    for(int y = 0; y < src_height; y++){
        for(int x = 0; x < src_width; x++){
            if(path[y] == x){
                p = 1;      
                continue;
            }
            else if (p ==1){    
                int r = get_pixel(src, y, x, 0);   // 0 is red 1 is green 2 is blue
                int g = get_pixel(src, y, x, 1);
                int b = get_pixel(src, y, x, 2);
                set_pixel(*dest, y, x-1, r, g, b);
            }
            else{
                int r = get_pixel(src, y, x, 0);   // 0 is red 1 is green 2 is blue
                int g = get_pixel(src, y, x, 1);
                int b = get_pixel(src, y, x, 2);
                set_pixel(*dest, y, x, r, g, b);
            }
        }
        p = 0;  
    }
} 