#include <stdio.h>
#include <fstream>
#include <string.h>
#include <set>

const int BUFSIZE = 500;

using namespace std;

int main(int argc, char** argv) {

	if(argc == 1) {

		printf("Please provide a document to parse\n");
		return 0;
	}
	
	ifstream file;

	file.open(argv[1]);

	if(file.good()) {

		const char* ignored_words[] = {
			"I", "We", "You", "They",
			"a", "and", "the", "that",
			"of", "for", "with"
		};

		set<string> ignored_words_set(ignored_words, ignored_words+11);

		char buf[BUFSIZE];
		char* word;
		int line_count = 0;
		int word_count = 0;
		int byte_count = 0;
		int proper_word_count = 0;
		int proper_byte_count = 0;

		while(file.getline(buf, BUFSIZE)) {
			
			line_count++;
			
			// Counts bytes in a line including null and newline character
			byte_count += strlen(buf) + 1;
			proper_byte_count += strlen(buf) + 1;
			
			// Break up lines into words. Words may still contain ',.;' characters
			word = strtok(buf, " ");

			while(word != NULL) {

				word_count++;

				if(!ignored_words_set.count(word)) {
					proper_word_count++;
				}
				else {
					proper_byte_count -= strlen(word) + 1;
				}

				word = strtok(NULL, " ");
			}
		}

		printf(" all: %d %d %d %s\n", line_count, word_count, byte_count, argv[1]);
		printf(" proper: %d %d %d\n", line_count, proper_word_count, proper_byte_count);
		
	}
	else {

		printf("Error: File does not exist\n");
	}

	file.close();

	return 0;
}
