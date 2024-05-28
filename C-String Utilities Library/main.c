//  main.c
//  C-String Utilities Library
/**
 * In the main function below are two examples that demonstrate some potential
 * uses of the 'AuxiliaryUtilities' and 'StringUtilities' libraries.
 *
 * 		Example 1: 'extern const char *weekDays[7]' String Literal Manipulation
 * 		Example 2: Date/Time Operations, String Manipulation, and String Array Preprocessing
 */


#include <stdio.h>
#include "AuxiliaryUtilities.h"
#include "StringUtilities.h"






int main(int argc, const char * argv[])
{
// ------------- Example 1, weekDays String Literal Manipulation -------------
/// \{
	/// Using the 'ARRAY_SIZE' macro to determine the number of strings in an array of string literals
	int numStrings = ARRAY_SIZE(weekDays);
	printf("Number of Strings: %d", numStrings);
	print_char_ptr_array(weekDays, 7, "String Literal Array of Week Days");
	
	
	
	
	/// Concatenate the array of string literals of week days into a single string
	char *concatenatedWeekDaysString = append_string_array_to_string("", weekDays, numStrings, ",");
	print_string(concatenatedWeekDaysString);
	
	
	
	
	/// Find delimiter in the concatenated string
	int *delimiterCount = allocate_memory_int_ptr(1);
	char *delimiter = find_potential_delimiters(concatenatedWeekDaysString, delimiterCount); // the 'find_potential_delimiters' function is just one part of the verification process from the much more rigorous 'identify_delimiter' function, which is only compatible with arrays of tokenized strings
	printf("\n\nPotential Delimiters: %s\n", delimiter);
	printf("Delimiter Count: %d\n\n\n\n", *delimiterCount);
	
	
	
	
	/// Split the concatenated string into an array of strings
	char **segmentedWeekDaysStringArray = split_tokenized_string(concatenatedWeekDaysString, delimiter, numStrings);
	size_t stringCount = count_array_strings(segmentedWeekDaysStringArray);
	print_string_array(segmentedWeekDaysStringArray, stringCount, "Segmented String Array of Tokenized Week Days");
/// \}
	
	
	
	
	
	
	
	printf("\n\n\n\n\n\n\n\n==========================================\n\n\n\n");
	
	
	
	
	
	
	
// ------------- Example 2, Date/Time Operations, String Manipulation, and String Array Preprocessing -------------
/// \{
	/// Define some date-time strings, initialize an array of string literals with them, and use 'ARRAY_SIZE' macro to determine the number of strings
	char *dateTimeString1 = "05/24/2015 10:00:00 PM";
	char *dateTimeString2 = "05/26/2015 08:00:00 PM";
	char *dateTimeString3 = "05/22/2015 03:00:00 PM";
	const char *dateTimeStrings[3] = {dateTimeString1, dateTimeString2, dateTimeString3};
	
	int numDateTimeStrings = ARRAY_SIZE(dateTimeStrings);
	
	
	
	
	/// Concatenate the array of date-time strings into a single string
	char *concatenatedDateTimeStrings = append_string_array_to_string("", dateTimeStrings, numDateTimeStrings, ",");
	print_string(concatenatedDateTimeStrings);
	
	
	
	
	/// Split the concatenated string into an array of strings, make a new count based on the array
	char **segmentedDateTimeStringArray = split_tokenized_string(concatenatedDateTimeStrings, delimiter, numDateTimeStrings);
	size_t dateTimeCount = count_array_strings(segmentedDateTimeStringArray);
	print_string_array(segmentedDateTimeStringArray, dateTimeCount, "Segmented String Array of Tokenized DateTimes");
	

	
	
	/// Preprocess the array of strings to replace date-time strings with Unix timestamps
	bool dateTimeCheck = string_array_contains_date_time(segmentedDateTimeStringArray, numDateTimeStrings, delimiter);
	if(dateTimeCheck)
	{
		char **preprocessedDateTimeStringArray = preprocess_string_array(segmentedDateTimeStringArray, numDateTimeStrings, delimiter);
		print_string_array(preprocessedDateTimeStringArray, numDateTimeStrings, "Preprocessed Segmented String Array of Tokenized DateTimes with Unix Timestamps");
	}
	else
	{
		printf("The array of strings does not contain date-time strings.\n");
	}
/// \}
}




