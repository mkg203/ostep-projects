#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct KVP {
	char* key;
	char* value;
} KVP;

KVP key_value(char* arg, int len) {
	char* value = strstr(arg, ",") + 1;
	int val_len = strlen(value);
	int key_len = len - val_len;

	char* key = malloc(key_len);
	strncpy(key, arg, key_len);
	
	key[key_len - 1] = '\0';

	KVP ret = {.key = key, .value = value};
	return ret;
}

void put(KVP* kv) {
	FILE* fp = fopen("database.txt", "a");

	fprintf(fp, "%s,%s\n", kv->key, kv->value);

	fclose(fp);
}

char* get(char* _key) {
	char* line = NULL;
	size_t restrict_n = 0;
	
	int len = strlen(_key) + 1;
	char key[len];

	strcpy(key, _key);
	key[len - 1] = ',';
	key[len] = '\0';
	
	int n;

	FILE* fp = fopen("database.txt", "r");

	while ((n = getline(&line, &restrict_n, fp)) != -1) {
		char* value = strchr(line, ',');
		int _len = (int) (value - line) + 1;
		/*printf("%d\n", _len);*/
		if (strstr(line, key) && len == _len) {
			fclose(fp);
			return line;
		}
	}
	
	free(line);
	fclose(fp);

	return NULL;
}

void delete(char* _key) {
	char* line = NULL;
	size_t restrict_n = 0;
	
	int len = strlen(_key) + 1;
	char key[len];

	strcpy(key, _key);
	key[len - 1] = ',';
	key[len] = '\0';
	
	int n;

	FILE* fp = fopen("database.txt", "r");
	FILE* fpt = fopen("database_temp.txt", "a");

	while ((n = getline(&line, &restrict_n, fp)) != -1) {
		char* value = strchr(line, ',');
		int _len = (int) (value - line) + 1;
		if (strstr(line, key) && len == _len) {
			continue;
		}

		fprintf(fpt, "%s", line);
	}
	
	free(line);
	fclose(fp);
	fclose(fpt);

	remove("database.txt");
	rename("database_temp.txt", "database.txt");

	return ;
}

void all() {
	char* line = NULL;
	size_t restrict_n = 0;
	
	FILE* fp = fopen("database.txt", "r");

	while ((getline(&line, &restrict_n, fp)) != -1) {
		printf("%s", line);
	}
	
	free(line);
	fclose(fp);
}

void parse_args(char* arg){
	int len = strlen(arg);
	
	switch (arg[0]) {
		case 'p': {
			KVP kv = key_value(arg + 2, len - 2);

			char* tmp = strtok(arg + 2, ",");
			char* exists = get(tmp);
			if (exists) {
				free(exists);
				free(kv.key);
				break;
			}
			
			put(&kv);
			
			free(kv.key);
			break;
		}
		case 'g': {
			char* line = get(arg + 2);
			char* tmp = strtok(arg + 2, ",");
			if (line) {
				printf("%s", line);
				free(line);
			}
			else {
				printf("%s not found\n", tmp);
			}
			break;
		}
		case 'd': {
			delete(arg + 2);
			break;
		}
		case 'c': {
			fclose(fopen("database.txt", "w"));
			break;
		}
		case 'a': {
			all();
			break;
		}
		default: {
			printf("kv: invalid option (p, g, a, c, d)\n");
			break;
		}
	}
	return;
}

int main(int argc, char* argv[]) {
	for (int i = 1; i < argc; i++) {
		parse_args(argv[i]);
	}
}
