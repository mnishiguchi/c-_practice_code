//
//  Computer Science II
//  FunThing 3
//
//  Masatoshi Nishiguchi
//
//  Due: Saturday, April 16
//


#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cassert>
using namespace std;


//====================================================//
// FunThing class and its subclasses
//====================================================//


/**
 * Represents a fun thing.
 */
class FunThing {
public:

    // Constructor that is called via subclasses.
    FunThing( string thingName, int funLevel ) {
        this->funLevel  = funLevel;
        this->thingName = thingName;
    }

    // The destructor of the base class must be virtual.
    virtual ~FunThing() {}

    // Copy constructor.
    // - No need for custom copy because this class does not contain any pointer members.

    // Setters & getters.
    int getFunLevel() const { return funLevel; }
    void setFunLevel( int funLevel ) { this->funLevel = funLevel; }
    string getThingName() const { return thingName; }
    void setThingName( string thingName ) { this->thingName = thingName; }

    // Overload the pre-increment operators that takes no argument.
    // @return The FunThing object that has been updated.
    FunThing& operator++() {
        // Increment the funLevel and return this instance by reference.
        ++( this->funLevel );
        return *this;
    }

    // Overload the pre-decrement operators that takes no argument.
    // @return The FunThing object that has been updated.
    FunThing& operator--() {
        // Decrement the funLevel and return this instance by reference.
        --( this->funLevel );
        return *this;
    }
protected:
    int funLevel;
    string thingName;

}; // end FunThing

/**
 * Non-member Operator Overload.
 */
ostream& operator<<( ostream& os, const FunThing& obj ) {

    // TODO
    return os << "TODO: overload << operator for FunThing" << endl;

}


//====================================================//
// FunThing family A
//====================================================//


/**
 * Subclass of FunThing.
 */
class GenericThing : public FunThing {
public:
    // Constructor
    GenericThing( string thingName, int funLevel, int numberOfPlayers, bool isDangerous )
        : FunThing( thingName, funLevel ) {

        this->numberOfPlayers = numberOfPlayers;
        this->dangerous       = isDangerous;
    }

    int getNumberOfPlayers() { return this->numberOfPlayers; }
    bool isDangerous() { return this->dangerous; }
    string getFunLevelText() const;
    string getDangerText() const;

protected:
    bool dangerous;
    int numberOfPlayers;
}; // end GenericThing


/**
 * if 8 or more        : super-fun
 * if 7                : very fun
 * if 3-6, inclusive   : ok fun
 * if 0 - 2, inclusive : no fun
 * if less than 0      : pretty boring
 * @return text that describes the fun level.
 */
string GenericThing::getFunLevelText() const {
    if      ( funLevel >= 8 ) { return "super-fun"; }
    else if ( funLevel >= 7 ) { return "very fun"; }
    else if ( funLevel >= 3 ) { return "ok fun"; }
    else if ( funLevel >= 0 ) { return "no fun"; }

    // Anything else is "pretty boring".
    return "pretty boring";
}


/**
 * @return "Be careful, it can be dangerous" if the GenericThing is dangerous,
 * else "It's fun for Everyone.
 */
string GenericThing::getDangerText() const {
    return ( dangerous ) ? "Be careful, it can be dangerous" : "It's fun for Everyone";
}


/**
 * Subclass of FunThing. All instances of CrazySport considered dangerous.
 */
class CrazySport : public GenericThing {
public:
    // Constructor
    CrazySport( string thingName, int funLevel, int numberOfPlayers )
        : GenericThing( thingName, funLevel, numberOfPlayers, true ) {
    }
}; // end CrazySport


/**
 * Subclass of GenericThing. All instances of DomesticChore are NOT dangerous.
 */
class DomesticChore : public GenericThing {
public:
    // Constructor
    DomesticChore( string thingName, int funLevel, int numberOfPlayers )
        : GenericThing( thingName, funLevel, numberOfPlayers, false ) {
    }
}; // end DomesticChore


//====================================================//
// FunThing family B
//====================================================//


/**
 * Abstruct class that extends FunThing. Throws std::length_error.
 * Contains 1 purely virtual method called getRules() that will
 * return a VERY SHORT (50 characters or less) string of the basic rules of the game.
 * Also make a method called setRules() as a setter for BoardGame rules.
 * All BoardGame will output ONLY their rules when a left-shift operator is applied.
 */
class BoardGame : public FunThing {
public:
    // Requirement:
    // @return a VERY SHORT (50 characters or less) string of the basic rules of the game.
    virtual string getRules() const =0;
    virtual void setRules( string ) const =0;

    // NOTE: This is an abstract class; it does not hold any attributes.
    // Instead, add appropriate attributes in subclasses.

    // Constructor
    BoardGame( string thingName, int funLevel, string rules )
        : FunThing( thingName, funLevel ) {
    }
}; // end BoardGame


/**
 * Non-member Operator Overload.
 * All BoardGame will output ONLY their rules when this operator is applied.
 */
ostream& operator<<( ostream& os, const BoardGame& obj ) {
    return os << "Rules of " << obj.getThingName() << "\n" << obj.getRules();
}


/**
 * extends BoardGame
 */
class TwoPlayerBG : public BoardGame {
public:
    // Constructor
    TwoPlayerBG( string thingName, int funLevel, string rules )
        : BoardGame( thingName, funLevel, rules ) {
        this->rules = "undefined";
    }

    string getRules() const {
        return rules;
    }
    void setRules( string rules ) {
        if ( rules.length() > 50 ) {
            throw std::length_error(std::string("Error: max length is 50 characters for rules"));
        }
        this->rules = rules;
    }

private:
    string rules;
}; // end TwoPlayerBG


/**
 * extends BoardGame
 */
class MultiPlayerBG : public BoardGame {
public:
    // Constructor
    MultiPlayerBG( string thingName, int funLevel, string rules )
        : BoardGame( thingName, funLevel, rules ) {
        this->rules = "undefined";
    }

    string getRules() const { return this->rules; }
private:
    string rules;
}; // end MultiPlayerBG


//====================================================//
// Test functions
//====================================================//


template <typename DataType>
void assert_eq( DataType expected, DataType actual ) {
    if ( expected != actual ) {
        cout << "  Fail: \"" << actual << "\" should be equal to \"" << expected << "\"" << endl;
        assert( false );
    }
    cout << "  \"" << actual << "\" is equal to \"" << expected << "\"" << endl;
}

// TODO


//====================================================//
// Main Function
//====================================================//


int main() {
    // Tests.
    // TODO

    // Instantiate at least two instances of TwoPlayerBG and MultiPlayerBG.
    string rules = "Lorem ipsum dolor sit amet.";

    // TwoPlayerBG* chess      = new TwoPlayerBG( "chess", 43, rules );
    // TwoPlayerBG* poker      = new TwoPlayerBG( "poker", 55, rules );
    // MultiPlayerBG* trouble  = new MultiPlayerBG( "trouble", 11, rules );
    // MultiPlayerBG* sorry    = new MultiPlayerBG( "sorry", 132, rules );

    // Appropriately add each instance to the following vector:
    vector<FunThing*> v_boardGames;

    // v_boardGames.push_back(chess);
    // v_boardGames.push_back(poker);
    // v_boardGames.push_back(trouble);
    // v_boardGames.push_back(sorry);

    // Correctly iterate v_boardGames and << appropriately to output through
    // the left-shift operator.
    // Your loop must be coded in such a way that it will work for any number of
    // vector elements.



    return 0;

} // end main
