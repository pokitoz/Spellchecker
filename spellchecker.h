#ifndef SPELLCHECKER_H__
#define SPELLCHECKER_H__


/* If the file contains a word larger than 64 chracters;
 * the word will be read as follow: read first 64 characters
 * stop, process the 'half' word, then continue until a white character.
 * So the word will be broken into 64 chunks or less.
 * This is to avoid overflow.
 * The +1 is for the '\0' character at the end of a string
 */
#define SPELLCHECKER_MAX_WORD_SIZE 64
#define SPELLCHECKER_WORD_ARRAY_SIZE (SPELLCHECKER_MAX_WORD_SIZE+1)
#define SPELLCHECKER_INPUT_STRING_FMT(x) "%" #x "s"

#define FORMAT_STRING_APPEND(x) #x
#define FORMAT_EVAL_STRING(x) FORMAT_STRING_APPEND(x)
#define SPELLCHECKER_SCANF_FORMAT(x) "%" FORMAT_EVAL_STRING(x) "s"
#define SPELLCHECKER_INPUT_STRING_FORMAT \
		SPELLCHECKER_SCANF_FORMAT(SPELLCHECKER_MAX_WORD_SIZE)

void util_toLowerCase(char* word);
int util_isNumber(char* word);
int util_containsDigit(char* word);
void util_removeSpecialCharacter(char* word);

#endif
