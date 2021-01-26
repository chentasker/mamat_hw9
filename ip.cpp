#include "field.h"
#include "string.h"
#include "ip.h"

using namespace std;

#define MASK_SEGMENT 2
#define SEGMENTS 4
#define FAIL -1

unsigned int get_ip_int(String val_str);

Ip::Ip(String pattern):Field(pattern) {

}

// this function converts ip adress (stored as a String object) to integer
unsigned int get_ip_int(String val_str) {
	String *str_array;
	size_t size;
	val_str.split(".", &str_array, &size);
	if (size != SEGMENTS)
		return FAIL;
	int *values = new int[SEGMENTS];
	for (int i = 0; i < SEGMENTS; i++) {
		String trimmed_str=str_array[i].trim();
        values[i] = trimmed_str.to_integer();
	}
	return (values[0] << 24) | (values[1] << 16) | (values[2] << 8) | (values[3]);
}


bool Ip::set_value(String val) {
	String *rule_fields;
	size_t rule_fields_size;
	val.split("/", &rule_fields, &rule_fields_size);
    if(rule_fields_size!=MASK_SEGMENT) {
        delete[] rule_fields;
        return false;
    }
    // rule_fields[0] is an ip adress
    // rule_fields[1] is the amount of relevant digits, counting from the left

	String field1=rule_fields[1].trim();
    String field0=rule_fields[0].trim();
    int dc_num = 32 - field1.to_integer(); //dc_num is number of don't-care digits
	unsigned int val_int = get_ip_int(field0);
	
	// check if get_ip_int failed
    if((signed int)val_int == FAIL) {
        delete[] rule_fields;
        return false;
    }

    // calculate extreme possible ip adress (as integer) that fits the rule
	low = (val_int >> dc_num) << dc_num;
	high = (val_int >> dc_num);
	for (int i = 0; i < dc_num; i++) {
		high = high << 1;
		high ++;
	}

    delete[] rule_fields;
    return true;
}

bool Ip::match_value(String val) const {
	String trimmedval=val.trim();
    unsigned int ip_int = get_ip_int(trimmedval);
	return (ip_int <= high && ip_int >= low);
}

