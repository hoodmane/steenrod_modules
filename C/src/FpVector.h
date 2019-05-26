//
// Created by Hood on 5/22/2019.
//

#ifndef C_FPVECTOR_H
#define C_FPVECTOR_H

#include <stdbool.h>
#define MAX_DIMENSION 10000
typedef unsigned long long uint64;
typedef long long int64;
typedef unsigned int uint;
int array_to_string(char * buffer, uint* A, uint length);

void initializeModpLookupTable(uint p);
void initializeLimbBitIndexLookupTable(uint p);

uint modPLookup(uint p, uint n);

typedef struct VectorInterface_s VectorInterface;

typedef struct  {
    struct VectorInterface_s * interface;
    uint p;
    uint dimension;
    uint size;
    uint offset;
} Vector;

typedef struct {
    bool has_more;
    uint index;
    uint value;
// private
    Vector * vector;
    uint limb_index;
    uint bit_index;    
} VectorIterator;

struct VectorInterface_s {    
    uint container_size;
    uint (*getEntriesPer64Bits)(uint p);
    uint (*getSize)(uint p, uint dimension, uint offset);
    
    Vector * (*initialize)(uint p, uint64 * vector_container, uint64 * memory, uint dimension, uint offset);
    Vector * (*construct)(uint p, uint dimension, uint offset);
    void (*free)(Vector * v); 

    void (*assign)(Vector * target, Vector * source);
    void (*setToZero)(Vector * target);
    void (*pack)(Vector * target, uint * source);
    void (*unpack)(uint * target, Vector * source);

    uint (*getEntry)(Vector * v, uint index);
    void (*setEntry)(Vector * v, uint index, uint value);
    
    void (*slice)(Vector *result, Vector *source, uint start, uint end);
    VectorIterator (*getIterator)(Vector * v); 
    VectorIterator (*stepIterator)(VectorIterator);

    void (*addBasisElement)(Vector * target, uint idx, uint c);
    void (*addArray)(Vector * target, uint * source, uint c);
    void (*add)(Vector * target, Vector * source, uint c);
    void (*scale)(Vector * target, uint c);   
};

extern VectorInterface VectorGenericInterface;
extern VectorInterface Vector2Interface;

uint getEntriesPer64Bits(uint p);
uint getVectorSize(uint p, uint dimension, uint offset);

Vector * initializeVector(VectorInterface *interface, uint p, uint64 * vector_container, uint64 * memory, uint dimension, uint offset);
Vector * constructVector(VectorInterface *interface, uint p, uint dimension, uint offset);

Vector * initializeVectorGeneric(uint p, uint64 * vector_container, uint64 * memory, uint dimension, uint offset);
Vector * constructVectorGeneric(uint p, uint dimension, uint offset);

Vector * initializeVector2(uint p, uint64 * vector_container, uint64 * memory, uint dimension, uint offset);
Vector * constructVector2(uint p, uint dimension, uint offset);

void freeVector(Vector * v); 

void assignVector(Vector * target, Vector * source);
void setVectorToZero(Vector * target);
void packVector(Vector * target, uint * source);
void unpackVector(uint * target, Vector * source);

uint getVectorEntry(Vector * v, uint index);
void setVectorEntry(Vector * v, uint index, uint value);

void sliceVector(Vector *result, Vector *source, uint start, uint end);
VectorIterator getVectorIterator(Vector * v); 
VectorIterator stepVectorIterator(VectorIterator);

// Maybe delete addArray methods?
void addBasisElementToVectorGeneric(Vector * target, uint idx, uint c);
void addArrayToVectorGeneric(Vector * target, uint * source, uint c);
void addVectorsGeneric(Vector * target, Vector * source, uint c);
void scaleVectorGeneric(Vector * target, uint c);

void addBasisElementToVector2(Vector * target, uint idx, uint c);
void addArrayToVector2(Vector * target, uint * source, uint c);
void addVectors2(Vector * target, Vector * source, uint c);
void scaleVector2(Vector * target, uint c);


uint vectorToString(char * buffer, Vector * v);
void printVector(uint p, Vector * v);

uint getMatrixSize(VectorInterface * interface, uint p, uint rows, uint cols);
Vector** initializeMatrix(uint64 * memory, VectorInterface * interface, uint p, uint rows, uint cols);
Vector** constructMatrix(VectorInterface * interface, uint p, uint rows, uint cols);

Vector** constructMatrixGeneric(uint p, uint rows, uint cols);
Vector** constructMatrix2(uint p, uint rows, uint cols);

uint matrixToString(char * buffer, Vector **M, uint rows);
void printMatrix(Vector **matrix, uint rows);

void rowReduce(Vector **matrix, int * column_to_pivot_row, uint rows);

#endif //C_FPVECTOR_H
