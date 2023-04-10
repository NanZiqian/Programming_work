#include <cstdio>
#include <time.h>
#define NODE_MAX 40

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
    int depth;              //记录子树的深度
    heapNode *firstChild;
    heapNode *nextSibling;  //使用了firstChild，nextSibling的方式记录子结点
    bool operator<(heapNode &another) const {
        return this->distanceTraveled < another.distanceTraveled;
    }
};
typedef struct heapNode *heapPtr;

void addChild(heapPtr parent, heapPtr child) {  //将某一结点并入另一结点的子结点
    child->nextSibling = parent->firstChild;
    parent->firstChild = child;
    parent->depth ++;
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

void forestJoin(heapPtr forestA[], heapPtr forestB[]) { //二项堆合并，其过程类似二进制加法
    heapPtr c = NULL;
    for(int i = 0; i < NODE_MAX; i ++) {
        if(forestA[i] == NULL) {
            if(forestB[i] == NULL) {
                forestA[i] = c;
                c = NULL;
            } else {
                if(c == NULL) {
                    forestA[i] = forestB[i];
                } else {
                    c = heapJoin(forestB[i], c);
                }
            }
        } else {
            if(forestB[i] == NULL) {
                if(c != NULL) {
                    c = heapJoin(forestA[i], c);
                    forestA[i] = NULL;
                }
            } else {
                if(c == NULL) {
                    c = heapJoin(forestA[i], forestB[i]);
                    forestA[i] = NULL;
                } else {
                    c = heapJoin(forestB[i], c);
                }
            }
        }
    }
}

class BinomialHeap {    //二项堆定义
    private:
        heapPtr *forest;    //forest数组用于记录所有树
    
    public:
        BinomialHeap() {
            forest = new(heapPtr[NODE_MAX]);
            for(int i = 0; i < NODE_MAX; i ++) {
                forest[i] = NULL;
            }
        }
        heapPtr top() { //查看最小值，通过比较根结点得到
            int ret = -1;
            for(int i = 0; i < NODE_MAX; i ++) {
                if(forest[i] != NULL && (ret == -1 || forest[ret] > forest[i])) {
                    ret = i;
                }
            }
            return forest[ret];
        }
        void pop() {    //取出最小值结点
            int split = -1;
            for(int i = 0; i < NODE_MAX; i ++) {
                if(forest[i] != NULL && (split == -1 || forest[split] > forest[i])) {
                    split = i;
                }
            }
            heapPtr splitHeap = forest[split];
            forest[split] = NULL;   //删除该树
            heapPtr *splitForest = new(heapPtr[NODE_MAX]);
            for(int i = 0; i < NODE_MAX; i ++) {    //记录所有子树成为新的二项堆
                splitForest[i] = NULL;
            }
            for(heapPtr i = splitHeap->firstChild; i != NULL; i = i->nextSibling) {
                splitForest[i->depth] = i;
            }
            forestJoin(forest, splitForest);    //二项堆合并
        }
        void push(heapPtr insertHeap) { //插入新结点，相当于与只有一个结点的二项堆合并
            heapPtr *insertForest = new(heapPtr[NODE_MAX]);
            for(int i = 0; i < NODE_MAX; i ++) {
                insertForest[i] = NULL;
            }
            insertForest[0] = insertHeap;
            forestJoin(forest, insertForest);
        }
        bool empty() {
            for(int i = 0; i < NODE_MAX; i ++) {
                if(forest[i] != NULL) {
                    return false;
                }
            }
            return true;
        }
};
BinomialHeap priorityQueue = BinomialHeap();

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
    initialHeap->depth = 0;
    initialHeap->firstChild = initialHeap->nextSibling = NULL;
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
                newHeap->depth = 0;
                newHeap->firstChild = newHeap->nextSibling = NULL;
	            priorityQueue.push(newHeap);
	        }
	    }
	}
}