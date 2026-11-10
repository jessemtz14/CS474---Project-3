#include <iostream>
using namespace std;
#include <cassert>
#include "SequenceableCollection.h"
#include <stdexcept> 

void printCollection(const SequenceableCollection& collection)
{
    std::cout << "[";

    for (int i = 0; i < collection.size(); i++)
    {
        std::cout << collection.get(i);

        if (i < collection.size() - 1)
        {
            std::cout << ", ";
        }
    }

    std::cout << "]\n";
}

int main(){
    cout << "Testing inserting at start middle and end:" << endl;

    SequenceableCollection collection; //test constructor

    assert(collection.isEmpty()); // Test isEmpty()

    assert(collection.size() == 0); // Test size()

    assert(collection.capacity() == 8); // Test capacity()

    collection.insert(0, 42);
    printCollection(collection);

    assert(!collection.isEmpty()); // Insert into collection 
    assert(collection.size() == 1); // Size is now 1
    assert(collection.capacity() == 8); // still 8 becuase memory hasnt been allocated for it
    assert(collection.get(0) == 42);

    collection.insert(1,99);    // Second insert
    printCollection(collection);
    
    assert(collection.size() == 2); // size should be 2 now
    assert(collection.get(0) == 42); // get first element
    assert(collection.get(1) == 99); // get second element
    assert(collection.capacity() == 8); //capacity is still 8

    collection.insert(1, 77); // Insert in the middle
    printCollection(collection);

    assert(collection.size() == 3); // Size should be 3 now
    assert(collection.get(0) == 42);
    assert(collection.get(1) == 77);
    assert(collection.get(2) == 99); // [42, 77, 99]

    collection.insert(0, 11); // Insert at the front after multuiple insertions
    printCollection(collection);

    assert(collection.size() == 4); // Size should be 4 now
    assert(collection.get(0) == 11);
    assert(collection.get(1) == 42);
    assert(collection.get(2) == 77); 
    assert(collection.get(3) == 99); // [11,42,77,99]

    collection.insert(0, 14); // Insert at the front after multuiple insertions
    printCollection(collection);

    assert(collection.size() == 5); // Size should be 4 now
    assert(collection.get(0) == 14);
    assert(collection.get(1) == 11);
    assert(collection.get(2) == 42);
    assert(collection.get(3) == 77); 
    assert(collection.get(4) == 99); // [14,11,42,77,99]


    /////////////////////////////////////////////////////////////////
    // Test full list now
    /////////////////////////////////////////////////////////////////

    SequenceableCollection full;
    full.insert(0,1);
    full.insert(1,2);
    full.insert(2,3);
    full.insert(3,4);
    full.insert(4,5);
    full.insert(0,6);
    full.insert(0,7);
    full.insert(0,8);
    
    cout << "Full Test: " << endl;
    printCollection(full);

    assert(full.size() == 8);
    assert(full.capacity() == 8);

    // Insert after capacity is reached
    full.insert(8, 9);

    cout << "After resize:" << endl;
    printCollection(full);

    assert(full.size() == 9);
    assert(full.capacity() == 16); // new allocated memory
    assert(full.get(0) == 8);
    assert(full.get(1) == 7);
    assert(full.get(2) == 6);
    assert(full.get(3) == 1);
    assert(full.get(4) == 2);
    assert(full.get(5) == 3);
    assert(full.get(6) == 4);
    assert(full.get(7) == 5);
    assert(full.get(8) == 9);

    for (int value = 10; value <= 16; value++){
        full.insert(full.size(), value);
    }

    cout << full.size() << endl;
    assert(full.size() == 16);
    assert(full.capacity() == 16);

    // 17th value
    full.insert(full.size(), 17);

    printCollection(full);

    assert(full.size() == 17);
    assert(full.capacity() == 32);

    bool invalidInsertRejected = false;

    try
    {
        full.insert(full.size() + 1, 18);
    }
    catch (const std::out_of_range&)
    {
        invalidInsertRejected = true;
    }

    assert(invalidInsertRejected);



    bool invalidGetRejected = false;

    try
    {
        full.get(full.size());
    }
    catch (const std::out_of_range&)
    {
        invalidGetRejected = true;
    }

    assert(invalidGetRejected);

    // copy constructor test
    SequenceableCollection original;
    original.insert(0,0);
    original.insert(1,1);

    SequenceableCollection copy(original);

    assert(copy.size() == 2);
    assert(copy.get(0) == 0);
    assert(copy.get(1) == 1);

    cout << "Before change:" << endl;
    printCollection(copy);

    // modify exisiting element
    copy.set(0, 200);

    cout << "After changes: " << endl;
    printCollection(copy);


    assert(copy.get(0) == 200);
    assert(original.get(0) == 0);

    //copy assignment
    SequenceableCollection assigned;
    cout << "Original:\n";
    printCollection(original);

    assigned = original;
    cout << "Assigned:" << endl;
    printCollection(assigned);

    assert(assigned.size() == original.size());
    assert(assigned.get(0) == original.get(0));
    assert(assigned.get(1) == original.get(1));

    assigned.set(0, 300);
    cout << "Changed assgined:" << endl;
    printCollection(assigned);

    assert(assigned.get(0) == 300);
    assert(original.get(0) == 0);



    SequenceableCollection edge;

    for (int value = 1; value <= 12; value++)
    {
        edge.insert(edge.size(), value);
    }

    edge.insert(2, 99);

    printCollection(edge);

    assert(edge.size() == 13);
    assert(edge.get(0) == 1);
    assert(edge.get(1) == 2);
    assert(edge.get(2) == 99);
    assert(edge.get(3) == 3);
    assert(edge.get(12) == 12);

    // invalid set
    bool invalidSetRejected = false;

    try
    {
        full.set(full.size(), 500);
    }
    catch (const std::out_of_range&)
    {
        invalidSetRejected = true;
    }

    assert(invalidSetRejected);

    //self assginment
    assigned = assigned;

    assert(assigned.size() == 2);
    assert(assigned.get(0) == 300);
    assert(assigned.get(1) == 1);

    //edge case: front insertion when _start = 0
    SequenceableCollection frontEdge;

    frontEdge.insert(0, 1);
    frontEdge.insert(0, 2);
    frontEdge.insert(0, 3);
    frontEdge.insert(0, 4);
    frontEdge.insert(0, 5);

    printCollection(frontEdge);

    assert(frontEdge.size() == 5);
    assert(frontEdge.get(0) == 5);
    assert(frontEdge.get(4) == 1);

    // copy resized collection
    cout << "Resized copy test:" << endl;

    SequenceableCollection resizedCopy(full);

    cout << "Original full collection:" << endl;
    printCollection(full);

    cout << "Copied collection:" << endl;
    printCollection(resizedCopy);

    assert(resizedCopy.size() == full.size());
    assert(resizedCopy.capacity() == full.capacity());

    for (int i = 0; i < full.size(); i++)
    {
        assert(resizedCopy.get(i) == full.get(i));
    }

    resizedCopy.set(0, 999);

    cout << "After changing copied collection:" << endl;
    printCollection(resizedCopy);

    cout << "Original collection should be unchanged:" << endl;
    printCollection(full);

    assert(resizedCopy.get(0) == 999);
    assert(full.get(0) != 999);

    //resized assignment test
    cout << "Resized assignment test:" << endl;

    SequenceableCollection resizedAssigned;

    resizedAssigned = full;

    cout << "Assigned resized collection:" << endl;
    printCollection(resizedAssigned);

    assert(resizedAssigned.size() == full.size());
    assert(resizedAssigned.capacity() == full.capacity());

    for (int i = 0; i < full.size(); i++)
    {
        assert(resizedAssigned.get(i) == full.get(i));
    }

    resizedAssigned.set(0, 888);

    cout << "After changing assigned collection:" << endl;
    printCollection(resizedAssigned);

    cout << "Original full collection:" << endl;
    printCollection(full);

    assert(resizedAssigned.get(0) == 888);
    assert(full.get(0) != 888);

    return 0;
}

