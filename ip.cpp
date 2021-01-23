#include "field.h"


#include "string.h"
#include "ip.h"

using namespace std;

#define MASK_SEGMENT 2
#define SEGMENTS 4

unsigned int get_ip_int(String val_str);

Ip::Ip(String pattern):Field(pattern) {

}

unsigned int get_ip_int(String val_str) {
	String *str_array;
	size_t size;
	char del = '.';
	val_str.split(&del, &str_array, &size);
	if (size != SEGMENTS)
		return 0;
	int *values = new int[SEGMENTS];
	for (int i = 0; i < SEGMENTS; i++) {
		String trimedstr=str_array[i].trim();
        values[i] = trimedstr.to_integer();
	}
	return (values[0] << 24) | (values[1] << 16) | (values[2] << 8) | (values[3]);
}


bool Ip::set_value(String val) {
	String *rule_fields;
	size_t rule_fields_size;
	char del = '/';
	val.split(&del, &rule_fields, &rule_fields_size);
    if(rule_fields_size!=MASK_SEGMENT) {
        delete[] rule_fields;
        return false;
    }
	String field1=rule_fields[1].trim();
    String field0=rule_fields[0].trim();
    int dc_num = 32 - field1.to_integer();
	unsigned int val_int = get_ip_int(field0);
    if(val_int==0) {
        delete[] rule_fields;
        return false;
    }
	low = (val_int >> dc_num) << dc_num;
	high = (val_int >> dc_num);
	for (int i = 0; i < dc_num; i++) {
		high = high << 1;
		high ++;
	}
    delete[] rule_fields;
    return false;
    return true;
}

bool Ip::match_value(String val) const {
	String trimmedval=val.trim();
    unsigned int ip_int = get_ip_int(trimmedval);
	return (ip_int <= high && ip_int >= low);
}

