
#include "jsonc.h"
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

static json_return *GetValByKey(json_object * jobj, char *sname) {
	json_return *back = (json_return *) malloc(sizeof(json_return));
	json_object *pval = NULL;
	enum json_type type;

	char *p, *strs;
	strs = (char *) malloc(strlen(sname) + 1);
	strcpy(strs, sname);
	pval = json_object_object_get(jobj, strtok(strs, "->"));

	while ((p = strtok(NULL, "->")))
		pval = json_object_object_get(pval, p);
	free(strs);

	if (NULL != pval) {
		type = json_object_get_type(pval);
		switch (type) {
		case json_type_string:
		{
			back->type = CHARER;
			const char *res = json_object_get_string(pval);
			back->rs.rs_c = (char *) malloc(strlen(res) + 1);
			strcpy(back->rs.rs_c, res);
			break;
		}
		case json_type_int:
			//printf("Key:%s  value: %d\n", sname, json_object_get_int(pval));
			back->type = CHARER
			;
			back->rs.rs_i = json_object_get_int(pval);
			break;
		default:
			break;
		}
	}
	return back;
}


static int calu_append_num(char *str, const char *key)
{
	int couts = 0;
	char *point;
	point = str;
	while (point != NULL) {
		point = strstr(point, key);
		if (point != NULL) {
			point = point + 2;
			couts++;
		}
	}
	return couts;


}

void SetValByKey(json_object * jobj, char *sname, char *key) {
	json_object *pval = jobj;
	char *p, *strs;
	strs = (char *) malloc(strlen(sname) + 1);
	strcpy(strs, sname);

	int couts = calu_append_num(sname, "->");
	char *bak;
	bak = sname;
	if (couts != 0) {
		pval = json_object_object_get(jobj, strtok(strs, "->"));
		couts--;
		while ((p = strtok(NULL, "->"))) {
			free(bak);

			if (couts == 0) {
				bak = (char *) malloc(strlen(p) + 1);
				strcpy(bak, p);
				bak[strlen(p)] = '\0';
				couts--;
			} else {
				pval = json_object_object_get(pval, p);
			}

		}

	}
	json_object_object_del(pval, bak);
	json_object_object_add(pval, bak, json_object_new_string(key));
	free(strs);
}



void dele_json_backs(json_return *pobj)
{
     if(0 == pobj->type )
     {
        free(pobj->rs.rs_c);
     }
     free(pobj);
}


json_return  *get_val(char *name) {
	json_object *pobj = NULL;
	pobj = json_object_from_file("./conf.json");
	json_return *back;
	back = GetValByKey(pobj, name);
	json_object_to_file("./conf.json", pobj);
	json_object_put(pobj);
	return back;
}

void set_json_val(char *name, char *key)
{
	json_object *pobj = NULL;
	pobj = json_object_from_file("./conf.json");
	SetValByKey(pobj, name, key);
	json_object_to_file("./conf.json", pobj);
	json_object_put(pobj);

}
