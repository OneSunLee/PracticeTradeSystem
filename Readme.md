## 一个简单的管理系统的重写

文件介绍：  
main.cpp是我写的程序。
这里面没有用到太多面向对象的东西。  
origin_edition.cpp是原版的程序，是c的，我随便在一个群里下载的，然后就拿来给自己练手了。  
items.csv是数据文件，就是一张表，所以也用不到其他复杂的数据交换格式。  

我重写这个是为了练习c++。

原版的实现是个本科生，用c，每个函数都打开文件，统计行数，存入数组，存数组的开销很大;  
函数没有返回，是靠调用showmenu实现到达初始界面，最终内存占用越来越大，改成主函数中的循环;  
原版是静态数组，改成了vector<>。  

原版c没有用传址，我c++传引用，没太大差别。  

原版的实现add_items中有个scanf，如果%lf的是字符串，会陷入死循环，改成了ostream。  

原版的修改是跳转到指定行覆写。  

删除部分直接重写。  

目前还有查询和排序没有做，明天再做。