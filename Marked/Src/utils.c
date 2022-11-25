
#include <math.h>
#include "cprocessing.h"

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{	
	float x_left_coords = area_center_x - area_width / 2.0f;
	float x_right_coords = area_center_x + area_width / 2.0f;
	float y_top_coords = area_center_y - area_height / 2.0f;
	float y_bottom_coords = area_center_y + area_height / 2.0f;

	CP_BOOL within_x_range = 0;
	CP_BOOL within_y_range = 0;

	// if x coordinates of mouse within range of area
	if ( click_x > x_left_coords  &&  click_x < x_right_coords) {
		within_x_range = 1;
	} //else within_x_range is false

	// if y coordinates of mouse within range of area
	if (click_y > y_top_coords && click_y < y_bottom_coords) {
		within_y_range = 1;
		
	} //else within_y_range is false

	//when mouse cursor within rectangle, and mouse is clicked
	if (within_x_range && within_y_range && CP_Input_MouseClicked()){
		printf("area clicked\n"); //debug purposes
		return 1;
	}

	return 0;
}
