#include "Entity.h"

Entity::Entity(Vector pos, Vector rot, Vector s) {
	pos = Vector(0, 0, 0);
	rot = Vector(0, 0, 0);
	size = Vector(1, 1, 1);
}

void Entity::translate(float x, float y, float z) {
	position = position + Vector(x, y, z);
}

void Entity::rotateX(float deg) {
	rotation = rotation.m_x * deg;
}

void Entity::rotateY(float deg) {

}

void Entity::rotateZ(float deg) {

}

void Entity::scale(float factor) {
	size = size * factor;
}