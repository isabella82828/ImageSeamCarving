#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "seamcarving.h"
#include "seamcarving.c" // either include this and get seg fault or comment out and get undefined architecture symbols
#include "c_img.h"
#include "c_img.c"

int main(void){
    struct rgb_img *im;
    struct rgb_img *cur_im;
    struct rgb_img *grad;
    double *best;
    int *path;

    //printf("test1\n");

    read_in_img(&im, "HJoceanSmall.bin");
    //printf("test2\n");
    for(int i = 0; i < 400; i++){
        printf("i = %d\n", i);
        calc_energy(im,  &grad);
        //print_grad(grad);
        //printf("width: %i\n", grad->width);
        //printf("height: %i\n", grad->height);
        dynamic_seam(grad, &best);
        //printf("test3\n");
        recover_path(best, grad->height, grad->width, &path);
        //printf("test4\n");
        remove_seam(im, &cur_im, path);
        //printf("test5\n");
        char filename[200];
        sprintf(filename, "oceanTEST%d.bin", i);
        write_img(cur_im, filename);


        destroy_image(im);
        destroy_image(grad);
        free(best);
        free(path);
        im = cur_im;
    }
    destroy_image(im);
    return 0;
}