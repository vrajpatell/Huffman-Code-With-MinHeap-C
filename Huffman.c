#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "Huffman.h"
int top=0;

//--------#---------#---------#---------#--------#
static inline void exchangePtr( HuffmanNodePtr *a, HuffmanNodePtr *b ) \
  {
  HuffmanNodePtr t;
  t = *a;
  *a = *b;
  *b = t;
  }

//--------#---------#---------#---------#--------#
static inline int LEFT(int i)   { /* PUT SOMETHING HERE */ return 2 * i + 1 ;}
static inline int RIGHT(int i)  { /* PUT SOMETHING HERE */ return 2 * i + 2; }
static inline int PARENT(int i) { /* PUT SOMETHING HERE */ return ((i + 1) / 2) - 1; }
//--------#---------#---------#---------#--------#
static void minHeapify( HuffmanHeapPtr h, int i )
{
 
  int smallest = i;
  int ell = LEFT(i);
  int arr = RIGHT(i);
  if (ell < h->heapsize && h->A[ell]->frequency < h->A[smallest]->frequency)
  {
  smallest = ell;
  }
  if (arr < h->heapsize && h->A[arr]->frequency < h->A[smallest]->frequency) 
  {
      smallest = arr;
  }
  if (smallest != i) 
  { 
        exchangePtr(&h->A[smallest], &h->A[i]); 
        minHeapify(h, smallest); 
  } 
}

//--------#---------#---------#---------#--------#
void addElement( HuffmanHeapPtr h, HuffmanNodePtr newNodePtr )
{
  ++h->heapsize; 
  int n = h->heapsize - 1; 
  int count=0;
  while (n && (newNodePtr->frequency < h->A[(n - 1) / 2]->frequency))
  { 
h->A[n] = h->A[(n - 1) / 2]; 
        n = (n - 1) / 2; 
  } 
  h->A[n] = newNodePtr; 
}

//--------#---------#---------#---------#--------#
HuffmanNodePtr buildHuffmanCode( HuffmanHeapPtr h )
{
  struct _HuffmanNode *top,*left,*right;
  while(h->heapsize > 1)
  {
  left = extractMin(h);
  right = extractMin(h);
  top = makeHuffmanNode(-1, left->frequency + right->frequency);
top->left=left;
top->right=right;
  addElement(h, top);
  }
  return extractMin(h);
  
}

int temp=0;
int printArr(HuffmanNodePtr n, char arr[], int top) 
{ 

if(!(n->left) && !(n->right))
{
printf("%c : %3d : ", n->character, n->frequency); 
int i; 
for (i = 0; i < top; ++i) 
{	
printf("%c", arr[i]); 
}

printf("\n");
temp=temp+(n->frequency)*top;
}

if (n->left) { 

arr[top] = '0'; 
printArr(n->left, arr, top+1);
} 
if (n->right) { 

arr[top] = '1'; 
printArr(n->right, arr, top+1);
} 

return(temp);
} 

//--------#---------#---------#---------#--------#
int dumpHuffmanCode( HuffmanNodePtr n )
{
char *arr = (char *)malloc(sizeof(char));

int bits=printArr(n, arr, 0); 

free(arr);

return(bits);
}


//--------#---------#---------#---------#--------#
HuffmanNodePtr extractMin( HuffmanHeapPtr h )
{

  HuffmanNodePtr temp = h->A[0];
  h->A[0] = h->A[h->heapsize - 1];
  --h->heapsize;
  minHeapify(h,0);
  return temp;  
}

//--------#---------#---------#---------#--------#
HuffmanHeapPtr makeHuffmanHeap( int size )
{
  HuffmanHeapPtr h = (HuffmanHeapPtr)malloc(sizeof(struct _HuffmanHeap));
  h->heapsize = 0;
  h->size = size;
  h->A=(HuffmanNodePtr*)malloc((h->size)*sizeof(HuffmanNodePtr));
  return h;
}

//--------#---------#---------#---------#--------#
HuffmanNodePtr makeHuffmanNode( int character, int frequency )
{
    HuffmanNodePtr n = (HuffmanNodePtr)malloc(sizeof(struct _HuffmanNode));
  
  n->character = character;
  n->frequency = frequency;
  n->left = NULL;
n->right = NULL;
  return n;
}



//--------#---------#---------#---------#--------#
void dumpHuffmanHeap( HuffmanHeapPtr h )
{
  printf( "===== Huffman Heap =====\n" );
  printf( "size %d, heapsize %d\n", h->size, h->heapsize );
  for ( int i=0; i < h->heapsize; i++ ) {
    dumpHuffmanNode( h->A[i], 1 );
  }
}

//--------#---------#---------#---------#--------#
void dumpHuffmanNode( HuffmanNodePtr n, int indent )
{
  printf( "%*c", indent*2, ' ' );

  if ( n->character == -1 ) {
    printf( "[Interior] %d\n", n->frequency );
    dumpHuffmanNode( n->left, indent+1 );
    dumpHuffmanNode( n->right, indent+1 );
  } else {
    if ( isprint( n->character ) ) {
      printf( "'%c' %d\n", n->character, n->frequency );
    } else {
      printf( "%03d %d\n", n->character, n->frequency );
    }
  }
}

//--------#---------#---------#---------#--------#
