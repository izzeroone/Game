#ifndef __QUADTREE_H__
#define __QUADTREE_H__
#include "define.h"
#include <vector>
#include <list>
#include "rectutils.h"
#include "../../pugixml/src/pugixml.hpp"

using namespace pugi;
#define MAX_DEPTH 5
DEFINE_FRAMEWORK_START

class QuadTreeNode;
typedef void(*QTAction)(QuadTreeNode*);

//feel that list is much effect
//bottom-left cordinate
class QuadTreeNode
{
public:
	QuadTreeNode();
	QuadTreeNode(RECT bound, int level);
	bool isLeaf();
	RECT getBound();
	// Total number of nodes in the this node and all SubNodes
	int getCount();
	list<string> getSubTreeContents();
	list<string> getActiveObject(const RECT &queryArea);
	list<string> getContents();
	
	void insert(const string &name, const RECT &rect);
	void forEach(QTAction action);
	void writeXML(const string &path);
	void readXML(const string &path);

	static list<string> ActiveObject;

	~QuadTreeNode();
private:
	RECT _bound;
	list<string> _contents;
	list<RECT> _contendBound;
	list<QuadTreeNode*> _nodes;
	list<string> _subTreeContent;
	int _level;
	void createSubNodes();
	void fetchSubTreeContents(list<string> &result);
	void query(RECT rect, list<string> &result);
	void buildWriteableNode(xml_node &node);
	void readNode(xml_node &node);
};

DEFINE_FRAMEWORK_END

#endif

