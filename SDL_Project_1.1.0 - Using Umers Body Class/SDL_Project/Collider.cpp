#include "Collider.h"
#include "VMath.h"
#include "Body.h"
using namespace MATH;

bool Collider::Collided(const Body &b1, const Body &b2){
	float distance = VMath::distance(b1.pos, b2.pos);
	if (distance < (b1.radius + b2.radius)) {
		return true;
	}
	return false;
}

void Collider::HandleCollision(Body& b1, Body& b2) {
	float epsilon = 0.5f;
	Vec3 normal = b2.pos - b1.pos;
	normal = VMath::normalize(normal);

	float v1f = VMath::dot(b1.vel, normal);
	float v2f = VMath::dot(b2.vel, normal);
	float v1fnew = ((b1.mass - epsilon * b2.mass) * v1f + (1.0f + epsilon) * b2.mass * v2f) / (b1.mass + b2.mass);
	float v2fnew = ((b2.mass - epsilon * b1.mass) * v2f + (1.0f + epsilon) * b1.mass * v1f) / (b1.mass + b2.mass);
	b1.vel += (v1fnew - v1f) * normal;
	b2.vel += (v2fnew - v2f) * normal;
	return;
}
