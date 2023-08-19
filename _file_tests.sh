#!/bin/bash

# Name of the log file
log_file="_file_tests.log"

# List of input files
input_files=(
    "maps/everything_valid.cub"
    "maps/map_complex_leading_spaces_1.cub"
    "maps/map_complex_leading_spaces_2.cub"
    "maps/map_complex_leading_spaces_differing_line_lengths.cub"
    "maps/map_complex_subject.cub"
    "maps/map_none.cub"
    "maps/map_simple_all_walls.cub"
    "maps/map_simple_extra_position.cub"
    "maps/map_simple_illegal_char.cub"
    "maps/map_simple_large.cub"
    "maps/map_simple_minimap_test.cub"
    "maps/map_simple_no_position.cub"
    "maps/map_simple_rect_wide.cub"
    "maps/map_simple_smallest_valid.cub"
    "maps/map_single_0.cub"
    "maps/map_single_1.cub"
    "maps/map_single_illegal_char.cub"
    "maps/map_wall_jean.cub"
    "maps/map_wall_slack_1_valid.cub"
    "maps/map_wall_slack_2_valid.cub"
    "maps/map_wall_slack_3_invalid.cub"
    "maps/preamble_color_double_comma.cub"
    "maps/preamble_color_extra_comma.cub"
    "maps/preamble_color_invalid_value_1.cub"
    "maps/preamble_color_invalid_value_2.cub"
    "maps/preamble_color_invalid_value_3.cub"
    "maps/preamble_color_omitted_comma.cub"
    "maps/preamble_color_omitted_prefix.cub"
    "maps/preamble_color_omitted_values.cub"
    "maps/preamble_color_repeated_prefix.cub"
    "maps/preamble_newlines_at_end_invalid.cub"
    "maps/preamble_newlines_none.cub"
    "maps/preamble_newlines_random.cub"
    "maps/preamble_random_order.cub"
    "maps/preamble_spaces_none.cub"
    "maps/preamble_spaces_random.cub"
    "maps/preamble_texture_double_repeated_prefix.cub"
    "maps/preamble_texture_invalid.cub"
    "maps/preamble_texture_omitted_path.cub"
    "maps/preamble_texture_omitted_prefix.cub" 
    "maps/preamble_texture_repeated_prefix.cub"
)

# Clear the log file if it exists
> "$log_file"

# Loop through each input file and run ./cub3d, logging the result
for file in "${input_files[@]}"; do
    echo "Running $file" >> "$log_file"
    # remove "test" to test graphically with maps
    ./cub3d "$file" 2>&1 | sed 's/^/  /' >> "$log_file"
    # ./cub3d "$file" "test" 2>&1 | sed 's/^/  /' >> "$log_file"
    echo "--------------------------------------------------" >> "$log_file"
done