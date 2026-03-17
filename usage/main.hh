/*
    usage/main.hh
    Q@khaa.pk
 */

/*
    Model Notes:- 
    1. Note on Loss Values: Don't expect the loss to ever hit zero. In Skip-gram with Negative Sampling,
       a total loss around 10–15 is often the "global minimum" because natural language is inherently fuzzy
       (a word can't be 100% related to one word and 0% related to all others).
 */ 

#include <iostream>

#include "../lib/argsv-cpp/lib/parser/parser.hh"
#include "../lib/sundry/cooked_read_new.hh"
#include "../lib/sundry/cooked_write_new.hh"
#include "../lib/read_write_weights/header.hh"

#ifndef WORD_EMBEDDING_ALGORITHMS_SKIP_GRAM_USAGE_MAIN_HH
#define WORD_EMBEDDING_ALGORITHMS_SKIP_GRAM_USAGE_MAIN_HH

#define SKIP_GRAM_DEFAULT_CORPUS_FILE ".\\data\\corpus.txt"
#define TRAINED_INPUT_WEIGHTS_FILE_NAME     "W1trained.dat"
#define TRAINED_OUTPUT_WEIGHTS_FILE_NAME    "W2trained.dat"
#define INITIAL_W1_WEIGHT_TXT_FILE          "W1initial.txt"
#define INITIAL_W2_WEIGHT_TXT_FILE          "W2initial.txt"
#define TRAINED_W1_WEIGHT_TXT_FILE          "W1trained.txt"
#define TRAINED_W2_WEIGHT_TXT_FILE          "W2trained.txt"
#define DEFAULT_PAIRS_FILE_NAME             "pairs.dat"

#ifdef GRAMMAR_END_OF_TOKEN_MARKER
#undef GRAMMAR_END_OF_TOKEN_MARKER
#endif
#define GRAMMAR_END_OF_TOKEN_MARKER ' '

#ifdef GRAMMAR_END_OF_LINE_MARKER
#undef GRAMMAR_END_OF_LINE_MARKER
#endif
#define GRAMMAR_END_OF_LINE_MARKER '\n'

#ifdef SKIP_GRAM_EMBEDDNG_VECTOR_SIZE
#undef SKIP_GRAM_EMBEDDNG_VECTOR_SIZE
#endif
#define SKIP_GRAM_EMBEDDNG_VECTOR_SIZE 8

// Start with small values (e.g., 0.001) and adjust based on performance.
#ifdef SKIP_GRAM_REGULARIZATION_STRENGTH
#undef SKIP_GRAM_REGULARIZATION_STRENGTH
#endif
#define SKIP_GRAM_REGULARIZATION_STRENGTH 0.001

#ifdef SKIP_GRAM_CONTEXT_WINDOW_SIZE
#undef SKIP_GRAM_CONTEXT_WINDOW_SIZE
#endif
#define SKIP_GRAM_CONTEXT_WINDOW_SIZE 1

#ifdef SKIP_GRAM_WINDOW_SIZE
#undef SKIP_GRAM_WINDOW_SIZE
#endif
#define SKIP_GRAM_WINDOW_SIZE 1

#ifdef SKIP_GRAM_CLIP_GRADIENTS_DEFAULT_THRESHOLD
#undef SKIP_GRAM_CLIP_GRADIENTS_DEFAULT_THRESHOLD
#endif
#define SKIP_GRAM_CLIP_GRADIENTS_DEFAULT_THRESHOLD 5.0

/*
    If you want the learning rate to remain constant throughout training, set the learning rate decay factor to 1
 */
#ifdef SKIP_GRAM_LEARNING_RATE_DECAY
#undef SKIP_GRAM_LEARNING_RATE_DECAY
#endif
#define SKIP_GRAM_LEARNING_RATE_DECAY 0.99

#define DEFAULT_TRAINING_LOOP_PATIENCE 3

#ifdef SKIP_GRAM_DEFAULT_NUMBER_OF_NEGATIVE_SAMPLES
#undef SKIP_GRAM_DEFAULT_NUMBER_OF_NEGATIVE_SAMPLES 
#endif
#define SKIP_GRAM_DEFAULT_NUMBER_OF_NEGATIVE_SAMPLES 0

//#include "../lib/argsv-cpp/lib/parser/parser.hh"
//#include "../lib/sundry/cooked_read_new.hh"
//#include "../lib/sundry/cooked_write_new.hh"
//#include "../lib/read_write_weights/header.hh"
#include "../lib/WordEmbedding-Algorithms/Word2Vec/Skip-gram/header.hh"

#define COMMAND "h -h help --help ? /? (Displays the help screen, listing available commands and their descriptions.)\n\
v -v version --version /v (Shows the current version of the software.)\n\
e epoch --epoch /e (Sets the epoch count, determining the number of iterations for the training loop.)\n\
corpus --corpus (Specifies the path to the file containing the training data.)\n\
verbose --verbose (Enables detailed output for each operation during execution.)\n\
lr --lr learningrate (Defines the learning rate parameter to control the rate of convergence.)\n\
rs --rs (Sets the regularization strength, used to prevent overfitting.)\n\
loop --loop (Repeats the training loop on previously trained weights at least one additional time.)\n\
batch --batch (Loads initial weights from a specified file, allowing batch processing with predefined starting weights.)\n\
input --input (Specifies the filenames to retrieve the partially input and output trained weights during training.)\n\
output --output (Specifies the filenames to store the input and output trained weights after completion of training.)\n\
ns --ns negative_sampling --negative_sampling (This flag enables negative sampling. It is the process of approximating the softmax function by just drawing a few examples from the set of samples that do not appear in the context of the main word.)\n\
show_pairs --show_pairs (Displays pairs of target/center words and their surrounding context words. The number of context words for each target word is determined by the macro SKIP_GRAM_WINDOW_SIZE, which is a configurable hyperparameter)\n\
save_initial_weights --save_initial_weights (Saves the initial \"randomly initialized weights\" for the embedding matrices W1 W2 to the files before training begins.)\n\
shuffle_target_context_pairs --shuffle_target_context_pairs (Shuffles the target/center word and its context words during training, at the start of each new epoch begins.)\n\
random_number_generator_seed --random_number_generator_seed (Sets the seed for the random number generator.)\n\
learning_rate_decay --learning_rate_decay lr_decay --lr_decay learning_rate_scheduling --learning_rate_scheduling (It is a technique in ML where the learning rate gradually decreases over time during training, typically starting with a larger value to allow for bigger parameter updates and faster initial learning. This command optionaly accepts an argument. If you want the learning rate to remain constant throughout training, set the learning rate decay factor to 1)\n\
clip_gradients_threshold --clip_gradients_threshold (Enable and optinally sets threshold for gradient clipping to prevent exploding gradients, recommended: 1.0–5.0.)\n\
write_pairs --write_pairs (Writes the pairs of target/center words and their surrounding context words to a file.)\n\
read_pairs --read_pairs (Reads the pairs of target/center words and their surrounding context words from a file.)\n"

#endif