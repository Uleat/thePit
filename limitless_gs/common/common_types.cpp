#include "common_types.h"


template<size_t S>
void CommonUseArray <char, S>::mem_cpy(const char* r) {
	int pos = 0;
	bool read = (r != nullptr);

	while (pos < S) {
		if (read)
			Data[pos] = r[pos];
		else
			Data[pos] = '\0';
		
		++pos;
	}
}

template<size_t S>
void CommonUseArray <char, S>::str_cpy(const char* r) {
	int pos = 0;
	
	if (r != nullptr) {
		while (pos < (S - 1)) {
			Data[pos] = r[pos];
			
			if (r[pos] == '\0')
				break;

			++pos;
		}
	}
	else {
		Data[0] = '\0';
	}

	str_safe();
}

template<size_t S>
void CommonUseArray <char, S>::str_n_cpy(const char* r) {
	int pos = 0;
	bool read = (r != nullptr);

	while (pos < (S - 1)) {
		if (read)
			Data[pos] = r[pos];
		else
			Data[pos] = '\0';

		if (r[pos] == '\0')
			read = false;

		++pos;
	}

	str_safe();
}