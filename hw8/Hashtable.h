#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <iostream>
#include <vector>

/**
 * A Hashtable to store <std::string, int> as the entries. The string represents
 * the element in the Hashtable, and the int represents the number of instances of
 * that string in the Hashtable.
 */
class Hashtable
{
public:
    /**
     * Creates a new Hashtable instance. Two optional parameters are provided, and by
     * default are turned off. If the debug parameter is set to true, then the Hashtable
     * should use the pre-prescribed random numbers in the assignment description. The
     * probing parameter will always be 0, 1, or 2, indicating the kind of collision
     * avoidance strategy.
     * 0: Linear probing
     * 1: Quadratic probing
     * 2: Double hashing
     */
    Hashtable(bool debug = false, unsigned int probing = 0);
    
    /**
     * Destructor.
     */
    ~Hashtable();
    
    /**
     * If the parameter k already exists as an element in the Hashtable, increment the
     * total number of entries. Otherwise create a new entry with a count of 1.
     */
    void add(const std::string& k);
    
    /**
     * Returns the total number of entries for the given string, or 0 if it does not
     * exist in the Hashtable.
     */
    int count(const std::string& k) const;
    
    /**
     * Outputs to the provided stream every key-value pair of elements in the Hashtable
     * in the order they appear. The output should follow the format that each
     * key-value pair is printed on a separate line, and the key is separated from the
     * value by a space .
     */
    void reportAll(std::ostream& out) const;
    
    
    
public:
    /**
     * A helper function to resize and rehash the entries in the table when the load
     * factor is >= 0.5. See the assignment description for the specific increments
     * when increasing the size of the Hashtable as well as other implementation details.
     */
    void resize();
    
    /**
     * The actual hash function that transforms the string input into the index where
     * the element should be stored. See the assignment for more details on how to
     * implement this function according to our specific guidelines.
     */
    int hash(const std::string& k) const;
    
    long long secondHash(const std::string& k) const;
    
private:
    /**
     * Include any additional private data members and/or helper functions to finish
     * this problem. 
     */
    // hashtable is a vector of pair
    // the first is the string, the second is the times this string appears
    std::vector<std::pair<std::string, int> > hash_array;
    
    // private variable
    int probing;
    bool debug;
    
    // default variable
    long long r1 = 983132572;
    long long r2 = 1468777056;
    long long r3 = 552714139;
    long long r4 = 984953261;
    long long r5 = 261934300;
    
    //resize hash table size
    long long resize_size[28] = {11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437, 102877, 205759, 411527, 823117, 1646237, 3292489, 6584983, 13169977, 26339969, 52679969, 105359969, 210719881, 421439783, 842879579, 1685759167};
    
    // second hash table size
    long long second_hash_size[28] = {7, 19, 43, 89, 193, 389, 787, 1583, 3191, 6397, 12841, 25703, 51431, 102871, 205721, 411503, 823051, 1646221, 3292463, 6584957, 13169963, 26339921, 52679927, 105359939, 210719881, 421439749, 842879563, 1685759113};
    
    double loadFactor();
    
    // record the number of different items, for the use of load factor
    int num_items;
    
};


#endif /* HASHTABLE_H*/
