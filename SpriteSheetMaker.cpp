#include <allegro5\allegro.h>	
#include <allegro5\allegro_image.h>

//GLOBALS========================
enum KEYS{UP,DOWN,LEFT,RIGHT,SPACE};
bool keys[5] = {false,false,false,false,false};

int main(void)
{
	const int width = 1280;
	const int height = 720;
	
	int imageWidth = 0;
	int imageHeight = 0;
	
	const int arraySize = 2;
	
	
	//Allegro vars========
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_BITMAP *images[arraySize];
	ALLEGRO_BITMAP *outImage;
	
	//Initializers============================
	if(!al_init())
		return -1;
	
	display = al_create_display(width,height);
	
	al_init_image_addon();
	
	images[0] = al_load_bitmap("Audio and Images/Bat.bmp");
	
	imageWidth = al_get_bitmap_width(images[0]);
	imageHeight = al_get_bitmap_height(images[0]);
	
	outImage = al_create_bitmap(imageWidth*arraySize,imageHeight);
	
	al_set_target_bitmap(outImage);
	al_clear_to_color(al_map_rgb(0,0,0));
	
	for(int i=0;i<arraySize;i++)
	{
		al_draw_bitmap(images[0], i*imageWidth, 0, 0);
	}
	
	al_save_bitmap("Bat1.bmp", outImage);
	
	al_set_target_bitmap(al_get_backbuffer(display));
	
	al_destroy_bitmap(images[0]);
	al_destroy_display(display);
	
	return 0;
}