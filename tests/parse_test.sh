#!/bin/bash

##############################################################################
C_RED='\e[1;31m'
C_GREEN='\e[1;32m'
C_YELLOW='\e[1;33m'
C_CYAN='\e[1;36m'
C_RESET='\e[0m'
##############################################################################
EXECUTABLE="../cub3D"			# Cube3D executable
VALGRIND_PATH=$(whereis valgrind | awk '{print $2}')
VALGRIND_ERROR=42
VALGRIND="/usr/bin/valgrind --leak-check=full --error-exitcode=$VALGRIND_ERROR --log-file=/dev/null"	# Valgrind executable
##############################################################################
MAPS_FOLDER="maps"	# Path in which the maps are located
RESULT_EXTENSION="res"	# Results files extension
##############################################################################
TEST_PASS=0	# Counter of passed tests
TEST_FAIL=0	# Counter of failed tests
##############################################################################

PASSED_TESTS=0
TOTAL_TESTS=0

EXECUTION_MAP=
EXECUTION_CMD_NORMAL=
EXECUTION_RESULT_NORMAL=
EXECUTION_RESULT_ANALYSIS=

EXECUTION_CMD_VALGRIND=
EXECUTION_RESULT_LEAKS=


##############################################################################
#                              PRINT FUNCTIONS                               #
##############################################################################



# NOTE: Function to print the result of the execution, saved on the above variables
print_execution()
{
	# Print the line with the final check and the map that is being testing
	if [ "$EXECUTION_RESULT_ANALYSIS" -eq 1 ] && [ "$EXECUTION_RESULT_LEAKS" -ne "$VALGRIND_ERROR" ]; then
		echo -ne "${C_GREEN}[   OK   ]${C_RESET}"
	else
		echo -ne "${C_RED}[ FAILED ]${C_RESET}"
	fi
	echo -e " ${C_YELLOW}$EXECUTION_MAP${C_RESET}"

	# Info about the normal execution
	echo -e "\t· Normal execution: $EXECUTION_CMD_NORMAL"
	echo -en "\t· Result: "
	if [ "$EXECUTION_RESULT_ANALYSIS" -eq 1 ]; then
		echo -ne "${C_GREEN}OK${C_RESET}"
	else
		echo -ne "${C_RED}FAILED${C_RESET}"
	fi
	echo -e "\t\t(${C_CYAN}${EXECUTION_RESULT_NORMAL}${C_RESET})"

	# Info about the valgrind execution
	echo -e "\t· Valgrind execution: $EXECUTION_CMD_VALGRIND"
	echo -en "\t· Leaks/errors: "
	if [ "$EXECUTION_RESULT_LEAKS" -ne "$VALGRIND_ERROR" ]; then
		echo -ne "${C_GREEN}OK${C_RESET}"
	else
		echo -ne "${C_RED}FAILED${C_RESET}"
	fi
	echo -e "\t(${C_CYAN}${EXECUTION_RESULT_LEAKS}${C_RESET})"

	echo -e "\n"
}

# NOTE: Function that print an error, passed on $1
print_error()
{
	echo -e "${C_RED}[ ERROR ]${C_RESET} $1"
}

##############################################################################
#                             EXECUTION FUNTIONS                             #
##############################################################################

# NOTE: Function to execute the program with a map, passed on the first argument ($1)
check_execution()
{
	local filename=${1##*/}

	# Set the map that is going to be tested
	EXECUTION_MAP=$1

	# Execute the programm, and save the line code, saving the result
	EXECUTION_CMD_NORMAL="$EXECUTABLE $1 > "$1.$RESULT_EXTENSION""
	$EXECUTABLE $1 > "$1.$RESULT_EXTENSION"
	EXECUTION_RESULT_NORMAL=$?

	# Execute with valgrind to check the leaks
	EXECUTION_CMD_VALGRIND="$VALGRIND $EXECUTABLE $1 > /dev/null"
	$VALGRIND $EXECUTABLE $1 > /dev/null
	EXECUTION_RESULT_LEAKS=$?

	if [[ "$filename" == "ok"* ]]; then
		check_result $1 0 $EXECUTION_RESULT_NORMAL
	fi

	if [[ "$filename" == "ko"* ]]; then
		check_result $1 1 $EXECUTION_RESULT_NORMAL
	fi
}

# NOTE: Function to check if the execution was successfull or not.
#	    Params:
#			$1: name of the map
#			$2: Expected result
#			$3: Result obtained
check_result()
{
	# Increment the number of tests done
	((TOTAL_TESTS++))

	if [[ "$2" -eq "$3" ]]; then
		EXECUTION_RESULT_ANALYSIS=1
		((PASSED_TESTS++))
	else
		EXECUTION_RESULT_ANALYSIS=0
	fi
}

# NOTE: Remove the results of the previous executions
clean()
{
	rm -rf "$MAPS_FOLDER"/*".$RESULT_EXTENSION"
}

##############################################################################
#                               MAIN FUNCTIONS                               #
##############################################################################

# NOTE: Function to execute just one map
execute_one_map()
{
	local filename=${1##*/}

	if [[ "$filename" != "ok"* ]] && [[ "$filename" != "ko"* ]]; then
		echo -e "The file ${C_YELLOW}must${C_RESET} start with 'ok' or 'ko':"
		echo -e "\t· If the file starts with ${C_GREEN}'ok'${C_RESET}, the execution should be correct"
		echo -e "\t· If the file starts with ${C_RED}'ko'${C_RESET}, the execution should be wrong"
		exit 1
	fi

	if [ ! -f $1 ]; then
		print_error "The file don't exist!"
		exit 1
	fi

	check_execution $1
	print_execution
}

# NOTE: Function to execute all the files saved on the folder $MAPS_FOLDER
execute_all_maps()
{
	# List the maps of the folder and iterate on it
	maps=($(ls "$MAPS_FOLDER" | grep -E '^(ok|ko)-'))
	for current_map in "${maps[@]}"; do
		check_execution "$MAPS_FOLDER/$current_map"
		print_execution
	done
}

# $1 (optional):
#	· "clean":	deletes the .$(RESULT_EXTENSION) files
#	· other:	normal compilation
# NOTE: Main function.Check s that the  env is okay and execute the program, depending of the script arguments:
#		Params:
#			$1 (optional): If there is no  one of the follow key words, the param is the path of a file, so the script will be checker; otherwise:
#				· 'clean': the result files of the execution are deleted
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
		print_error "The map folder don't exist!"
		exit 1
	fi

	# Check if the executable exists
	if [ ! -f "$EXECUTABLE" ]; then
		print_error "Executable don't exists!"
		exit 1
	fi

	if [ ! -f "$VALGRIND_PATH" ]; then
		print_error "Valgrind dont installed!"
	fi

	if [ $# -eq 1 ] && [[ $1 != "clean" ]];then
		execute_one_map $1	
	else
		execute_all_maps
	fi

	# Print the final result
	local msg="Result: $PASSED_TESTS / $TOTAL_TESTS"
	local length=${#msg}
	local border=$(printf '%*s' $((length + 4)) | tr ' ' '#')

	echo -e "\t\t\t\t\t${C_CYAN}$border${C_RESET}"
	echo -e "\t\t\t\t\t${C_CYAN}# ${C_YELLOW}$msg ${C_CYAN}#${C_RESET}"
	echo -e "\t\t\t\t\t${C_CYAN}$border${C_RESET}"

	exit 0
}

# Entry point
main $1
