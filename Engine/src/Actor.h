#pragma once
#include "Renderer.h"
#include "Transform.h"
#include "Type.h"

class World;

//Basic Object to placed in world.
class Actor:public Object
{
public:
	
	Actor();
	//Actor(const Actor& copy);
	virtual ~Actor();

	String tag;
	int layer;
	
	//Enable or disable this object
	void SetActive(bool value);
	bool IsActive();

	Transform& GetTransform();

	virtual void Awake(){}
	virtual void Start(){}
	virtual void Update(){}


	virtual Actor* Clone() const;

	template<class T>
	T* AddComponent();

	template<class T>
	T* GetComponent();

	template<class T>
	T* FindObjectWithTag();


protected:
	Transform transform;
	
private:
	
	bool isActive;
	List<Component*> components;

};


template <class T>
T* Actor::AddComponent()
{
	if (!Type::IsChildOf<Component, T>())
	{
		LOG_ERROR("Given type does not derive Component.");
		return nullptr;
	}
	
	LOG("Adding Component.");
	Component* newComponent = new T(this);
	components.push_back(newComponent);
	
	World::GetInstance()->RegisterComponent(newComponent);
	return static_cast<T*>(newComponent);
}

template <class T>
T* Actor::GetComponent()
{
	if (!Type::IsChildOf<Component, T>())
	{
		LOG_ERROR("Given type does not derive Component.");
		return nullptr;
	}
	return nullptr;
}

template <class T>
T* Actor::FindObjectWithTag()
{
	return nullptr;
}
