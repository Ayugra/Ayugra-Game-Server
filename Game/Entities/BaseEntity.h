#pragma once

#include "Game/Types/EntityType.h"

class BaseEntity
{
public:
	BaseEntity(EntityType EntityType, int Id, int X, int Y)
		: entityType(EntityType)
		, id(Id)
		, x(X)
		, y(Y)
	{

	}

	EntityType getEntityType() const { return entityType; }
	int getEntityID() const { return id; }
	int getX() const { return x; }
	int getY() const { return y; }

protected:
	EntityType entityType;
	int id;
	int x;
	int y;
};
