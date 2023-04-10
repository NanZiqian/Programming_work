#include <cstdio>
#include <time.h>
#define NODE_MAX 10000

using namespace std;

struct edgeNode;
typedef struct edgeNode edge;

struct pointNode {  //用于记录点的信息：点的编号、与其连接的所有边
    int index;
    edge *edgeList;
    int edgeCnt;
};
typedef struct pointNode *point;

struct edgeNode {   //用于记录边的信息：连接的相邻点、长度
    point destination;
    int length;
};

inline void addEdge(point A, point B, int l) {  //在点的信息中添加相应边的记录
    A->edgeList[A->edgeCnt].destination = B;
    A->edgeList[A->edgeCnt].length = l;
    A->edgeCnt ++;
    B->edgeList[B->edgeCnt].destination = A;
    B->edgeList[B->edgeCnt].length = l;
    B->edgeCnt ++;
}

struct heapNode {   //堆中的结点的结构定义
    point currentPoint;     //所在点
    int distanceTraveled;   //从起点到达此结点的距离
    int degree;             //记录了子结点的数量
    heapNode *firstChild;
    heapNode *preSibling;   //记录了前一个子结点，形成双向链表
    heapNode *nextSibling;  //使用了firstChild，nextSibling的方式记录子结点
    bool operator<(heapNode* &another) const {
        return this->distanceTraveled < another->distanceTraveled;
    }
};
typedef struct heapNode *heapPtr;

void addChild(heapPtr parent, heapPtr child) {  //将某一结点并入另一结点的子结点
    child->nextSibling = parent->firstChild;
    parent->firstChild = child;
    parent->degree ++;
}

heapPtr heapJoin(heapPtr heapA, heapPtr heapB) {    //合并堆
    if(heapA < heapB) {
        addChild(heapA, heapB);
        return heapA;
    } else {
        addChild(heapB, heapA);
        return heapB;
    }
}

class FibonacciHeap {    //斐波那契堆定义
    private:
        heapPtr fibonacciRoot;  //使用一个虚拟的根结点作为所有树的父结点
    
    public:
        FibonacciHeap() {
            fibonacciRoot = new(heapNode);
            fibonacciRoot->firstChild = NULL;
        }
        void nodeDelete(heapPtr hp) { //从虚拟的根节点的子树中取出一棵树
            if(hp->preSibling != NULL) {
                hp->preSibling->nextSibling = hp->nextSibling;
            } else {
                fibonacciRoot->firstChild = hp->nextSibling;
            }
            if(hp->nextSibling != NULL) {
                hp->nextSibling->preSibling = hp->preSibling;
            }
        }
        void nodeInsert(heapPtr hp) {   //加入一棵树
            hp->preSibling = NULL;
            hp->nextSibling = fibonacciRoot->firstChild;
            if(hp->nextSibling != NULL) {
                hp->nextSibling->preSibling = hp;
            }
            fibonacciRoot->firstChild = hp;
        }
        heapPtr top() { //查看最小值，通过比较根结点得到
            heapPtr ret = NULL;
            for(heapPtr i = fibonacciRoot->firstChild; i != NULL; i = i->nextSibling) {
                if(ret == NULL || i->distanceTraveled < ret->distanceTraveled) {
                    ret = i;
                }
            }
            return ret;
        }
        void pop() {    //取出最小值结点
            heapPtr split = NULL;
            for(heapPtr i = fibonacciRoot->firstChild; i != NULL; i = i->nextSibling) {
                if(split == NULL || i->distanceTraveled < split->distanceTraveled) {
                    split = i;
                }
            }
            nodeDelete(split);  //删除该树
            heapPtr next = NULL;
            for(heapPtr i = split->firstChild; i != NULL; i = next) {
                next = i->nextSibling;
                nodeInsert(i);  //并入所有子树
            }
            scan();
        }
        void push(heapPtr insertHeap) {
            nodeInsert(insertHeap);
            scan();
        }
        void scan() {   //每次树的组成发生变化后，查看是否有度相同的树，有则将其合并
            heapPtr heapList[NODE_MAX];
            for(int i = 0; i < NODE_MAX; i ++) {
                heapList[i] = NULL;
            }
            while(fibonacciRoot->firstChild != NULL) {
                heapPtr temp = fibonacciRoot->firstChild;
                nodeDelete(temp);
                while(heapList[temp->degree] != NULL) {
                    int d = temp->degree;
                    temp = heapJoin(temp, heapList[temp->degree]);
                    heapList[d] = NULL;
                }
                heapList[temp->degree] = temp;
            }
            for(int i = 0; i < NODE_MAX; i ++) {
                if(heapList[i] != NULL) {
                    nodeInsert(heapList[i]);
                }
            }
        }
        bool empty() {
            return fibonacciRoot->firstChild == NULL;
        }
};
FibonacciHeap priorityQueue = FibonacciHeap();

bool confirmed[50000] = {false};
int dis[50000] = {0};
void dijkstra();

int main() {
    int n, m;
    scanf("%d %d", &n, &m); //0到n-1共n个点，以0为起点
    point pointList[50000];
    for(int i = 0; i < n; i ++) {   //读入点
        pointList[i] = new(pointNode);
        pointList[i]->index = i;
        pointList[i]->edgeList = new(edge[50000]);
        pointList[i]->edgeCnt = 0;
    }

    for(int i = 0; i < m; i ++) {   //读入边
        int pointA, pointB, length;
        scanf("%d %d %d", &pointA, &pointB, &length);
        addEdge(pointList[pointA], pointList[pointB], length);
    }

    heapPtr initialHeap = new(heapNode);    //初始结点
    initialHeap->currentPoint = pointList[0];
    initialHeap->distanceTraveled = 0;
    initialHeap->degree = 0;
    initialHeap->firstChild = initialHeap->preSibling = initialHeap->nextSibling = NULL;
    priorityQueue.push(initialHeap);

    double begin = clock();
    dijkstra();
    double end = clock();

    for(int i = 0; i < n; i ++) {
        printf("%d: %d\n", i, dis[i]);
    }
    printf("Total time: %lfms", end - begin);
    return 0;
}

void dijkstra() {   //Dijkstra算法
	while(!priorityQueue.empty()) {
		heapPtr topHeap = priorityQueue.top();
	    priorityQueue.pop();
	    while(confirmed[topHeap->currentPoint->index] && !priorityQueue.empty()) {
	        topHeap = priorityQueue.top();
	        priorityQueue.pop();
	    }
	    if(confirmed[topHeap->currentPoint->index] && priorityQueue.empty()) {
	    	break;
		}
	
	    point currentPoint = topHeap->currentPoint;
	    int distanceTraveled = topHeap->distanceTraveled;
	    confirmed[currentPoint->index] = true;
	    dis[currentPoint->index] = distanceTraveled;
		
	    for(int i = 0; i < currentPoint->edgeCnt; i ++) {
	        edge nextEdge = currentPoint->edgeList[i];
	        
	        if(!confirmed[nextEdge.destination->index]) {
                heapPtr newHeap = new(heapNode);
                newHeap->currentPoint = nextEdge.destination;
                newHeap->distanceTraveled = distanceTraveled + nextEdge.length;
                newHeap->degree = 0;
                newHeap->firstChild = NULL;
                newHeap->preSibling = NULL;
                newHeap->nextSibling = NULL;
	            priorityQueue.push(newHeap);
	        }
	    }
	}
}