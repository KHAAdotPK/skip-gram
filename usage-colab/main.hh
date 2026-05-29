/*
 * usage/main.hh
 * Q@hackers.pk
 */

#include <iostream>

#ifndef USAGE_MAIN_HH
#define USAGE_MAIN_HH

#ifdef CSV_PARSER_TOKEN_DELIMITER
#undef CSV_PARSER_TOKEN_DELIMITER
#endif
#define CSV_PARSER_TOKEN_DELIMITER ' '

#ifndef ITERATOR_GUARD_AGAINST_EMPTY_STRING 
#define ITERATOR_GUARD_AGAINST_EMPTY_STRING
#endif

#ifndef ITERATOR_USER_DEFINED_CLEANER_CODE
#define ITERATOR_USER_DEFINED_CLEANER_CODE
#endif

#define CORPUS_SERIALIZATION_CHECKPOINT_INTERVAL 20000
#define KEYS_LOAD_FACTOR_THRESHOLD 0.90f
//#define KEYS_COMMON_STARTING_SIZE 76963 // Prime number, Option 3
//#define KEYS_COMMON_STARTING_SIZE 120003 // Prime number, Option 4
#define KEYS_COMMON_STARTING_SIZE 80003 // Prime number, Option 5

#define CONTEXT_WINDOW_SIZE 2 // Number of tokens to the left and the number of tokens to the right of the target/center token to include in the context of that center/target word/token

#include "../lib/Numcy/header.hh"
#include "../lib/Hash/header.hh"
#include "../lib/Imprint/header.hh"
/*
    You can also include lib/Corpus/header.hh and lib/Parser/header.hh in any order
    without affecting the functionality of the program. This is because:
        1. Corpus/header.hh includes Parser/header.hh and vice versa
        2. Parser/Parser.hh includes Corpus/Serialisation.hh
        3. Corpus/Serialisation.hh includes Parser/WordRecord.hh
        
    Read Circular-Dependency.md for more information        
*/
#include "../lib/Corpus/header.hh"
#include "../lib/Parser/header.hh"

#include "../lib/Pairs/header.hh"

#endif


