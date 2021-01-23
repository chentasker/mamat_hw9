#include "string.h"
#include "field.h"

using namespace std;

Field::Field(String pattern, field_type type) {
	this->pattern=pattern;
	this->type=type;
}

Field::Field(String pattern) {
	String trimmed_pattern=pattern.trim();
    if(trimmed_pattern.equals("src-ip") || trimmed_pattern.equals("dst-ip") ) {
		this->type=IP;
	}
	else {
		this->type=PORT;
	}
	this->pattern=pattern;
}

Field::~Field() {
	
}

field_type Field::get_type() const {
	return this->type;
}

bool Field::set_value(String val) {
    return false;
}

bool Field::match_value(String val) const {
    return false;
}

bool Field::match(String packet) {
	String *packet_fields;
	char delimeter = ',';
	size_t size;
	packet.split(&delimeter,&packet_fields,&size);
	for(size_t i=0;i<size;i++) {
		delimeter='=';
		size_t size_field;
		String *field_values;
		packet_fields[i].split(&delimeter,&field_values,&size_field);
        String trimmed_field0=field_values[0].trim();
		if (trimmed_field0.equals(this->pattern)) {
			String trimmed_field1=field_values[1].trim();
            bool result = this->match_value(trimmed_field1);
            //delete[] field_values;
            //delete[] packet_fields;
            return result;
		}
		delete[] field_values;
	}
	delete[] packet_fields;
    return false;
}