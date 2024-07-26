



### 常用的刚开始不知道啥意思的函数

1. `super(类名,self).__init__()`可以粗浅的理解为继承最近父类的init函数

2. `lr_scheduler.StepLR(optimizer,step,gamma)`：调整学习率随epoch的增大而减小的速率，即在过了step之后学习率变为之前的gamma

3. `enumerate()`用来进行可遍历对象的索引和值都要遍历的情况，有两个返回值要用两个变量来接:`index,item=enumerate(数组等)`

4. ```python
           # 清空过往梯度        
            		 optimizer.zero_grad()
           # 反向传播，计算当前梯度
           cur_loss.backward()
           # 根据梯度更新网络参数
           optimizer.step()
   ```









### 常见超参数感性认知

1. 学习率LR：略
2. momentum动量：用来解决梯度下降太慢的问题。若不为0，梯度下降的方向不仅与当前梯度有关，还和之前梯度相关；之前是向下这次还是向下，那就会向下的更快，诸如此类
3. step,gamma：见上面的第二点
4. dropout的丢弃率





## 相关库的常用函数



### from torchvision.transforms import functional as F