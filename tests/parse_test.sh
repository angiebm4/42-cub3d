#!/bin/bash

##############################################################################
C_RED='\e[1;31m'
C_GREEN='\e[1;32m'
C_YELLOW='\e[1;33m'
C_CYAN='\e[1;36m'
C_RESET='\e[49m'
##############################################################################
EXECUTABLE="../cub3D"	# Cube3D Executable
MAPS_FOLDER="maps"		# Path in which the maps are located
RESULT_EXTENSION="res"
DEBUG_MODE=0
##############################################################################

# $1: map filename
check_execution()
{
	if [[ "$DEBUG_MODE" -eq 1 ]]; then
		echo -ne "${C_CYAN}""[ DEBUG ] Ejecutando:"
		echo -e "${C_YELLOW}""$EXECUTABLE $MAPS_FOLDER"/"$1" ">" "$MAPS_FOLDER/$1.$RESULT_EXTENSION""${C_RESET}"
	fi

	$EXECUTABLE $MAPS_FOLDER/$1 > "$MAPS_FOLDER/$1.$RESULT_EXTENSION"
	if [[ $1 == "ok"* ]]; then
		echo -e "OK FILE: [$?]"
		check_result $1 0 $? 
	fi

	if [[ $1 == "ko"* ]]; then
		echo -e "KO FILE: [$?]"
		check_result $1 1 $? 
	fi
}

# $1: name of the map
# $2: Expected result
# $3: Result obtained
check_result()
{
	if [[ "$DEBUG_MODE" -eq 1 ]]; then
		echo -ne "\\t"
	fi

	if [[ "$2" -eq "$3" ]]; then
		echo -ne "${C_GREEN}"[   OK   ] "${C_RESET}"		
	else
		echo -ne "${C_RED}"[ FAILED ] "${C_RESET}"
	fi
	echo -e "${C_RESET}Checking $1..."
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

	if [[ "$1" == "debug" ]]; then
		DEBUG_MODE=1
	fi

	# If the folder don't exist, exit
	if [ ! -d "$MAPS_FOLDER" ]; then
		echo "The map folder don't exist!"
		exit 1
	fi

	# Check if the executable exists
	if [ ! -f "$EXECUTABLE" ]; then
		echo "Executable don't exists"
		exit 1
	fi

	# List the maps of the folder and iterate on it
	maps=($(ls "$MAPS_FOLDER" | grep -E '^(ok|ko)-'))
	for current_map in "${maps[@]}"; do
		check_execution $current_map
	done
}

# Entry point
main $1