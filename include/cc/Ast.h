/* "$Id: $"
 *
 *                          17 March MMXII PUBLIC DOMAIN
 *             The author disclaims copyright to this source code.
 *
 *          s = (a + b + c) / 2.0;
 *          A = sqrt(s * (s - a) * (s - b) * (s - c));    // Heron of Alexandria
 */

#ifndef CC__AST_H
#define CC__AST_H

#include <lang/Object.h>
#include <lang/Hash.h>
#include <cc/PreToken.h>
#include <cc/Type.h>

typedef struct cc__AstData {
	cc__PreToken *token;
	cc__Type *type;
	struct cc__AstData *left;
	struct cc__AstData *right;
	struct cc__AstData *body;
	struct cc__AstData *parent;	
} cc__AstData;

typedef struct cc__Ast {
	// Object
	struct cc__Ast__class *_;

	// Ast
	cc__AstData *root;
	cc__AstData *parser_current;
	cc__AstData *last;
	cc__AstData *tmp;
} cc__Ast;

typedef struct cc__Ast__class {
	// Object
	utf8 *__name__;
	uint32 __size__;
	struct Object__class *super;
	void (*__init__)(Ex **e__);
	void (*__ctor__)(Ex **e__, cc__Ast *self);
	void (*__dtor__)(Ex **e__, cc__Ast *self);
	uint32 (*hash_code)(Ex **e__, cc__Ast *self); 
	void (*to_string)(Ex **e__, cc__Ast *self, String *out);

	// Ast
	cc__AstData *(*new_node)(Ex **e__, cc__Ast *self);
	void (*parser_current_up)(Ex **e__, cc__Ast *self, uint32 id);
	void (*push_body_current)(Ex **e__, cc__Ast *self, cc__PreToken *token, cc__Type *type, uint8 set);
	void (*push_left_current)(Ex **e__, cc__Ast *self, cc__PreToken *token, cc__Type *type, uint8 set);
	void (*push_right_current)(Ex **e__, cc__Ast *self, cc__PreToken *token, cc__Type *type, uint8 set);
	void (*set_type_current)(Ex **e__, cc__Ast *self, cc__Type *type);
	void (*set_current_last)(Ex **e__, cc__Ast *self);
	void (*set_current_parent)(Ex **e__, cc__Ast *self);
	void (*set_current_null)(Ex **e__, cc__Ast *self);
	void (*dump)(Ex **e__, cc__Ast *self);
	void (*new_tmp)(Ex **e__, cc__Ast *self, cc__PreToken *token);
} cc__Ast__class; 

EXPORT cc__Ast__class cc__Ast__;

#endif // CC__AST_H

