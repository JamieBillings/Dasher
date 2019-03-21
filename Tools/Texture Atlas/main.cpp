#include <cstdio>
#include <cstdlib>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

/*  Mask
        Single Composistion
        Black = 0
        White = 255
*/

//@@ TO DO make it so I can get a 32bit pixel array so I dont have to do maths when trying to copy pixel data over.

class Image
{
public:
    uint8_t* pixel_data;

    int width;
    int height;
    int componants;

    std::string location;

    void LoadImage(std::string _source);
    void LoadMask(std::string _source);
    void Free();
};

class Box
{
public:

    int x;
    int y;
    int width;
    int height;

    void Create(int _x, int _y, int _width, int _height);
    bool Compare(Box _box);
    bool Compare(int _x, int _y);

    void Copy(Box* _rhs);
};

/*  ARGV
        0 = .exe location           (manditory)
        1 = Unedited image location (manditory)
        2 = Unedited image mask     (manditory)
        2 = Edited image location
        3 = Atlas text file location
*/

int mask_array_count = 0;
Box mask_array[100];
Box pos_array[100];

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

    Image mask_image;
    mask_image.LoadMask(argv[2]);

    Image old_image;
    old_image.LoadImage(argv[1]);

    for(int i = 0; i < mask_array_count; i++){
        printf("Box #%d | x: %d | y: %d | w: %d | h: %d \n", i, mask_array[i].x, mask_array[i].y, mask_array[i].width, mask_array[i].height);
    }
    printf("BOX COUNT: %d\n", mask_array_count);

    //@@add a endian check : Project will only build for Little Endian

    //@@Find where to put all the sprites
        //try the most top left spot, if that doesnt work try to the right then down
    for(int i = 0; i < mask_array_count; i++){
        for(int y = 0; y < old_image.height; y++){
        for(int x = 0; x < old_image.width x++){
            //if
        }
        }
    }



    //@@ Change later so the the new image changes in doubles 2x2 4x4 8x8 16x16 32x32
    Image new_image;
    new_image.width = old_image.width;
    new_image.height = old_image.height;
    //new_image.pixel_data =  //@@Maybe not needed

    uint32_t* old_pixel_data = reinterpret_cast<uint32_t*>(old_image.pixel_data);
    uint8_t* ra_pixel_data = static_cast<uint8_t*>(malloc(old_image.width * old_image.height * 4)); //reinterpret_cast<uint32_t*>(new_image.pixel_data);

    //Testing the pixel data @@remove later
    //for(int i = 0; i < 5*5; i++){new_pixel_data[i] = old_pixel_data[i];}
    if(memset(ra_pixel_data, 255, old_image.width * old_image.height * 4) == nullptr){
        printf("MEMORY ERROR\n");
    } // Alpha = 255 ; rest = 0

    uint32_t* new_pixel_data = reinterpret_cast<uint32_t*>(ra_pixel_data);


    //@@ Moving the masked pixelled to the determined area.
    for(int i = 0; i < mask_array_count; i++){


    }

    uint8_t* return_cast = reinterpret_cast<uint8_t*>(new_pixel_data);

    for(int i = 0; i < 25; i++)
    {
        printf("%x : %x \n",old_pixel_data[i],new_pixel_data[i]);
    }


    printf("FIXED BOXES\n");
    //CRASHES HERE PROBABLY DUE TO BAD MEMORY
    //stbi_write_png("Testings.png", old_image.width, old_image.height, 4, return_cast, old_image.width * 4);
    stbi_write_png("Testings.png", 4, 4, 4, return_cast, 16);


    printf("FIXED DRAWING\n");
    //free(new_pixel_data);
    //old_image.Free();
    //mask_image.Free();


    return 0;
}

void Image::LoadImage(std::string _source)
{
    pixel_data = stbi_load(_source.c_str(), &width, &height, &componants, 4);
    componants = 4;

    stbi_write_png("Testing2.png", width, height, 4, pixel_data, width * componants);

    //printf("| Image Width %d | Image Height %d | BYTE Data Count: %d \n", width, height, width * height * componants);
}

void Image::LoadMask(std::string _source)
{
    pixel_data = stbi_load(_source.c_str(), &width, &height, &componants, 1);
    componants = 1;

    printf("| Image Width %d | Image Height %d |\n", width, height);

    //Find a black pixel
    //scan to the right of the pixel until it hits white
    //scan down from the left most pixel until it hits white
    //save this as the height width y and x of the sprite

    for(int y = 0; y < height; y++){
    for(int x = 0; x < width; x++){
        if(pixel_data[y * width + x] != 255){
            bool matching = false;
            for(int i = 0; i < mask_array_count; i++){
                if(mask_array[i].Compare(x,y)){matching = true;}
            }
            if(matching){continue;}

            int scan_x = 0;
            for(scan_x = x; scan_x < width; scan_x++){
                if(pixel_data[y * width + scan_x] == 255){break;}
            }

            int scan_y = 0;
            for(scan_y = y; scan_y < height; scan_y++){
                if(pixel_data[scan_y * width + x] == 255){break;}
            }

            Box new_box;
            new_box.Create(x, y, scan_x - x, scan_y - y);

            mask_array[mask_array_count] = new_box;
            mask_array_count++;

        }
    }
    }
}

void Image::Free()
{
    stbi_image_free(pixel_data);
}

void Box::Create(int _x, int _y, int _width, int _height)
{
    x = _x;
    y = _y;
    width  = _width;
    height = _height;
}

bool Box::Compare(Box _box)
{
    if(_box.x >= x && _box.x <= x + width){
        if(_box.y >= y && _box.y <= y + height){
            return true;
        }
    }

    return false;
}

bool Box::Compare(int _x, int _y)
{
    if(_x >= x && _x <= x + width){
        if(_y >= y && _y <= y + height){
            return true;
        }
    }

    return false;
}

void Box::Copy(Box* _rhs)
{
    width = _rhs->width;
    height = _rhs->height;
}