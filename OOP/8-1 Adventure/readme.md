# 8-1 Adventure

南子谦 信息与计算科学 3210104676

## How to play

*注意：本人在visual studio code可以正常运行该程序，在其他环境运行可能会有问题*

### 如何开始游戏？

进入游戏时，您将需要输入每一层的size与层数level；这样将会生成level层以size为边长的正方形。

每当一盘游戏结束时，程序将循环是否重新开始，如果输入"y"，则会重新开始一盘游戏；如果输入其他程序将结束，这是通过 `Menu()`函数实现的。

### 如何与游戏互动？

在程序告知您有哪些出口时，您能做的不止通过出口离开；这是通过 `console()`函数实现的

`cheat`您将会得到Monster、princess、lobby以及stair的下标，可以帮助你完成游戏

`location`您将会获得您当前所在的房间的下标

`win`您将会直接获得胜利，进行下一盘游戏

`go east/south/west/north/up/down`您将可以进入下一个房间

`talk to myself`您将可以自言自语

`talk to princess`如果公主在您身边，您将可以与公主对话；（功能开发中）

### 如何获得胜利?

您将需要避开Monster，找到公主，并带着公主回到lobby；

如果进入了monster所在的房间，游戏失败；

如果您带着公主绕过了monster回到了lobby，游戏胜利；

## 游戏机制

每一层是size为边长的正方形，地图共有level层。

每两层之间将随机生成梯子，供玩家进行层与层之间的移动。

monster与princess的位置是随机生成的，但Monster、princess、lobby的位置将不会重合。
