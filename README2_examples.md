
  
<br/>

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
```c
double minVal = min(a, b);
double maxVal = max(a, b);
double minElem = min_element(data, n);
double maxElem = max_element(data, n);
```
<br/>




<br/>

#### Time Operations
Conversion between date/time strings and Unix time, thread-safe localtime conversion.
```c
time_t unixTime = convert_to_unix_time(dateTimeString);
struct tm result;
struct tm *localTime = thread_safe_localtime(&tim, &result);
```
  <br/>





#### Bitwise Operations

Manipulation of double precision floating-point numbers through their binary representation.
```c
uint64_t flippedValue = flip_sign_bit(value);
uint64_t intValue = double_to_uint64(value);
double doubleValue = uint64_to_double(intValue);
```
<br/>




#### Sorting

Sort arrays using robust sorting algorithms merge sort or radix sort:

```c
merge_sort(unsortedData, numElements);
radix_sort_doubles(unsortedData, numElements);
```
<br/>




#### Memory Operations

Functions for setting and copying memory blocks.

```c
set_memory_block(&tm, 0, sizeof(struct tm)); // Reset the tm structure for each iteration.
copy_memory_block(&destination, source, sizeof(n));
```
<br/>










  
<br/>

### String Utilities
  

#### Character Properties

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
<br/>




#### String Properties

```c
bool isNumeric = string_is_numeric(characterString);
bool isHyphen = string_is_hyphen_else_is_minus_sign(characterString);
int *dateTimeFields = string_is_date_time(characterString, delimiter, fieldCount);
bool containsDateTime = string_array_contains_date_time(stringArray, stringCount, delimiter);
```
<br/>




#### Counting and Identifying
  
<br/>

```c
size_t length = string_length(characterString);
int stringCount = count_array_strings(stringArray);
int occurrences = count_character_occurrences(characterString, c);
char commonChar = find_most_common_non_alphanumeric_character(characterString);
char *delimiters = find_potential_delimiters(characterString, &delimiterCount);
char *delimiter = identify_delimiter(stringArray, stringCount);
char *delimiterRecursive = identify_delimiter_recursive(stringArray, stringCount, primaryDelimiters, primaryDelimiterCount);
const char* type = determine_string_representation_type(token);
int cmpResult = compare_character_strings(characterString1, characterString2);
char *commonDataType = determine_most_common_string(stringArray, stringCount);
```
<br/>





  


#### Copying and Duplicating Strings

```c
char *dupString = duplicate_string(characterString);
char *copiedString = copy_string(destination, source);
char *concatenatedString = concatenate_string(destination, source);
```
  <br/>









#### String Manipulation
  

##### Combining and Concatenating Strings
```c
char *combinedString = combine_strings(characterString1, characterString2);
char **combinedArrays = combine_string_arrays(stringArray1, stringCountArray1, stringArray2, stringCountArray2);
char *appendedString = append_string_array_to_string(characterString1, stringArray, numArrayStrings, delimiter);
char *concatenatedArray = concatenate_string_array(stringArray, stringCount, delimiter);
```
<br/>





##### Tokenizing and Segmenting Strings
```c
char *token = tokenize_string(s, delim);
char **splitStrings = split_tokenized_string(characterString, delimiter, divisions);
```
<br/>








##### Trimming and Pruning Strings

```c
char *trimmedString = trim_string_whitespaces(untrimmedString);
char *prunedString = prune_string_whitespaces(unprunedString);
char *prunedDelimiterString = prune_repeated_delimiters_from_string(unprunedString, delimiter);
char *processedString = prune_and_trim_problematic_characters_from_string(originalString, delimiter, fieldCount);
```
<br/>





##### Formatting Strings
```c
char *unixTimeString = replace_date_time_with_unix(characterString, delimiter, fieldCount);
char **processedArray = preprocess_string_array(stringArray, stringCount, delimiter);
```

<br/>





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

