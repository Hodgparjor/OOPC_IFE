 #pragme once
 #include <iostream>
 
 using namespace std;
 
 template<class K, class V> Map {
  public:
    Map() {}
    ~Map() {}
    add(K key, V value) {}
    find(K key) {}
  private:
    struct keyValueNode {
		keyValueNode* next;
		K key;
		V value;
	}
};
