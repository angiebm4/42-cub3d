#!/bin/bash

##############################################################################
C_RED='\e[1;31m'
C_GREEN='\e[1;32m'
C_YELLOW='\e[1;33m'
C_CYAN='\e[1;36m'
C_RESET='\e[0m'
##############################################################################
EXECUTABLE="../cub3D"			# Cube3D executable
VALGRIND_ERROR=42
VALGRIND="/usr/bin/valgrind --leak-check=full --error-exitcode=$VALGRIND_ERROR --log-file=/dev/null"	# Valgrind executable
##############################################################################
MAPS_FOLDER="maps"	# Path in which the maps are located
RESULT_EXTENSION="res"	# Results files extension
##############################################################################
TEST_PASS=0	# Counter of passed tests
TEST_FAIL=0	# Counter of failed tests
##############################################################################

EXECUTION_MAP=
EXECUTION_CMD_NORMAL=	
EXECUTION_RESULT_NORMAL=	# 1 Okay, 0 Error

EXECUTION_CMD_VALGRIND=
EXECUTION_RESULT_LEAKS=		# 1 Okay, 0 Error

print_execution()
{
	local res=0

	# Print the line with the final check and the map that is being testing
	if [ "$EXECUTION_RESULT_NORMAL" -eq 1 ] && [ "$EXECUTION_RESULT_LEAKS" -ne "$VALGRIND_ERROR" ]; then
		echo -e "${C_GREEN}[   OK   ]${C_RESET} $EXECUTION_MAP"
	else
		echo -e "${C_RED}[ FAILED ]${C_RESET} $EXECUTION_MAP"
	fi

	# NOTE: Info about the normal execution
	echo -e "\t· Normal execution: $EXECUTION_CMD_NORMAL"
	echo -en "\t· Result: "
	if [ "$EXECUTION_RESULT_NORMAL" -eq 1 ]; then
		echo -e "${C_GREEN}OK${C_RESET}"
	else
		echo -e "${C_RED}FAILED${C_RESET}"
	fi

	# NOTE: Info about the valgrind execution
	echo -e "\t· Valgrind execution: $EXECUTION_CMD_VALGRIND"
	echo -en "\t· Leaks/errors: "
	if [ "$EXECUTION_RESULT_LEAKS" -ne "$VALGRIND_ERROR" ]; then
		echo -e "${C_GREEN}OK${C_RESET}"
	else
		echo -e "${C_RED}FAILED${C_RESET}"
	fi
	echo
}

# $1: map filename
check_execution()
{
	# Set the map that is going to be tested
	EXECUTION_MAP=$1

	# Execute the programm, and save the line code, saving the result
	EXECUTION_CMD_NORMAL="$EXECUTABLE $MAPS_FOLDER/$1 > "$MAPS_FOLDER/$1.$RESULT_EXTENSION""
	$EXECUTABLE $MAPS_FOLDER/$1 > "$MAPS_FOLDER/$1.$RESULT_EXTENSION"
	EXECUTION_RESULT_NORMAL=$?

	# Execute with valgrind to check the leaks
	EXECUTION_CMD_VALGRIND="$VALGRIND $EXECUTABLE $MAPS_FOLDER/$1 > /dev/null"
	$VALGRIND $EXECUTABLE $MAPS_FOLDER/$1 > /dev/null
	EXECUTION_RESULT_LEAKS=$?

	if [[ $1 == "ok"* ]]; then
		check_result $1 0 $EXECUTION_RESULT_NORMAL
	fi

	if [[ $1 == "ko"* ]]; then
		check_result $1 1 $EXECUTION_RESULT_NORMAL
	fi
}

# $1: name of the map
# $2: Expected result
# $3: Result obtained
check_result()
{
	if [[ "$2" -eq "$3" ]]; then
		EXECUTION_RESULT_NORMAL=1
	else
		EXECUTION_RESULT_NORMAL=0
	fi
}
##############################################################################

# Remove the results of the previous executions
clean()
{
	rm -rf "$MAPS_FOLDER"/*".$RESULT_EXTENSION"
}

# $1 (optional):
#	· "clean":	deletes the .$(RESULT_EXTENSION) files
#	· other:	normal compilation
main()
{
	# Deletes the previous results
	clean

	# If the first arguments is "clean", the execution ends
	if [[ "$1" == "clean" ]]; then
		exit 0
	fi

	# If the folder don't exist, exit
	if [ ! -d "$MAPS_FOLDER" ]; then
		echo "The map folder don't exist!"
		exit 1
	fi

	# Check if the executable exists
	if [ ! -f "$EXECUTABLE" ]; then
		echo "Executable don't exists!"
		exit 1
	fi

	if [ ! -f /usr/bin/valgrind ]; then
		echo "Valgrind dont installed!"
	fi

	# List the maps of the folder and iterate on it
	maps=($(ls "$MAPS_FOLDER" | grep -E '^(ok|ko)-'))
	for current_map in "${maps[@]}"; do
		check_execution $current_map
		print_execution
	done

	# echo "Result: $TEST_PASS / $($TEST_PASS + $TEST_FAIL)"
}

# Entry point
main $1
