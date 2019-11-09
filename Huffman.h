// Patel, Vraj H
// vhp9326
// 2019-07-30
//--------#---------#---------#---------#--------#

typedef struct _HuffmanNode {
  int frequency;
  int character;
  struct _HuffmanNode *left;
  struct _HuffmanNode *right;
} HuffmanNode, *HuffmanNodePtr;

typedef struct _HuffmanHeap {
  HuffmanNodePtr *A;
  int size;
  int heapsize;
} HuffmanHeap, *HuffmanHeapPtr;

//--------#---------#---------#---------#--------#

void addElement( HuffmanHeapPtr h, HuffmanNodePtr newNodePtr );
HuffmanNodePtr buildHuffmanCode( HuffmanHeapPtr h );
int dumpHuffmanCode( HuffmanNodePtr n );
void dumpHuffmanHeap( HuffmanHeapPtr h );
void dumpHuffmanNode( HuffmanNodePtr n, int indent );
HuffmanNodePtr extractMin( HuffmanHeapPtr h );
HuffmanHeapPtr makeHuffmanHeap( int size );
HuffmanNodePtr makeHuffmanNode( int character, int frequency );

//--------#---------#---------#---------#--------#
