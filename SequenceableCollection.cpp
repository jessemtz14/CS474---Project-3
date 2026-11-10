#include "SequenceableCollection.h"
#include <stdexcept>

SequenceableCollection::SequenceableCollection() :
    _elements(new int[8]),
    _start(3),
    _end(2),
    _capacity(8)
{}

SequenceableCollection::SequenceableCollection(const SequenceableCollection& other) :
    _elements(new int[other._capacity]),
    _start(other._start),
    _end(other._end),
    _capacity(other._capacity){

    for(int i = 0; i < other.size(); i++){
        _elements[_start + i] = other._elements[other._start + i];
    }
}

SequenceableCollection::~SequenceableCollection(){
    delete[] _elements; // Release allocated array
}

SequenceableCollection& SequenceableCollection::operator=(const SequenceableCollection& other){
    if (this != &other){
        int* newElements = new int[other._capacity];

        for(int i = 0; i < other.size(); i++){
            newElements[other._start + i] = other._elements[other._start + i];
        }

        delete[] _elements;

        _elements = newElements;
        _start = other._start;
        _end = other._end;
        _capacity = other._capacity;
    }

    return *this;
}

bool SequenceableCollection::isEmpty() const {
    return _end < _start;
}

int SequenceableCollection::size() const {
    if(_end < _start){
        return 0;
    }

    return _end - _start + 1;
}

int SequenceableCollection::capacity() const {
    return _capacity;
}

void SequenceableCollection::reallocate(){
    int oldSize = size();
    int newCapacity = _capacity * 2;
    int newStart = (newCapacity - oldSize) / 2;

    int* newElements = new int[newCapacity];

    for(int i = 0; i < oldSize; i++){
        newElements[newStart + i] = _elements[_start + i];
    }
    delete[] _elements;

    _elements = newElements;
    _capacity = newCapacity;
    _start = newStart;
    _end = newStart + oldSize - 1;
}

void SequenceableCollection::insert(int pos, int val) {

    if(pos < 0 || pos > size()){ // Invalid position
        throw std::out_of_range("Invalid insertion position");
    }

    if(isEmpty() && pos == 0){ // If its the first element
        _elements[_start] = val;
        _end = _start;
        return;
    }

    if(_start == 0 && _end == _capacity - 1){ // if capacity is reached
        reallocate();
    }

    if(pos == 0){
        
        if(_start > 0){ // Insert at the front
             _start--;
            _elements[_start] = val;
        }
        else if(_end + 1 < _capacity){
            for (int i = _end; i >= _start; i--){
                _elements[i + 1] = _elements[i];
            }
            _elements[_start] = val;
            _end++;
        }

    }
    else if(pos == size()){ // Insert at the end

        if(_end + 1 >= _capacity && _start > 0){
            for(int i = _start; i <= _end; i++){
                _elements[i - 1] = _elements[i];
            }
            _start--;
            _end--;
        }
        if(_end + 1 < _capacity){
            _elements[_end + 1] = val;
            _end++;
        }

    }
    else if(pos > 0 && pos < size()){ // Insert in the middle
        if(_end + 1 < _capacity){
            for(int i = _end; i >= _start + pos; i--){
                _elements[i + 1] = _elements[i];
            }
            _elements[_start + pos] = val;
            _end++;
        }
        else if(_start > 0){
            for(int i = _start; i < _start + pos; i++){
                _elements[i - 1] = _elements[i];
            }
            _start--;
            _elements[_start + pos] = val; 
        }
    }
}

int SequenceableCollection::get(int pos) const{

    if(pos < 0 || pos >= size()){
        throw std::out_of_range("Invalid access point");
    }
    return _elements[_start + pos];
}

void SequenceableCollection::set(int pos, int val){
    if(pos < 0 || pos >= size()){
        throw std::out_of_range("Invalid set position");
    }
    _elements[_start + pos] = val;
}

