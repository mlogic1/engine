#include "GameObject.h"


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::SetVisible(bool visibleState)
{
	this->m_isVisible = visibleState;
}

bool GameObject::GetVisible()
{
	return this->m_isVisible;
}
