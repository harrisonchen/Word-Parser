#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <set>
#include <map>
#include <list>

using namespace std;

// IGNORED WORD SET
const char* ignored_words[] = {
	"I", "We", "You", "They",
	"a", "and", "the", "that",
	"of", "for", "with"
};

const int BUFSIZE = 500;

// Checks if line segment represents the start of an Article.
// @param{line} : sentence line segment to be parsed.
// @param{article} : sets to which article it is once determined.
bool isArticle(char* line, char* article) {

	char temp[BUFSIZE];
	strcpy(temp, line);

	char* word = strtok(line, " ");

	if(strcmp(word, "Article") == 0) {

		word = strtok(NULL, " ");

		if(word != NULL) {
			if(isdigit(word[0])) {
				if(strtok(NULL, " ") == NULL) {
					temp[strlen(temp)-1] = '\0';
					strcpy(article, temp);
					return true;
				}
			}
		}	
	}
	
	return false;
}

// Checks if line segment represents the start of a Section
// @param{line} : sentence line segment to be parsed.
bool isSection(char* line) {

	char* word = strtok(line, " ");

	if(strcmp(word, "Section") == 0) {

		word = strtok(NULL, " ");

		if(word != NULL) {
			if(isdigit(word[0])) {
				if(strtok(NULL, " ") == NULL) {
					return true;
				}
			}
		}	
	}
	
	return false;
}

// Increments Section count of the Article by 1
// @param{sections_per_article} : map of all pairs of articles and sections.
// @param{article} : the article for which its section is to be incremented.
void addSection(map<char*, int> &sections_per_article, char* article) {
	
	map<char*, int>::iterator it = sections_per_article.find(article);
	it->second = it->second + 1;
}

int main(int argc, char** argv) {

	if(argc == 1) {

		printf("Please provide a document to parse\n");
		return 0;
	}
	
	ifstream file;

	file.open(argv[1]);

	if(file.good()) {

		set<string> ignored_words_set(ignored_words, ignored_words+11);

		char buf[BUFSIZE];
		char buf_copy[BUFSIZE];
		char* word;
		int line_count = 0;
		int word_count = 0;
		int byte_count = 0;
		int proper_word_count = 0;
		int proper_byte_count = 0;
		int total_articles = 0;
		int total_sections = 0;
		bool article_flag = false;
		bool section_flag = false;
		char article[BUFSIZE];
		char* new_article;
		map<char*, int> sections_per_article;

		while(file.getline(buf, BUFSIZE)) {

			strcpy(buf_copy, buf);
			
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

				if(strcmp(word, "Article") == 0) {
					article_flag = true;
				}
				else if(strcmp(word, "Section") == 0) {
					section_flag = true;
				}

				word = strtok(NULL, " ");
			}

			if(article_flag) {
				
				if(isArticle(buf_copy, article)) {
					total_articles++;
					new_article = new char[BUFSIZE];
					strcpy(new_article, article);
					sections_per_article.insert(pair<char*, int>(new_article, 0));
				}
				article_flag = false;
			}
			else if(section_flag) {

				if(isSection(buf_copy)) {
					total_sections++;
					addSection(sections_per_article, new_article);
				}
				section_flag = false;
			}
		}

		printf(" all: %d %d %d %s\n", line_count, word_count, byte_count, argv[1]);
		printf(" proper: %d %d %d\n", line_count, proper_word_count, proper_byte_count);
		printf(" Total Articles: %d\n", total_articles);
		printf(" Total Sections: %d\n", total_sections);
		printf(" Total Sections per Article:\n");
		
		for(map<char*, int>::iterator it = sections_per_article.begin();
				it != sections_per_article.end(); ++it) {
			printf("     %s: %d\n", it->first, it->second);
		}
		
	}
	else {

		printf("Error: File does not exist\n");
	}

	file.close();

	return 0;
}
