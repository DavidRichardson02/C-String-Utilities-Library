# C-String Utilities Library

## Overview
The C-String Utilities Library provides a comprehensive suite of utilities for string manipulation and analysis, as well as auxiliary functions and definitions for performing various computational tasks 
This library is designed to aid in data parsing, preprocessing, and various computational tasks that involve strings and/or memory operations.
The library is focused on providing functions for handling C-style strings, namely: char, char*, char*[], and char**.


## Table of Contents
- [Files](#files)
- [Installation](#installation)
- [Usage](#usage)
- [Functions](#functions)
  - [Auxiliary Utilities](#auxiliary-utilities)
  - [String Utilities](#string-utilities)
- [Contributing](#contributing)




## Files

1. **AuxiliaryUtilities.h** - Header file for auxiliary utilities, declares functions for general utility purposes, including memory operations, time conversions, and bitwise operations, additionally, this file also defines the global constants used throughout the program.
2. **AuxiliaryUtilities.c** - Implementation file for auxiliary utilities.
3. **StringUtilities.h** - Header file for string utilities, declares functions for string manipulation and analysis.
4. **StringUtilities.c** - Implementation file for string utilities.

## Installation

To use the C-String Utilities Library in your project, include the header files and compile the source files along with your project files.

### Example:
```sh
gcc -o my_program my_program.c AuxiliaryUtilities.c StringUtilities.c -lpthread
```

## Usage
To use the library, include the header files in your C source files:
```c
#include "AuxiliaryUtilities.h"
#include "StringUtilities.h"
```

## Functions

### Auxiliary Utilities

#### General Utilities
- `double min(double a, double b)` - Returns the minimum of two values.
- `double max(double a, double b)` - Returns the maximum of two values.
- `double min_element(double *data, int n)` - Returns the minimum element in an array.
- `double max_element(double *data, int n)` - Returns the maximum element in an array.

#### Time Operations
- `time_t convert_to_unix_time(const char *dateTimeString)` - Converts a date/time string into Unix time.
- `struct tm *thread_safe_localtime(const time_t *tim, struct tm *result)` - A thread-safe wrapper around localtime.

#### Bitwise Operations
- `uint64_t flip_sign_bit(uint64_t value)` - Flips the sign bit of a 64-bit integer.
- `uint64_t double_to_uint64(double value)` - Reinterprets a double as a uint64_t.
- `double uint64_to_double(uint64_t value)` - Reinterprets a uint64_t as a double.

#### Sorting
- `void merge_sort(double *unsortedData, const int numElements)` - Sorts an array of doubles using the merge sort algorithm.
- `void radix_sort_doubles(double *unsortedData, const int numElements)` - Sorts an array of doubles using radix sort.

#### Memory Operations
- `void *set_memory_block(void *block, int c, size_t n)` - Sets the first `n` bytes of the memory block to the value specified by `c`.
- `void *copy_memory_block(void *destination, const void *source, size_t n)` - Copies `n` bytes from source to destination.

### String Utilities

#### Character Properties
- `bool char_is_alpha(char c)` - Checks if a character is alphabetic.
- `bool char_is_digit(char c)` - Checks if a character is a digit.
- `bool char_is_alnum(char c)` - Checks if a character is alphanumeric.
- `bool char_is_whitespace(char c)` - Checks if a character is whitespace.
- `bool char_is_punctuation(char c)` - Checks if a character is punctuation.
- `bool char_is_underscore(char c)` - Checks if a character is an underscore.
- `bool char_is_sign(char c)` - Checks if a character is a sign.
- `bool char_is_delimiter(char c)` - Checks if a character is a delimiter.

#### String Properties
- `bool string_is_numeric(const char *characterString)` - Checks if a string represents a numeric value.
- `int *string_is_date_time(const char *characterString, const char *delimiter, const int fieldCount)` - Analyzes a string to detect occurences of commonly used date/time formats(defined in AuxiliaryUtilities.h).
- `bool string_array_contains_date_time(char **stringArray, int stringCount, const char *delimiter)` - Checks if any string in an array contains a date/time format.

#### Counting and Identifying
- `int count_character_occurrences(const char *characterString, char c)` - Counts occurrences of a character in a string.
- `char find_most_common_non_alphanumeric_character(const char *characterString)` - Finds the most common non-alphanumeric character in a string.
- `char *find_potential_delimiters(const char *characterString, int *delimiterCount)` - Finds potential delimiters in a string.
- `char *identify_delimiter(char **stringArray, int stringCount)` - Identifies the most common delimiter across an array of strings.
- `const char *determine_string_representation_type(const char *token)` - Determines if a string is numeric or non-numeric, FYI this function was made with the intention of passing in delimited data fields and individually assessing their type.

#### String Manipulation
- `size_t character_string_length(const char *characterString)` - Returns the length of a character string.
- `char *tokenize_character_string(char *s, const char *delim)` - Tokenizes a character string based on a delimiter.
- `char *duplicate_character_string(const char *characterString)` - Duplicates a character string.
- `char *copy_character_string(char *destination, const char *source)` - Copies a character string.
- `char *copy_n_character_string(char *destination, const char *source, size_t n)` - Copies up to `n` characters from source to destination.
- `char *concatenate_character_string(char *destination, const char *source)` - Concatenates two character strings.
- `char *concatenate_n_character_string(char *destination, const char *source, size_t n)` - Concatenates up to `n` characters from source to destination.
- `char **split_string_tokens(const char *characterString, const char *delimiter, int divisions)` - Splits a string into an array of strings based on a delimiter.
- `char *combine_char_ptr(const char *characterString1, const char *characterString2)` - Combines two strings.
- `char **combine_char_ptr_ptr(const char **stringArray1, int stringCountArray1, const char **stringArray2, int stringCountArray2)` - Combines two arrays of strings.
- `char *combine_char_ptr_arr(const char *characterString1, const char *characterStringArray[], int stringCount)` - Combines a string with each string in an array.
- `char *concatenate_string_array(const char **stringArray, int stringCount, const char *delimiter)` - Concatenates an array of strings into a single string.
- `char *replace_date_time_with_unix(char *characterString, const char *delimiter, const int fieldCount)` - Replaces date/time with Unix time in a string.
- `char *trim_string_whitespaces(char *untrimmedString)` - Trims whitespace from a string.
- `char *prune_string_whitespaces(char *unprunedString)` - Removes all whitespaces from a string.
- `char *prune_repeated_delimiters_from_string(char *unprunedString, const char *delimiter)` - Handles repeated delimiters in a string.
- `char *prune_and_trim_problematic_characters_from_string(char *originalString, const char *delimiter, const int fieldCount)` - Prunes and trims problematic characters.

#### String Comparison
- `int compare_character_strings(const char *characterString1, const char *characterString2)` - Compares two character strings for equality.
- `char *determine_most_common_string(char **stringArray, int stringCount)` - Determines the most common string in an array of strings.

#### Printing Functions (for debugging)
- `void print_string(char *string)` - Prints a single string.
- `void print_string_array(char **stringArray, int stringCount, char *label)` - Prints an array of strings.
- `void print_string_array_array(char ***stringArrayArray, int stringArraysCount, int stringSubArraysCount, char *label)` - Prints a 2D array of strings.
- `void print_array(int n, double *data, char *label)` - Prints an array of doubles.
- `void print_array_array(double **data, int rows, int columns, char *label)` - Prints a 2D array of doubles.
- `void print_char_ptr_array(char *charPtrArr[], int stringCount, char *label)` - Prints an array of char pointers.

## Contributing
Contributions to the C-String Utilities Library are welcome. If you have any bug reports, feature requests, or improvements, please open an issue or submit a pull request on GitHub.


