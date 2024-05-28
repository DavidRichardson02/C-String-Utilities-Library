



# C-String Utilities Library

## Overview
The C-String Utilities Library provides a comprehensive suite of utilities for string manipulation and analysis, as well as auxiliary functions and definitions for performing various computational tasks 
This library is designed to aid in data parsing, preprocessing, and various computational tasks that involve strings and/or memory operations,
it includes functions for general computational tasks, memory management, mathematical operations, time conversions, bitwise operations, sorting algorithms, and extensive string handling. 
This library is particularly useful for data parsing and preprocessing in contexts where string data must be examined, transformed, or formatted before being used in computations or visualizations.
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

1. **AuxiliaryUtilities.h** - Header file for auxiliary utilities, declares functions and global constants for general utility purposes.
2. **AuxiliaryUtilities.c** - Implementation file for auxiliary utilities.
3. **StringUtilities.h** - Header file for string utilities, declares functions for string manipulation and analysis.
4. **StringUtilities.c** - Implementation file for string utilities.





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
3. Include the header files in your C project and compile the source files along with your project files.:
    ```c
    #include "AuxiliaryUtilities.h"
    #include "StringUtilities.h"
    ```







## Functions

### Auxiliary Utilities
### Global Constants and Macros

The `AuxiliaryUtilities.h` file includes several useful constants and macros designed to simplify common programming tasks and enhance code readability. Here are some of the key elements:

#### Global Constants

1. **MAX_STRING_SIZE**
    ```c
    static const size_t MAX_STRING_SIZE = 1000;
    ```
    This constant defines the maximum string size that can be handled by the utility functions. It's useful for setting buffer sizes and ensuring consistent memory allocation across different string operations.

2. **months**
    ```c
    extern const char *months[12];
    ```
    This array contains the names of the twelve months of the year. It is useful for converting numeric month representations into their corresponding textual names.

3. **weekDays**
    ```c
    extern const char *weekDays[7];
    ```
    This array holds the names of the seven days of the week. It can be used to map numeric day representations to their corresponding day names.

4. **commonDateTimeFormats**
    ```c
    extern const char *commonDateTimeFormats[12];
    ```
    This array contains string literals representing commonly used date/time formats. These formats are crucial for parsing and standardizing date/time strings from various data sources. Each format specifier adheres to the C standard library conventions for date/time formatting.

#### Macros

1. **ARRAY_SIZE**
    ```c
    #define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
    ```
    This macro computes the number of elements in a statically-allocated array. It is useful for determining the size of an array at compile time, enhancing code readability and preventing off-by-one errors.

2. **VAR_NAME_AS_STRING**
    ```c
    #define VAR_NAME_AS_STRING(var) #var
    ```
    This macro creates a string representation of its argument. It can be used to convert variable names to strings, which is particularly useful for debugging and logging purposes.

### Mutex for Thread Safety

The file also defines a mutex for thread safety when accessing local time functions:

```c
static pthread_mutex_t localtime_mutex = PTHREAD_MUTEX_INITIALIZER;
```

This mutex ensures that access to the `localtime` function is thread-safe, preventing potential data races in multi-threaded applications.

### Summary

These global constants, macros, and mutexes provide a foundation for the utility functions in the library, enhancing code readability, memory management, date/time handling, and thread safety. They are integral parts of the `AuxiliaryUtilities` module, ensuring that common tasks are performed efficiently and consistently.













## Usage

### General Utilities

#### Memory Allocation
 Functions for allocating and deallocating memory for basic and derived types.
Allocate memory for basic types:
```c
int *intPtr = allocate_memory_int_ptr(sizeI);
float *floatPtr = allocate_memory_float_ptr(sizeF);
double *doublePtr = allocate_memory_double_ptr(sizeD);
char *charPtr = allocate_memory_char_ptr(sizeC);
```

Allocate memory for derived types:
```c
int **intPtrPtr = allocate_memory_int_ptr_ptr(sizeI);
float **floatPtrPtr = allocate_memory_float_ptr_ptr(sizeF);
double **doublePtrPtr = allocate_memory_double_ptr_ptr(sizeD);
char **charPtrPtr = allocate_memory_char_ptr_ptr(strSize, numStrings);
```

Deallocate memory for derived types:
```c
deallocate_memory_int_ptr_ptr(intPtrPtr, numInts);
deallocate_memory_float_ptr_ptr(floatPtrPtr, numFloats);
deallocate_memory_double_ptr_ptr(doublePtrPtr, numDoubles);
deallocate_memory_char_ptr_ptr(charPtrPtr, numStrings);
```




#### Mathematical Operations
Functions for finding minimum and maximum values, both overall and within arrays.
Perform mathematical operations on containers:

- `double min(double a, double b)` - Returns the minimum of two values.
- `double max(double a, double b)` - Returns the maximum of two values.
- `double min_element(double *data, int n)` - Returns the minimum element in an array.
- `double max_element(double *data, int n)` - Returns the maximum element in an array.

```c
double minVal = min(a, b);
double maxVal = max(a, b);
double minElem = min_element(data, n);
double maxElem = max_element(data, n);
```




#### Time Operations
Conversion between date/time strings and Unix time, thread-safe localtime conversion.
Convert date/time strings to Unix time:

- `time_t convert_to_unix_time(const char *dateTimeString)` - Converts a date/time string into Unix time.
- `struct tm *thread_safe_localtime(const time_t *tim, struct tm *result)` - A thread-safe wrapper around localtime.

```c
time_t unixTime = convert_to_unix_time(dateTimeString);
struct tm result;
struct tm *localTime = thread_safe_localtime(&tim, &result);
```




#### Bitwise Operations
 Manipulation of double precision floating-point numbers through their binary representation.
Perform bitwise operations on numerical data:

- `uint64_t flip_sign_bit(uint64_t value)` - Flips the sign bit of a 64-bit integer.
- `uint64_t double_to_uint64(double value)` - Reinterprets a double as a uint64_t.
- `double uint64_to_double(uint64_t value)` - Reinterprets a uint64_t as a double.

```c
uint64_t flippedValue = flip_sign_bit(value);
uint64_t intValue = double_to_uint64(value);
double doubleValue = uint64_to_double(intValue);
```




#### Sorting
Sort arrays using robust sorting algorithms merge sort or radix sort:
- `void merge_sort(double *unsortedData, const int numElements)` - Sorts an array of doubles using the merge sort algorithm.
- `void radix_sort_doubles(double *unsortedData, const int numElements)` - Sorts an array of doubles using radix sort.

```c
merge_sort(unsortedData, numElements);
radix_sort_doubles(unsortedData, numElements);
```




#### Memory Operations

Functions for setting and copying memory blocks.
- `void *set_memory_block(void *block, int c, size_t n)` - Sets the first `n` bytes of the memory block to the value specified by `c`.
- `void *copy_memory_block(void *destination, const void *source, size_t n)` - Copies `n` bytes from source to destination.

```c
set_memory_block(&tm, 0, sizeof(struct tm)); // Reset the tm structure for each iteration.
copy_memory_block(&destination, source, sizeof(n));
```












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

```c
bool isAlpha = char_is_alpha(c);
bool isDigit = char_is_digit(c);
bool isAlnum = char_is_alnum(c);
bool isWhitespace = char_is_whitespace(c);
bool isPunctuation = char_is_punctuation(c);
bool isUnderscore = char_is_underscore(c);
bool isSign = char_is_sign(c);
bool isDelimiter = char_is_delimiter(c);
```




#### String Properties
- `bool string_is_numeric(const char *characterString)` - Checks if a string represents a numeric value.
- `bool string_is_hyphen_else_is_minus_sign(char *characterString)` - Differentiates between hyphens and minus signs.
- `int *string_is_date_time(const char *characterString, const char *delimiter, const int fieldCount)` - Analyzes a string to detect occurences of commonly used date/time formats(defined in AuxiliaryUtilities.h).
- `bool string_array_contains_date_time(char **stringArray, int stringCount, const char *delimiter)` - Checks if any string in an array contains a date/time format.

```c
bool isNumeric = string_is_numeric(characterString);
bool isHyphen = string_is_hyphen_else_is_minus_sign(characterString);
int *dateTimeFields = string_is_date_time(characterString, delimiter, fieldCount);
bool containsDateTime = string_array_contains_date_time(stringArray, stringCount, delimiter);
```




#### Counting and Identifying
- `size_t string_length(const char *characterString)` - Returns the length of a character string.
- `int count_array_strings(char **stringArray)` - Counts the number of strings in an array of strings.
- `int count_character_occurrences(const char *characterString, char c)` - Counts occurrences of a character in a string.
- `char find_most_common_non_alphanumeric_character(const char *characterString)` - Finds the most common non-alphanumeric character in a string.
- `char *find_potential_delimiters(const char *characterString, int *delimiterCount)` - Finds potential delimiters in a string.
- `char *identify_delimiter(char **stringArray, int stringCount)` - Identifies the most common delimiter across an array of strings.
- `char *identify_delimiter_recursive(char** stringArray, int stringCount, char **primaryDelimiters, int *primaryDelimiterCount)` - Pass in primary delimiters(and count) by reference... a special case function
- `const char *determine_string_representation_type(const char *token)` - Determines if a string is numeric or non-numeric, FYI this function was made with the intention of passing in delimited data fields and individually assessing their type.

```c
size_t length = string_length(characterString);
int stringCount = count_array_strings(stringArray);
int occurrences = count_character_occurrences(characterString, c);
char commonChar = find_most_common_non_alphanumeric_character(characterString);
char *delimiters = find_potential_delimiters(characterString, &delimiterCount);
char *delimiter = identify_delimiter(stringArray, stringCount);
char *delimiterRecursive = identify_delimiter_recursive(stringArray, stringCount, primaryDelimiters, primaryDelimiterCount);
const char* type = determine_string_representation_type(token);
```








#### String Operations


#### Copying and Duplicating Strings
- `char *duplicate_string(const char *characterString)`- Duplicates a character string.
- `char *copy_string(char *destination, const char *source)`- Copies a character string.
- `char *copy_n_string(char *destination, const char *source, size_t n)`- Copies up to n characters from the string pointed to by 'source' and to 'destination', where any n greater than the length of 'source' is padded with null characters.
- `char *concatenate_string(char *destination, const char *source)`- Concatenates two character strings.
- `char *concatenate_n_string(char *destination, const char *source, size_t n)` - Concatenates up to n characters from the string pointed to by 'source' to the end of the string pointed to by 'destination'.

```c
char *dupString = duplicate_string(characterString);
char *copiedString = copy_string(destination, source);
char *concatenatedString = concatenate_string(destination, source);
```




#### String Comparison
- `int compare_character_strings(const char *characterString1, const char *characterString2)` - Compares two character strings for equality.
- `char *determine_most_common_string(char **stringArray, int stringCount)` - Determines the most common string in an array of strings.

```c
int cmpResult = compare_strings(characterString1, characterString2);
char *commonDataType = determine_most_common_string(stringArray, stringCount);
```



#### String Manipulation

Manipulate strings and arrays:


##### Combining and Concatenating Strings
- `char *combine_strings(const char *characterString1, const char *characterString2)` - Returns a new string with contents of the second string appended to the first.
- `char **combine_string_arrays(const char **stringArray1, int stringCountArray1, const char **stringArray2, int stringCountArray2)` - // Combines two arrays of strings.
- `char *append_string_array_to_string(const char *characterString1, const char *characterStringArray[], int numArrayStrings, const char *delimiter)` - Combines each string in the array with the original string to return a single string having the contents of the original string with each string from the array appended to it seperated by the specified delimiter.
- `char *concatenate_string_array(const char** stringArray, int stringCount, const char *delimiter)` - Concatenates an array of strings into a single string with elements/fields seperated by the specified delimiter

```c
char *combinedString = combine_strings(characterString1, characterString2);
char **combinedArrays = combine_string_arrays(stringArray1, stringCountArray1, stringArray2, stringCountArray2);
char *appendedString = append_string_array_to_string(characterString1, stringArray, numArrayStrings, delimiter);
char *concatenatedArray = concatenate_string_array(stringArray, stringCount, delimiter);
```


##### Tokenizing and Segmenting Strings
- `char *tokenize_string(char *s, const char *delim)` - Tokenizes a character string based on a delimiter.
- `char **split_tokenized_string(const char* characterString, const char* delimiter, int divisions)` - Splits a tokenized string into an array of strings based on a given delimiter.

```c
char *token = tokenize_string(s, delim);
char **splitStrings = split_tokenized_string(characterString, delimiter, divisions);
```


##### Trimming and Pruning Strings
- `char *trim_string_whitespaces(char *untrimmedString)` - Trims whitespace from a string.
- `char *prune_string_whitespaces(char *unprunedString)` - Removes all whitespaces from a string.
- `char *prune_repeated_delimiters_from_string(char *unprunedString, const char *delimiter)` - Handles repeated delimiters in a string.
- `char *prune_and_trim_problematic_characters_from_string(char *originalString, const char *delimiter, const int fieldCount)` - Prunes and trims problematic characters.

```c
char *trimmedString = trim_string_whitespaces(untrimmedString);
char *prunedString = prune_string_whitespaces(unprunedString);
char *prunedDelimiterString = prune_repeated_delimiters_from_string(unprunedString, delimiter);
char *processedString = prune_and_trim_problematic_characters_from_string(originalString, delimiter, fieldCount);
```


##### Formatting Strings
- `char *replace_date_time_with_unix(char *characterString, const char *delimiter, const int fieldCount)` - Replaces date/time with Unix time in a string.
- `char **preprocess_string_array(char **stringArray, int stringCount, const char *delimiter)` - Preprocesses an array of strings, trimming and pruning whitespaces, repeated delimiters, and standardizing some variable parameters/

```c
char *unixTimeString = replace_date_time_with_unix(characterString, delimiter, fieldCount);
char **processedArray = preprocess_string_array(stringArray, stringCount, delimiter);
```




#### Printing
Print various representations of strings and arrays:
```c
print_string(string);
print_string_array(stringArray, stringCount, label);
print_string_array_array(stringArrayArray, stringArraysCount, stringSubArraysCount, label);
print_array(n, data, label);
print_array_array(data, rows, columns, label);
print_char_ptr_array(charPtrArr, stringCount, label);
```







## Documentation and Examples

For detailed documentation of each function, please refer to the comments in the source files `AuxiliaryUtilities.h`, `AuxiliaryUtilities.c`, `StringUtilities.h`, and `StringUtilities.c`.
For  to the `main.c` file for example usage of the library functions.






## Contributing
Contributions to the C-String Utilities Library are welcome. If you have any bug reports, feature requests, or improvements, please open an issue or submit a pull request on GitHub.
