/*
Jesse Martinez

SequenceableCollection.h
Declares a class SequenceableCollection that contains definitions for:
- default constructor
- a method that reports whether the collection is empty
- a method that gets the current size
- a method that reports its capacity
*/

class SequenceableCollection 
{
private:
    int* _elements; // Pointer to the dynamically allocated integer region
    int _start; // First occupied physical location
    int _end; // Last occupied phyical location
    int _capacity; // Stores the allocated region size

    void reallocate(); // doubles the capacity

public:

    SequenceableCollection(); // Default constructor

    ~SequenceableCollection(); // Destructor

    SequenceableCollection(const SequenceableCollection& other);

    SequenceableCollection& operator=(const SequenceableCollection& other);

    void set(int, int); // Modify an exisiting element

    bool isEmpty() const; // Checks whether the collection is empty

    int size() const; // Returns the size of the collection

    int capacity() const; // Getter of capacity variable

    void insert(int, int); // insert into a collection

    int get(int) const; // Retrieve the inserted value

};
