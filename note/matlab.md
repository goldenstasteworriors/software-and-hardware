注释：%%

**真从1开始而不是0**

数据类型：

1. 数字

2. 字符和字符串：单引号    

   ```matlab
   abs(s)  输出97： 字符转ASCLL码  
   char(97)  输出s：ASCLL码转字符
   num2str(65) 输出65  :数字转字符串
   leangth()   :输出字符串长度
   ```

   

3. 矩阵:分号';'换行,空格或逗号隔开同行元素

   ```matlab
   A = [1 2 3;4 5 6; 7 8 9]
   B = A‘ ：  转置
   C = A(;)  ：竖着拉长 C会变为1,4,7,2,5,8,3,6,9
   D = inv(A) :求逆
   E = zeros(10,5,3)
   E = eye(3):生成单位矩阵
   E = rand(10,5,3)  :分布在（0，1）伪随机数
   E = randn(10,5,3)  :分布在（0，1）符合正态分布的伪随机数
   E = randi(10,5,3)  :伪随机整数
   ```

   

4. 元胞数组:类似一个元组之类的反正不管元素是啥，能包起来就行

   ```matlab
   A = cell(1,6)：创建一行六列的元胞数组
   A(2) = eye(3)
   ```

   

5. 结构体：python中的字典

   ```matlab
   ```

   

6. 



矩阵操作：

1. 矩阵定义和构造:

   ```matl
   A = 1:2:9 ：得到一个等差数列，左端是首相，中间式公差，右边是边界。这里结果就是1,3,5,7,9
   B = remap(A,3,2) ：将A重复 ，这里是横着重复3次竖着重复2次 即1 3 5 7 9 1 3 5 7 9 1 3 5 7 9
   								  					  1 3 5 7 9 1 3 5 7 9 1 3 5 7 9
   ```

   

2. 四则运算: 加上'.'就代表对应项操作 `A.*B就是对应项相乘 A./B就是对应项相除`

3. 