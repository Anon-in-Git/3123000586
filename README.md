| 这个作业属于哪个课程 | [https://edu.cnblogs.com/campus/gdgy/Class12Grade23ComputerScience](https://edu.cnblogs.com/campus/gdgy/Class12Grade23ComputerScience) |
| ------------------ | --------------------------------------------------------------------------- |
| 这个作业要求在哪里 | [https://edu.cnblogs.com/campus/gdgy/Class12Grade23ComputerScience/homework/13468](https://edu.cnblogs.com/campus/gdgy/Class12Grade23ComputerScience/homework/13468) |
| 这个作业的目标 | 使用 **C++** 实现论文查重项目，通过 **GitHub** 记录各个版本并完成单元测试 |

## 一、GitHub链接
仓库地址：[https://github.com/Anon-in-Git/3123000586](https://github.com/Anon-in-Git/3123000586)
<br>Release地址：[https://github.com/Anon-in-Git/3123000586/releases/tag/Campus](https://github.com/Anon-in-Git/3123000586/releases/tag/Campus)

## 二、PSP表格预估耗时
| **PSP2.1** | **Personal Software Process Stages** | **预估耗时（分钟）** | **实际耗时（分钟）** |
| --- | --- | --- | --- |
| Planning | 计划 | 10 | |
| Estimate | 估计这个任务需要多少时间 | 5 | |
| Development | 开发 | 10 | |
| Analysis | 需求分析（包括学习新技术） | 20 | |
| Design Spec | 生成设计文档 | 20 | |
| Design Review | 设计复审 | 10 | |
| Coding Standard | 代码规范（为目前的开发制定合适的规范） | 5 | |
| Design | 具体设计 | 10 | |
| Coding | 具体编码 | 30 | |
| Code Review | 代码复审 | 5 | |
| Test | 测试(自我测试，修改代码，提交修改) | 20 | |
| Reporting | 报告 | 15 | |
| Test Report | 测试报告 | 15 | |
| Size Measurement | 计算工作量 | 5 | |
| Postmortem & Process Improvement Plan | 事后总结，并提出过程改进计划| 10 | |
| Total | 合计 | 190 | | 


## 三、计算模块接口的设计与实现过程
个人项目代码主要分为四个模块，输入模块，分词模块，查重模块，输出模块。

输入模块负责从命令行参数读取原文文件，抄袭文件以及答案文件的绝对路径并记录下来，同时将尝试查询原文文件和抄袭文件的具体内容，发送给查重模块。

分词模块会根据UTF-8标准进行划分，对于英语，一个单词会被视为一个最小单位，同时将大写字母全部转换为小写字母；对于中文以及其他语言，一个字会被视为一个最小单位。这是这个程序的独到之处。

查重模块将使用核心最长公共子序列（LCS）算法，计算查重率，送至输出模块。

输出模块将尝试把答案写入答案文件，接着正常结束程序的运行。

其中基本功能为查重模块，扩展功能为输入模块，分词模块和输出模块。

在核心功能的查重模块中，计算原文和抄袭文本的最长公共子序列的长度时模块是关键任务，即使有分词模块划分最小单位。但是经过不断的思考和推敲后，决定使用了动态规划算法（dp），规定了状态表示，确定了转移方程，答案也是信手拈来。
具体来说，分别枚举原文和抄袭文本的分词，```dp[i][j]``` 表示考虑到原文的第 ```i``` 个词和抄袭文本的 ```j``` 个词的最长公共子序列长度。考虑转移方程，当原文的第 ```i``` 个词和抄袭文本的第 ```j``` 个词相同时，显然 ```dp[i][j] = dp[i - 1][j - 1] + 1``` 最优；不匹配时，```dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])``` 最优。二者的最长公共子序列长度自然为 ```dp[n][m]```，```n``` 表示原文的总词数，```m``` 表示抄袭文本的总词数，重复率的百分数为 ```dp[n][m] / m * 100```。
其中，时间复杂度为 ```O(nm)```，空间复杂度为 ```O(nm)```。

### 请注意，程序的所有编码都采用<font color = red> **UTF-8**</font>，请勿使用其他编码方式。

### 对程序进行无效输入，程序会默认给出答案<font color = red> **0**</font>。

![draw](https://img2024.cnblogs.com/blog/3698606/202509/3698606-20250921200755628-337662300.png)

## 四、计算模块接口部分的性能改进
在查重模块使用的 LCS 算法中，dp数组使用的空间复杂度理论为 ```O(nm)```。如果使用轮换数组，可以将空间复杂度压缩为 ```O(m)```。
具体来说，只需要将转移方程改写：当原文的第 ```i``` 个词和抄袭文本的第 ```j``` 个词相同时，显然 ```dp[i % 2][j] = dp[(i % 2) ^ 1][j - 1] + 1``` 最优；不匹配时，```dp[i % 2][j] = max(dp[(i % 2) ^ 1][j], dp[i % 2][j - 1])``` 最优。二者的最长公共子序列长度自然为 ```dp[n % 2][m]```。在改进计算模块性能上所花费的时间大约为 1 小时。

输入模块的时间复杂度为 ```O(n + m)```；分词模块的时间复杂度为 ```O(n + m)```；查重模块的时间复杂度为 ```O(nm)```；输出模块的时间复杂度为 ```O(1)```。
程序中消耗最大的函数为 LCS（查重模块），时间复杂度为 ```O(nm)```，空间复杂度为 ```O(m)```。

![image](https://img2024.cnblogs.com/blog/3698606/202509/3698606-20250921194322879-301134979.png)

## 五、计算模块部分单元测试展示
在编写单元测试代码时，我选择使用不同的数字和句子进行样例测试，包括纯中文，纯英文，纯日文，纯数字和中英文数字混合，大部分还是纯中文为主进行测试，直接使用封装好的函数进行测试得到答案并与算法预期得到答案进行对比。

此处附上几组测试样例以及预期输出:

* <font color = lime>汉皇重色思倾国，御宇多年求不得。杨家有女初长成，养在深闺人未识。</font>
* <font color = cyan>浔阳江头夜送客，枫叶荻花秋瑟瑟。主人下马客在船，举酒欲饮无管弦。</font>
* ```12.5```
---
* <font color = lime>生活就像海洋，只有意志坚强的人，才能到达彼岸。</font>
* <font color = cyan>生活就像天空，只有自强不息的人，才能自由翱翔。</font>
* ```60.86```
---
* <font color = lime>The industrial revolution, which began in Britain in the late 18th century, was a profound transformation of the global economic and social landscape, marked primarily by the shift from agrarian societies to industrialized ones.</font>
* <font color = cyan>Beginning in Britain during the late 1700s, the industrial revolution profoundly transformed the global economic and social landscape. This great change was defined by the major shift from agrarian societies to industrialized ones.</font>
* ```57.57```
---
* <font color = lime>998244353.1e7</font>
* <font color = cyan>19260817.1e9</font>
* ```0```
---
* <font color = lime>我昨天买了3个apple，一共花了15.99 yuan，性价比真的很高！My rating: 5 stars.</font>
* <font color = cyan>昨日购入了apples共计3个，消费总金额为15.99元，觉得性价比超高！我的评分是5星。</font>
* ```0```
---
* <font color = lime>私は昨日、新しいソフトウェアをダウンロードしました。</font>
* <font color = cyan>わたしはきのう、あたらしいソフトをダウンロードしました。</font>
* ```67.85```

![image](https://img2024.cnblogs.com/blog/3698606/202509/3698606-20250921230401798-1020939063.png)

![image](https://img2024.cnblogs.com/blog/3698606/202509/3698606-20250921230812752-1538892726.png)

---

在 ```Visual Studio 2022``` 进行单元测试需要使用收费企业版（Enterprise），而使用扩展插件进行统计分析也并不容易，此处我选择使用 ```CLion 2025.1.5``` 填入程序实参 ```C:\Users\Administrator\Desktop\Project\orig.txt``` ```C:\Users\Administrator\Desktop\Project\orig_0.8_add.txt``` ```C:\Users\Administrator\Desktop\Project\out.txt``` 覆盖率统计分析，并附上使用其他测试文本运行的结果：

![image](https://img2024.cnblogs.com/blog/3698606/202509/3698606-20250921234502011-420939702.png)
![image](https://img2024.cnblogs.com/blog/3698606/202509/3698606-20250921233118356-1245224778.png)
![image](https://img2024.cnblogs.com/blog/3698606/202509/3698606-20250921233210845-909612003.png)
![image](https://img2024.cnblogs.com/blog/3698606/202509/3698606-20250921233247945-297362184.png)
![image](https://img2024.cnblogs.com/blog/3698606/202509/3698606-20250921233318163-1564162097.png)
![image](https://img2024.cnblogs.com/blog/3698606/202509/3698606-20250921233339314-1123690059.png)
---
* ```C:\Users\Administrator\Desktop\Project\orig.txt``` 
```C:\Users\Administrator\Desktop\Project\orig_0.8_add.txt``` 
```C:\Users\Administrator\Desktop\Project\out.txt```
* ```84.39```
---
* ```C:\Users\Administrator\Desktop\Project\orig.txt``` 
```C:\Users\Administrator\Desktop\Project\orig_0.8_del.txt``` 
```C:\Users\Administrator\Desktop\Project\out.txt```
* ```100.00```
---
* ```C:\Users\Administrator\Desktop\Project\orig.txt``` 
```C:\Users\Administrator\Desktop\Project\orig_0.8_dis_1.txt``` 
```C:\Users\Administrator\Desktop\Project\out.txt```
* ```97.05```
---
* ```C:\Users\Administrator\Desktop\Project\orig.txt``` 
```C:\Users\Administrator\Desktop\Project\orig_0.8_dis_10.txt``` 
```C:\Users\Administrator\Desktop\Project\out.txt```
* ```84.26```
---
* ```C:\Users\Administrator\Desktop\Project\orig.txt``` 
```C:\Users\Administrator\Desktop\Project\orig_0.8_dis_10.txt``` 
```C:\Users\Administrator\Desktop\Project\out.txt```
* ```68.37```

## 六、计算模块部分异常处理说明
在运行测试单元中，并未遇到异常情况，后续将持续观察。

## 七、PSP表格实际耗时
| **PSP2.1** | **Personal Software Process Stages** | **预估耗时（分钟）** | **实际耗时（分钟）** |
| --- | --- | --- | --- |
| Planning | 计划 | 10 | 10 |
| Estimate | 估计这个任务需要多少时间 | 5 | 5 |
| Development | 开发 | 10 | 60 |
| Analysis | 需求分析（包括学习新技术） | 20 | 60 |
| Design Spec | 生成设计文档 | 20 | 10 |
| Design Review | 设计复审 | 10 | 5 |
| Coding Standard | 代码规范（为目前的开发制定合适的规范） | 5 | 5 |
| Design | 具体设计 | 10 | 10 |
| Coding | 具体编码 | 30 | 30 |
| Code Review | 代码复审 | 5 | 120 |
| Test | 测试(自我测试，修改代码，提交修改) | 20 | 120 |
| Reporting | 报告 | 15 | 120 |
| Test Report | 测试报告 | 15 | 15 |
| Size Measurement | 计算工作量 | 5 | 5 |
| Postmortem & Process Improvement Plan | 事后总结，并提出过程改进计划| 10 | 10 |
| Total | 合计 | 190 | 585 | 
