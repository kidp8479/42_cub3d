#!/bin/bash

TEST_BIN="bin/test_parse_header_integ"
MAP_DIR="../maps/test_cub_files/"
#MAP_DIR="../maps"

echo "=== Running integration tests for all .cub maps ==="
#find "$MAP_DIR" -type f -name "*.cub" | while read -r map; do
for map in "$MAP_DIR"/*.cub; do
	echo
	echo -e "\033[36m=== Testing: $map ===\033[0m"

	$TEST_BIN "$map"
	STATUS=$?

	if [ $STATUS -eq 0 ]; then
		echo -e "\033[32m[OK]\033[0m Test passed for $map"
	else
		echo -e "\033[31m[FAIL]\033[0m Test failed for $map (exit code $STATUS)"
	fi
done

echo
echo "=== ALL MAP TESTS FINISHED ==="
