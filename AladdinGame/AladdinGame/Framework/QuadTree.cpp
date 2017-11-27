#include "QuadTree.h"
#include "../debug.h"
LINK_FRAMEWORK

list<string> QuadTreeNode::ActiveObject;

QuadTreeNode::QuadTreeNode()
{
	
}


QuadTreeNode::~QuadTreeNode()
{
}

void QuadTreeNode::createSubNodes()
{
	//hệ tọa độ bottom-left
	// the smallest subnode has an area
	float boundWidth = _bound.right - _bound.left;
	float boundHeight = _bound.top - _bound.bottom;
	if ((boundWidth * boundHeight) <= 10.0f)
		return;

	float halfWidth = boundWidth / 2.0f;
	float halfHeight = boundHeight / 2.0f;

	RECT nodeRect;
	//first root
	//m_nodes.Add(new QuadTreeNode<T>(new RectangleF(m_bounds.Location, new SizeF(halfWidth, halfHeight))));
	nodeRect.left = _bound.left;
	nodeRect.top = _bound.top;
	nodeRect.right = nodeRect.left + halfWidth;
	nodeRect.bottom = nodeRect.top - halfHeight;
	_nodes.push_back(new QuadTreeNode(nodeRect, _level + 1));

	//second root
	//m_nodes.Add(new QuadTreeNode<T>(new RectangleF(new PointF(m_bounds.Left, m_bounds.Top + halfHeight), new SizeF(halfWidth, halfHeight))));
	nodeRect.left = _bound.left;
	nodeRect.top = _bound.top - halfHeight;
	nodeRect.right = nodeRect.left + halfWidth;
	nodeRect.bottom = nodeRect.top - halfHeight;
	_nodes.push_back(new QuadTreeNode(nodeRect, _level + 1));

	//third root
	//m_nodes.Add(new QuadTreeNode<T>(new RectangleF(new PointF(m_bounds.Left + halfWidth, m_bounds.Top), new SizeF(halfWidth, halfHeight))));
	nodeRect.left = _bound.left + halfWidth;
	nodeRect.top = _bound.top;
	nodeRect.right = nodeRect.left + halfWidth;
	nodeRect.bottom = nodeRect.top - halfHeight;
	_nodes.push_back(new QuadTreeNode(nodeRect, _level + 1));

	//fourth root
	//m_nodes.Add(new QuadTreeNode<T>(new RectangleF(new PointF(m_bounds.Left + halfWidth, m_bounds.Top + halfHeight), new SizeF(halfWidth, halfHeight))));
	nodeRect.left = _bound.left + halfWidth;
	nodeRect.top = _bound.top - halfHeight;
	nodeRect.right = nodeRect.left + halfWidth;
	nodeRect.bottom = nodeRect.top - halfHeight;
	_nodes.push_back(new QuadTreeNode(nodeRect, _level + 1));

}


QuadTreeNode::QuadTreeNode(RECT bound, int level)
{
	_bound = bound;
	_level = level;
}

bool QuadTreeNode::isLeaf()
{
	return _level >= MAX_DEPTH;
}

RECT QuadTreeNode::getBound()
{
	return _bound;
}

int QuadTreeNode::getCount()
{
	int count = 0;
	for (auto node : _nodes)
	{
		count += node->getCount();
	}

	count += _contents.size();

	return count;
}

list<string> QuadTreeNode::getSubTreeContents()
{
	_subTreeContent.clear();
	fetchSubTreeContents(_subTreeContent);
	return _subTreeContent;
}

list<string> QuadTreeNode::getActiveObject(const RECT &queryArea)
{
	ActiveObject.clear();
	query(queryArea, ActiveObject);
	return ActiveObject;
	
}

void QuadTreeNode::fetchSubTreeContents(list<string> &result)
{

	//Don't use, just a fast way to implement,

	for (auto node : _nodes)
	{
		fetchSubTreeContents(result);
	}

	result.insert(result.end(), _contents.begin(), _contents.end());

}

list<string> QuadTreeNode::getContents()
{
	return _contents;
}

void QuadTreeNode::query(RECT queryArea, list<string> &result)
{

	if (isLeaf())
	{
		for (auto content : _contents)
		{
			auto it = std::find(result.begin(), result.end(), content);
			if (it == result.end() || it._Ptr == nullptr)
			{
				result .push_back(content);
			}
		}
	}
	for (auto node : _nodes)
	{
		if (isRectangleIntersected(getBound(), queryArea))
		{
			node->query(queryArea, result);
		}
	}
}

void QuadTreeNode::buildWriteableNode(xml_node & root)
{

	auto node = root.append_child("Node");
	node.append_attribute("left") = getBound().left;
	node.append_attribute("right") = getBound().right;
	node.append_attribute("top") = getBound().top;
	node.append_attribute("bottom") = getBound().bottom;
	node.append_attribute("level") = _level;

	string result;
	
	if (_contents.size() != 0)
	{
		for (auto content : _contents)
		{
			result += content + string(" ");
		}

		node.append_attribute("object") = result.c_str();
	}

	if (isLeaf())
		return;

	for (auto child : _nodes)
	{
		child->buildWriteableNode(node);
	}

}

void QuadTreeNode::readNode(xml_node & node)
{	
	_level = node.attribute("level").as_int();
	_bound.left = node.attribute("left").as_int();
	_bound.right = node.attribute("right").as_int();
	_bound.top = node.attribute("top").as_int();
	_bound.bottom = node.attribute("bottom").as_int();

	if (isLeaf() == true)
	{
		_contents = splitString(node.attribute("object").as_string(), ' ');
	}

	for (auto child : node.children())
	{
		QuadTreeNode * qnode = new QuadTreeNode();
		qnode->readNode(child);
		_nodes.push_back(qnode);
	}

}


void QuadTreeNode::insert(const string &name, const RECT &rect)
{
	// if the item is not contained in this quad, there's a problem
	if (!isRectangleIntersected(_bound, rect))
	{
		OutputDebugStringW(L"feature is out of the bounds of this quadtree node \n");
		return;
	}

	// if the subnodes are null create them. may not be sucessfull: see below
	// we may be at the smallest allowed size in which case the subnodes will not be created
	if (_nodes.size() == 0 && _level < MAX_DEPTH)
	{
		createSubNodes();
	}

	// for each subnode:
	// if the root contains the item, add the item to that root and return
	// this recurses into the root that is just large enough to fit this item
	bool _isInserdToChild = false;
	for (auto node : _nodes)
	{
		if (isRectangleIntersected(node->getBound(), rect))
		{
			node->insert(name, rect);
			_isInserdToChild = true;
		}
	}

	if (_isInserdToChild == true)
		return;

	// if we make it to here, either
	// 1) none of the subnodes completely contained the item. or
	// 2) we're at the smallest subnode size allowed 
	// add the item to this root's contents.
	_contents.push_back(name);

}

void QuadTreeNode::forEach(QTAction action)
{
	action(this);

	for (auto node : _nodes)
	{
		action(node);
	}
}

void QuadTreeNode::writeXML(const string & path)
{
	xml_document doc;

	auto declarationNode = doc.append_child(pugi::node_declaration);
	declarationNode.append_attribute("version") = "1.0";
	declarationNode.append_attribute("encoding") = "ISO-8859-1";
	declarationNode.append_attribute("standalone") = "yes";

	// A valid XML doc must contain a single root root of any name
	//auto root = doc.append_child("Quadtree");
	// Append some child elements below root

	buildWriteableNode(doc);

	bool saveSucceeded = doc.save_file(path.c_str(), PUGIXML_TEXT("  "));
}

void QuadTreeNode::readXML(const string & path)
{
	pugi::xml_document doc;

	// Mở file và đọc
	xml_parse_result result = doc.load_file(path.data(), pugi::parse_default | pugi::parse_pi);
	if (result == false)
	{
		return;
	}

	pugi::xml_node rootxml = doc.first_child();
	readNode(rootxml);
}


