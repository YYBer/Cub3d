# TODO:

## Interim

DONE: read map from file and include in main struct
TODO: sometimes on run the 0's in the map are 8's!!
TODO: are x and y coords read the right way round in read.c?
TODO: norminette what's there
TODO: leak check (currently it seems MLX42 itself leaks)

## Mandatory

DONE: make map dynamic size and not global
DONE: load map from file
TODO: map error checking
TODO: add floor and ceiling colours
TODO: take floor and ceiling colour from file (RGB)
TODO: create an array to store multiple textures. We need to store 4: NO, SO, WE & EA
TODO: load textures from file
TODO: take texture names from file

## Bonus

TODO: minimap
TODO: opening/closing doors
TODO: animated sprite
TODO: point of view rotation with mouse

# NOTES:

## textured raycaster principles

loop in the yTODO: direction is required to go through every pixel to determinate which texel (texture pixel) of the texture should be used for it.
use a 2D array as screen buffer this time, and copy it to the screen at once
need extra array for textures
we already have a screen buffer in the form of mlxTODO: >img
the resize function resizes the array to the give size i.e. 64 x 64 (why don't we just generate the required size for now)
they generate some textures, which we can also do but need RGB color values