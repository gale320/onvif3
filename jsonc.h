/*
 * jsonc.h
 *
 *  Created on: 2011-12-16
 *      Author: root
 */

#ifndef JSONC_H_
#define JSONC_H_
#define NUMER 1;
#define CHARER 0;
#include <stdarg.h>

typedef struct _json_return json_return;

struct _json_return {
	short type; //1代表数字 0代表字符
	union {
		int rs_i;
		char *rs_c;
	}rs;
};

#include "../jsonlib/json.h"

void set_json_val(char *name, char *key);
void SetValByKey(json_object * jobj,char *name, char *key);
json_return *get_val(char *name);
void dele_json_backs(json_return *pobj);


#endif /* JSONC_H_ */
