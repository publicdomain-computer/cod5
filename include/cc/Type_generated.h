#define CC__TOKEN_AUTO	0x00000000
#define CC__TOKEN_BREAK	0x00000001
#define CC__TOKEN_CASE	0x00000002
#define CC__TOKEN_CHAR	0x00000003
#define CC__TOKEN_CONST	0x00000004
#define CC__TOKEN_CONTINUE	0x00000005
#define CC__TOKEN_DEFAULT	0x00000006
#define CC__TOKEN_DO	0x00000007
#define CC__TOKEN_DOUBLE	0x00000008
#define CC__TOKEN_ELSE	0x00000009
#define CC__TOKEN_ENUM	0x0000000a
#define CC__TOKEN_EXTERN	0x0000000b
#define CC__TOKEN_FLOAT	0x0000000c
#define CC__TOKEN_FOR	0x0000000d
#define CC__TOKEN_GOTO	0x0000000e
#define CC__TOKEN_IF	0x0000000f
#define CC__TOKEN_INLINE	0x00000010
#define CC__TOKEN_INT	0x00000011
#define CC__TOKEN_LONG	0x00000012
#define CC__TOKEN_REGISTER	0x00000013
#define CC__TOKEN_RESTRICT	0x00000014
#define CC__TOKEN_RETURN	0x00000015
#define CC__TOKEN_SHORT	0x00000016
#define CC__TOKEN_SIGNED	0x00000017
#define CC__TOKEN_STATIC	0x00000018
#define CC__TOKEN_STRUCT	0x00000019
#define CC__TOKEN_SWITCH	0x0000001a
#define CC__TOKEN_TYPEDEF	0x0000001b
#define CC__TOKEN_UNION	0x0000001c
#define CC__TOKEN_UNSIGNED	0x0000001d
#define CC__TOKEN_VOID	0x0000001e
#define CC__TOKEN_VOLATILE	0x0000001f
#define CC__TOKEN_WHILE	0x00000020
#define CC__TOKEN__BOOL	0x00000021
#define CC__TOKEN__COMPLEX	0x00000022
#define CC__TOKEN__IMAGINARY	0x00000023
#define CC__TOKEN_POINTER	0x00000024
#define CC__TOKEN_OBJECT_TYPE	0x00000025
#define CC__TOKEN_FUNCTION_TYPE	0x00000026
#define CC__TOKEN_LABEL	0x00000027
#define CC__TOKEN_TYPEDEF_IDENTIFIER	0x00000028
#define CC__TOKEN_STRING_CONSTANT	0x00000029
#define CC__TOKEN_CHARACTER_CONSTANT	0x0000002a
#define CC__TOKEN_NUMBER_CONSTANT	0x0000002b
#define CC__TOKEN_PARANTHES	0x0000002c
#define CC__TOKEN_PLUSPLUS	0x0000002d
#define CC__TOKEN_MINUSMINUS	0x0000002e
#define CC__TOKEN_AND	0x0000002f
#define CC__TOKEN_STAR	0x00000030
#define CC__TOKEN_PLUS	0x00000031
#define CC__TOKEN_MINUS	0x00000032
#define CC__TOKEN_COLON	0x00000033
#define CC__TOKEN_SEMICOLON	0x00000034
#define CC__TOKEN_BRACKET	0x00000035
#define CC__TOKEN_BRACE	0x00000036
#define CC__TOKEN_CLOSING_BRACE	0x00000037
#define CC__TOKEN_CLOSING_PARANTHESIS	0x00000038
#define CC__TOKEN_CLOSING_BRACKET	0x00000039
#define CC__TOKEN_ARRAY_SUBSCRIPTING	0x0000003a
#define CC__TOKEN_FUNCTION_CALLS	0x0000003b
#define CC__TOKEN_STRUCTURE_MEMBER	0x0000003c
#define CC__TOKEN_POINTER_STRUCTURE_MEMBER	0x0000003d
#define CC__TOKEN_POSTFIX_INCREMENT	0x0000003e
#define CC__TOKEN_POSTFIX_DECREMENT	0x0000003f
#define CC__TOKEN_COMPOUND_LITERALS	0x00000040
#define CC__TOKEN_PREFIX_INCREMENT	0x00000041
#define CC__TOKEN_PREFIX_DECREMENT	0x00000042
#define CC__TOKEN_ADDRESS	0x00000043
#define CC__TOKEN_INDIRECTION	0x00000044
#define CC__TOKEN_UNARY_PLUS	0x00000045
#define CC__TOKEN_UNARY_MINUS	0x00000046
#define CC__TOKEN_BITWISE_COMPLEMENT	0x00000047
#define CC__TOKEN_LOGICAL_NEGATION	0x00000048
#define CC__TOKEN_SIZEOF	0x00000049
#define CC__TOKEN_CAST	0x0000004a
#define CC__TOKEN_MULTIPLY	0x0000004b
#define CC__TOKEN_DIVIDE	0x0000004c
#define CC__TOKEN_MODULO	0x0000004d
#define CC__TOKEN_ADDITION	0x0000004e
#define CC__TOKEN_SUBSTRACTION	0x0000004f
#define CC__TOKEN_BITWISE_SHIFT_LEFT	0x00000050
#define CC__TOKEN_BITWISE_SHIFT_RIGHT	0x00000051
#define CC__TOKEN_LESS_THAN	0x00000052
#define CC__TOKEN_GREATER_THAN	0x00000053
#define CC__TOKEN_LESS_THAN_OR_EQUAL_TO	0x00000054
#define CC__TOKEN_GREATER_THAN_OR_EQUAL_TO	0x00000055
#define CC__TOKEN_EQUAL_TO	0x00000056
#define CC__TOKEN_NOT_EQUAL_TO	0x00000057
#define CC__TOKEN_BITWISE_AND	0x00000058
#define CC__TOKEN_BITWISE_EXCLUSIVE_OR	0x00000059
#define CC__TOKEN_BITWISE_INCLUSIVE_OR	0x0000005a
#define CC__TOKEN_LOGICAL_AND	0x0000005b
#define CC__TOKEN_LOGICAL_OR	0x0000005c
#define CC__TOKEN_CONDITONAL	0x0000005d
#define CC__TOKEN_SIMPLE_ASSIGNMENT	0x0000005e
#define CC__TOKEN_MULTIPLY_ASSIGNMENT	0x0000005f
#define CC__TOKEN_DIVIDE_ASSIGNMENT	0x00000060
#define CC__TOKEN_MODULO_ASSIGNMENT	0x00000061
#define CC__TOKEN_ADDITION_ASSIGNMENT	0x00000062
#define CC__TOKEN_SUBSTRACTION_ASSIGNMENT	0x00000063
#define CC__TOKEN_SHIFT_LEFT_ASSIGNMENT	0x00000064
#define CC__TOKEN_SHIFT_RIGHT_ASSIGNMENT	0x00000065
#define CC__TOKEN_AND_ASSIGNMENT	0x00000066
#define CC__TOKEN_EXCLUSIVE_OR_ASSIGNMENT	0x00000067
#define CC__TOKEN_INCLUSIVE_OR_ASSIGNMENT	0x00000068
#define CC__TOKEN_COMMA	0x00000069
#define CC__TYPE_NB_TYPES 106

#define CC__TOKEN_IDENTIFIER 0x00800000
#define CC__TOKEN_STORAGE_CLASS 0x80000000
#define CC__TOKEN_TYPE_SPECIFIER 0x40000000
#define CC__TOKEN_QUALIFIER 0x20000000
#define CC__TOKEN_OPERATOR 0x10000000
#define CC__TOKEN_JUMP 0x08000000
#define CC__TOKEN_TYPEDEFINE 0x04000000
#define CC__TOKEN_STATEMENT 0x02000000
#define CC__TOKEN_EXPRESSION 0x01000000
#define CC__TOKEN_CONSTANT 0x00400000
#define CC__TOKEN_ASSOCIATIVITY_LEFT 0x00000001
#define CC__TOKEN_ASSOCIATIVITY_RIGHT 0x00000000
#define CC__TOKEN_ASSOCIATIVITY_NONE 0x00000002
