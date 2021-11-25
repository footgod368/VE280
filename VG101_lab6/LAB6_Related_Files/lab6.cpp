#include "lab6.h"

/***
 * For this LAB, you just need to change this file.
 * To finish Objective I, you should implement the functions in MyGame class
 * To finish Objective II, you should give interface to your MyBrain class and complete your judge function based on your MyGame class.
 */

using namespace std;

// Create Your Data Structure Here


class MyGame : public Game {
    // Create Your Data Structure Here

public:
    /**
     * @param A_X The X position for P1
     * @param A_Y The Y position for P1
     * @param B_X The X position for P2
     * @param B_Y The Y position for P2
     * @param A_direction The direction for P1
     * @param B_direction The direction for P2
     * To know the definition of Direction type, you can look at `lab6.h`
     * D_Left (0) -> Towards negative X
     * D_Up (1) -> Towards negative y
     * D_Right (2) -> Towards positive X
     * D_Down (3) -> Towards positive Y
     */
    void initialize(int A_X, int A_Y, int B_X, int B_Y, Direction A_direction, Direction B_direction) override {
        // Initialize Your Game Here
    }

    /**
     * @param tank The tank that is to move
     * Tank_A (0) -> P1
     * Tank_B (1) -> P2
     * @param move The move it wants to take
     * M_Straight (0) -> Go straightly
     * M_Left (1) -> TurnStatus Left
     * M_Right (2) -> TurnStatus Right
     */
    void move(Tank tank, Move move) override {
        // Record A Move And Update Your Game
        // 1. Move
        // 2. Shoot
    }

    /**
     * Calculate the result at the end of the TurnStatus. It will be called after two tanks makes their move.
     * @return
     * T_Cont (0) -> Game continues
     * T_A_Win (1) -> P1 Wins
     * T_B_Win (2) -> P2 Wins
     * T_Draw (3) -> Draw
     */
    TurnStatus TurnStatus() override {
        // Make Your TurnStatus Here
        // 0. Tank Crash
        // 1. Move Bullets
        // 2. Out of Boundary
        // 3. Win or Lose
        return T_Cont;
    }

    /**
     * Draw the battlefield
     * @return
     */
    string draw() const override {
    }


    /**
     * Get the battlefield.
     * Map.blocks: Each blocks of the map. The first index is `y` and the second index is `x`
     * @return
     */
    Map getMap() const override {
    }

    /**
     * Set the position of a tank. Notice that its life point and cd will not change
     * @param tank
     * @param pos
     * @param direction
     */
    void moveTank(Tank tank, const Vector2<> &pos, Direction direction) override {
    }

    /**
     * Add a bullet to the battlefield
     * @param pos
     * @param direction
     */
    void addBullet(const Vector2<> &pos, Direction direction) override {
    }

    /**
     * Set the border to certain value, notice that it will not reset the shrink time
     * @param border
     */
    void setBorder(int _border) override {
    }
};

class MyBrain : public Brain {
    // Create Your Status Variables Here
    const MyGame* game = nullptr;
public:
    void initialize() override {
        // Initialize Your AI here
        game = dynamic_cast<MyGame*>(getMyGame()); // This will give you a MyGame pointer from the Game pointer returned by getMyGame() So you can access the variable before it's declared.
    }

    Move judge() override {
        // Move Your Move Here

        return M_Straight;
    }
};

static MyGame game;
static MyBrain brain;

Game* getMyGame() {
    return &game;
}

Brain* getMyBrain() {
    return &brain;
}