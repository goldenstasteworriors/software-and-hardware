系统结构：

工作空间-->功能包-->节点





### 功能包创建和使用：

1. 在工作空间的src里创建功能包
1. 在功能包src文件下添加代码
1. 修改Cake文件，使用`add_executable()    link_libraries(不叫这名字，反正在Build下面找)`把代码添加到执行名单中
2. 编译
3. 添加环境变量`source ~/pkg/devel/setup.bash`



### 自定义话题

