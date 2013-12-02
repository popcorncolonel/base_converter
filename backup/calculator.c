#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "parser.h"

typedef struct operator {
        char operator;
        int lhs;
        int rhs;
} operator;

// 1 + 3 + 5
// 1 * 2 * 3 + 4 * 2 * 5
//    *, *, +, *, * 
// 3 + 4 * 8 + 2 * 16
// +, *, +, *

int num_ops = 0;

/* TODO: parentheses, exponentiation */
/* orders an array of operators - precidence = '*' == '/' > '+' == '-' */
//static inline operator *calculate_muls(operator *ops);
static inline int num_valid_ops(operator *ops);
static inline void singularize_ops(operator *ops);
static inline int do_op(operator op);
int calculate(char **cmds, int num_cmds, int base)
{
        char op= '\0';
        int num = 0;
        int i;
        num_ops = (num_cmds - 1) / 2;
        /* size is 12 */
        operator oplist[num_ops];
        for (i = 0; i < num_cmds; i++) {
                if (i % 2 == 0) /* is a number */
                {
                        num = n_to_dec(cmds[i], base);
                        if (i != 0)        oplist[(i - 2) / 2].rhs = num;
                        if (i != num_cmds) oplist[(i    ) / 2].lhs = num;
                }
                else /* is an operator */
                {
                        op = cmds[i][0];
                        if  (cmds[i][1] != '\0') syntax_error(cmds[i]);
                        oplist[(i - 1) / 2].operator = op;
                }
        }
        /* getting it down to just one operation in PEMDAS order */
        singularize_ops(oplist);
        for (i = 0; i < num_ops; i++)
        {
                if (oplist[i].operator != '\0')
                {
                        num = do_op(oplist[i]);
                        break;
                }
        }
        return num;
}

static inline void set_right_op(operator *ops, int i, int answer)
{
        int j;
        for (j = i + 1; j < num_ops; j++)
        {
                if (ops[j].operator != '\0') {
                        ops[j].lhs = answer;
                        return;
                }
        }
}

static inline void set_left_op(operator *ops, int i, int answer)
{
        int j;
        for (j = i - 1; j >= 0; j--)
        {
                if (ops[j].operator != '\0') {
                        ops[j].rhs = answer;
                        return;
                }
        }
}

static inline void singularize_ops(operator *ops)
{
        int i;
        int answer = 0;
        operator *op;
        for (i = 0; i < num_ops; i++)
        {
                op = &ops[i];
                if (num_valid_ops(ops) != 1) {
                        if ((* op).operator == '*' || (* op).operator == '/') {
                                answer = do_op(ops[i]);
                                (* op).operator = '\0';
                                set_right_op(ops, i, answer);
                                set_left_op(ops, i, answer);
                                singularize_ops(ops);
                                return;
                        }
                }
        }

        for (i = 0; i < num_ops; i++)
        {
                op = &ops[i];
                if (num_valid_ops(ops) != 1) {
                        if ((* op).operator == '+' || (* op).operator == '-') {
                                answer = do_op(ops[i]);
                                (* op).operator = '\0';
                                set_right_op(ops, i, answer);
                                set_left_op(ops, i, answer);
                                singularize_ops(ops);
                                return;
                        }
                }
        }
}

static inline int num_valid_ops(operator *ops)
{
        int i, total = 0;
        for(i = 0; i < num_ops; i++)
                if (ops[i].operator != '\0')
                        total++;
        return total;
}

static inline int do_op(operator op)
{
        int to_return = 0;
        switch (op.operator)
        {
                case '+':
                        to_return = op.lhs + op.rhs;
                        break;
                case '-':
                        to_return = op.lhs - op.rhs;
                        break;
                case '*':
                        to_return = op.lhs * op.rhs;
                        break;
                case '/':
                        to_return = op.lhs / op.rhs;
                        break;
        }
        return to_return;
}

