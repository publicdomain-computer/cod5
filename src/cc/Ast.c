/* "$Id: $"
 *
 *                          17 March MMXII PUBLIC DOMAIN
 *             The author disclaims copyright to this source code.
 *
 *          s = (a + b + c) / 2.0;
 *          A = sqrt(s * (s - a) * (s - b) * (s - c));    // Heron of Alexandria
 */

#include <cc/Semantic.h>

static void __init__(Ex **e__)
{
	(void)e__;
	cc__Semantic__.super = &Object__;
	return;
}


static void __ctor__(Ex **e__, cc__Semantic *self)
{
	F("__ctor__");

	(void)__func__;
	(void)e__;

	return;
}


static void __dtor__(Ex **e__, cc__Semantic *self)
{
	F("__dtor__");
	
	return;
}

static uint32 hash_code(Ex **e__, cc__Semantic *self)
{
	(void)e__;

#ifdef _MSC_VER
	return *((uint32*)&self) >> 4;
#else 
	return (uint32)self;
#endif

} 

static void to_string(Ex **e__, cc__Semantic *self, String *out)
{
	F("to_string");
	String s;

	STR(s, self->_->__name__);
	out->_->add(e__, out, &s);
	CHECK(error);
error:
	return;
}

INIT_EXPORT cc__Semantic__class cc__Semantic__  = {
	// Object
	(utf8*)"cc__Semantic",
	sizeof(cc__Semantic),
	0,
	__init__,
	__ctor__,
	__dtor__,
	hash_code,
	to_string,

	// Semantic
};

