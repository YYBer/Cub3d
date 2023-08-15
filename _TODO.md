# TODO:

## Mandatory
TODO: ensure initial player position is set to middle of square
TODO: use ft_error whenever there is an exit call and make it call the same code as when window is closed with mouse or ESC
TOFIX: replace strcmp and atoi with ft versions (and check for others!)
TOFIX: sometimes on run the 0's in the map are 8's!! (file read error)
TOFIX: worlds are mirrored!
TODO : map wall checks and tests
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