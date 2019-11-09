// Dalio, Brian A.
// dalioba
// 2019-07-25
//--------#---------#---------#---------#--------#
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "Huffman.h"

//--------#---------#---------#---------#--------#
// DO NOT CHANGE ANYTHING IN THIS FILE!
//--------#---------#---------#---------#--------#
int main( int argc, char *argv[] ) {
  HuffmanHeapPtr heap;

  // No buffering of output.
  setbuf( stderr, NULL );
  setbuf( stdout, NULL );

  // Enable thousand separators in printf().
  setlocale( LC_NUMERIC, "" );

  // Open the source file.
  if ( argc != 2 ) {
    fprintf( stderr, "Usage: %s <fName>\n", argv[0] );
    exit( 1 );
  }

  FILE *fp = fopen( argv[1], "r" );
  if ( fp == NULL ) {
    fprintf( stderr, "Unable to open '%s'.\n", argv[1] );
    exit( 1 );
  }

  // Count the ASCII characters in the given file.
  int numChars  = 0;
  int *charFreq = (int *) calloc( 128, sizeof( int ) );
  if ( charFreq == NULL ) {
    fprintf( stderr, "Unable to allocate character frequency table.\n" );
    exit( 1 );
  }

  for ( int ch = fgetc( fp ); ch != EOF; ch = fgetc( fp ) ) {
    numChars++;
    if ( ch < 128 ) {
      charFreq[ch]++;
    } else {
      fprintf( stderr, "Non-ASCII character %03d at position %d.\n", ch, numChars );
    }
  }

  // Allocate a heap that has enough space for all ASCII chars.
  heap = makeHuffmanHeap( 128 );

  // Add all non-zero characters to the heap.
  for ( int i = 0; i < 128; i++ ) {
    if ( charFreq[i] > 0 ) {
      addElement( heap, makeHuffmanNode( i, charFreq[i] ) );
    }
  }

  // Build the Huffman Code ...
  HuffmanNodePtr n = buildHuffmanCode( heap );

  // ... and dump it out.
  int bits = dumpHuffmanCode( n );
  double ratio = bits / (8.0*numChars);

  printf( "%'d characters, %'d fixed bits, %'d Huffman bits (%'d bytes), ratio %.4f.\n",
    numChars, 8*numChars, bits, (bits+7)/8, ratio );
}

//--------#---------#---------#---------#--------#
