#include <iostream>
#include <string>

#include "tinyxml2.h"
#include "tinyxml2.cpp"

//tinyxml2的类在tinyxml2命名空间
using namespace tinyxml2;

// void create_xml(const char* xmlPath);//测试生成xml

// void parse_xml(const char* xmlPath);//测试解析xml

// void traversal_node(XMLNode* node);//遍历xml node

// void traversal_element(XMLNode* node, int level);//遍历xml element

// void create_xml2(const char* xmlPath);//生成预定格式xml

// void parse_xml2(const char* xmlPath);//解析预定义格式xml

void traversal_node(XMLNode* node)
{
	if (!node)
		return;
	for (XMLNode* current = node->FirstChild(); current != nullptr; current = current->NextSibling())
	{
		XMLNode* temp = current;
		if (temp->Value() != nullptr)
			std::cout << temp->Value() << std::endl;
		if (!temp->NoChildren())
			traversal_node(temp);
	}
}

void traversal_element(XMLNode* node, int level)
{
	if (!node)
		return;
	for (XMLElement* current = node->FirstChildElement(); current != nullptr; current = current->NextSiblingElement())
	{
		XMLElement* temp = current;
		//这里我使用点号来表示层级缩进
		std::cout << std::string(level * 5, '.') << temp->Name() << std::endl;
		if (temp->GetText() != nullptr)
			std::cout << std::string(level * 5, '.') << "> Text" << ":" << temp->GetText() << std::endl;
		const XMLAttribute* attr = temp->FirstAttribute();
		if (attr != nullptr)
			std::cout << std::string(level * 5, '.') << "> Attr" << ":" << attr->Value() << std::endl;
		if (temp->FirstChildElement() != nullptr)
			traversal_element(temp, level + 1);
	}
}

void create_xml(const char* xmlPath){
	std::cout << "\ncreate_xml:" << xmlPath << std::endl;
	//【】构造一个xml文档类
	XMLDocument doc;
	//【】操作文档相关接口
	//创建与此文档关联的新声明。对象的内存由文档管理。
	//如果'text'参数为null，则使用标准声明:
	//<?xml version="1.0" encoding="UTF-8"?>
	XMLDeclaration* declaration = doc.NewDeclaration();
	//创建与此文档关联的新元素。元素的内存由文档管理。
	XMLElement* element = doc.NewElement("ElementA");
	//创建与此文档关联的新注释。注释的内存由文档管理。
	XMLComment* comment = doc.NewComment("My TinyXml2 Test... ...");
	//创建与此文档关联的新文本。文本的存储由文档管理。
	XMLText* text = doc.NewText("Some Test");
	//创建与此文档关联的新的未知节点。对象的内存由文档管理。
	XMLUnknown* unknown = doc.NewUnknown("Unknown");
	//【】创建了节点还要插入文档中
	//添加一个子节点作为最后一个（右）子节点。如果子节点已经是文档的一部分，则将其从其旧位置移至新位置。
	//XMLNode* tinyxml2::XMLNode::InsertEndChild(XMLNode * addThis);
	//添加一个子节点作为第一个（左）子节点。如果子节点已经是文档的一部分，则将其从其旧位置移至新位置。
	//XMLNode* tinyxml2::XMLNode::InsertFirstChild(XMLNode* addThis);
	//在指定的子节点之后添加一个节点。如果子节点已经是文档的一部分，则将其从其旧位置移至新位置。
	//XMLNode* tinyxml2::XMLNode::InsertAfterChild(XMLNode * afterThis, XMLNode * addThis);
	doc.InsertFirstChild(declaration);
	doc.InsertAfterChild(declaration, element);
	doc.InsertEndChild(comment);
	doc.InsertEndChild(text);
	doc.InsertEndChild(unknown);

	//【】操作节点相关接口
	//将命名属性设置为对应类型的value
	element->SetAttribute("Level", "A");
	element->SetAttribute("Value", 1992);
	//设置文本
	element->SetText("ElementA text");
	//注释
	element->InsertNewComment("ElementA comment");
	//添加子节点，接口已经带insert功能了
	XMLElement* sub_element = element->InsertNewChildElement("ElementB");
	sub_element->SetAttribute("Level", "B");
	sub_element->SetText("ElementB text");
	sub_element->InsertNewComment("ElementB comment");

	//【】存储到文件，参数2 compact紧凑默认false
	//结构写的不规范，感觉应该拿一个根节点把那些注释，文本包起来
	//不然解析的时候没法访问啊
	doc.SaveFile(xmlPath);
}

void parse_xml(const char* xmlPath)
{
	std::cout << "\nparse_xml:" << xmlPath << std::endl;
	//【】构造一个xml文档类
	XMLDocument doc;
	//【】读取文件
	//从磁盘加载XML文件。成功返回XML_SUCCESS（0），或者返回errorID。
	XMLError error = doc.LoadFile(xmlPath);
	//也可以解析字符串
	//从字符串解析XML文件。成功返回XML_SUCCESS（0），或者返回errorID。
	//XMLError tinyxml2::XMLDocument::Parse(const char *xml,size_t nBytes = static_cast<size_t>(-1));
	if (error != XMLError::XML_SUCCESS)
		return;
	//注意，实际解析时返回的指针记得判空，不然遇到解析失败异常就遭了

	//【】解析根元素
	//返回DOM的根元素。等效于FirstChildElement。要获取第一个节点，请使用FirstChild。
	XMLElement* root = doc.RootElement();
	std::cout << "RootElement name:" << root->Name() << std::endl;
	//获取第一个子元素，或者选择具有指定名称的第一个子元素。
	XMLElement* first = doc.FirstChildElement("ElementA");
	//给定一个属性名称，Attribute返回该名称的属性的值；如果不存在，则返回null。
	std::cout << "FirstChildElement Attr Level:" << first->Attribute("Level") << std::endl;
	std::cout << "FirstChildElement Attr Value:" << first->Attribute("Value") << std::endl;
	//如果'this'的第一个Child是XMLText，则GetText返回Text节点的字符串，否则返回null。
	std::cout << "FirstChildElement Text:" << first->GetText() << std::endl;

	//【】解析子元素
	XMLElement* sub = root->FirstChildElement("ElementB");
	std::cout << "SubElement Attr Level:" << sub->Attribute("Level") << std::endl;
	std::cout << "SubElement Text:" << sub->GetText() << std::endl;

	//【】
	//可使用FirstChild+NextSibling遍历子节点
	std::cout << "\ntraversal_xml:" << std::endl;
	traversal_node(&doc);
	//或者FirstChildElement+NextSiblingElement遍历子元素
	std::cout << "\ntraversal_element:" << std::endl;
	traversal_element(&doc, 0);
}

void create_xml2(const char* xmlPath)
{
	std::cout << "\ncreate_xml2:" << xmlPath << std::endl;
	//【】构造一个xml文档类
	XMLDocument doc;
 
	//【】构建我们的xml数据结构
	XMLDeclaration* declaration = doc.NewDeclaration();
	doc.InsertFirstChild(declaration);
	//创建与此文档关联的新元素。元素的内存由文档管理。
	XMLElement* root = doc.NewElement("serialization");
	doc.InsertEndChild(root);
	//子节点
	XMLElement* group_a = root->InsertNewChildElement("std_pair");
	XMLElement* a_1 = group_a->InsertNewChildElement("fisrt val=\"2\"");
	XMLElement* a_2 = group_a->InsertNewChildElement("second val=\"3.1000000000000001\"");
	XMLElement* group_b = root->InsertNewChildElement("GroupB");
	group_b->SetAttribute("Type", "B");
	XMLElement* group_c = root->InsertNewChildElement("GroupC");
	group_c->SetAttribute("Type", "C");
 
 
	//【】存储到文件，参数2 compact紧凑默认false
	doc.SaveFile(xmlPath);
}
 
void parse_xml2(const char* xmlPath)
{
	std::cout << "\nparse_xml2:" << xmlPath << std::endl;
	//【】构造一个xml文档类
	XMLDocument doc;
	//【】读取文件
	//从磁盘加载XML文件。成功返回XML_SUCCESS（0），或者返回errorID。
	XMLError error = doc.LoadFile(xmlPath);
	//也可以解析字符串
	//从字符串解析XML文件。成功返回XML_SUCCESS（0），或者返回errorID。
	//XMLError tinyxml2::XMLDocument::Parse(const char *xml,size_t nBytes = static_cast<size_t>(-1));
	if (error != XMLError::XML_SUCCESS)
		return;
	//注意，实际解析时返回的指针记得判空，不然遇到解析失败异常就遭了
 
	//【】解析根节点
	//返回DOM的根元素。等效于FirstChildElement。要获取第一个节点，请使用FirstChild。
	XMLElement* root = doc.RootElement();
	//【】查找
	XMLElement* find_ele = root->FirstChildElement("GroupA");
	if (find_ele) {
		std::cout << find_ele->Name() << std::endl;
		const XMLAttribute* attr = find_ele->FindAttribute("Type");
		if (attr) {
			std::cout << attr->Name() << ":" << attr->Value() << std::endl;
		}
		XMLElement* find_sub = find_ele->FirstChildElement("Name");
		if (find_sub && find_sub->GetText()) {
			std::cout << find_sub->GetText() << std::endl;
		}
	}
 
	//【】遍历
	std::cout << "\ntraversal_element:" << std::endl;
	traversal_element(&doc, 0);
}

int main()
{
	const char* path = "./test.xml";
	create_xml(path);
	parse_xml(path);
 
	const char* path2 = "./test2.xml";
	create_xml2(path2);
	parse_xml2(path2);
 
	system("pause");
	return 0;
}