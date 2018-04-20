#ifndef COLLIDER_H
#define COLIDER_H

class Body;
class Collider
{
public:
	static bool Collided(const Body &b1, const Body &b2);
	static void HandleCollision(Body &b1, Body &b2);
};
#endif // !COLLIDER_H


