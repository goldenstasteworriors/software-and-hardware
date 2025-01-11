



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



纯小白，要被代理折磨疯了。我用一个据学长说需要代理才能上外网(相对局域网)的服务器的时候，刚开始时我试了下不做任何操作但是在用conda和pip时都会报ProxyError: Conda cannot proceed due to an error in your proxy configuration。所以我按照学长的文档想把export all_proxy='127.0.0.1:10408然后在ssh配置里面ForwardAgent yes；RemoteForward 10408 localhost:60000。其中60000是本地clash的代理端口，但还是会报ProxyError，而且ping不同百度官网，后面在condarc后面加了proxy_servers:
  http: http://127.0.0.1:10408
  https: http://127.0.0.1:10408也还是解决不了



下午都在上课,刚才回宿舍又试了一下，发现我proxy之后外网确实是不通的：之前wget只能得到一个空白文件且proxy前也能得到；我ping不同百度官网；pip和conda都会报proxy_error；

还发现vscode的ssh界面显示端口转发并不是每次都打开了(且打开了也连不上外网)

是我电脑的代理的问题还是梯子质量问题呢，但是我确实可以通过这个梯子上外网(我用的clash for windows，我按图中给端口给的7890)



下载链接

https://download.pytorch.org/whl/torch_stable.html