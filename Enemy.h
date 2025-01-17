#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

//Class specifically for enemy characters.
class Enemy : public BaseCharacter
{
private:
    Character* target;
    float damagePerSec{10.f};
    float radius {25.f};
    
public:
    Enemy(Vector2 pos, Texture2D idle_Texture, Texture2D run_Texture);
    virtual void tick(float deltaTime) override;
    void setTarget (Character* character) { target = character; } 
    virtual Vector2 getScreenPos() override;
};


