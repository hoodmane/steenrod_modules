//
// Created by Hood on 5/20/2019.
//

#ifndef CSTEENROD_ALGEBRA_H
#define CSTEENROD_ALGEBRA_H
#include <stdbool.h>

#include "FpVector.h"

typedef struct {
    uint length;
    uint *degrees;
    uint *indices;
} FiltrationOneProductList;

typedef struct Algebra {
    uint p;
    uint max_degree; 
    char *name;
    FiltrationOneProductList *product_list; // This determines which indecomposibles have lines drawn for them.
// Methods:
    void (*computeBasis)(struct Algebra* this, uint degree);
    uint (*getDimension)(struct Algebra* this, int degree, uint excess);
    void (*multiplyBasisElements)(struct Algebra* this, Vector *result, uint coeff, uint r_degree, uint r, uint s_degree, uint s, uint excess);
} Algebra;

// Careful with these macros: could cause multiple evaluation of algebra / module.
#define algebra_computeBasis(algebra, degree) (*(algebra)->computeBasis)(algebra, degree)
#define algebra_getDimension(algebra, degree, excess) (*(algebra)->getDimension)(algebra, degree, excess)
#define algebra_multiplyBasisElements(algebra, result, coeff, r_deg, r, s_deg, s, excess) (*(algebra)->multiplyBasisElements)(algebra, result, coeff, r_deg, r, s_deg, s, excess)
#define algebra_getFiltrationOneProducts(algebra) (*(algebra)->getFiltrationOneProducts)(algebra)




#endif //CSTEENROD_ALGEBRA_H
