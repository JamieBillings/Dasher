#include <cstdio>
#include <cstdlib>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

/*  Mask
        Single Composistion
        Black = 0
        White = 255
*/

class Image
{
public:
    unsigned char* pixel_data;

    int width;
    int height;
    int componants;

    std::string location;

    void LoadImage(std::string _source);
    void LoadMask(std::string _source);
};

class Box
{
    int x;
    int y;
    int width;
    int height;
};

/*  ARGV
        0 = .exe location           (manditory)
        1 = Unedited image location (manditory)
        2 = Unedited image mask     (manditory)
        2 = Edited image location
        3 = Atlas text file location
*/

int main(int argc, char** argv)
{
    switch(argc){
        case 1:
            printf("Please enter the source image to Atlas\n");
            return -1;
        case 2:
            printf("Please enter the source mask\n");
            return -1; 
    }

    Image new_image;
    new_image.LoadImage(argv[1]);

    Image mask_image;
    mask_image.LoadMask(argv[2]);


    return 0;
}

void Image::LoadImage(std::string _source)
{
    pixel_data = stbi_load(_source.c_str(), &width, &height, &componants, 0);

    printf("| Image Width %d | Image Height %d |\n", width, height);

    stbi_image_free(pixel_data);
}

void Image::LoadMask(std::string _source)
{
    pixel_data = stbi_load(_source.c_str(), &width, &height, &componants, 1);

    printf("| Image Width %d | Image Height %d |\n", width, height);

    //Find a black pixel
    //scan to the right of the pixel until it hits white
    //scan down from the left most pixel until it hits white
    //save this as the height width y and x of the sprite

    for(int y = 0; y < height; y++){
    for(int x = 0; x < width; x++){
        if(pixel_data[y * width + x] < 255){
            //Scan for the bounds of the mask
            for(int i = 0; i < width - x; i++){
                if(pixel_data[y * width ]) //stuff about the width - x here
            }
        }
    }
    }
    
    printf("COMPO %d \n", componants);

    stbi_image_free(pixel_data);
}