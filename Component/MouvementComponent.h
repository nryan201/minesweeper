
#ifndef MINESWEEPER_MOUVEMENTCOMPONENT_H
#define MINESWEEPER_MOUVEMENTCOMPONENT_H

enum movement_states{IDLE=0,MOVING,MOVING_LEFT,MOVING_RIGHT,MOVING_UP,MOVING_DOWN,IDLE_LEFT};

class MouvementComponent {
private:
    sf::Sprite& sprite;
    float maxVelocity;
    float acceleration;
    float deceleration;


    sf::Vector2f velocity;
    sf::Vector2f lastVelocity;
    //Initializer functions

public:
    MouvementComponent(sf::Sprite& sprite,
                       float maxVelocity,float acceleration,float deceleration);
    virtual ~MouvementComponent();

    //Accessors
    const sf::Vector2f& getVelocity() const; // Corrected const reference return type
    const float& getMaxVelocity() const;

    //functions
    void stopVelocity();
    void stopVelocityX();
    void stopVelocityY();


    const bool getState(const short unsigned state) const;
    const bool Idle() const;
    const bool moving() const;
    const bool movingLeft() const;
    const bool movingRight() const;
    const bool movingUp() const;
    const bool movingDown() const;
    const bool idleLeft() const;
    const bool idleFront() const;



    void update(const float& dt);
    void move(const float x, const float y, const float& dt);
};


#endif //MINESWEEPER_MOUVEMENTCOMPONENT_H
