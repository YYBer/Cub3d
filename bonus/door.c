#include "cub3d_bonus.h"

int ft_door(t_main *m)
{
    int animationFrames = 60;  // Total frames for the animation
    int animationSpeed = 100;  // Delay between frames in milliseconds
    int closedY = 300;  // Y-coordinate of the closed door
    int openY = 100;    // Y-coordinate of the open door
    int currentFrame;

    while (1) {
        mlx42_clear();  // Clear the screen
        
        // Calculate the interpolated position of the door
        int currentY = closedY + ((openY - closedY) * currentFrame / animationFrames);
        
        // Render the door at the current position
        mlx42_draw_image(doorImage, x, currentY);
        
        mlx42_refresh();  // Refresh the display
        
        // Delay to control animation speed
        mlx42_delay(animationSpeed);
        
        // Increment frame counter
        currentFrame++;
        
        // Exit the loop when the animation is complete
        if (currentFrame >= animationFrames) {
            break;
        }
    }
    
    mlx42_cleanup();  // Clean up and exit
    return 0;
}
