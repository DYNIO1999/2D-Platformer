#ifndef _SRC_PATHFINDING_PATHFINDING_H_
#define _SRC_PATHFINDING_PATHFINDING_H_

namespace DEngine{
namespace Pathfinding
{
class Node
{
public:
    Node();
    ~Node();
private:

    int i;
    int j;
    int previousNode;
};
}

}
#endif