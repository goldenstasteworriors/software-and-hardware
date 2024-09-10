[TOC]

## 5.9

5学习视觉时需要在markdown中写矩阵等等数学公式，赶紧回来补LaTex

LaTex作为文本语言的优点是内容和排版分开

## 其他运用

### 内容

LaTex中所有的命令都以'\\'开头，后面可以跟一个{},代表该命令的参数

注释用%

开始要用\documents{...}这里可以是article(普通文章)，report,book,beamer(幻灯片)等等

而由于我们要使用中文，所以我们要使用ctexart文档类型，它支持中英文的混编；也不要忘了指定编码类型

在\begin{document}前的内容称为前言，可以指定文档的格式，页面的尺寸，需要导入的宏包等等，还有一些基本信息，如最基础的:\title{文章的标题},\author{罗斯},\date{\today}(里面是写日期的，不过\today命令可以自动显示当天日期)

\begin{document}和\end{document}中间的内容称为正文，这里的内容都会被显示出来

要显示刚才的基本信息，可以在正文中加上\maketitle命令，会在当前位置生成文档的标题，标题信息就是这些基本信息

在正文中用的多的有(要操作的文字都写在花括号内):\textbf{}(加粗),\textit{}(斜体),\underline{}(下划线)

需要额外注意的是要换行需要两个换行符，一个换行符只会生成一个空格，不会开始新的段落

---

### 层次划分

要开始一个新的章节可以用\section{},花括号内是章节名称，底下可以接这个章节的内容；要创建子章节可以用\subtitle{}；子章节的子章节用\subsubsection....一直无限套娃

如果我们的文档比较大，比如是\\documents{ctexbook},可以加上比段落还要大的\chapter{}(章),还有更大的\part{}(部分)

---

### 添加图片

要添加图片首先要在前言中引用graphic包,具体如下:`\usepackege{graphicx}`

md太复杂了记不住，还是直奔主线吧，下次无聊再来学。。。

# markdown中的LaTex表示数学公式

单独成行的每个数学公式块都要用前后两个'\$'包起来，行内公式只要前后各一个'\$'$E=mc^2$`$E=mc^2$`

如果实在强迫症可以像某up一样:

1. 用\text{}强行将字母改成直立体
2. 用\rm{}将某些字母改成罗马体(罗马体和直立体一样)
3. 用\bf{}将某些字母加粗
4. 在某些地方用`'\,'`(是逗号不是句号)加上一段小间隔,大一点的可以`\ `(\\+空格),再大可以用`\quad`



以下为正文:

1. 希腊字母:$$ \alpha $$`$$\alpha$$`$$\beta$$`$$\beta$$`希腊字母用'\\'在前后用它们的读音就能打出来，如果有大小写，直接打就是大写，小写就要加上var,如$\phi$`$\phi$`,$\varphi$`$\varphi$`

2. 上下标：用'_'连接表示下标，用'\^'连接表示上标，如$a^5$`&&a^5&&`,$a_i$`$$a_i$$`，但如果上下标多与一个字符，就要用{}进行包裹，如$x^{y+z}$`$x^{y+z}$`

3. 分式和根式:$\frac{a}{b}$`$\frac{a}{b}$`不过这里只有一个字符就可以不加{},直接`$\frac a b$`也行,如果觉得分式之后太小了可以用$\dfrac{a}{b}$`$\dfrac{a}{b}$`;根号就用$\sqrt2$`$sqrt{2}$`

4. 普通运算符:乘:$\times$`$\times$`,点乘:$\cdot$`$\cdot$`,(cdots就是省略号)(centre)除$\div$`$\div$`(divide)(这个有问题不知道为啥，在jupyternotebook里面是对的),正负号:$\pm$`$\pm$`，负正号:$\mp$`$\mp$`,(minus-plus),<>直接输入,大于等于:$\ge$`$\ge$`(greater-equal),小于等于:$\le$`$\le$`(less-equal),不等于$\ne$`$\ne$`(not equal),远大于$\gg$`$\gg$`,远小于$\ll$`$\ll$`,约等于$\approx$`$\approx$`(approximate),恒等于$\equiv$`$\equiv$`(equivalent)

5. 特殊符号:无穷$\infin$`$\infin$`,偏微分符号$\part$`$\part$`(partial)，拉普拉斯算子$\nabla$`$\nabla$`，正比于$\propto$`$\propto$`(proportional to),度:$\degree$`$\degree$`,三角函数$\sin x$`$\sin x$`,对数$\log_2 x$`$\log_2 x$`,趋于$\lim_{x \to 0}$`$\lim_{x \to 0}$`(在公式块中x->0在lim底下，味更正)(其实这种都是行内显示在下/上角而公式块显示在正下/上方,如果不爽可以在_前加上\limits来使它显示在正上/下方)

   横省略号$\cdots$`$\cdots$`,竖省略号$\vdots$`$\vdots$`,斜省略号$\ddots$`$\ddots$`

6. 大型运算符:累加：$ \sum\limits_{i=0}^{n} $`$\sum_(i=0)^n$`,累乘：$\prod\limits_{i=0}^n$`$\prod_{i=0}^n$`(product)，积分:$\int$`$\int$`(integral),双重积分:$\iint$`$\iint$`,闭合曲线积分$\oint$`$\oint$`       标准的积分：$\int^1_0f(x) \,\text{dx}$

7. 标注符号:一个字符的小向量$\vec x$`$\vec x$`(vector),,两个以上字符的向量:$\overrightarrow ABCD$(有些编辑器是对的),上划线$\overline AB$`$\overline AB$`

8. 箭头 ：(以右箭头为例)$\rightarrow$`$\rightarrow$`,双箭头$\Rightarrow$`$\Rightarrow$`,等价于(左右双箭头)$\Leftrightarrow$`$\Leftrightarrow$`,不够长就1加上long

9. 括号与定义符：括号竖线什么的正常打，不过大小是固定的，如果想要大小自适应可以加上\left和\right,但如果只要一边，可以在另一边加上`\left.` $\left.\dfrac{\part f}{\part x}\right|_0^1$`$\left.\dfrac{\part f}{\part x}\right|_0^1$`

10. 多行公式 一般是用\\\换行的，不过这样1. 有些编译器读不了 2. 对齐很奇怪  所以我们一般专门用一个环境{align}(对齐)来写,如

    ```latex
    \begin{align}
    a&=b+c+d\\
    &=e+f%&的作用是标记对齐点，这里就是对齐等号,不然默认右对齐
    \end{align}
    ```

    效果如下
    
    $$
    
    $$
    \begin{align}
    a&=b+c+d\\
    &=e+f
    \end{align}
    $$
    
11. 大括号：还是和多行一样，不过要用cases对齐

    ```latex
    f(x)=
    \begin{cases}
    
    \sin x,&-\pi\le x\le\pi\\
    0,&\text{其它}
    \end{cases}
    ```

    效果如下:
    $$
    f(x)=
    \begin{cases}
    
    \sin x,&-\pi\le x\le\pi\\
    0,&\text{其它}
    \end{cases}
    $$
    
12. 矩阵：常用的环境有{matrix},{bmatrix},(bracket方括号){pmatrix}(parethesis圆括号),{vmatrix}(vertical bar竖向短线)，他们的区别仅仅是括号不同

    ```latex
    \begin{bmatrix}
    a&b&c\\
    \vdots&\ddots&\vdots\\
    e&f&g
    \end{bmatrix}
    ```

    
    $$
    \begin{bmatrix}
    a&b&c\\
    \vdots&\ddots&\vdots\\
    e&f&g
    \end{bmatrix}
    $$
    一般行列式会用粗体大写字母表示如$\bf{A}$`$\bf{A}$`,转置会用罗马的的T来表示$\bf{B}^\text{T}$

13. $$
    f(x)=\frac{1}{\sqrt{2\pi}\sigma}\rm{e}^{-\frac{{x-\mu}^2}{2\mu^2}}
    $$