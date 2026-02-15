#define MAX_LENGTH 1000

typedef enum {
    INT,
    OPERATOR,
    INVALID_TYPE,
    WHITE_SPACE
} TokenType;

typedef struct {
    TokenType type;
    union {
        int int_value;
        char op_value;
    } value;
} Token;

typedef struct {
    int current_pos;
    char *text;
    Token current_token;
    char current_operator;
    int result;
} Interpreter;
