#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "defines.h"
#include "struct_node.h"
long double tree_culc(struct __tree_node* tree)
{
    switch(tree->type)
    {
        case CONSTANT:
            return tree->constant_value;
        case VARIABLE:
            return tree->constant_value;
        case UNARY_MINUS:
            return -tree_culc(tree->pointer_down);
        case SUM:
            return tree_culc(tree->pointer_left) + tree_culc(tree->pointer_right);
        case SUB:
            return tree_culc(tree->pointer_left) - tree_culc(tree->pointer_right);
        case MUL:
            return tree_culc(tree->pointer_left) * tree_culc(tree->pointer_right);
        case FRAC:
            return tree_culc(tree->pointer_left) / tree_culc(tree->pointer_right);
        case SQRT:
            return sqrt(tree_culc(tree->pointer_down));
        case LN:
            return log(tree_culc(tree->pointer_down));
        case EXP:
            return exp(tree_culc(tree->pointer_down));
        case SIN:
            return sin(tree_culc(tree->pointer_down));
        case COS:
            return cos(tree_culc(tree->pointer_down));
        case TAN:
            return tan(tree_culc(tree->pointer_down));
        case ARCSIN:
            return asin(tree_culc(tree->pointer_down));
        case ARCCOS:
            return acos(tree_culc(tree->pointer_down));
        case ARCTAN:
            return atan(tree_culc(tree->pointer_down));
        default:
            return 0;
    }
}
int main(void)
{

    return 0;
}
