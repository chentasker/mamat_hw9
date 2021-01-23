#include <stddef.h>
#include <iostream>
#include <cstring>
#include "string.h"

using namespace std;

/**
 * @brief Initiates an empty string
 */
String::String() {
	data = new char[1];
	data[0] = '\0';
	length=0;
}

/**
 * @brief Initiates string from other string
 */
String::String(const String &str) {
	length=str.length;
	data=new char[(int)length+1];
	strcpy(data,str.data);
}

/**
 * @brief Initiates a string from char array
 */
String::String(const char *str) {
	if (str == NULL || str[0] == '\0') {
		data = new char[1];
		data[0] = '\0';
		length=0;
	}
	else {
		length=strlen(str);
		data=new char[(int)length+1];
		strcpy(data,str);
	}
}

String::~String() {
	delete[] data;
}

/**
 * @brief Changes this from String
 */
String& String::operator=(const String &rhs) {
	length=rhs.length;
	if (length == 0) {
		data = NULL;
		return *this;
	}
	char *tmp_data=data;
	data=new char[length+1];
	if(tmp_data!=NULL) {
        delete[] tmp_data;
    }
	strcpy(data,rhs.data);
	return *this;
}

/**
 * @brief Changes this from char array
 */
String& String::operator=(const char *str){
	if (str == NULL || str[0] == '\0') {
		length = 1;
		data = NULL;
		return *this;
	}
	length=strlen(str);
	char *tmp_data=data;
	data=new char[length+1];
	if(tmp_data!=NULL) {
        delete[] tmp_data;
    }
	strcpy(data,str);
	return *this;
}

/**
 * @brief Returns true iff the contents of this equals to the
 * contents of rhs
 */
bool String::equals(const String &rhs) const {
	if (length == rhs.length && strcmp(data,rhs.data)==0 ) {
		return true;
	}
	else {
		return false;
	}
}

/**
 * @brief Returns true iff the contents of this equals to rhs
 */
bool String::equals(const char *rhs) const {
	std::cout << "this string: |" << data << "|" <<std::endl;
	std::cout << "other string: |" << rhs << "|" <<std::endl;
	if (strcmp(data,rhs)==0 ) {
		std::cout << "EQUALS!" << std::endl;
		std::cout << std::endl;
		return true;
	}
	else {
		std::cout << "DIFFERENT!" << std::endl;
		std::cout << std::endl;
		return false;
	}
}

/**
 * @brief Splits this to several sub-strings according to delimiters.
 * Allocates memory for output that the user must //delete (using //delete[]).
 * @note Does not affect this->
 * @note If "output" is set to NULL, do not allocated memory, only
 * compute "size".
 */
void String::split(const char *delimiters, String **output, size_t *size) const{

	//unsigned int delimetes_length = std::strlen(delimiters);

	// Finding the amount of delimeters in string
	int delimeters_count=0;
	for(size_t i=0;i<length;i++) {
		for(size_t j=0;j<strlen(delimiters);j++) {
			if(data[i]==delimiters[j]) {
				//std::cout << "Found delimeter " << delimeters[j] << " in position: " << i << std::endl;
				delimeters_count++;
			}
		}
	}

	*size = delimeters_count + 1;
	if (output == NULL) {
		return;
	}
	*output = new String[delimeters_count + 1];

	bool skip=false;
	int cur_out=0,num_chars=0;
	char *tmp_data=new char[length+1];
	for(size_t i=0;i<length;i++) {
		skip=false;
		for(size_t j=0;j<strlen(delimiters);j++) {
			if(data[i]==delimiters[j]) {
				skip=true;
				break;
			}
		}
		if(!skip) {
			tmp_data[num_chars]=data[i];
			num_chars++;
		}
		else {
			tmp_data[num_chars]='\0';
			num_chars++;
			char *tmp_str=new char[num_chars];
			strncpy(tmp_str,tmp_data,num_chars+1);
			*output[cur_out]=tmp_str;
			cur_out++;
			num_chars=0;
		}
	}

	delete[] tmp_data;	

}

/**
 * @brief Try to convert this to an integer. Returns 0 on error.
 */
int String::to_integer() const {
	int num=0;
	int addval;
	for(size_t i=0;i<length;i++) {
		if(data[i]<'0' || data[i]>'9') {
			return 0;
		}
		num=num*10;
		addval=data[i]-'0';
		num=num+addval;
	}
	return num;
}

/**
 * @brief Remove any leading or trailing white-spaces.
 * Does not change this->
 */
String String::trim() const {
	int begin_space=0,end_space=0;
	for(size_t i=0;i<length;i++) {
		if(data[i]==' '){
			begin_space++;
		}
		else {
			break;
		}
	}
	for(size_t i=0;i<length;i++) {
		if(data[length-i-1]==' '){
			end_space++;
		}
		else {
			break;
		}
	}
	if((int)length-end_space-begin_space<0) {
		return String();
	}
	char *newstr=new char[length-end_space-begin_space];
	strncpy(newstr,data+begin_space,length-end_space-begin_space);
	return String(newstr);
}