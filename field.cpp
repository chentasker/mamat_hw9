#include "string.h"
#include "field.h"
#include "ip.h"
#include "port.h"

using namespace std;

Field::Field(String pattern, field_type type) {
	this->pattern=pattern;
	this->type=type;
}

Field::Field(String pattern) {
	// Set this->type with respect to pattern
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
	// Call child set_value, depending to type
	if (type == IP) {
		return ((Ip*)this)->set_value(val);
	}
	else if (type == PORT) {
		return ((Port*)this)->set_value(val);
	}
    return false;
}

bool Field::match_value(String val) const {
	// Call child match_value, depending to type
	if (type == IP) {
		return ((Ip*)this)->match_value(val);
	}
	else if (type == PORT) {
		return ((Port*)this)->match_value(val);
	}
    return false;
}

bool Field::match(String packet) {
	// check if packet is an empty string
	if (packet.equals(String())) {
		return false;
	}

	String *packet_fields; // Points to a String array, containing the fields
	size_t size;
	packet.split(",",&packet_fields,&size);

	// loops through the fields in the packet
	for(size_t i=0;i<size;i++) {
		size_t size_field;
		String *field_values;
		packet_fields[i].split("=",&field_values,&size_field);
		// field[0] is the field's pattern
		// field[1] is the field's value
        
        String trimmed_field0=field_values[0].trim();
        if (trimmed_field0.equals(String())) {
			delete[] field_values;
        	continue;
        }
        // if current field's pattern matches this, test the value and return the result
		if (trimmed_field0.equals(this->pattern)) {
			String trimmed_field1=field_values[1].trim();
            bool result = match_value(trimmed_field1);
            delete[] field_values;
            delete[] packet_fields;
            return result;
		}
		delete[] field_values;
	}
	delete[] packet_fields;

	// if the loops ends without returning, no field's pattern matches this
    return false;
}