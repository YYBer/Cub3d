#!/bin/bash

# Name of the log file
log_file="_file_tests.log"

# List of input files
input_files=(
    "maps/everything_valid.cub" #TESTED
    "maps/map_complex_leading_spaces_1.cub" #TESTED
    "maps/map_complex_leading_spaces_2.cub" #TESTED
    "maps/map_complex_leading_spaces_differing_line_lengths.cub" #TESTED
    "maps/map_complex_subject.cub" #TESTED
    "maps/map_none.cub" #TESTED
    "maps/map_simple_all_walls.cub" #TESTED
    "maps/map_simple_extra_position.cub" #TESTED
    "maps/map_simple_illegal_char.cub" #TESTED
    "maps/map_simple_large.cub" #TESTED
    "maps/map_simple_no_position.cub" #TESTED
    "maps/map_simple_rect_wide.cub" #TESTED
    "maps/map_simple_smallest_valid.cub" #TESTED
    "maps/map_single_0.cub" #TESTED
    "maps/map_single_1.cub" #TESTED
    "maps/map_single_illegal_char.cub" #TESTED
    "maps/map_wall_jean.cub" #TESTED
    "maps/map_wall_slack_1_valid.cub" #TESTED
    "maps/map_wall_slack_2_valid.cub" #TESTED
    "maps/map_wall_slack_3_invalid.cub" #TESTED
    "maps/preamble_color_double_comma.cub" #TESTED
    "maps/preamble_color_extra_comma.cub" #TESTED
    "maps/preamble_color_invalid_value_1.cub" #TESTED
    "maps/preamble_color_invalid_value_2.cub" #TESTED
    "maps/preamble_color_invalid_value_3.cub" #TESTED
    "maps/preamble_color_omitted_comma.cub" #TESTED
    "maps/preamble_color_omitted_prefix.cub" #TESTED
    "maps/preamble_color_omitted_values.cub" #TESTED
    "maps/preamble_color_repeated_prefix.cub" #TESTED
    "maps/preamble_newlines_at_end_invalid.cub" #TESTED
    "maps/preamble_newlines_none.cub" #TESTED
    "maps/preamble_newlines_random.cub" #TESTED
    "maps/preamble_random_order.cub" #TESTED
    "maps/preamble_spaces_none.cub" #TESTED
    "maps/preamble_spaces_random.cub" #TESTED
    "maps/preamble_texture_double_repeated_prefix.cub" #TESTED
    "maps/preamble_texture_invalid.cub" #TESTED
    "maps/preamble_texture_omitted_path.cub" #TESTED
    "maps/preamble_texture_omitted_prefix.cub" #TESTED 
    "maps/preamble_texture_repeated_prefix.cub" #TESTED
)

# Clear the log file if it exists
> "$log_file"

# Loop through each input file and run ./cub3d, logging the result
for file in "${input_files[@]}"; do
    echo "Running $file" >> "$log_file"
    ./cub3d "$file" 2>&1 | sed 's/^/  /' >> "$log_file"
    echo "--------------------------------------------------" >> "$log_file"
done