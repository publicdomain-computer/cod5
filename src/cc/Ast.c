/* "$Id: $"
 *
 *                          17 March MMXII PUBLIC DOMAIN
 *             The author disclaims copyright to this source code.
 *
 *          s = (a + b + c) / 2.0;
 *          A = sqrt(s * (s - a) * (s - b) * (s - c));    // Heron of Alexandria
 */

#include <cc/Ast.h>

static void __init__(Ex **e__)
{
	(void)e__;
	cc__Ast__.super = &Object__;
	return;
}


static void __ctor__(Ex **e__, cc__Ast *self)
{
	F("__ctor__");

	(void)__func__;
	(void)e__;

	self->last = 0;
	self->parser_current = 0;
	self->root = 0;
	self->tmp = 0;
	return;
}


static void __dtor__(Ex **e__, cc__Ast *self)
{
	F("__dtor__");
	
	return;
}

static uint32 hash_code(Ex **e__, cc__Ast *self)
{
	(void)e__;

#ifdef _MSC_VER
	return *((uint32*)&self) >> 4;
#else 
	return (uint32)self;
#endif

} 

static void to_string(Ex **e__, cc__Ast *self, String *out)
{
	F("to_string");
	String s;

	STR(s, self->_->__name__);
	out->_->add(e__, out, &s);
	CHECK(error);
error:
	return;
}

static cc__AstData *new_data(Ex **e__, cc__Ast *self)
{
	F("new_node");
	cc__AstData *a;
	
	a = (cc__AstData*)Gc__malloc(e__, sizeof(cc__AstData));
	CHECK(error1);
	a->left = 0;
	a->right = 0;
	a->body = 0;
	a->parent = 0;
	a->type = 0;
	return a;
error1:
	return 0;
}

static cc__AstData *new_node(Ex **e__, cc__Ast *self)
{
	F("new_node");
	cc__AstData *a;
	
	a = new_data(e__, self);
	CHECK(error1);
	a->parent = self->parser_current;
	self->last = a;
	return a;
error1:
	return 0;
}

static void parser_current_up(Ex **e__, cc__Ast *self, uint32 id)
{
	while (self->parser_current->type->id != id) {
		self->parser_current = self->parser_current->parent;
	}
}

static void push_body_current(Ex **e__, cc__Ast *self, cc__PreToken *token, cc__Type *type, uint8 set)
{
	F("push_body");
	cc__AstData *a;
	
	a = new_node(e__, self);
	CHECK(error1);
	if (self->parser_current != 0) {
		while (self->parser_current->body) {
			self->parser_current = self->parser_current->body;
		}
		self->parser_current->body = a;
		a->parent = self->parser_current;
	} else {
		if (self->root != 0) {
			a->parent = self->root;
			self->root->body = a;
		} else {
			self->root = a;
		}
	}
	a->token = token;
	a->type = type;

	if (set) {
		self->parser_current = a;
	}
	return;
error1:
	return;
}

static void push_left_current(Ex **e__, cc__Ast *self, cc__PreToken *token, cc__Type *type, uint8 set)
{
	F("push_left");
	cc__AstData *a;
	
	a = new_node(e__, self);
	CHECK(error1);
	if (self->parser_current != 0) {
		a->left = self->parser_current->left;
		self->parser_current->left = a;
		if (a->left != 0) {
			a->left->parent = a;
		}
	} else {
		a->left = self->root;
		if (self->root != 0) {
			self->root->parent = a;
		}
		self->root = a;
	}
	a->token = token;
	a->type = type;

	if (set) {
		self->parser_current = a;
	}
	return;
error1:
	return;
}

static void push_right_current(Ex **e__, cc__Ast *self, cc__PreToken *token, cc__Type *type, uint8 set)
{
	F("push_right");
	cc__AstData *a;
	
	a = new_node(e__, self);
	CHECK(error1);
	if (self->parser_current != 0) {
		a->left = self->parser_current->right;
		self->parser_current->right = a;
		if (a->left != 0) {
			a->left->parent = a;
		}
	} else {
		a->left = self->root;
		if (self->root != 0) {
			self->root->parent = a;
		}
		self->root = a;
	}
	a->token = token;
	a->type = type;

	if (set) {
		self->parser_current = a;
	}
	return;
error1:
	return;
}

static void set_type_current(Ex **e__, cc__Ast *self, cc__Type *type)
{
	F("set_type_current");

	self->parser_current->type = type;
}

static void set_current_last(Ex **e__, cc__Ast *self)
{
	F("set_current_last");

	self->parser_current = self->last;
}

static void set_current_parent(Ex **e__, cc__Ast *self)
{
	F("set_current_parent");

	self->parser_current = self->parser_current->parent;
}

static void set_current_null(Ex **e__, cc__Ast *self)
{
	F("set_current_null");

	self->parser_current = 0;
}

static void dump_ast(Ex **e__, cc__Ast *self, cc__AstData *ast, int32 depth)
{
	F("dump_ast");
	int32 i;

	if (ast == 0) return;
	dump_ast(e__, self, ast->left, depth + 1);

	for (i = 0; i < depth; i++) {
		ECHO(" ");
	}
	ECHO(ast->token->identifier);
	ECHO(" ");
	ECHO_NUM(ast->token->type);
	ECHO("\n");

	dump_ast(e__, self, ast->right, depth + 1);
	dump_ast(e__, self, ast->body, depth + 1);

}

static void dump(Ex **e__, cc__Ast *self)
{
	dump_ast(e__, self, self->root, 0);
}

static void new_tmp(Ex **e__, cc__Ast *self, cc__PreToken *token)
{
	F("new_tmp");
	cc__AstData *a;
	
	a = new_data(e__, self);
	CHECK(error1);

	a->token = token;
	a->left = self->tmp;
	if (self->tmp) self->tmp = a;
	self->tmp = a;
	return;
error1:
	return;
}

INIT_EXPORT cc__Ast__class cc__Ast__  = {
	// Object
	(utf8*)"cc__Ast",
	sizeof(cc__Ast),
	0,
	__init__,
	__ctor__,
	__dtor__,
	hash_code,
	to_string,

	// Ast
	new_node,
	parser_current_up,
	push_body_current,
	push_left_current,
	push_right_current,
	set_type_current,
	set_current_last,
	set_current_parent,
	set_current_null,
	dump,
	new_tmp
};

