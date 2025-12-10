#!/bin/bash

TEST_BIN="bin/test_validate_map_integ"
MAP_DIR="../maps/test_maps"

echo "=== Running integration tests for all .cub maps ==="

for map in "$MAP_DIR"/*.cub; do
	echo
	echo -e "\033[36m=== Testing: $map ===\033[0m"

	$TEST_BIN "$map"
	STATUS=$?

	if [ $STATUS -eq 0 ]; then
		echo "[OK] Test passed for $map"
	else
		echo "[FAIL] Test failed for $map (exit code $STATUS)"
	fi
done

echo
echo "=== ALL MAP TESTS FINISHED ==="
