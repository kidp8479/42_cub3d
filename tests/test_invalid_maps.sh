#!/bin/bash

TEST_BIN="./cub3D"
MAP_DIR="../maps/invalid"

echo "=== Running tests for invalid maps .cub maps ==="
for map in "$MAP_DIR"/*; do
	echo
	echo -e "\033[36m=== Testing: $map ===\033[0m"

	$TEST_BIN "$map"
	STATUS=$?

	if [ $STATUS -eq 0 ]; then
		echo -e "\033[32m[OK]\033[0m Test passed for $map"
	else
		echo -e "\033[31m[FAIL]\033[0m Test failed for $map"
	fi
done

echo
echo "=== ALL MAP TESTS FINISHED ==="
