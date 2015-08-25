
#include <iostream>
#include <random>
#include <string>
#include <cstring>
#include <cassert>

bool first_is_letter   = false;
bool use_mixed_case    = false;
bool use_numbers       = false;

int  max_punctuation   = 2;
int  length            = 15;
int  count             = 10;

void usage(const char *argv0) {
	printf("usage: %s [OPTIONS]\n", argv0);
	printf("--help                  : display this message\n");
	printf("--first-is-letter       : create passwords which begin with a letter\n");
	printf("--mixed-case            : create passwords which have both lower and upper case letters\n");
	printf("--include-digits        : create passwords which have digits in them\n");
	printf("--count <int>           : create <int> passwords (default 10)\n");
	printf("--length <int>          : create passwords of <int> length (default 15)\n");
	printf("--max-punctuation <int> : use at most <int> punctuation characters per password (default 2)\n");
	exit(0);
}

int main(int argc, char *argv[]) {


	for(int i = 1; i < argc; ++i) {
		const char *const arg = argv[i];
		if(strcmp(arg, "--first-is-letter") == 0) {
			first_is_letter = true;
		} else if(strcmp(arg, "--mixed-case") == 0) {
			use_mixed_case = true;
		} else if(strcmp(arg, "--include-digits") == 0) {
			use_numbers = true;
		} else if(strcmp(arg, "--help") == 0) {
			usage(argv[0]);
		} else if(strcmp(arg, "--count") == 0) {
			if(i == (argc - 1)) {
				usage(argv[0]);
			}
			count = atoi(argv[++i]);
			assert(count > 0);
		} else if(strcmp(arg, "--length") == 0) {
			if(i == (argc - 1)) {
				usage(argv[0]);
			}
			length = atoi(argv[++i]);
			assert(length > 0);
			
		} else if(strcmp(arg, "--max-punctuation") == 0) {
			if(i == (argc - 1)) {
				usage(argv[0]);
			}
			max_punctuation = atoi(argv[++i]);	
		} else {
			usage(argv[0]);
		}
		
	}

	const char alphabet_l[]  = "abcdefghijklmnopqrstuvwxyz";
	const char alphabet_h[]  = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const char digits[]      = "0123456789";
	//const char punctuation[] = "!@#$%^&*()_-=+{[}]:;\"'<,>.?/`~|\\";
	const char punctuation[] = "%&_?#=-";
	
	
	// similar
	// i, l, o, 1, 0, I
	
	std::string set;
	set.append(punctuation);
	set.append(alphabet_l);
	
	if(use_mixed_case) {
		set.append(alphabet_h);
	}
	
	if(use_numbers) {
		set.append(digits);
	}
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, set.size() - 1);
	
	for(int n = 0; n < count; ++n) {
		int punctuation_count = 0;
		for(int i = 0; i < length; ++i) {			
			char ch;
			do {
				do {
					const int x = dis(gen);
					ch = set[x];
				} while(i == 0 && first_is_letter && !isalpha(ch));
				
			} while(!isalnum(ch) && punctuation_count >= max_punctuation);
			
			if(!isalnum(ch)) {
				++punctuation_count;
			}

			std::cout << ch;
		}
		
		std::cout << std::endl;
	}
}
