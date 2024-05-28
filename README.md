# C-String Utilities Library

## Overview
The C-String Utilities Library provides a comprehensive suite of utilities for string manipulation and analysis, as well as auxiliary functions and definitions for performing various computational tasks. This library is designed to aid in data parsing, preprocessing, and various computational tasks that involve strings and/or memory operations. It includes functions for general computational tasks, memory management, mathematical operations, time conversions, bitwise operations, sorting algorithms, and extensive string handling. This library is particularly useful for data parsing and preprocessing in contexts where string data must be examined, transformed, or formatted before being used in computations or visualizations. The library is focused on providing functions for handling C-style strings, namely: `char`, `char*`, `char*[]`, and `char**`.




<br/>

## Table of Contents
- [Files](#files)
- [Installation](#installation)
- [Usage](#usage)
- [Functions](#functions)
  - [Auxiliary Utilities](#auxiliary-utilities)
  - [String Utilities](#string-utilities)
- [Contributing](#contributing)




<br/>

## Files
1. **AuxiliaryUtilities.h** - Header file for auxiliary utilities, declares functions and global constants for general utility purposes.
2. **AuxiliaryUtilities.c** - Implementation file for auxiliary utilities.
3. **StringUtilities.h** - Header file for string utilities, declares functions for string manipulation and analysis.
4. **StringUtilities.c** - Implementation file for string utilities.



  
<br/>

## Installation

To install the C-String Utilities Library for use in your project, follow these steps:

1. Clone the repository to your local machine:
    ```sh
    git clone https://github.com/yourusername/c-string-utilities-library.git
    ```
2. Navigate to the project directory:
    ```sh
    cd c-string-utilities-library
    ```
3. Include the header files in your C project and compile the source files along with your project files:
    ```c
    #include "AuxiliaryUtilities.h"
    #include "StringUtilities.h"
    ```
4. Compile the source files with your project files:
    ```sh
    gcc -o my_program my_program.c AuxiliaryUtilities.c StringUtilities.c -lpthread
    ```



  
<br/>

## Functions

### Auxiliary Utilities
The `AuxiliaryUtilities.h` file includes several useful constants and macros designed to simplify common programming tasks and enhance code readability. Here are some of the key elements:

#### Global Constants

1. **MAX_STRING_SIZE**
    - `static const size_t MAX_STRING_SIZE = 1000;` - Defines the maximum string size that can be handled by the utility functions, useful for setting buffer sizes and ensuring consistent memory allocation across different string operations.

2. **months**
    - `extern const char *months[12];` - Contains the names of the twelve months of the year, useful for converting numeric month representations into their corresponding textual names.

3. **weekDays**
    - `extern const char *weekDays[7];` - Holds the names of the seven days of the week, useful for mapping numeric day representations to their corresponding day names.

4. **commonDateTimeFormats**
    - `extern const char *commonDateTimeFormats[12];` - Contains string literals representing commonly used date/time formats, crucial for parsing and standardizing date/time strings from various data sources.

#### Macros

1. **ARRAY_SIZE**
    - `#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))` - Computes the number of elements in a statically-allocated array, useful for determining the size of an array at compile time.

2. **VAR_NAME_AS_STRING**
    - `#define VAR_NAME_AS_STRING(var) #var` - Creates a string representation of its argument, useful for debugging and logging purposes.

#### Mutex for Thread Safety

The file also defines a mutex for thread safety when accessing local time functions:
- `static pthread_mutex_t localtime_mutex = PTHREAD_MUTEX_INITIALIZER` - This mutex ensures that access to the `localtime` function is thread-safe, preventing potential data races in multi-threaded applications.






<br/>
<br/>  
<br/>

### General Utilities


#### Time Operations
Conversion between date/time strings and Unix time, thread-safe localtime conversion.
- `time_t convert_to_unix_time(const char *dateTimeString)` - Converts a date/time string into Unix time.
- `struct tm *thread_safe_localtime(const time_t *tim, struct tm *result)` - A thread-safe wrapper around localtime.
<br/>


  


#### Bitwise Operations
- `uint64_t flip_sign_bit(uint64_t value)` - Flips the sign bit of a 64-bit integer.
- `uint64_t double_to_uint64(double value)` - Reinterprets a double as a uint64_t.
- `double uint64_to_double(uint64_t value)` - Reinterprets a uint64_t as a double.
<br/>


  

#### Sorting
- `void merge_sort(double *unsortedData, const int numElements)` - Sorts an array of doubles using the merge sort algorithm.
- `void radix_sort_doubles(double *unsortedData, const int numElements)` - Sorts an array of doubles using radix sort.
<br/>


  

#### Memory Operations
- `void *set_memory_block(void *block, int c, size_t n)` - Sets the first `n` bytes of the memory block to the value specified by `c`.
- `void *copy_memory_block(void *destination, const void *source, size_t n)` - Copies `n` bytes from source to destination.
<br/>













<br/>
<br/>
<br/>

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
<br/>



#### String Properties
- `bool string_is_numeric(const char *characterString)` - Checks if a string represents a numeric value.
- `bool string_is_hyphen_else_is_minus_sign(char *characterString)` - Differentiates between hyphens and minus signs.
- `int *string_is_date_time(const char *characterString, const char *delimiter, const int fieldCount)` - Analyzes a string to detect occurrences of commonly used date/time formats (defined in AuxiliaryUtilities.h).
- `bool string_array_contains_date_time(char **stringArray, int stringCount, const char *delimiter)` - Checks if any string in an array contains a date/time format.
<br/>





#### Counting and Identifying
- `size_t string_length(const char *characterString)` - Returns the length of a character string.
- `int count_array_strings(char **stringArray)` - Counts the number of strings in an array of strings.
- `int count_character_occurrences(const char *characterString, char c)` - Counts occurrences of a character in a string.
- `char find_most_common_non_alphanumeric_character(const char *characterString)` - Finds the most common non-alphanumeric character in a string.
- `char *find_potential_delimiters(const char *characterString, int *delimiterCount)` - Finds potential delimiters in a string.
- `char *identify_delimiter(char **stringArray, int stringCount)` - Identifies the most common delimiter across an array of strings.
- `char *identify_delimiter_recursive(char** stringArray, int stringCount, char **primaryDelimiters, int *primaryDelimiterCount)` - Identifies delimiters recursively, passing in primary delimiters and count by reference.
- `const char *determine_string_representation_type(const char *token)` - Determines if a string is numeric or non-numeric, useful for assessing delimited data fields.
- `int compare_character_strings(const char *characterString1, const char *characterString2)` - Compares two character strings for equality.
- `char *determine_most_common_string(char **stringArray, int stringCount)` - Determines the most common string in an array of strings.
<br/>








#### Copying and Duplicating Strings
- `char *duplicate_string(const char *characterString)` - Duplicates a character string.
- `char *copy_string(char *destination, const char *source)` - Copies a character string.
- `char *copy_n_string(char *destination, const char *source, size_t n)` - Copies up to `n` characters from the string pointed to by `source` to `destination`, padding with null characters if `n` is greater than the length of `source`.
- `char *concatenate_string(char *destination, const char *source)` - Concatenates two character strings.
- `char *concatenate_n_string(char *destination, const char *source, size_t n)` - Concatenates up to `n` characters from the string pointed to by `source` to the end of the string pointed to by `destination`.
<br/>






#### String Manipulation
  

##### Combining and Concatenating Strings
- `char *combine_strings(const char *characterString1, const char *characterString2)` - Returns a new string with contents of the second string appended to the first.
- `char **combine_string_arrays(const char **stringArray1, int stringCountArray1, const char **stringArray2, int stringCountArray2)` - Combines two arrays of strings.
- `char *append_string_array_to_string(const char *characterString1, const char *characterStringArray[], int numArrayStrings, const char *delimiter)` - Combines each string in the array with the original string to return a single string having the contents of the original string with each string from the array appended to it separated by the specified delimiter.
- `char *concatenate_string_array(const char** stringArray, int stringCount, const char *delimiter)` - Concatenates an array of strings into a single string with elements/fields separated by the specified delimiter.
<br/>




##### Tokenizing and Segmenting Strings

- `char *tokenize_string(char *s, const char *delim)` - Tokenizes a character string based on a delimiter.
- `char **split_tokenized_string(const char* characterString, const char* delimiter, int divisions)` - Splits a tokenized string into an array of strings based on a given delimiter.

<br/>



  

##### Trimming and Pruning Strings


- `char *trim_string_whitespaces(char *untrimmedString)` - Trims whitespace from a string.
- `char *prune_string_whitespaces(char *unprunedString)` - Removes all whitespaces from a string.
- `char *prune_repeated_delimiters_from_string(char *unprunedString, const char *delimiter)` - Handles repeated delimiters in a string.
- `char *prune_and_trim_problematic_characters_from_string(char *originalString, const char *delimiter, const int fieldCount)` - Prunes and trims problematic characters.
  
<br/>




##### Formatting Strings

  

- `char *replace_date_time_with_unix(char *characterString, const char *delimiter, const int fieldCount)` - Replaces date/time with Unix time in a string.
- `char **preprocess_string_array(char **stringArray, int stringCount, const char *delimiter)` - Preprocesses an array of strings, trimming and pruning whitespaces, repeated delimiters, and standardizing some variable parameters.
  





<br/>
<br/>
<br/>

## Documentation and Examples

For detailed documentation of each function, please refer to the comments in the source files `AuxiliaryUtilities.h`, `AuxiliaryUtilities.c`, `StringUtilities.h`, and `StringUtilities.c`. Refer to the `main.c` file for example usage of the library functions.



  
<br/>

## Contributing

Contributions to the C-String Utilities Library are welcome. If you have any bug reports, feature requests, or improvements, please open an issue or submit a pull request on GitHub.

<br/>
<br/>


### NOTE
For the sake of brevity, some of the less interesting sections were omitted from this README, among them include:
- Memory Allocation Functions for allocating and deallocating memory for basic and derived types.
- Mathematical Operations Functions for finding minimum and maximum values, both overall and within arrays.
- Printing functions various representations of strings and arrays.
<br/>
