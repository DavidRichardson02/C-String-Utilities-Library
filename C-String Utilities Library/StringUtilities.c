//  StringUtilities.h
//  C-String Utilities Library
//  DavidRichardson02


#include "StringUtilities.h"






/**
 * char_is_alpha
 * Checks if a given character is an alphabetic character.
 *
 * @param c The character to be checked.
 * @return Returns true if 'c' is an alphabetic character (either lowercase or uppercase), false otherwise.
 */
bool char_is_alpha(char c)
{
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}


/**
 * char_is_digit
 * Checks if a given character is a digit.
 *
 * @param c The character to be checked.
 * @return Returns true if 'c' is a digit ('0' to '9'), false otherwise.
 */
bool char_is_digit(char c)
{
	return (c >= '0' && c <= '9');
}


/**
 * char_is_alnum
 * Checks if a given character is alphanumeric.
 * This function checks if the character is either a letter (alphabetic) or a digit (numeric).
 *
 * @param c The character to be checked.
 * @return Returns true if 'c' is an alphanumeric character, false otherwise.
 */
bool char_is_alnum(char c)
{
	return char_is_alpha(c) || char_is_digit(c);
}


/**
 * char_is_whitespace
 * Checks if a given character is a whitespace character.
 *
 * @param c The character to be checked.
 * @return Returns true if 'c' is a whitespace character (space, tab, newline, vertical tab, form feed, carriage return), false otherwise.
 */
bool char_is_whitespace(char c)
{return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');}


/**
 * char_is_punctuation
 * Checks if a given character is punctuation.
 *
 * @param c The character to be checked.
 * @return Returns true if 'c' is a: hyphen, period, comma, colon, semicolon, underscore, false otherwise.
 */
bool char_is_punctuation(char c)
{return (c == '-' || c == '.' || c == ',' || c == ':' || c == ';' || c == '!' || c == '?');}


/**
 * char_is_underscore
 * Checks if a given character is an underscore.
 * This function primarily serves to isolate the underscore
 * character from the other punctuation characters as well as the
 * whitespace characters, the reason for singling out the underscore
 * character is it's prevalent use in CSV datasets, variable names, and identifiers.
 *
 * @param c The character to be checked.
 * @return Returns true if 'c' is an underscore ('_'), false otherwise.
 */
bool char_is_underscore(char c)
{return c == '_';}


/**
 * char_is_sign
 * Checks if a given character is a sign.
 *
 * @param c The character to be checked.
 * @return Returns true if 'c' is a plus sign, minus sign, greater than sign, less than sign, or equal to sign, false otherwise.
 */
bool char_is_sign(char c)
{return (c == '-' || c == '+' || c == '>' || c == '<' || c == '=');}


/**
 * char_is_delimiter
 * Checks if a given character is a delimiter.
 * A delimiter in this context is defined as a character that is neither alphanumeric nor a whitespace.
 *
 * @param c The character to be checked.
 * @return Returns true if 'c' is a delimiter, false otherwise.
 */
bool char_is_delimiter(char c)
{
	return !char_is_alnum((unsigned char)c) && !char_is_whitespace((unsigned char)c) && !char_is_underscore(c) && !char_is_sign(c);
}




/**
 * string_is_numeric
 *
 * Determines if a string represents a valid double value.
 * Used to handle cases where the use of some character is in question during string parsing for
 * determining whether the character is being used as a numeric sign, punctuation, or is some unknown
 * use like a place holder for blank values in a data set like a space or hyphen.
 *
 * @param characterString Pointer to the string to be interpreted.
 * @return Returns true if the string can be converted to a numeric value, false otherwise.
 */
bool string_is_numeric(const char *characterString)
{
	// Check for NULL input and handle error.
	if (characterString == NULL){ perror("\n\nError: characterString was NULL in 'string_is_numeric'.\n");      return NULL; }
	
	char* end;
	strtod(characterString, &end);  // Parses the string as a floating-point number
	if (end != characterString && *end == '\0')
	{
		return true; // numeric
	}
	else
	{
		return false; // nonnumeric
	}
}




/**
 * string_is_hyphen_else_is_minus_sign
 * Determines if a "-" character is being used as a hyphen, or as a minus sign, only
 *
 * @param characterString Pointer to the string to be interpreted.
 * @return Returns true if the string can be converted to a double, false otherwise.
 */
bool string_is_hyphen_else_is_minus_sign(char *characterString)
{
	// Check for NULL input and handle error.
	if (characterString == NULL){ perror("\n\nError: characterString was NULL in 'string_is_hyphen_else_is_minus_sign'.\n");      return NULL; }
	
	
	char* end;
	strtod(characterString, &end);
	return end != characterString && *end == '\0';
}






/**
 * string_is_date_time
 *
 * This function analyzes each field in a delimited string and determines if any part of the string
 * matches one of the common date/time formats specified in commonDateTimeFormats.
 *
 * Works by first tokenizing the input string based on the provided delimiter. It then iterates
 * over each token (field) and attempts to parse it using each of the common date/time formats. If a field is
 * successfully parsed and the entire field is consumed, it is considered a match and the corresponding index
 * in the results array is set to 1, and if no format matches, the index is set to 0. The results array is then
 * returned with it's elements each set to 1(true) if the field matches a date/time format, 0 (false) otherwise.
 *
 * @note This function is designed to work with the common date/time formats specified in 'extern const char *commonDateTimeFormats[12]' in GeneralUtilities.
 *
 * @param characterString Pointer to the string to be interpreted.
 * @param delimiter The delimiter character used to delimit fields/tokens in string.
 * @param fieldCount The number of fields in the string.
 * @return An integer array where each element corresponds to a field in the input string and indicates whether that field matches a date/time format.
 */
int* string_is_date_time(const char *characterString, const char *delimiter, const int fieldCount)
{
	// Check for NULL input and handle error.
	if (characterString == NULL){ perror("\n\nError: characterString was NULL in 'string_is_date_time'.\n");      return NULL; }
	
	
	// Allocate memory to store results. Each element represents a field with a value indicating whether it matches a date/time format.
	int *results = (int *)malloc(fieldCount * sizeof(int));
	char *copyOfString = duplicate_string(characterString);     // Create a duplicate of the input string because 'duplicate_string' modifies the string it processes.
	
	// Tokenize the duplicated string using the provided delimiter.
	char *token = tokenize_string(copyOfString, delimiter);
	int index = 0; // Index for tracking current field.
	
	
	// Iterate over each token(field) in the string.
	while (token != NULL)
	{
		struct tm tm; // Holds the parsed date/time values.
		bool foundDateTime = false; // Flag to indicate if a date/time format is found.
		
		
		// Iterate over the common date/time formats.
		for (int i = 0; i < 12; i++)
		{
			// Reset the tm struct for each format.
			set_memory_block(&tm, 0, sizeof(struct tm));
			
			// Parse the current field(token) using the current format.
			char *parsed = strptime(token, commonDateTimeFormats[i], &tm);
			
			
			
			// Check if parsing is successful and the entire field(token) is consumed.
			if (parsed != NULL && *parsed == '\0')
			{
				results[index] = 1;  // Field matches a date/time format from 'commonDateTimeFormats', set the corresponding index in results to 1.
				foundDateTime = true;
				break;
			}
		}
		
		
		if (foundDateTime == false) // If no date/time format matched, set the corresponding index in results to 0.
		{
			results[index] = 0; // Field does not match a date/time format from 'commonDateTimeFormats'
		}
		
		// Increment the index and move to the next field(token) in the string.
		index++;
		token = tokenize_string(NULL, delimiter);
	}
	// Cleanup
	free(copyOfString);
	
	
	return results; // Return the results array.
}







/**
 * string_array_contains_date_time
 *
 * Checks if any string in an array contains a date/time format specified in the commonDateTimeFormats array.
 *
 * @param stringArray The array of strings to be checked.
 * @param stringCount The size of the array.
 * @param delimiter The delimiter character used to separate fields in the strings.
 * @return true if at least one string contains a date/time format, false otherwise.
 */
bool string_array_contains_date_time(char **stringArray, int stringCount, const char *delimiter)
{
	for (size_t i = 0; i < stringCount; i++)
	{
		// Split the string into fields and count them
		int fieldCount = 1;
		for (char *p = stringArray[i]; *p; p++)
		{
			if (*p == *delimiter)
			{
				fieldCount++;
			}
		}
		
		// Check if the string contains a date/time format
		int *dateTimeResults = string_is_date_time(stringArray[i], delimiter, fieldCount);
		if (dateTimeResults == NULL)
		{
			continue; // Skip this string if there was an error
		}
		
		for (int j = 0; j < fieldCount; j++)
		{
			if (dateTimeResults[j] == 1)
			{
				free(dateTimeResults);
				return true; // A date/time format was found
			}
		}
		
		free(dateTimeResults);
	}
	
	return false; // No date/time format was found in any string
}








size_t string_length(const char *characterString)
{
	register const char *s; // The 'register' keyword is a hint to the compiler to store the variable in a CPU register for faster access(though 'register' is mostly deprecated in modern C).
	
	for (s = characterString; *s; ++s); // Uses a pointer s to iterate over the characters in the string until the null terminator is reached.
	return(s - characterString); // The difference between the final value of s and the original characterString gives the length of the string.
	
	/**
	 size_t length = 0; // Initialize the length to zero
	 while (*characterString++) // Iterate over the string until the null terminator is reached
	 { length++; } return length; //*/
}




/**
 * count_array_strings
 *
 * Counts the number of non-NULL strings in an array of strings. This function is useful for determining
 * the length of an array where the end is marked by a NULL pointer.
 *
 * @param stringArray Array of strings, NULL-terminated.
 * @return The count of non-NULL strings in the array.
 */
int count_array_strings(char **stringArray)
{
	// Check for NULL input and handle error.
	if (stringArray == NULL){ return 0; }
	
	
	int stringCount = 0;
	while (stringArray[stringCount] != NULL)
	{
		stringCount++;
	}
	
	return stringCount;
}




/**
 * count_character_occurrences
 *
 * Counts occurrences of a specific character in a string.
 * This function iterates over each character in the provided string,
 * incrementing a counter each time it encounters the specified character.
 *
 * @param characterString Pointer to the string to be searched.
 * @param c The character to count occurrences of.
 * @return The count of occurrences of character c in characterString.
 */
int count_character_occurrences(const char *characterString, char c)
{
	// Check for NULL input and handle error.
	if (characterString == NULL){ perror("\n\nError: characterString was NULL in 'count_character_occurrences'.\n");      exit(1); }
	
	int count = 0;
	
	// Loop through each character of the string.
	for (int i = 0; characterString[i] != '\0'; i++)
	{
		if (characterString[i] == c) // Check if the current character is the one we're counting.
		{
			count++; // Increment count if the character matches.
		}
	}
	return count; // Return the final count of the character.
}




/**
 * find_most_common_non_alphanumeric_character
 *
 * Finds the most common non-alphanumeric character in a string.
 * This function maintains an array to count the occurrences of each character.
 * It iterates over the string, updating the count for non-alphanumeric characters.
 * Finally, it returns the character with the highest occurrence count.
 *
 * @param characterString Pointer to the string to be searched.
 * @return The most common non-alphanumeric character in characterString.
 */
char find_most_common_non_alphanumeric_character(const char *characterString)
{
	// Check for NULL input and handle error.
	if (characterString == NULL){ perror("\n\nError: characterString was NULL in 'find_most_common_non_alphanumeric_character'.\n");      exit(1); }
	
	
	int ascii[256] = {0};  // Array to count occurrences of each ASCII character.
	int maxCount = 0;  // Variable to store the maximum count found.
	char commonChar = '\1';  // Use '\1' as a special indicator for no clear delimiter and/or as a Variable to store the most common character found.
	char firstNonAlnumChar = '\0'; // Variable to store the first non-alphanumeric character encountered to handle single occurences... Currently indecisive about what to do with this, not being used for now.
	
	
	
	// Iterate over each character of the string.
	for (int i = 0; characterString[i] != '\0'; i++)
	{
		if (char_is_whitespace((unsigned char)characterString[i]))  // Skip spaces.
		{
			continue;
		}
		
		
		
		if (!char_is_alnum((unsigned char)characterString[i]))  // Check if character is non-alphanumeric.
		{
			if (firstNonAlnumChar == '\0') // Store the first non-alphanumeric character encountered.
			{
				firstNonAlnumChar = characterString[i];
			}
			
			
			ascii[(unsigned char)characterString[i]]++;  // Increment count for this character.
			if (ascii[(unsigned char)characterString[i]] > maxCount)  // Check if this character now has the highest count.
			{
				maxCount = ascii[(unsigned char)characterString[i]]; // Update max count.
				commonChar = characterString[i];  // Update most common character.
			}
		}
	}
	
	
	
	// IGNORE THIS LINE FOR NOW, STILL INVESTIGATING //return (maxCount > 1) ? commonChar : firstNonAlnumChar; // If no character appeared more than once, return the first non-alphanumeric character encountered.
	return commonChar; // Return the most common non-alphanumeric character.
}




/**
 * find_potential_delimiters
 *
 * This function is designed to identify potential delimiters in a given string.
 * It does this by iterating over each character in the string and checking if it is a delimiter.
 * If it is, it increments a count for that character in an ASCII array.
 * The function then collects all characters that have the maximum count (i.e., the most common potential delimiters)
 * and stores them in a dynamically allocated string, which it returns.
 * The count of potential delimiters is also returned via a pointer argument.
 *
 * @param characterString Pointer to the string to be searched.
 * @param delimiterCount Pointer to an integer in which to store the count of potential delimiters found.
 * @return A dynamically allocated string containing the potential delimiters.
 */
char *find_potential_delimiters(const char *characterString, int *delimiterCount)
{
	/// Check if the input string is NULL. If it is, print an error message and exit.
	if (characterString == NULL)
	{
		perror("\n\nError: characterString was NULL in 'find_potential_delimiters'.\n");
		exit(1);
	}
	
	
	
	int ascii[256] = {0}; // Initialize an ASCII array to zero
	int maxCount = 0;
	char *delimiters = malloc(256); // Allocate memory to store potential delimiters.
	
	
	/// Iterate over each character of the string.
	for (int i = 0; characterString[i] != '\0'; i++)
	{
		/// If the character is a delimiter, increment its count in the ASCII array.
		if (char_is_delimiter(characterString[i]))
		{
			ascii[(unsigned char)characterString[i]]++;
			
			/// If this character now has the highest count, update maxCount.
			if (ascii[(unsigned char)characterString[i]] > maxCount)
			{
				maxCount = ascii[(unsigned char)characterString[i]];
			}
		}
	}
	
	/// Collect all characters that have the max count.
	int count = 0;
	for (int i = 0; i < 256; i++)
	{
		/// If the character count equals maxCount and maxCount is greater than 0, add it to the delimiters string.
		if (ascii[i] == maxCount && maxCount > 0)
		{
			delimiters[count++] = (char)i;
		}
	}
	
	
	/// Null-terminate the string of delimiters and set the count of delimiters found.
	delimiters[count] = '\0';
	*delimiterCount = count;
	
	
	return delimiters; // Return the string of potential delimiters.
}




/**
 * identify_delimiter
 *
 * Identifies the most common delimiter in an array of strings to determine what can be reasonably assumed as the delimiter.
 * This function analyzes each string to find its most common non-alphanumeric character
 * and the number of occurrences of this character. It then compares these results across all strings
 * to attempt to identify a consistently occuring delimiter that meets the criteria (same delimiter and same number of occurrences
 * in more than half of the strings). It returns the identified delimiter or will attempt to find the most
 * common delimiter across all strings if no consistent delimiter is found.
 *
 * @param stringArray Pointer to the string to be searched.
 * @param stringCount The number of strings in stringArray.
 * @return The most common delimiter character as a string.
 */
char *identify_delimiter(char** stringArray, int stringCount)
{
	if (stringArray == NULL || stringCount <= 0)
	{
		perror("\n\nError: stringArray was NULL in 'identify_delimiter'.\n");
		return "\0";
	}
	
	int delimitersCounts[256] = {0}; // Array to count occurrences of each potential delimiter across all strings
	
	for (int i = 0; i < stringCount; i++)
	{
		if (stringArray[i] == NULL)
		{
			continue;
		}
		
		
		/// Find potential delimiters in the current string and count their occurrences.
		int delimiterCount = 0;
		char *delimiters = find_potential_delimiters(stringArray[i], &delimiterCount);
		
		
		/// Count occurrences of each potential delimiter
		for (int j = 0; j < delimiterCount; j++)
		{
			delimitersCounts[(unsigned char)delimiters[j]]++;
		}
		free(delimiters); // Free the memory allocated for delimiters
	}
	
	
	/// Iterate over the counts of each potential delimiter to find the most common one
	int maxCount = 0;
	char mostCommonDelimiter = '\0';
	for (int i = 0; i < 256; i++)
	{
		/// If the current delimiter has a higher count than the current most common one, update the most common one
		if (delimitersCounts[i] > maxCount)
		{
			maxCount = delimitersCounts[i];
			mostCommonDelimiter = (char)i;
		}
	}
	
	
	
	/// If a most common delimiter was found, return it. Otherwise, return '\0'.
	if (mostCommonDelimiter != '\0')
	{
		char *identifiedDelimiter = (char*)malloc(2 * sizeof(char));//allocate_memory_char_ptr(2);
		identifiedDelimiter[0] = mostCommonDelimiter;
		identifiedDelimiter[1] = '\0';
		return identifiedDelimiter;
	}
	else
	{
		printf("\n\nNo consistent delimiter found in 'identify_delimiter'.");
		return "\0";
	}
}




/**
 * identify_delimiter_recursive... a special case function(i.e., made specifcally for an unrelated program, only useful for that very specific task, mostly)
 *
 * This function is an extension of the 'identify_delimiter' function.
 * It is designed to handle cases where the most common delimiter is a combination of delimiters,
 * such as a comma and a space, or a comma and a tab, etc.
 *
 * It calls itself recursively by specifying previously identified delimiting characters
 * so that it can ignore them in the next call and return the "secondary" delimiting character.
 * The specified delimiting characters passed in as arguments are the "primary" delimiting characters and are ignored.
 *
 * @param stringArray Pointer to an array of strings to be analyzed.
 * @param stringCount The number of strings in the array.
 * @param primaryDelimiters Pointer to an array of primary delimiters to be ignored.
 * @param primaryDelimiterCount The number of primary delimiters that are to be ignored.
 * @return The function returns a pointer to the most common delimiter that is not a primary delimiter. If no such delimiter is found, it returns a null character.
 */
char *identify_delimiter_recursive(char** stringArray, int stringCount, char **primaryDelimiters, int *primaryDelimiterCount)
{
	/// Check for invalid arguments and handle error.
	if (stringArray == NULL || stringCount <= 0 || primaryDelimiters == NULL || *primaryDelimiterCount <= 0)
	{
		perror("\n\nError: Invalid arguments in 'identify_delimiter_recursive'.\n");
		return "\0";
	}
	
	/// Initialize an array to count the occurrences of each potential delimiter.
	int delimitersCounts[256] = {0};
	
	/// Iterate over each string in the array.
	for (int i = 0; i < stringCount; i++)
	{
		/// Skip null strings.
		if (stringArray[i] == NULL)
		{
			continue;
		}
		
		/// Find the potential delimiters in the current string.
		int delimiterCount = 0;
		char *delimiters = find_potential_delimiters(stringArray[i], &delimiterCount);
		
		/// Iterate over each potential delimiter.
		for (int j = 0; j < delimiterCount; j++)
		{
			/// Check if the current delimiter is a primary delimiter.
			int isPrimary = 0;
			for (int k = 0; k < *primaryDelimiterCount; k++)
			{
				/// If it is, mark it as such and break the loop.
				if (delimiters[j] == (*primaryDelimiters)[k])
				{
					isPrimary = 1;
					break;
				}
			}
			
			/// If the current delimiter is not a primary delimiter, increment its count.
			if (!isPrimary)
			{
				delimitersCounts[(unsigned char)delimiters[j]]++;
			}
		}
		/// Free the memory allocated for the potential delimiters.
		free(delimiters);
	}
	
	/// Find the most common non-primary delimiter.
	int maxCount = 0;
	char mostCommonDelimiter = '\0';
	for (int i = 0; i < 256; i++)
	{
		/// If the current delimiter has a higher count than the current most common one, update the most common one.
		if (delimitersCounts[i] > maxCount)
		{
			maxCount = delimitersCounts[i];
			mostCommonDelimiter = (char)i;
		}
	}
	
	/// If a most common non-primary delimiter was found, return it. Otherwise, return a null character.
	if (mostCommonDelimiter != '\0')
	{
		char *identifiedDelimiter = (char*)malloc(2 * sizeof(char));//= allocate_memory_char_ptr(2);
		identifiedDelimiter[0] = mostCommonDelimiter;
		identifiedDelimiter[1] = '\0';
		return identifiedDelimiter;
	}
	else
	{
		printf("\n\nNo consistent delimiter found in 'identify_delimiter_recursive'.");
		return "\0";
	}
}




/**
 * determine_string_representation_type
 *
 * This function analyzes a string to infer the data type of the value it represents.
 * The function is designed to handle numeric and non-numeric strings.
 * The function uses the `string_is_numeric` function to check if the string can be interpreted as
 * a numeric value(parsed as a floating-point number), and if it can, it returns "numeric".
 * Also, it treats a single hyphen as a non-numeric string because a hyphen alone does not represent a valid number.
 *
 * @param token Pointer to a delimited string, is analyzed to determine its data type.
 * @return The function returns a pointer to a string describing the data type of the input.
 */
const char* determine_string_representation_type(const char* token)
{
	// Check for NULL input and handle error.
	if (token == NULL){ perror("\n\nError: token was NULL in 'determine_string_representation_type'.\n");      exit(1); }
	
	
	// Treat a single hyphen as non-numeric
	if (compare_strings(token, "-") == 0)
	{
		return "nonnumeric";
	}
	
	
	
	/// This function determines the type of the string representation.
	/// It checks if the string can be interpreted as a numeric value.
	/// If it can, it returns "numeric". Otherwise, it returns "nonnumeric".
	if(string_is_numeric(token))
	{
		return "numeric";
	}
	else
	{
		return "nonnumeric";
	}
}








/**
 * duplicate_string
 *
 * This function duplicates a string by allocating memory for a new string and copying the contents of the original string.
 * The duplicated string is a deep copy, and the caller is responsible for freeing the memory allocated for the new string.
 *
 * @param characterString The string to be duplicated.
 * @return A pointer to the duplicated string, or NULL if memory allocation fails.
 */
char *duplicate_string(const char *characterString)
{
	if (characterString == NULL)
	{
		return NULL; // Return NULL if the input string is NULL
	}
	
	size_t length = string_length(characterString) + 1; // Calculate the length of the string including the null terminator
	char *dup = (char *)malloc(length); // Allocate memory for the duplicated string
	
	if (dup == NULL)
	{
		return NULL; // Return NULL if memory allocation fails
	}
	
	copy_memory_block(dup, characterString, length); // Copy the original string to the newly allocated memory
	return dup; // Return the pointer to the duplicated string
}




/**
 * copy_string
 *
 * This function copies the string pointed to by src, including the null terminator,
 * to the buffer pointed to by dest. The destination buffer must be large enough to
 * receive the copied string.
 *
 * @param destination The destination buffer where the string will be copied.
 * @param source The source string to be copied.
 * @return A pointer to the destination string.
 */
char *copy_string(char *destination, const char *source)
{
	char *dest_start = destination; // Save the start of destination buffer
	
	//while ((*destination++ = *source++) != '\0'); // Copy each character from source to destination including the null terminator
	while ((*destination++ = *source++)); // Copy each character from src to dest, including the null terminator
	
	return dest_start; // Return the start of the destination buffer
}




/**
 * copy_n_string
 *
 * This function copies up to 'n' characters from the source string to the destination string.
 * If the length of the source string is less than 'n', the remainder of the destination string is padded with null characters.
 * The destination string must be large enough to receive the copy.
 *
 * @param destination The destination buffer where the content is to be copied.
 * @param source The source null-terminated string to be copied.
 * @param n The maximum number of characters to copy from source to destination.
 * @return A pointer to the destination string.
 */
char *copy_n_string(char *destination, const char *source, size_t n)
{
	char *dest_start = destination; // Save the start of the destination buffer
	
	
	// Copy up to n characters from source to destination
	while (n > 0 && (*source != '\0'))
	{
		*destination++ = *source++;
		n--;
	}
	
	
	// Null-pad the remaining bytes
	while (n > 0)
	{
		*destination++ = '\0';
		n--;
	}
	
	return dest_start; // Return the start of the destination buffer
}




/**
 * concatenate_string
 *
 * This function concatenates the source string to the destination string.
 * The destination string must have enough space to hold the concatenated result.
 *
 * @param destination The destination string to which the source string will be concatenated.
 * @param source The source string to be concatenated.
 * @return A pointer to the destination string.
 */
char *concatenate_string(char *destination, const char *source)
{
	char *dest_start = destination; // Save the start of destination buffer
	
	// Move dest to the end of the current string
	while (*destination)
	{
		destination++;
	}
	
	// Copy each character from source to destination, including the null terminator
	while ((*destination++ = *source++));
	
	return dest_start; // Return the start of the destination buffer
}







/**
 * concatenate_n_string
 *
 * Appends at most 'n' characters from the source string to the destination string,
 * and then appends a null terminator. The destination string must have enough space
 * to hold the resulting concatenated string.
 *
 * @param destination The destination string to which the source string will be concatenated.
 * @param source The source string to be concatenated.
 * @param n The maximum number of characters to concatenate from the source string.
 * @return A pointer to the destination string.
 */
char *concatenate_n_string(char *destination, const char *source, size_t n)
{
	char *dest_start = destination; // Save the start of destination buffer
	
	// Move destination to the end of the current string
	while (*destination)
	{
		destination++;
	}
	
	// Copy up to 'n' characters from source to destination
	while (n-- > 0 && *source)
	{
		*destination++ = *source++;
	}
	
	// Null-terminate the destination string
	*destination = '\0';
	
	return dest_start; // Return the start of the destination buffer
}








/**
 * determine_most_common_string
 *
 * This function determines the most frequently occurring string in a given array of strings.
 * It returns a pointer to a new memory location containing the most common string from the array.
 * If the array is empty or stringCount is less than or equal to 0, it returns NULL.
 *
 * @note This function uses two arrays to keep track of each unique string and its frequency in the array.
 *       It iterates over each string in the given array and checks if it is already present in the unique strings array.
 *       If present, it increments the count of that string in the counts array, otherwise, it adds the string to the unique strings array and sets its count to 1.
 *       It also keeps track of the string with the maximum count.
 *
 * @param stringArray This is a pointer to an array of pointers to strings. Each element in this array points to a string.
 * @param stringCount The number of strings in the array.
 * @return The most common string in the array.
 */
char* determine_most_common_string(char **stringArray, int stringCount)
{
	// Check if the count is less than or equal to 0. If so, return NULL.
	if(stringCount <= 0)
	{
		return NULL;
	}
	
	// Allocate memory for two arrays: one to store unique strings and another to store their counts.
	char **uniqueStrings = (char**)calloc(stringCount, sizeof(char*));
	int *counts = (int*)calloc(stringCount, sizeof(int));
	int maxCount = 0, maxIndex = 0;
	
	// Iterate over each string in the given array to find unique strings and count their occurrences.
	for(int i = 0; i < stringCount; i++)
	{
		int j;
		
		// If the string is already present in the unique strings array increment its count in the counts array.
		for(j = 0; j < i; j++)
		{
			// If the string is present, increment its count, done to keep track of the frequency of each unique string.
			if(uniqueStrings[j] != NULL && compare_strings(stringArray[i], uniqueStrings[j]) == 0)
			{
				counts[j]++;
				
				// If the count of the current string is greater than maxCount, update maxCount and maxIndex, done to keep track of the most common string as the array is processed.
				if(counts[j] > maxCount)
				{
					maxCount = counts[j];
					maxIndex = j;
				}
				break;
			}
		}
		
		
		// If the string is not present in the unique strings array, add it to the array and set its count to 1, done to keep track of the frequency of each unique string.
		if(j == i)
		{
			uniqueStrings[i] = stringArray[i];
			counts[i] = 1;
		}
	}
	
	// Allocate for the most common string and copy it to this location.
	char* mostCommonString = duplicate_string(uniqueStrings[maxIndex]);
	
	// Cleanup.
	free(uniqueStrings);
	free(counts);
	
	return mostCommonString; // Return the most common string.
}




/**
 * compare_strings
 *
 * Performs a binary comparison of the characters of the two strings and returns an integer value based on the
 * comparison result(0 if equal, -1 if less than, 1 if greater than).
 * This function compares two character strings for equality, returning an integer value
 * indicating the difference between the first non-matching characters in the strings.
 * It is designed to handle unaligned memory access and optimize the comparison process
 * by comparing aligned memory blocks of the strings.
 *
 * @param characterString1 The first character string to compare.
 * @param characterString2 The second character string to compare.
 * @return An integer value indicating the difference between the first non-matching characters.
 */
int compare_strings(const char *characterString1, const char *characterString2)
{
	// Handle unaligned bytes of characterString1 first
	uintptr_t numUnalignedBytes = -(uintptr_t)characterString1 % sizeof(unsigned long); // Calculate the number of unaligned bytes
	
	
	// Iterate over the unaligned bytes
	for (uintptr_t i = 0; i < numUnalignedBytes; ++i)
	{
		unsigned char c1 = *characterString1++;
		unsigned char c2 = *characterString2++;
		
		int diff = c1 - c2;
		if (c1 == '\0' || diff != 0)
		{
			return diff;
		}
	}
	
	
	// characterString1 is now aligned to unsigned long, characterString2 may or may not be
	
	
	// Cast the strings to unsigned long pointers for the aligned comparison.
	const unsigned long *x1 = (const unsigned long *) characterString1;
	const unsigned long *x2 = (const unsigned long *) characterString2;
	
	
	
	
	// Compare the aligned parts of the strings
	while (*x1 == *x2)
	{
		// Check for null character in the aligned memory
		if (((const unsigned char*)x1)[0] == '\0' || ((const unsigned char*)x1)[1] == '\0' ||
			((const unsigned char*)x1)[2] == '\0' || ((const unsigned char*)x1)[3] == '\0')
		{
			break;
		}
		x1++;
		x2++;
	}
	
	
	// Cast the pointers back to char pointers to compare the remaining bytes.
	characterString1 = (const char *)x1;
	characterString2 = (const char *)x2;
	
	
	// Compare the remaining bytes character by character while they are equal and neither string has reached its null terminator
	while (*characterString1 && (*characterString1 == *characterString2))
	{
		characterString1++;
		characterString2++;
	}
	
	
	// Return the difference between the first non-matching characters
	return (unsigned char)*characterString1 - (unsigned char)*characterString2;
}








/**
 * combine_strings
 *
 * Combine two strings into a new string. Allocates memory for the new string, intitializes
 * it with the first input string, and appends the contents of the second input string to the first.
 * Handles NULL inputs by treating them as empty strings.
 *
 * @param characterString1 The first character string.
 * @param characterString2 The second character string.
 * @return A pointer to the combined new string.
 */
char *combine_strings(const char* characterString1, const char* characterString2)
{
	// Check for NULL input and handle error.
	if (characterString1 == NULL) characterString1 = " ";
	if (characterString2 == NULL) characterString2 = " ";
	
	
	/* Determine Count of Characters of Both Strings and Allocate Memory Appropriately */
	int characterCount = string_length(characterString1) + 1 + string_length(characterString2) + 1;
	char *combinedString = (char*)malloc(characterCount * sizeof(char));   //Allocate memory based on character count.
	
	
	/* Populate the CombinedString with the contents of the two strings */
	copy_string(combinedString, characterString1);     // Initialize with the first string.
	concatenate_string(combinedString, characterString2);   // Append the second string to the first.
	
	return combinedString;
}




/**
 * combine_string_arrays
 *
 * Merges two arrays of strings into a new array. Each element of the new array is
 * created by concatenating corresponding elements from the two input arrays.
 * Allocates memory for the new array and individual strings. Handles different sizes
 * of input arrays and NULL elements.
 *
 * @param stringArray1 The first array of strings.
 * @param stringCountArray1 The number of strings in the first array.
 * @param stringArray2 The second array of strings.
 * @param stringCountArray2 The number of strings in the second array.
 * @return A pointer to the combined new array of strings.
 */
char **combine_string_arrays(const char **stringArray1, int stringCountArray1, const char **stringArray2, int stringCountArray2)
{
	// Check for NULL input and handle error.
	if (stringArray1 == NULL){ perror("\n\nError: stringArray1 was NULL in 'combine_string_arrays'.\n");      exit(1); }
	if (stringArray2 == NULL){ perror("\n\nError: stringArray2 was NULL in 'combine_string_arrays'.\n");      exit(1); }
	
	
	/* Determine the total number of strings and allocate memory appropriately */
	int maxNumStrings = max(stringCountArray1, stringCountArray2);
	char **combinedStringArray = (char**)malloc((maxNumStrings + 1) * sizeof(char*));// = allocate_memory_char_ptr_ptr(strlen(*stringArray1), (maxNumStrings + 1));
																					 //For each pointer, allocate memory for a char pointer
	for(size_t i = 0; i < (maxNumStrings + 1); i++)
	{
		combinedStringArray[i] = (char*)malloc(string_length(*stringArray1) * sizeof(char));// = allocate_memory_char_ptr(strSize);
	}
	
	
	
	
	// Combine strings while both arrays have elements
	for (int i = 0; i < stringCountArray1 && i < stringCountArray2; i++)
	{
		/* Determine Count of Characters of Both Strings and Allocate Memory Appropriately */
		char *str1 = (i < stringCountArray1) ? stringArray1[i] : "";
		char *str2 = (i < stringCountArray2) ? stringArray2[i] : "";
		
		// Protect against NULL pointers
		if (str1 == NULL) str1 = "";
		if (str2 == NULL) str2 = "";
		
		
		combinedStringArray[i] = combine_strings(str1, str2);
		
		free(str1);
		free(str2);
	}
	
	// Copy remaining strings from the longer array
	if (stringCountArray1 > stringCountArray2)
	{
		for (int i = 0; i < stringCountArray1; i++)
		{
			combinedStringArray[i] = stringArray1[i]; // Copy remaining strings from array1
		}
	}
	else
	{
		for (int i = 0; i < stringCountArray2; i++)
		{
			combinedStringArray[i] = stringArray2[i]; // Copy remaining strings from array2
		}
	}
	
	// Null-terminate the array
	combinedStringArray[maxNumStrings] = NULL;
	return combinedStringArray;
}




/**
 * append_string_array_to_string
 *
 * Combines a string with each string in an array, creating a new combined string.
 * Allocates memory for a new string that combines the initial string with each string in the array.
 *
 * @param characterString1 The initial string.
 * @param characterStringArray The array of strings to be combined with the initial string.
 * @param stringCount The number of strings in the array.
 * @return A pointer to the newly allocated combined string.
 */
char *append_string_array_to_string(const char *characterString1, const char *characterStringArray[], int stringCount, const char *delimiter)
{
	// Check for NULL input and handle error.
	if (characterString1 == NULL || characterStringArray == NULL){ perror("\n\nError: characterString1 and/or characterStringArray was NULL in 'combine_char_ptr_arr'.\n");      return NULL; }
	
	
	size_t characterCount = string_length(characterString1) + 1; // +1 for the null terminator
	for(int i = 0; i < stringCount && characterStringArray[i] != NULL; i++)
	{
		characterCount += string_length(characterStringArray[i]);
	}
	
	
	char *combinedString = (char*)malloc(characterCount * sizeof(char)); //initialize with memory to copy first string
	copy_string(combinedString, characterString1); // Initialize the string
	
	
	for(int i = 0; i < stringCount; i++)
	{
		concatenate_string(combinedString, characterStringArray[i]);  //append each string in the string array to the combined string
		
		
		// Insert the delimiter between strings
		if (i < stringCount - 1 && characterStringArray[i + 1] != NULL) // Last string in the string array is not reached and the next string is not null(avoids interruptor strings)
		{
			// Because it is assumed we are in the midst of concatenating strings, the number of delimiters should be less than
			// or equal to the number of strings in the array, if the number of delimiters is equal to or greater than the number
			// of strings at any point, then it means that either the delimiter is not present as intended in the string
			// array(very unlikely at this point) or it means that the delimiting character has been inserted into the string
			// array at some point in an unintended manner.
			concatenate_string(combinedString, delimiter);
		}
	}
	
	return combinedString;
}




/**
 * concatenate_string_array
 *
 * Concatenates each string from an array of strings into one single string, separated by commas(not strictly commas, but whatever delimiter is passed in, commas by convention).
 * Each element from the passed in character double pointer(used here as an array of arrays of characters) is itself a character pointer(used here as an array of characters),
 * meaning that the (individual characters) from a double pointer char(effectively an array of strings) to create one single string , separated by commas.
 *
 * @param stringArray The array of strings to concatenate.
 * @param stringCount The number of strings in the array.
 * @return A pointer to the newly allocated concatenated string.
 */
char* concatenate_string_array(const char** stringArray, int stringCount, const char *delimiter)
{
	// Check for NULL input and handle error.
	if (stringArray == NULL){ perror("\n\nError: stringArray was NULL in 'concatenate_string_array'.\n");      return 0; }
	
	
	
	// Determine the length of the concatenated string
	size_t totalLength = 0;
	for (int i = 0; i < stringCount && stringArray[i] != NULL; i++)
	{
		totalLength += string_length(stringArray[i]) + 1; // +1 for comma or null terminator
	}
	
	// Allocate memory for the concatenated string
	char* concatenated = (char*)malloc(totalLength * sizeof(char));// = allocate_memory_char_ptr(totalLength);
	
	
	int emptyStringCount = 0; // Track the number of empty strings
	int *emptyStringIndices = (int*)malloc(stringCount * sizeof(int)); // = allocate_memory_int_ptr(stringCount); // Track the indices of empty strings
	for (int i = 0; i < stringCount; i++)
	{
		if((stringArray[i] == NULL) || (compare_strings(stringArray[i], "") == 0) || (string_length(stringArray[i]) == 0) || (stringArray[i] == (void *)0) || (compare_strings(stringArray[i], delimiter) == 0))
		{
			emptyStringCount++;
			emptyStringIndices[i] = 1; // A value of 1 indicates an empty string and a value of 0 indicates a non-empty string
		}
		else
		{
			emptyStringIndices[i] = 0;
		}
	}
	
	
	
	
	// Concatenate the fields
	copy_string(concatenated, ""); // Initialize the string
	for (int i = 0; i < stringCount && stringArray[i] != NULL; i++)
	{
		if(emptyStringIndices[i] == 1) // This string is empty
		{
			continue; // Skip this string
		}
		concatenate_string(concatenated, stringArray[i]);
		
		
		if (i < stringCount - 1 && stringArray[i + 1] != NULL)// && count_character_occurrences(concatenated, delimiter[0]) < (stringCount - emptyStringCount) ) // Last string in the string array is not reached, the next string is not null(avoids interruptor strings), and the occurences of the delimiter is less than the number of strings
		{
			// Because it is assumed we are in the midst of concatenating strings, the number of delimiters in the concatenated string should be less than
			// or equal to the number of strings in the string array, if the number of delimiters is at any point equal to or greater than the number of strings,
			// then it means that either the delimiter is not present as intended in the string array(very unlikely at this point) or it means that the delimiting
			// character has been inserted into the string array at some point in an unintended manner.
			
			// If the last element in the string array is the delimiter then it means that either the last string is empty or the delimiter was inserted into the string array at some point in an unintended manner
			concatenate_string(concatenated, delimiter);
		}
	}
	
	return concatenated;
}








/**
 * tokenize_string
 *
 * This function tokenizes a string based on a delimiter character and returns the next token.
 * It is similar to the standard strtok function but is reentrant and thread-safe.
 *
 * @param s The string to be tokenized.
 * @param delim The delimiter character used to tokenize the string.
 * @return A pointer to the next token in the string, or NULL if no more tokens are found.
 */
char *tokenize_string(char *s, const char *delim)
{
	// Register variables for optimization
	register char *spanp;
	register int c, sc;
	char *tok;
	static char *last;
	
	// If s is NULL, use the saved pointer last
	if (s == NULL && (s = last) == NULL)
		return (NULL);
	
	// Skip leading delimiters
cont:
	c = *s++;
	for (spanp = (char *)delim; (sc = *spanp++) != 0;)
	{
		if (c == sc)
			goto cont;
	}
	
	// If the end of the string is reached, return NULL
	if (c == 0)
	{
		last = NULL;
		return (NULL);
	}
	tok = s - 1;
	
	// Scan the token
	for (;;)
	{
		c = *s++;
		spanp = (char *)delim;
		do
		{
			if ((sc = *spanp++) == c)
			{
				if (c == 0)
					s = NULL;
				else
					s[-1] = 0;
				last = s;
				return (tok);
			}
		} while (sc != 0);
	}
	// NOTREACHED
}




/**
 * split_tokenized_string
 *
 * Splits a string into an array of strings based on a given delimiter.
 *
 *
 * @param characterString The string to be split.
 * @param delimiter The delimiter used to split the string.
 * @param divisions The maximum number of parts to split the string into.
 * @return An array of strings, each representing a part of the original string.
 */
char** split_tokenized_string(const char* characterString, const char* delimiter, int divisions)
{
	char** parts = (char**)malloc(sizeof(char*) * (divisions + 1));
	if (parts == NULL)
	{
		fprintf(stderr, "Memory allocation failed in split_tokenized_string\n");
		exit(EXIT_FAILURE);
	}
	
	char* strCopy = duplicate_string(characterString); // Duplicate the string to avoid modifying the original
	if (strCopy == NULL)
	{
		fprintf(stderr, "Memory allocation failed in split_tokenized_string\n");
		exit(EXIT_FAILURE);
	}
	
	
	//printf("\n\n\n\n characterString: %s \ndivisions: %d \ndelimiter: %s", characterString, divisions, delimiter);
	char* token = tokenize_string(strCopy, delimiter);
	int i = 0;
	while (token != NULL && i < divisions)
	{
		parts[i] = duplicate_string(token);
		
		if (parts[i] == NULL)
		{
			fprintf(stderr, "Memory allocation failed in split_tokenized_string\n");
			exit(EXIT_FAILURE);
		}
		
		token = tokenize_string(NULL, delimiter);
		i++;
	}
	//print_string_array(parts, i, "split_tokenized_string parts");
	
	parts[i] = NULL; // Null-terminate the array
	free(strCopy);
	return parts;
}








/**
 * trim_string_whitespaces
 *
 * Trims leading and trailing whitespace from a string and returns a new string.
 * This function removes all whitespace characters from the beginning and end
 * of the provided string. Whitespace is defined as any character for which
 * the isspace() function returns true (i.e., space, tab, newline).
 *
 *
 * @param untrimmedString A pointer to the string to be trimmed.
 * @return A pointer to the newly allocated trimmed string, or NULL if the input string is NULL or empty.
 */
char *trim_string_whitespaces(char* untrimmedString)
{
	// Check for NULL or empty string
	if (!untrimmedString || !*untrimmedString)
	{
		return NULL;
	}
	
	
	// Traversing the string to find the first and last non-whitespace character
	const char *startPtr, *endPtr;
	for (startPtr = untrimmedString; *startPtr && char_is_whitespace((unsigned char)*startPtr); startPtr++);
	
	
	
	// Handle the case where the entire string is whitespace
	if (!*startPtr)
	{
		char *emptyStr = (char *)malloc(1);
		if (emptyStr)
		{
			*emptyStr = '\0';
		}
		return emptyStr;
	}
	
	
	
	// Find the last non-whitespace character
	for (endPtr = untrimmedString + string_length(untrimmedString) - 1; endPtr > startPtr && char_is_whitespace((unsigned char)*endPtr); endPtr--);
	
	
	
	// Calculate the length of the trimmed string
	size_t trimmedLength = endPtr - startPtr + 1;
	
	
	// Allocate memory for the new string
	char *trimmedString = (char *)malloc(trimmedLength + 1); // +1 for the null terminator
	if (!trimmedString)
	{
		return NULL; // Allocation failed
	}
	
	
	// Copy the trimmed content
	copy_n_string(trimmedString, startPtr, trimmedLength);
	trimmedString[trimmedLength] = '\0'; // Null-terminate the new string
	return trimmedString;
}




/**
 * prune_string_whitespaces
 *
 * Removes all whitespace characters from a string and returns a new string.
 * This function removes all whitespace characters (as defined by isspace())
 * from the provided string.
 *
 * @param unprunedString A pointer to the string from which whitespaces are to be removed.
 * @return A pointer to the newly allocated pruned string, or NULL if the input string is NULL or empty.
 */
char *prune_string_whitespaces(char *unprunedString)
{
	// Check for NULL or empty string
	if (!unprunedString || !*unprunedString)
	{
		return NULL;
	}
	
	// Allocate memory for the new string
	char *prunedString = (char *)malloc(string_length(unprunedString) + 1);
	if (!prunedString)
	{
		return NULL; // Allocation failed
	}
	
	const char *readPtr = unprunedString;
	char *writePtr = prunedString;
	
	// Iterate over the input string and copy non-whitespace characters
	while (*readPtr)
	{
		if (!char_is_whitespace((unsigned char)*readPtr))
		{
			*writePtr++ = *readPtr;
		}
		readPtr++;
	}
	
	// Null-terminate the new string
	*writePtr = '\0';
	
	
	// Reallocate prunedString to fit the actual pruned length
	char *fitString = realloc(prunedString, string_length(prunedString) + 1);
	if (fitString)
	{
		prunedString = fitString;
	}
	
	return prunedString;
}




/**
 * prune_repeated_delimiters_from_string
 *
 * Inserts a '0' character between consecutive delimiters in a string and returns a new string.
 * This function is particularly useful for processing CSV data. It ensures that empty fields
 * (indicated by consecutive delimiters) are explicitly represented with a '0' value, aiding in
 * correct data alignment during parsing.
 *
 *
 * @param unprunedString A pointer to the string to be processed.
 * @param delimiter The delimiter character used to identify consecutive occurrences.
 *        If the string is NULL or empty, the function returns NULL.
 * @return A pointer to the newly allocated processed string, or NULL if the input string is NULL or empty.
 */
char *prune_repeated_delimiters_from_string(char *unprunedString, const char *delimiter)
{
	// Check for NULL or empty string
	if (!unprunedString || !*unprunedString)
	{
		return NULL;
	}
	
	
	/// Allocate Memory for the New Pruned String
	size_t originalLength = string_length(unprunedString) + 1;
	size_t newLength = originalLength; // Initial estimate of new length
	
	
	// First pass: count consecutive delimiters to estimate the new length, i.e., the number of additional '0' characters required
	for (size_t i = 0; i < originalLength; i++)
	{
		if (unprunedString[i] == *delimiter && unprunedString[i + 1] == *delimiter)
		{
			newLength++;
		}
	}
	
	
	
	// Allocate memory for the new string
	char *prunedString = (char *)malloc((newLength) * sizeof(char));
	const char *readPtr = unprunedString; // Pointer for reading the input string
	char *writePtr = prunedString; // Pointer for writing to the new string
	bool previousCharWasDelimiter = false; // Track if the previous character was a delimiter
	
	
	// Iterate over the input string and process delimiters
	while (*readPtr)
	{
		if (readPtr == delimiter)
		{
			if (!previousCharWasDelimiter) //Will occur when
			{
				*writePtr++ = *readPtr; // Copy the first occurrence of the delimiter
			}
			else // if we reach here it means that the delimiter was true on the last iteration and it is also true this iteration
			{
				// Here is where the consecutive delimiters occur
				// Need to insert '0' between consecutive delimiters, memory was already allocated, so no concerns
				*writePtr++ = '0';
				*writePtr++ = *readPtr;
			}
			
			
			previousCharWasDelimiter = true;
		}
		else
		{
			*writePtr++ = *readPtr; // Copy non-delimiter character
			previousCharWasDelimiter = false;
		}
		readPtr++;
	}
	
	
	// Null-terminate the new string
	*writePtr = '\0';
	
	
	
	// Reallocate the pruned string to fit the actual length
	char *fitString = realloc(prunedString, string_length(prunedString) + 1);
	if (fitString)
	{
		prunedString = fitString;
	}
	
	return prunedString;
}




/**
 * prune_and_trim_problematic_characters_from_string
 *
 * Processes a string by trimming whitespace, pruning whitespace, handling repeated delimiters, and replacing date/time fields with Unix time.
 * The function first trims leading and trailing whitespaces, then removes all internal whitespaces,
 * handles repeated delimiters by inserting '0' characters, and finally replaces any date/time fields with their Unix time equivalents.
 *
 * @param originalString Pointer to the original string to be processed.
 * @param delimiter Pointer to the delimiter character used in the string.
 * @param fieldCount Number of fields expected in the string.
 * @return Pointer to the newly created string after processing, or NULL in case of an error or if the original string is NULL or empty.
 */
char *prune_and_trim_problematic_characters_from_string(char *originalString, const char *delimiter, const int fieldCount)
{
	// Check for NULL or empty string
	if (!originalString || !*originalString)
	{
		return NULL;
	}
	
	
	
	// Step 1: Trim whitespace from the beginning and end of the string.
	char *trimmedString = trim_string_whitespaces(originalString);
	if (!trimmedString)
	{
		perror("\n\nError: Step 1: Trim whitespace from string failure in 'prune_and_trim_problematic_characters_from_string'.\n");
		return originalString; // If the whitespace trimming fails then the original string is returned
	}
	
	
	
	// Step 2: Prune all internal whitespace characters from the string.
	char *prunedWhitespaceString = prune_string_whitespaces(trimmedString);
	if (!prunedWhitespaceString)
	{
		perror("\n\nError: Step 2: Prune whitespace from string failure in 'prune_and_trim_problematic_characters_from_string'.\n");
		return trimmedString; // If the whitespace pruning fails then the last successful string format is returned
	}
	else
	{
		free(trimmedString); // Free the memory allocated by trim_string_whitespaces and proceed to the next step
	}
	
	
	
	// Step 3: Process repeated delimiters by inserting '0' characters.
	char *prunedDelimiterString = prune_repeated_delimiters_from_string(prunedWhitespaceString, delimiter);
	if (!prunedDelimiterString)
	{
		perror("\n\nError: Step 3: Prune repeated delimiters from string failure in 'prune_and_trim_problematic_characters_from_string'.\n");
		return prunedWhitespaceString; // If the delimiter replacement fails then the last successful string format is returned
	}
	else
	{
		free(prunedWhitespaceString); // Proceed only if step 3 was successful and the previous string was replaced
	}
	
	
	
	// Step 4: Detect Date/Time Fields in string and Replace them with Unix Time
	char *unixTimeString = replace_date_time_with_unix(prunedDelimiterString, delimiter, fieldCount);
	if (!unixTimeString)
	{
		//perror("\n\nError: Step 4: Replace date/time fields with Unix time failure in 'prune_and_trim_problematic_characters_from_string'.\n");
		return prunedDelimiterString; // If the date/time replacement fails then the last successful string format is returned
	}
	else
	{
		free(prunedDelimiterString); // Only proceed if step 4 was successful and the previous string was replaced
	}
	
	
	
	return unixTimeString; // Return the final processed string if all 4 steps were successful
}








/**
 * replace_date_time_with_unix
 *
 * This function performs the task of replacing date/time fields in a given string with their Unix time
 * representations. It identifies date/time fields based on predefined formats and performs the
 * conversion when a field is a date/time string.
 *
 * The function begins by calling the string_is_date_time function to get an array indicating which fields are date/time fields.
 * It then counts the number of fields that are identified as date/time fields.
 * The function then estimates the size of the output string based on the number of date/time fields and the length of the input string.
 * It allocates memory for the output string based on the estimated size.
 * The function then duplicates the input string to avoid modifying it directly, as strtok modifies the string it processes.
 * It then initializes the output string to an empty string and tokenizes the copied string using the delimiter character.
 * The function then iterates over each token(field) in the string, checking if the current field is a date/time field.
 * If it is, it converts the date/time field to Unix time, prepares a string to hold the Unix time, and appends the Unix time string to the output.
 * If the field is not a date/time field, it appends it directly to the output.
 * The function then appends the delimiter for the next field and increments the index.
 * After iterating over all the fields, the function frees the memory allocated for the copy of the input string and the dateTimeIndicators array.
 * It then null-terminates the new string and reallocates the output to fit the actual length.
 * Finally, it returns the dynamically allocated output string.
 *
 *
 * @param characterString Pointer to the string to be interpreted.
 * @param delimiter The delimiter character used to identify consecutive occurrences.
 * @param fieldCount The number of fields found in the string.
 * @return A pointer to the newly allocated string with the date/time fields replaced with Unix time representations.
 */
char* replace_date_time_with_unix(char* characterString, const char *delimiter, const int fieldCount)
{
	// Call the string_is_date_time function to get an array indicating which fields are date/time fields.
	int *dateTimeIndicators = string_is_date_time(characterString, delimiter, fieldCount);
	
	// Count the number of fields that are identified as date/time fields.
	int dateTimeCount = 0;
	for(int i = 0; i < fieldCount; i++)
	{
		if(dateTimeIndicators[i] == 1)
		{
			dateTimeCount++;
		}
	}
	
	if(dateTimeCount == 0)
	{
		//perror("\n\nError: No date/time fields found in the string in 'replace_date_time_with_unix'.");
		return NULL;
	}
	
	
	// The max Unix timestamp is theoretically up to 9,223,372,036,854,775,807, far in the future and has 19 digits, so max length would be 20 characters(19 plus null terminator)
	size_t estimatedOutputSize = string_length(characterString) + dateTimeCount * 20;
	
	
	
	// Allocate memory for the output string based on the estimated size.
	char *output = (char *)malloc(estimatedOutputSize);
	
	// Duplicate the input string to avoid modifying it directly, as strtok modifies the string it processes.
	char* copyOfString = duplicate_string(characterString);
	
	
	
	
	output[0] = '\0'; // Initialize the output string to an empty string
	char* token = tokenize_string(copyOfString, delimiter);  // Tokenize the copied string using the delimiter character.
	int index = 0; // Initialize an index to track the current field
	
	// Iterate over each token(field) in the string.
	while (token != NULL)
	{
		// Check if the current field is a date/time field.
		if (dateTimeIndicators[index] == 1)
		{
			// Convert the date/time field to Unix time.
			time_t unixTime = convert_to_unix_time(token);
			
			// Prepare a string to hold the Unix time.
			char unixTimeString[20];
			snprintf(unixTimeString, sizeof(unixTimeString), "%ld", unixTime);
			
			// Append the Unix time string to the output.
			concatenate_n_string(output, unixTimeString, estimatedOutputSize - string_length(output) - 1);
		}
		else
		{
			// If the field is not a date/time field, append it directly to the output.
			concatenate_n_string(output, token, string_length(token) + 1);
		}
		
		
		// Append delimiter for next field.
		token = tokenize_string(NULL, delimiter);
		if (token != NULL && string_length(token) > 0 && index < fieldCount - 1)
		{
			concatenate_string(output, delimiter);
		}
		
		// Increment the index
		index++;
	}
	
	// Free the memory allocated for the copy of the input string and the dateTimeIndicators array.
	free(copyOfString);
	free(dateTimeIndicators);
	
	
	
	concatenate_string(output, "\0"); // Null-terminate the new string
	
	
	
	// Reallocate output to fit actual length.
	// Included here because the estimated size has to be able to account for the maximum possible size of the
	// outputted string, and since the outputted string usually changes minimnally in length from the inputtted string, it means that the estimate
	// often greatly exceeds the actual needed size, hence it's good practice to reallocate here.
	char *fitoutput = realloc(output, string_length(output) + 1);
	if (fitoutput)
	{
		output = fitoutput;
	}
	
	
	// Return the dynamically allocated output string.
	return output;
}




/**
 * preprocess_string_array
 *
 * Processes an array of strings by trimming whitespace, pruning whitespace, handling repeated delimiters, and replacing date/time fields with Unix time.
 * The function first trims leading and trailing whitespaces, then removes all internal whitespaces,
 * handles repeated delimiters by inserting '0' characters, and finally replaces any date/time fields with their Unix time equivalents.
 *
 * @param stringArray Pointer to the array of strings to be processed.
 * @param stringCount Number of strings in the array.
 * @param delimiter Pointer to the delimiter character used in the strings.
 * @return Pointer to the newly created array of processed strings, or NULL in case of an error or if the original string array is NULL.
 */
char **preprocess_string_array(char **stringArray, int stringCount, const char *delimiter)
{
	// Check for NULL input and handle error.
	if (stringArray == NULL){ perror("\n\nError: stringArray was NULL in 'preprocess_string_array'.\n");      return 0; }
	
	
	// Allocate memory for the new array
	char **processedStringArray = (char **)malloc((stringCount + 1) * sizeof(char *));
	if (processedStringArray == NULL)
	{
		perror("\n\nError: Memory allocation failed in 'preprocess_string_array'.\n");
		exit(EXIT_FAILURE);
	}
	
	
	// Process each string in the array
	for (int i = 0; i < stringCount; i++)
	{
		processedStringArray[i] = prune_and_trim_problematic_characters_from_string(stringArray[i], delimiter, stringCount);
	}
	
	// Null-terminate the array
	processedStringArray[stringCount] = NULL;
	return processedStringArray;
}
















/**
 * print_string
 * Prints a string with a label.
 *
 * @param string string to be printed.
 */
void print_string(char* string)
{
	// Check for NULL input and handle error.
	if (string == NULL){ perror("\n\nError: string was NULL in 'print_string'.\n");      exit(1); }
	printf("\n\n\n-----------------------------------------------------------------------------------------\n\n");
	printf("%s", string);
	printf("\n\n-----------------------------------------------------------------------------------------\n\n\n");
}


/**
 * print_string_array
 * Prints the elements of a string array with a label.
 *
 * @param stringArray Array of strings to be printed.
 * @param stringCount Number of strings in the array.
 * @param label Label to be printed before printing the array.
 */
void print_string_array(char** stringArray, int stringCount, char*label)
{
	// Check for NULL input and handle error.
	if(stringArray == NULL){ perror("\n\nError printing array of strings in 'print_string_array'.");      exit(1); }
	printf("\n\n%s: \n", label);
	for(int i = 0; i < stringCount; i++)
	{ printf("\n%s", stringArray[i]); } printf("\n\n");
}


/**
 * print_string_array_array
 *
 * This function prints the contents of an array of arrays of strings. It is assumed that all sub-arrays have the same dimension.
 * The output is formatted with a label and each string is printed on a new line.
 * The function first checks for NULL input to prevent errors. It then prints a label for the array.
 * It then iterates over the main array and for each sub-array, it calculates the length of the label, allocates memory for it,
 * and then prints the sub-array using the 'print_string_array' function.
 *
 * @param stringArrayArray The 2D array of strings to be printed.
 * @param stringArraysCount The number of sub-arrays in the main array.
 * @param stringSubArraysCount The number of strings in each sub-array.
 * @param label The label to be printed before printing the array.
 */
void print_string_array_array(char*** stringArrayArray, int stringArraysCount, int stringSubArraysCount, char* label)
{
	// Check for NULL input and handle error.
	if (stringArrayArray == NULL){ perror("\n\nError: stringArrayArray was NULL in 'print_string_array_array'.\n");      exit(1); }
	printf("\nprint_string_array_array %s =========================================================================================", label);
	printf("\n\n\n%s: \n", label);
	// Iterate over the main array.
	for (int i = 0; i < stringArraysCount; i++)
	{
		// For each sub-array, calculate the length of the label and allocate memory for it.
		int subArrayLabelCharacterCount = string_length(label);
		char* subArrayLabel = (char*)malloc((string_length(label) + 1) * sizeof(char));// = allocate_memory_char_ptr(strlen(label) + 1);

		// Print each sub-array.
		print_string_array(stringArrayArray[i], stringSubArraysCount, "stringArrayArray[i]");
	}
	
	printf("\n\n\n=========================================================================================\n\n");
}

/**
 * print_array
 * Prints the elements of a double array with a label.
 *
 * @param n Number of elements in the array.
 * @param data Array of doubles to be printed.
 * @param label Label to be printed before printing the array.
 */
void print_array(int n, double *data, char*label)
{
	// Check for NULL input and handle error.
	if (data == NULL){ perror("\n\nError: data was NULL in 'print_array'.\n");      exit(1); }
	printf("\n\n\n\n\n\n\n\n%s: \n", label);
	// Loop through the characters print
	for(int i = 0; i < n; i++)
	{ printf("%.17g ", data[i]); } printf("\n\n\n");
}


/**
 * print_array_array
 *
 * This function prints the contents of a 2D array with each element
 * displayed to 17 decimal places. The output is formatted with a label and
 * surrounded by a visual border for clarity.
 *
 * @param data A pointer to a pointer of doubles representing a 2D array.
 * @param rows The number of rows in the 2D array.
 * @param columns The number of columns in each row.
 * @param label A string label for the array.
 */
void print_array_array(double **data, int rows, int columns, char*label)
{
	// Check for NULL input and handle error.
	if (data == NULL){ perror("\n\nError: data was NULL in 'print_array_array'.\n");      exit(1); }
	
	printf("\n\n\n\n\n\n\nprint_array_array %s =========================================================================================", label);
	printf("\n\n%s: \n", label);
	
	for (int i = 0; i < rows; i++)
	{
		
		for (int j = 0; j < columns; j++)
		{
			printf("%.17g ", data[i][j]);
		}
		printf("\n"); // Newline after each row
	}
	printf("\n\n=========================================================================================\n\n");
}


/**
 * print_char_ptr_array
 * Prints the elements of a string array.
 *
 * @param charPtrArr Array of strings to be printed.
 * @param stringCount Number of strings in the array.
 */
void print_char_ptr_array(const char *charPtrArr[],  int stringCount, char* label)
{
	// Check for NULL input and handle error.
	if (charPtrArr == NULL){ perror("\n\nError: charPtrArr was NULL in 'print_char_ptr_array'.\n");      exit(1); }
	
	
	printf("\n\n%s: \n", label);
	// Loop through the elements array and print
	for (int i = 0; i < stringCount; i++)
	{
		printf("%s", charPtrArr[i]);
	}
	printf("\n\n\n");
}







