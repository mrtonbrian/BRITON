//
// Created by brianton on 5/31/20.
//

#include <cstdlib>
#include <iostream>
#include <cstring>
#include "TranspositionTable.h"
#include "Position.h"

#define MB 0x100000

HashTable globalHashTable;

void HashTable::initHashTable(int sizeMB) {
    numEntries = (sizeMB * MB) / sizeof(HashEntry);
    // Preventing Overflow
    numEntries -= 2;
    if (entries != NULL) {
        free(entries);
    }
    entries = (HashEntry *) malloc(numEntries * sizeof(HashEntry));

    std::cout << "HashTable init complete with " << numEntries << " entries" << std::endl;
}

void HashTable::clearHashTable() {
    memset(entries, 0, numEntries * sizeof(HashEntry));
}

void HashTable::storePvMove(uint64_t position, int move) {
    int index = position % numEntries;

    entries[index].positionKey = position;
    entries[index].move = move;
}

int HashTable::probeTable(uint64_t position) {
    int index = position % numEntries;

    if (entries[index].positionKey == position) {
        return entries[index].move;
    }
    return -1;
}