 #pragma once
 #include <iostream>
 
 using namespace std;

 class KeyAlreadyExistsException : public exception {
  public:
    const char* what() const throw() {
      return "Key already exists";
    }
};

class KeyNotFoundException : public exception {
  public:
    const char* what() const throw() {
      return "Key not found";
    }
};
 
 template<class Key, class Value> class Map {
  public:
    Map();
    Map(const Map<Key, Value>& map);
    ~Map();
    Map& operator=(const Map<Key, Value>& map);
    void add(Key key, Value value);
    Value* find(Key key);
    void remove(Key key);
    template<class SKey, class SValue> friend ostream& operator<<(ostream& out, const Map<SKey, SValue>&  map);
  private:
    long checkKey(Key key);
    void resize();
    Key* keys;
    Value* values;
    size_t currentSize;
    size_t allocatedSize;
};

template<class Key, class Value> Map<Key, Value>::Map() {
  this->currentSize = 0;
  this->allocatedSize = 50;
  this->keys = new Key[this->allocatedSize];
  this->values = new Value[this->allocatedSize];
}

template<class Key, class Value> Map<Key, Value>::Map(const Map<Key, Value>& map) {
  this->currentSize = map.currentSize;
  this->allocatedSize = map.allocatedSize;
  this->keys = new Key[this->allocatedSize];
  this->values = new Value[this->allocatedSize];
  for(size_t index = 0; index < map.currentSize; index++) {
    this->values[index] = map.values[index];
    this->keys[index] = map.keys[index];
  }
}

template<class Key, class Value> Map<Key, Value>::~Map() {
  delete[] this->values;
  delete[] this->keys;
}

template<class Key, class Value> Map<Key, Value>& Map<Key,Value>::operator=(const Map<Key, Value>& map) {
  if(this == &map) {
    return *this;
  }
  this->currentSize = map.currentSize;
  this->allocatedSize = map.allocatedSize;
  delete[] this->values;
  delete[] this->keys;
  this->keys = new Key[map.allocatedSize];   
  this->values = new Value[map.allocatedSize];
  for(size_t index = 0; index < map.currentSize; index++) {
    this->values[index] = map.values[index];
    this->keys[index] = map.keys[index];
  }
  return *this;
}

template<class Key, class Value> long  Map<Key, Value>::checkKey(Key key) {
  for(long index = 0; index < (long)this->currentSize; index++) {
    if(this->keys[index] == key) {
      return index;
    }
  }
  return -1;
}

template<class Key, class Value> void Map<Key, Value>::resize() {
  this->allocatedSize *= 2;
  Key* newKeys = new Key[this->allocatedSize];
  Value* newValues = new Value[this->allocatedSize];
  for(size_t index = 0; index < this->currentSize; index++) {
    newKeys[index] = this->keys[index];
    newValues[index] = this->values[index];
  }
  delete[] this->keys;
  delete[] this->values;
  this->keys = newKeys;
  this->values = newValues;
}

template<class Key, class Value> void Map<Key, Value>::add(Key key, Value value) {
  if(this->checkKey(key) != -1) {
    throw KeyAlreadyExistsException();
  }
  this->currentSize++;
  if(this->currentSize < this->allocatedSize) {
    this->resize();
  }
  this->keys[this->currentSize - 1] = key;
  this->values[this->currentSize - 1] = value;
}

template<class Key, class Value> Value* Map<Key, Value>::find(Key key) {
  long foundIndex = this->checkKey(key);
  if (foundIndex != -1) {
    return &this->values[foundIndex];
  } else {
    throw KeyNotFoundException();
  }
}

template<class Key, class Value> void Map<Key, Value>::remove(Key key) {
  long keyIndex = this->checkKey(key);
  if(keyIndex == -1) {
    throw KeyNotFoundException();
  }
  for(size_t index = (size_t)keyIndex + 1; index < this->currentSize; index++) {
    this->keys[index - 1] = this->keys[index];
    this->values[index - 1] = this->values[index];
  }
  this->currentSize--;
}

template<class Key, class Value> ostream& operator<<(ostream& out, const Map<Key, Value>& map) {
  for(size_t index = 0; index < map.currentSize; index++) {
    out << "---Pair No." << index + 1 << "---" << endl;
    out << "    Key| " << map.keys[index] << endl;
    out << "  Value| " << map.values[index] << endl << endl;
  }
  return out;
}