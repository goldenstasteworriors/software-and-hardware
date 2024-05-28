## transformer

为了实现不把windows开到大的离谱的前提下仍然能够让output考虑整个input，attention闪亮登场

query:注意力所在

key:客观属性

value:值



首先要评估每一个windows之间的关联性，a1和a2,a3等的关联性可以用score(注意力分数)表示 
$$
score=\alpha_{i,j}=normalization(q^j\cdot a^k)\\
b^i=\sum v^i\times\alpha_{i,j}
$$
