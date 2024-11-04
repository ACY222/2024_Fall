---
export_on_save:
   prince: true
   prince: pdf
---

# Answer

艾昶 PB22111620

## Git

1. * 通过 `git branch <branch>` 创建分支
   * 通过 `git checkout <newbranch>` 或 `git switch <newbranch>` 切换分支（更推荐后者，因为前者有类似的指令 `git checkout -- <file>` 用来撤销修改）
   * 通过 `git branch -d <branch>` 删除分支
   * 当在该分支上完成的工作已经检验正确且合并到主分支后可安全删除
2. * 如果已经保存到暂存区，第一步使用 `git reset HEAD <file>` 将该修改撤回到工作区，然后可以选择是否使用 `git checkout -- <file>` 来将该文件在工作取得修改全部撤销
   * 如果文件已经提交到版本库，可以通过 `git log` 查看提交历史，然后找到上次提交的版本号，最后使用 `git checkout <commit id> -- <file>` 撤销该提交
3. `git fetch` 从远程库下载最新的代码到本地库中的远程跟踪分支，并不自动合并到本地分支。而 `git pull` 从远程库获取代码并自动合并到本地分支上。从结果上看 `git pull` 包含 `git fetch` 和 `git merge` 两个操作，但实际上两者的实现方式不同。

## 如何 Debug

1. 为什么用 main.cpp:30L 替换 main.cpp:31L 会出现报错？
在文件 Student.hpp 中，'Student'被显式标记为已删除，故此处不能调用。
2. 为什么用 main.cpp:32L 替换 main.cpp:33L 会出现报错？
前面定义的 `check` 函数需要的是 `Student*` 类型的参数，但 `check(vec.back())` 返回的是 `Human*` 类型的参数，故出现类型不符的错误。
3. 为什么取消注释 main.cpp:35-39L 不会报错，但运行会出现段错误？
堆在被 `free` 之后被使用——该 `for` 循环将 `list` `free` 之后会再次访问。