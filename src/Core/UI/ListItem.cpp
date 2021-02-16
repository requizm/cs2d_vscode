#include "ListItem.hpp"

ListItem::ListItem(Panel *panel) : UIObject(panel->getPosition(), panel->getScale(), *(panel->rend))
{
	this->panel = panel;
}

ListItem::ListItem() : UIObject()
{
	this->position = Vector2<int>(0);
	this->scale = 0.0F;
}

ListItem::~ListItem()
{
	for (auto &item : items)
	{
		if (item != nullptr)
			delete item;
	}
	UIObject::removeParent();
}

void ListItem::AddItem(std::string &text)
{
#if defined(WIN32) && defined(TRACY_ENABLE)
	ZoneScoped;
#endif
	Button *bt = new Button(text, Vector2<int>(0.0F, static_cast<int>(i++ * 20)), Vector2<int>(panel->getSize().x, 20.0F), *(panel->rend), Vector3<float>(0.21F), Vector3<float>(0.58F), 1.0F, UIObjectType::LISTITEM);
	bt->setMouseClickColor(Vector3<float>(0.35F));
	bt->setMouseHoverColor(Vector3<float>(0.25F));
	bt->setLabelMouseHoverColor(Vector3<float>(1.0F));
	bt->setLabelClickColor(Vector3<float>(1.0F));
	bt->setOutline(false);
	bt->setParent(panel, true);
	bt->independent = true;
	bt->center = false;

	items.push_back(new ListItemElement(bt));
}

void ListItem::Clear()
{
	for (auto &item : items)
	{
		if (item != nullptr)
			delete item;
	}
	UIObject::removeParent();
	items.clear();
	i = 0;
}

void ListItem::AddListener(std::function<void(Button *, Button *)> func)
{
	listeners.push_back(std::move(func));
}

void ListItem::Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer)
{
	if (panel->isEnable())
	{
		for (auto &item : items)
		{
			item->Draw(spriteRenderer, squareRenderer);
		}
	}
}

void ListItem::ProcessInput()
{
	if (panel->isMouseEvents() && panel->isEnable())
	{
		for (std::vector<int>::size_type i = 0; i != items.size(); i++)
		{
			items[i]->ProcessInput();
			if (items[i]->isMouseDown() && items[i]->isRenderable() && i != selectedIndex)
			{
				Select(i);
				break;
			}
		}
	}
}

void ListItem::Update()
{
	if (panel->isMouseEvents() && panel->isEnable())
	{
		for (std::vector<int>::size_type i = 0; i != items.size(); i++)
		{
			items[i]->Update();
		}
		if (InputManager::scrollYPressed && panel->isScrollable())
		{
			if (!items.empty())
			{
				bool check_1 = items.at(0)->getLocalPosition().y == 0 && InputManager::scroll.y > 0;
				bool check_2 = items.at(items.size() - 1)->getLocalPosition().y + 20.0F <= panel->getSize().y && InputManager::scroll.y < 0;

				if (!check_1 && !check_2)
				{
					for (auto &tile : items)
					{
						tile->setPosition(tile->getLocalPosition().x, tile->getLocalPosition().y + InputManager::scroll.y * 20);
					}
				}
			}
			InputManager::scrollYPressed = false;
		}
	}
}

void ListItem::Select(int i)
{
	if (i < 0 || i > items.size())
	{
		WRITE_ERROR("Boyle bir list item indexi yok" + i);
		exit(EXIT_FAILURE);
	}
	int old = selectedIndex;
	if (selectedIndex != -1)
	{
		items[selectedIndex]->setButtonColor(Vector3<float>(0.21F));
		items[selectedIndex]->setMouseHoverColor(Vector3<float>(0.25F));
		items[selectedIndex]->setLabelColor(Vector3<float>(0.58F));
		items[selectedIndex]->selected = false;
	}
	items[i]->setButtonColor(Vector3<float>(0.35F));
	items[i]->setMouseHoverColor(Vector3<float>(0.35F));
	items[i]->setLabelColor(Vector3<float>(1.0F));
	items[i]->selected = true;
	selectedIndex = i;

	for (auto &f : listeners)
	{
		if (old != -1)
		{

			f(items[old], items[selectedIndex]);
		}
		else
		{
			f(nullptr, items[selectedIndex]);
		}
	}
}

int ListItem::getSelectedIndex()
{
	return selectedIndex;
}

ListItemElement *ListItem::getIndex(int i)
{
	if (i < 0 || i > items.size())
	{
		WRITE_ERROR("Boyle bir list item indexi yok" + i);
		exit(EXIT_FAILURE);
	}
	return items.at(i);
}

ListItemElement::ListItemElement(Button *btn) : Button(*btn)
{
	this->btn = btn;

	mDown = std::bind(&ListItemElement::onMouseDown, this);
	InputManager::addListenerDown(GLFW_MOUSE_BUTTON_LEFT, mDown, id);

	mUp = std::bind(&ListItemElement::onMouseUp, this);
	InputManager::addListenerUp(GLFW_MOUSE_BUTTON_LEFT, mUp, id);
	ObjectManager::listenerObjCount++;
}

ListItemElement::~ListItemElement()
{
	InputManager::removeListenerDown(GLFW_MOUSE_BUTTON_LEFT, mDown, id);
	InputManager::removeListenerUp(GLFW_MOUSE_BUTTON_LEFT, mUp, id);
	ObjectManager::listenerObjCount--;
	UIObject::removeParent();
	delete btn;
}

void ListItemElement::Update()
{
	if (isEnable() && isMouseEvents())
	{
		if (!isPressed && isMouseHover())
		{
			currentColor = mouseHoverColor;
			labelCurrentColor = labelMouseHoverColor;
		}
		else if (!isPressed)
		{
			currentColor = buttonColor;
			labelCurrentColor = labelColor;
		}
	}
}

void ListItemElement::onMouseDown()
{
	if (isEnable() && isMouseHover())
	{
		upTrigger = false;
		downTrigger = true;
		isPressed = true;
		for (auto &f : listenersDown)
		{
			f();
		}
	}
}

void ListItemElement::onMouseUp()
{
	if (isPressed)
	{
		if (isEnable())
		{
			for (auto &f : listenersUp)
			{
				f();
			}
		}
		upTrigger = true;
		downTrigger = false;
		isPressed = false;
	}
}