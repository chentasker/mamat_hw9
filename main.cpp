#include "string.h"
#include "field.h"
#include "ip.h"
#include "port.h"
#include "input.h"
#include <iostream>

extern int check_args(int,char**);
extern void parse_input(Field&);


using namespace std;

#define FAIL -1

int main(int argc, char** argv) {
	
	if (check_args(argc,argv) != 0) {
		return FAIL;
	}
	String rule(argv[1]);
	String *rule_fields;
	size_t rule_size=0;
	rule.split("=",&rule_fields,&rule_size);
	if (rule_fields==NULL) {
		return FAIL;
	}
	String rule_name = rule_fields[0].trim();
	String rule_val = rule_fields[1].trim();
	if( rule_name.equals("src-ip") || rule_name.equals("dst-ip") ) {
		Ip cur_rule(rule_name);
		cur_rule.set_value(rule_val);
		parse_input(cur_rule);
	}
	else if(rule_name.equals("src-port") || rule_name.equals("dst-port") ) {
		Port cur_rule(rule_name);
		cur_rule.set_value(rule_val);
		parse_input(cur_rule);
	}
	else {
		delete[] rule_fields;
		return FAIL;
	}
	delete[] rule_fields;
	
	return 0;
}

