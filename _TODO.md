# TODO:

## Mandatory
TOFIX: sometimes on run the 0's in the map are 8's!!
TOFIX: worlds are mirrored!
TODO : handle that first lines in map file can come in any order and can have any number of newlines between them [GRAHAM]
TODO : map error checking (make sure has surrounding wall, player position is there, can handle different line lengths and spaces within the map) [YUANYING]
TODO : detect whether we see N E S W of a wall and provide the right texture (current we only detect NS and EW using 'side' variable)
TODO : use player position (N E S W) on map to set 'dir.x' and 'dir.y' in main.c 'init_m' function
TODO : tidy up and refactor code into 5 functions per file, then norminette
TODO : leak checks, free correct resources for every 'exit' command (currently it seems MLX42 itself leaks)

## Bonus

TODO : minimap
TODO : opening/closing doors
TODO : animated sprite
TODO : point of view rotation with mouse

# NOTES:

## textured raycaster principles

loop in the yTODO: direction is required to go through every pixel to determinate which texel (texture pixel) of the texture should be used for it.
use a 2D array as screen buffer this time, and copy it to the screen at once
need extra array for textures
we already have a screen buffer in the form of mlxTODO: >img
the resize function resizes the array to the give size i.e. 64 x 64 (why don't we just generate the required size for now)
they generate some textures, which we can also do but need RGB color values