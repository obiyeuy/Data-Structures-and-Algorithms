#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int AtomType;
typedef enum {ATOM,LIST}ElemTag;

typedef struct GLNode {
	ElemTag tag;
	union {
		AtomType atom;
		struct {
			struct GLNode* hp, * tp;
		}ptr;
	};
}*GList;

