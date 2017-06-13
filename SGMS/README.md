+ 设计要求：

    本程序主要考察对链表概念的理解和链表相关操作的使用，包括链表节点的输入、输出、查找、插入、删除等操作。

+ 系统功能模块组成：

    学生成绩管理系统由如下五大功能模块组成：
    1. 输入记录模块
        输入记录模块主要完成从键盘逐个输入学生记录的工作。
    1. 查询记录模块
        用户可以按照学生的学号或姓名进行查找。
    1. 更新记录模块
        实现对学生记录的修改、删除、插入和排序操作。
    1. 统计记录模块
        完成对各门功课最高分和不及格人数的统计。
    1. 输出记录模块
        主要完成将学生记录信息以表格的形式在屏幕上打印出来。


+ 学生成绩信息结构体定义：
    ``` c
    struct student  
    {
        char num[10];   	/*学号*/
        char name[15];  	/*姓名*/
        int cgrade;     	/*C语言成绩*/
        int mgrade;     	/*数学成绩*/
        int egrade;     	/*英语成绩*/
        int total;      	/*总分*/
        float ave;      	/*平均分*/
        int mingci;     	/*名次*/
    };
    ```
ID    Name    C Language grade    Math grade    English grade    Total grade    Average grade    Rating
        44             QWE  78  99  80 257 85.666664