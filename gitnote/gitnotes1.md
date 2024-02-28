# git学习笔记
<br>
<br>
<br>

***
## 第一节  git初始化
### 创建版本库及提交
1. **git版本查看**
```
$git version  //查看git版本
```
2. **配置用户姓名和邮件地址(只需配置一次)**
```
$git config --global user.name "名字"
$git config --global user.email 邮箱
```
3. **可以为一些git命令取别名(非必要)**
```
$git config --global alias.st status  //git staus可以写成git st
$git config --global alias.ci commit  //git commit 可以写成git ci
$git config --global alias.co checkout //git checkout可以写成git co
$git config --global alias.br branch  //git branch可以写成git br
```
使用global参数表示只在本用户中配置了别名，如果将global换成system则所有用户都可以使用该配置，同时在配置时要用sudo,即系统的配置需要管理者权限，如
```
$sudo git config --system alias.st status
```
4. **可以在git命令输出中开启颜色显示**
```
$git config --global color.ui ture
```
5. **版本库的初始化**
首先创建一个空目录(空文件夹)作为工作目录，如在home中创建一个gittest,然后进入
```
~ $mkdir gittest
$cd gittest
```
然后在该目录中进行初始化
```
$git init
Initialized empty Git repository in 路径
```
我们发现，会有一个隐藏文件.git生成，这就是Git的版本库。.git所在的目录就成为工作区
6. **文件的提交**
首先我们在工作区创建一个文件,并写入内容
```
$touch welcome.txt
输入内容：1
```
然后就是我们的提交步骤
```
$git add welcome.txt
$git commit -m "Add welcome"
[master (root-commit) 09bfc1d] Add welcome.txt
 1 file changed, 1 insertion(+)
 create mode 100644 welcome.txt
```
-m参数表示提交说明，也即是对于我们提交的注释
命令输出的第一行说明此次提交是在master分支上，root-commit说明是该分支上的第一个提交，提交的ID为09bfc1d
命令输出的第二行说明这次提交改变了一个文件，有一行插入
命令输出第三行说明提交了welcome.txt文件
<br>

### 为什么工作区根目录下有一个.git目录
1. 这使得版本控制操作可以在本地完成，因为.git中包含储存版本控制的所有信息，使用者在本地就可以完成而无需依赖远程服务器，且安全属性更高，因为只需保护好这一个文件就可以防止安全泄漏
### git的相关操作一定要在根目录下执行吗
git在子目录执行某个操作的时候，会在工作区目录中依次向上递归查找.git，也即是说在子目录下是可以使用git相关操作的。但同时，在非git工作区下执行git命令会因找不到.git报错
### git config命令的各参数有何区别
```
在git工作区目录
$git config -e
```
打开.git/config文件
```
$git config -e --global
```
打开户主目录下的.gitconfig文件，即全局配置文件进行编辑
```
$git config -e system
```
打开系统级配置文件进行编辑
其中版本库级别配置文件优先级最高，依次优先级下降，同时，高优先级的文件能覆盖低优先级文件的配置环境

config配置文件是INI文件格式，git config命令可以读取或修改配置文件内容
```
$git config <section>.key   //读取
```
例如读取core小节bare属性值
```
$git config core.bare
false
```
```
$git config <section>.key <value>   //修改
```
例如修改core小节bare属性值
```
$git config core.bare ture
```
补充(什么是INI文件格式)：
```
INI 文件格式是一种简单的配置文件格式，通常用于存储应用程序的配置信息。INI 是 "Initialization"（初始化）的缩写，它的文件扩展名通常是 .ini。

INI 文件格式由一系列的节（section）和键值对（key-value pairs）组成。每个节包含一组相关的键值对，用于描述特定的配置信息。每个键值对由键（key）和值（value）组成，它们之间使用等号（=）或冒号（:）进行分隔。

下面是一个简单的 INI 文件的示例：

; 这是注释
[Section1]
Key1=Value1
Key2=Value2

[Section2]
Key3=Value3
Key4=Value4

在这个示例中，有两个节：Section1 和 Section2。每个节下面都有一组键值对。例如，在 Section1 中，有两个键值对：Key1=Value1 和 Key2=Value2。

INI 文件格式通常具有以下特点：

    节：节用于将相关的键值对进行分组。它们可以用来组织配置信息，使其更易于理解和维护。

    键值对：键值对用于存储具体的配置信息。键表示配置项的名称，值表示配置项的值。它们之间使用等号或冒号进行分隔。

    注释：注释用于提供对配置信息的说明。在 INI 文件中，注释通常以分号（;）开头，可以出现在文件的任何位置。

    大小写不敏感：在大多数情况下，INI 文件格式是大小写不敏感的，这意味着键和节的名称不受大小写的影响。

INI 文件格式非常简单且易于理解，因此在许多应用程序中被广泛使用。它通常用于存储应用程序的配置选项，例如数据库连接信息、用户首选项等。许多编程语言和框架都提供了用于解析和处理 INI 文件的库和工具。
```
补充(git config还可以操作任何其他INI文件)：
```
$GIT_CONFIG=test.ini git config a.b "fix"
&GIT_CONFIG=test.ini git config a.b
```
