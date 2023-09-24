#ifndef JPARSER_H_
#define JPARSER_H_

#include <stddef.h>

typedef enum {
    JP_T_PRIMITIVE = 0,
    JP_T_OBJECT = 1,
    JP_T_ARRAY = 2,
    JP_T_STRING = 3
} JP_JsonType;

typedef struct {
    JP_JsonType type;
    void* value;
} JP_Object;

typedef void (*callback_void_t)(void);

typedef struct {
    callback_void_t callback_ptrs[256];
    char* source;
    size_t cur;
    size_t bol;
    size_t row;
} JP_Parser;

JP_Parser* jp_init(char* input);
int jp_attach_callback(JP_Parser* parser,const char* key, callback_void_t);

inline JP_Parser* jp_init(char* input) {
    JP_Parser* parser = {0};
    parser->source = input;
    parser->cur = 0;
    parser->bol = 0;
    parser->row = 0;
    return parser;
}

#endif
