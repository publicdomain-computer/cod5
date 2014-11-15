/* "$Id: $"
 *
 *                          17 March MMXII PUBLIC DOMAIN
 *             The author disclaims copyright to this source code.
 *
 *          s = (a + b + c) / 2.0;
 *          A = sqrt(s * (s - a) * (s - b) * (s - c));    // Heron of Alexandria
 */

#ifndef CC__SEMANTIC_H
#define CC__SEMANTIC_H

#include <lang/Object.h>
#include <lang/Hash.h>
#include <cc/PreToken.h>


typedef struct cc__Semantic {
	// Object
	struct cc__Semantic__class *_;

	// Semantic
} cc__Semantic;

typedef struct cc__Semantic__class {
	// Object
	utf8 *__name__;
	uint32 __size__;
	struct Object__class *super;
	void (*__init__)(Ex **e__);
	void (*__ctor__)(Ex **e__, cc__Semantic *self);
	void (*__dtor__)(Ex **e__, cc__Semantic *self);
	uint32 (*hash_code)(Ex **e__, cc__Semantic *self); 
	void (*to_string)(Ex **e__, cc__Semantic *self, String *out);

	// Semantic
} cc__Semantic__class; 

EXPORT cc__Semantic__class cc__Semantic__;


#endif // CC__SEMANTIC_H

