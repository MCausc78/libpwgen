#include <iostream>
#include <pwgen/pwgen.hpp>

void print_password(pwgen::pwgen &pg, uint32_t len) {
	std::cout << "Generated a password with length " << len << " : \"" << pg.generate(len) << '"' << std::endl;
}

int main() {
	pwgen::pwgen pg;
	uint32_t i;
	std::cout << std::endl << "Example #1: Simple password generation" << std::endl << std::endl;
	for(i = 4; i <= 16; i++) {
		print_password(pg, i);
	}
	
	pwgen::pwgen pg2(pwgen::flags::NONE, "", "01");
	std::cout << std::endl << "Example #2: Including custom characters" << std::endl << std::endl;
	for(i = 4; i <= 16; i++) {
		print_password(pg2, i);
	}
	
	pwgen::pwgen pg3(pwgen::flags::LOWER_ASCII | pwgen::flags::UPPER_ASCII, "AEIOUaeiou");
	std::cout << std::endl << "Example #3: Excluding some characters" << std::endl << std::endl;
	for(i = 4; i <= 16; i++) {
		print_password(pg3, i);
	}
	
	return 0;
}
