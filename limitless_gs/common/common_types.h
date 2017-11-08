#pragma once


#include <string>
#include <vector>

#include "common_definitions.h"


typedef int8_t byte_t;
#define BYTE_T_MIN INT8_MIN
#define BYTE_T_MAX INT8_MAX

typedef uint8_t ubyte_t;
#define UBYTE_T_MIN 0ui8
#define UBYTE_T_MAX UINT8_MAX

typedef int16_t word_t;
#define WORD_T_MIN INT16_MIN
#define WORD_T_MAX INT16_MAX

typedef uint16_t uword_t;
#define UWORD_T_MIN 0ui16
#define UWORD_T_MAX UINT16_MAX

typedef int32_t dword_t;
#define DWORD_T_MIN INT32_MIN
#define DWORD_T_MAX INT32_MAX

typedef uint32_t udword_t;
#define UDWORD_T_MIN 0ui32
#define UDWORD_T_MAX UINT32_MAX

typedef int64_t qword_t;
#define QWORD_T_MIN INT64_MIN
#define QWORD_T_MAX INT64_MAX

typedef uint64_t uqword_t;
#define UQWORD_T_MIN 0ui64
#define UQWORD_T_MAX UINT64_MAX

typedef uint8_t bitmask8_t;
#define BITMASK8_T_NONE 0ui8
#define BITMASK8_T_ALL UINT8_MAX

typedef uint16_t bitmask16_t;
#define BITMASK16_T_NONE 0ui16
#define BITMASK16_T_ALL UINT16_MAX

typedef uint32_t bitmask32_t;
#define BITMASK32_T_NONE 0ui32
#define BITMASK32_T_ALL UINT32_MAX

typedef uint64_t bitmask64_t;
#define BITMASK64_T_NONE 0ui64
#define BITMASK64_T_ALL UINT64_MAX

//

typedef udword_t id_t;
#define ID_T_MIN UDWORD_T_MIN
#define ID_T_MAX UDWORD_T_MAX

typedef uword_t race_t;
#define RACE_T_MIN UWORD_T_MIN
#define RACE_T_MAX UWORD_T_MAX

typedef uword_t class_t;
#define CLASS_T_MIN UWORD_T_MIN
#define CLASS_T_MAX UWORD_T_MAX

typedef uword_t slot_t;
#define SLOT_T_MIN UWORD_T_MIN
#define SLOT_T_MAX UWORD_T_MAX

typedef word_t stat_value_t;
#define STAT_VALUE_T_MIN WORD_T_MIN
#define STAT_VALUE_T_MAX WORD_T_MAX

typedef float skill_t;

typedef udword_t price_t;
#define PRICE_T_MIN UDWORD_T_MIN
#define PRICE_T_MAX UDWORD_T_MAX

typedef qword_t credit_t;
#define CREDIT_T_MIN QWORD_T_MIN
#define CREDIT_T_MAX QWORD_T_MAX

typedef uword_t stack_t;
#define STACK_T_MIN UWORD_T_MIN
#define STACK_T_MAX UWORD_T_MAX

typedef uword_t charge_t;
#define CHARGE_T_MIN UWORD_T_MIN
#define CHARGE_T_MAX UWORD_T_MAX

template <class T, size_t S>
struct CommonUseArray {
	static_assert(sizeof(T) > 0, "Undefined types are not allowed in CommonUseArray<T>.");
	static_assert(S > 0, "Zero-sized arrays are not allowed in CommonUseArray<T>.");

	inline size_t sizeof_array() const { return S; }
	inline size_t sizeof_type() const { return sizeof(T); }
	inline size_t sizeof_data() const { return (sizeof(T) * S); }
	
	T Data[S];
};

template<size_t S>
struct CommonUseArray <char, S> {
	static_assert(S > 0, "Zero-sized arrays are not allowed in CommonUseArray<char>.");

	inline size_t sizeof_array() const { return S; }
	inline size_t sizeof_type() const { return sizeof(char); }
	inline size_t sizeof_data() const { return (sizeof(char) * S); }

	inline size_t str_capacity() const { return (S - 1); }
	inline void str_safe() { Data[S - 1] = '\0'; }
	
	void mem_cpy(const char* r);
	void str_cpy(const char* r);
	void str_n_cpy(const char* r);

	char Data[S];
};

typedef CommonUseArray<char, NAME_LEN> name_t;
typedef CommonUseArray<char, DESCRIPTION_LEN> description_t;

namespace objects {

	class Item;

} // namespace profiles

typedef std::vector<objects::Item*> item_vector_t;
typedef std::vector<item_vector_t*> inventory_vector_t;
