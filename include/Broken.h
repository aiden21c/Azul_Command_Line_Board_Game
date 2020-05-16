#ifndef APT_A2_BROKEN_H
#define APT_A2_BROKEN_H


#include "Types.h"

class Broken {
public:
    /**
     * Default constructor
     */
    Broken();

    /**
     * Construct broken vector from input string
     * @param input
     */
    explicit Broken(std::basic_string<char> input);

    /**
     * Default de-constructor
     */
    virtual ~Broken();

    /**
     * Add a tile to the broken list
     * @param tile
     * @return boolean state if add was successful
     */
    bool add(Tile tile);

    /**
     *
     * @param index
     * @return Tile at specifc index
     */
    Tile at(int index);

    /**
     * Clears the broken tiles vector
     */
    void clear();

    /**
     * @return String representation of broken "pile"
     */
    string toString() const;

    /**
     * @return vector of tiles
     */
    std::vector<Tile> getTiles() const;

    /**
     * @return size of broken tiles vector
     */
    int size() const;

private:
    /**
     * Vector of tiles
     */
    std::vector<Tile> tiles{};
};

#endif //APT_A2_BROKEN_H
