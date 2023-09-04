#pragma once

#include "tinyxml2.h"
#include <iostream>
#include <vector>

struct Status
{
	int mLevel{};
	int mHP{};
	int mMP{};

};

struct Item
{
	std::string mName{};
	int mGold;
};

class Monster2
{
private:
	std::string mName{};
	Status mStatus{};
	std::vector<Item> mDropItems{};

public:
	void SetName(std::string name) { mName = name; }
	void SetStatus(const Status& status) { mStatus = status; }
	void AddDropItem(const Item& item) { mDropItems.push_back(item); }

	std::string GetName() const { return mName; }
	Status& GetStatus() { return mStatus; }

	std::vector<Item>& GetDropItems() { return mDropItems; }
};

void SaveToXml(std::string path, std::vector<Monster2>& monsters)
{
	using namespace tinyxml2;
	XMLDocument doc;
	XMLDeclaration* decl = doc.NewDeclaration(R"(xml version = "1.0" encoding = "EUC-KR")");
	doc.LinkEndChild(decl);

	XMLElement* root = doc.NewElement("monsters");

	for (auto& monster : monsters)
	{
		auto monElement = doc.NewElement("monster");
		monElement->SetAttribute("name", monster.GetName().c_str());

		auto stautsElement = doc.NewElement("status");
		Status status = monster.GetStatus();
		stautsElement->SetAttribute("level", status.mLevel);
		stautsElement->SetAttribute("HP", status.mHP);
		stautsElement->SetAttribute("MP", status.mMP);
		monElement->LinkEndChild(stautsElement);

		auto itemsElement = doc.NewElement("items");
		for (auto& item : monster.GetDropItems())
		{
			auto itemElement = doc.NewElement("item");
			itemsElement->SetAttribute("name", item.mName.c_str());
			itemsElement->SetAttribute("gold", item.mGold);
			itemsElement->LinkEndChild(itemElement);
		}
		monElement->LinkEndChild(itemsElement);

		root->LinkEndChild(monElement);
	}
	doc.LinkEndChild(root);
	doc.SaveFile(path.c_str());
}
void LoadFromXml(std::string path, std::vector<Monster2>& monsters)
{
	using namespace tinyxml2;
	XMLDocument doc;

	doc.LoadFile(path.c_str());
	auto root = doc.FirstChildElement("monsters");
	for (auto monElement = root->FirstChildElement();
		monElement;
		monElement= monElement->NextSiblingElement())
	{
		Monster2 monster;
		monster.SetName(monElement->Attribute("name"));
		auto statusElement = monElement->FirstChildElement("status");
		Status status;
		status.mLevel = statusElement->IntAttribute("level");
		status.mHP = statusElement->IntAttribute("HP");
		status.mMP = statusElement->IntAttribute("MP");
		monster.SetStatus(status);
		
		auto itemsElement = monElement->FirstChildElement("items");

		for (auto itemElement = itemsElement->FirstChildElement();
			itemsElement;
			itemsElement = itemsElement->NextSiblingElement())
		{
			Item item;
			item.mName = itemsElement->Attribute("name");
			item.mGold = itemsElement->IntAttribute("gold");
			monster.AddDropItem(item);
		}
		monsters.push_back(monster);
	}
}

void TinyXml()
{
	std::vector<Monster2> monsters;
	Monster2 m;
	m.SetName("ΩΩ∂Û¿”");
	m.SetStatus({ 1,1,1 });
	m.AddDropItem({ "≤ˆ¿˚«— ¡©∏Æ", 1 });
	monsters.push_back(m);

	m.GetDropItems().clear();
	m.SetName("¥¡¥Î ¿Œ∞£");
	m.SetStatus({ 5,5,5 });
	m.AddDropItem({ "πﬂ≈È", 2 });
	m.AddDropItem({ "¥¡¥Î ∞°¡◊", 5 });
	monsters.push_back(m);

	m.GetDropItems().clear();
	m.SetName("æ«∏∂");
	m.SetStatus({ 10,10,10 });
	m.AddDropItem({ "≥Ø∞≥", 10 });
	m.AddDropItem({ "º’≈È", 5 });
	monsters.push_back(m);

	SaveToXml("Data/monsters.xml", monsters);
	monsters.clear();
	LoadFromXml("Data/monsters.xml", monsters);
}