#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "main.h"

bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

bool is_operator(char c) {
    return c == '+' || c == '-';
}

bool is_white_space(char c) {
    return c == ' ';
}

void skip_whitespace(Interpreter *i) {
    while(i->text[i->current_pos] != '\n' && is_white_space(i->text[i->current_pos])) {
        i->current_pos++;
    }
}

void advance_token(Interpreter *i) {
    skip_whitespace(i);

    char c = i->text[i->current_pos];

    if (c == '\0' || c == '\n') {
        i->current_token.type = INVALID_TYPE;
        return; 
    }

    if (is_digit(c)) {
        i->current_token.type = INT;
        int value = 0;
        while (is_digit(i->text[i->current_pos])) {
            value = value * 10 + (i->text[i->current_pos] - '0');
            i->current_pos++;
        }
        i->current_token.value.int_value = value;
    } 
    else if (is_operator(c)) {
        i->current_token.type = OPERATOR;
        i->current_token.value.op_value = c;
        i->current_pos++;
    } 
    else {
        printf("Error: invalid character encountered: %c at pos %d\n", c, i->current_pos);
        exit(1);
    }
}

Token peek_next_token(Interpreter *i) {
    int temp_pos = i->current_pos;

    while (i->text[temp_pos] != '\0' && i->text[temp_pos] != '\n' && is_white_space(i->text[temp_pos])) {
        temp_pos++;
    }

    char c = i->text[temp_pos];
    Token next_token;

    if (c == '\0' || c == '\n') {
        next_token.type = INVALID_TYPE;
    } else if (is_digit(c)) {
        next_token.type = INT;
        int value = 0;
        while (is_digit(i->text[temp_pos])) {
            value = value * 10 + (i->text[temp_pos] - '0');
            temp_pos++;
        }
        next_token.value.int_value = value;
    } else if (is_operator(c)) {
        next_token.type = OPERATOR;
        next_token.value.op_value = c;
    } else {
        next_token.type = INVALID_TYPE;
    }

    return next_token;
}

bool is_invalid_next_token(Interpreter *i) {
    Token next_token = peek_next_token(i);
    if (i->current_token.type == next_token.type) {
        return true;
    }
    return false;
}


void parse_and_execute(Interpreter *i) {
    if (is_invalid_next_token(i)) {
        printf("Syntax error: invalid character '%c' at [%d]\n", i->text[i->current_pos], i->current_pos);
        exit(1);
    }
    if (i->current_token.type == INT) {
        if (i->current_operator == '+') i->result += i->current_token.value.int_value;
        else if (i->current_operator == '-') i->result -= i->current_token.value.int_value;
    }
    else if (i->current_token.type == OPERATOR) {
        i->current_operator = i->current_token.value.op_value;
    }
}

void interpret(char *text) {
    Interpreter i = {
        .current_pos = 0,
        .text = text,
        .current_operator = '+',
        .current_token = { .type = INVALID_TYPE },
        .result = 0
    };

    while (text[i.current_pos] != '\0' && text[i.current_pos] != '\n') {
        advance_token(&i);
        parse_and_execute(&i);
    }

    printf("%d\n", i.result);
}

int main() {
    char input[MAX_LENGTH];
    printf("Starting arithmetic interpreter...\n");
    while (true) {
        printf(">>> ");
        fgets(input, MAX_LENGTH ,stdin);
        interpret(input);
    }
    return 0;
}
