# git学习笔记
<br>
<br>
<br>

***
## 第四节git检出
<br>

### HEAD的重置即检出
HEAD即可以理解为头指针，是工作区的“基础版”，当执行提交时，HEAD指向的提交将作为新提交的父提交
```
$cat .git/HEAD
ref: refs/heads/master
```
可以看出HEAD指向master分支，用git branch也可以查看
```
git branch -v  //-v参数表示显示哈希值和主题，若参数出现两次则显示上游分支
* master 2f1d36f Add new_commit.txt
```
现在使用git checkout检出该ID的父提交
```
$git checkout 2f1d36f^
注意：正在切换到 '2f1d36f^'。

您正处于分离头指针状态。您可以查看、做试验性的修改及提交，并且您可以在切换
回一个分支时，丢弃在此状态下所做的提交而不对分支造成影响。

如果您想要通过创建分支来保留在此状态下所做的提交，您可以通过在 switch 命令
中添加参数 -c 来实现（现在或稍后）。例如：

  git switch -c <新分支名>

或者撤销此操作：

  git switch -

通过将配置变量 advice.detachedHead 设置为 false 来关闭此建议

HEAD 目前位于 aebd02e Add 2222
```
分离头指针状态是指头指针指向了一个具体ID提交，而不是一个引用
```
$git reflog -l
aebd02e (HEAD) HEAD@{0}: checkout: moving from master to 2f1d36f^
```
通过reflog我们可以查看到HEAD改变的记录，注意，头指针的改变不意味着分支发生了改变，如果我们查看一下HEAD和master的ID,会发现他们的指向不同
```
git rev-parse HEAD master
aebd02e60903a4087a720193e9d376f247a4ab89
2f1d36f9b99a6ede0435a0f11698881f938b2ed0
```
现在做一次提交会发生什么
```
$touch detacched-commit.txt
$git add detacched-commit.txt
$git status
头指针分离于 aebd02e
要提交的变更：
  （使用 "git restore --staged <文件>..." 以取消暂存）
        新文件：   detacched-commit.txt
$git commit -m "Add detacched-commit.txt"
[分离头指针 cc2e956] Add detacched-commit.txt
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 detacched-commit.txt
```
此时我们发现输出提示我们头指针发生了分离，现在我们再看看HEAD的指向
```
$cat .git/HEAD
cc2e95649fcabded85ac3bf23e5a73a8aa5c9a53
```
HEAD的指向发生了改变
```
$git log --graph --pretty=oneline
* cc2e95649fcabded85ac3bf23e5a73a8aa5c9a53 (HEAD) Add detacched-commit.txt
* aebd02e60903a4087a720193e9d376f247a4ab89 Add 2222
* 09bfc1d650e512fce82b9d870bc31f9d75f7cd34 Add welcome.txt
```
HEAD指向了新的提交，且新提交是建立在之前提交的基础上，此时再切换到master分支查看
```
$ git checkout master                                                                                                   at 09:59:18 下午
警告：您正丢下 1 个提交，未和任何分支关联：

  cc2e956 Add detacched-commit.txt

如果您想要通过创建新分支保存它，这可能是一个好时候。
如下操作：

 git branch <新分支名> cc2e956

切换到分支 'master'
```
这是怎么回事？
```
$ ls
a  new_commit.txt  welcome.txt
```
新建的文件也没有了
```
$git log --graph --pretty=oneline
* 2f1d36f9b99a6ede0435a0f11698881f938b2ed0 (HEAD -> master) Add new_commit.txt
* aebd02e60903a4087a720193e9d376f247a4ab89 Add 2222
* 09bfc1d650e512fce82b9d870bc31f9d75f7cd34 Add welcome.txt
```
提交日志也消失了，那么刚才的提交还在对象库吗
```
$git show cc2e956
commit cc2e95649fcabded85ac3bf23e5a73a8aa5c9a53
Author: lankunGitHub <lkLKlkLKlkLK09@outlook.com>
Date:   Tue Dec 5 21:54:51 2023 +0800

    Add detacched-commit.txt

diff --git a/detacched-commit.txt b/detacched-commit.txt
new file mode 100644
index 0000000..e69de29
```
它还存在与对象库新、中，但因为它并没有被追踪，因此不能保证永久存在。在提交日志过期后，它随时就可以被删除
### 挽救分离指针
使用git merge命令将先前丢失的提交合并到分支中
```
$git merge cc2e956
```
```
$git cat-file -p HEAD
tree e7ababe0c87443f8e868808154fde00e485fe40a
parent 2f1d36f9b99a6ede0435a0f11698881f938b2ed0
parent cc2e95649fcabded85ac3bf23e5a73a8aa5c9a53
author lankunGitHub <lkLKlkLKlkLK09@outlook.com> 1702290869 +0800
committer lankunGitHub <lkLKlkLKlkLK09@outlook.com> 1702290869 +0800

Save HEAD
```
现在，该提交有两次父提交
### gitcheckout的秘密
```
      git checkout [-q] [-f] [-m] [<branch>]
      git checkout [-q] [-f] [-m] --detach [<branch>]
      git checkout [-q] [-f] [-m] [--detach] <commit>
      git checkout [-q] [-f] [-m] [[-b|-B|--orphan]<new-branch>] [<start-point>]
      git checkout [-f] <tree-ish> [--] <pathspec>...
      git checkout [-f] <tree-ish> --pathspec-from-file=<file> [--pathspec-file-nul]
      git checkout [-f|--ours|--theirs|-m|--conflict=<style>] [--] <pathspec>...
      git checkout [-f|--ours|--theirs|-m|--conflict=<style>] --pathspec-from-file=<file> [--pathspec-file-nul]
      git checkout (-p|--patch) [<tree-ish>] [--] [<pathspec>...]

```
![Alt text](image-5.png)
```
git checkout branch //检出分支
git checkout(git checkout HEAD) //汇总暂存区，工作区和HEAD的差异
git checkout --filename  //用暂存区的文件取代工作区的文件
git checkout branch --filname //用分支的某文件替代工作区文件
git checkout . //用暂存区的全部文件替代工作区(慎用)
```