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
	// test if str is an empty string
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
	this->length = rhs.length;
	if (this->data != NULL) {
		delete[] data;
	}
	// test if rhs is an empty String
	if (rhs.data == NULL || rhs.data[0] == '\0' || rhs.data[0] == '\n') {
		length = 0;
		data = new char[1];
		data[0] = '\0';
		return *this;
	}
	this->data = new char[length+1];
	strcpy(this->data,rhs.data);
	return *this;
}

/**
 * @brief Changes this from char array
 */
String& String::operator=(const char *str){
	if (this->data != NULL) {
		delete[] data;
	}
	// test if str is an empty string
	if (str == NULL || str[0] == '\0' || str[0] == '\n') {
		length = 0;
		data = new char[1];
		data[0] = '\0';
		return *this;
	}
	size_t other_length = strlen(str);
	this->length = other_length;
	this->data = new char[length+1];
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
	if (strcmp(data,rhs)==0 ) {
		return true;
	}
	else {
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
	// if this is empty, return 1-cell array containing this
	if (data == NULL || data[0] == '\0') {
		*output=new String[1];
		(*output)[0]=*this;
		return;
	}

	// store this' fields in tmp
	char *delimiters_tmp = new char[strlen(delimiters)+1];
	strcpy(delimiters_tmp,delimiters);
	char* tmp_str = new char[length+1];
	strcpy(tmp_str, data);

	// Find the amount of parts in the string
	size_t count=0;
	char *del_loc=strtok(tmp_str,delimiters_tmp);
	while(del_loc!=NULL) {
		count++;
		del_loc=strtok(NULL,delimiters_tmp);
	}
	*size = count;

	if (output == NULL) {
		delete[] tmp_str;
		delete[] del_loc;
		return;
	}

	*output = new String[count];
	strcpy(tmp_str, data);
	del_loc=strtok(tmp_str,delimiters_tmp);
	int output_ind=0;
	while(del_loc!=NULL) {
		(*output)[output_ind] = String(del_loc);
		output_ind++;
		del_loc=strtok(NULL,delimiters_tmp);
	}

	delete[] tmp_str;
	delete[] del_loc;

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

	// amount of spaces in the beginning
	for(size_t i=0;i<length;i++) {
		if(data[i]==' '){
			begin_space++;
		}
		else {
			break;
		}
	}
	// amount of spaces in the end
	for(size_t i=0;i<length;i++) {
		if(data[length-i-1]==' '){
			end_space++;
		}
		else {
			break;
		}
	}

	// if this is spaces only - return empty String
	if((int)length-end_space-begin_space<0) {
		return String();
	}

	char *newstr=new char[length-end_space-begin_space+1];
	strncpy(newstr,data+begin_space,length-end_space-begin_space);
	newstr[length-end_space-begin_space] = '\0';
	String ret(newstr);
	delete[] newstr;
	return ret;
}