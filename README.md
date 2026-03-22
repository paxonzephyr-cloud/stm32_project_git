# 如何使用git管理项目

## 分支创建选择
 Develop 模型  
1. main (主分支)： 存放经过充分测试、可以直接烧录运行的稳定代码。比如你的毕业论文每一个大的阶段性成果。
2. develop (开发分支)： “主战场”。所有的日常开发逻辑都在这里汇合。
3. 其它分支管理
- feat: ... (新功能，比如加了个定时器驱动)
- fix: ... (修复 Bug，比如修正了寄存器偏移量)
- docs: ... (文档更新，比如写论文笔记或 README)
- refactor: ... (代码重构，没加新功能但优化了结构)


feat/... (新功能开发)  
场景： 你要加一个新的传感器驱动，或者写一个新的链表排序功能。  
命令： git switch -c feat/adc_dma  
提交： git commit -m "feat: 增加ADC的DMA数据采集功能"     

fix/... (Bug 修复)  
场景： 发现中断进不去，或者 EXTI 寄存器配置偏移量写错了，需要紧急修复。  
命令： git switch -c fix/exti_interrupt  
提交： git commit -m "fix: 修复外部中断标志位未清除导致的死循环"  

docs/... (文档与论文)  
场景： 更新项目的 README，或者在仓库里管理你的毕业论文文献综述笔记。  
命令： git switch -c docs/literature_review  
提交： git commit -m "docs: 补充海上风能替代模型的参考文献笔记"  

refactor/... (代码重构)  
场景： 代码能跑，但你觉得之前写的 C 语言链表节点保护逻辑太乱，想优化一下结构，但不增加新功能。  
命令： git switch -c refactor/linked_list_protect  
提交： git commit -m "refactor: 优化头指针保护逻辑，精简代码"  

# git 操作
- 初始化，在完成模板文件的创建后开始创建分支
~~~bash
#1. main中只提交大版本
git commit -m "initial commit trmplateDemo"

#2. develop提交测试完毕的内容
git branch develop

#3. feat/.每次创建外设时使用
git branch feat/
~~~

- 一般操作
```bash
# 1. 在功能分支测试完毕后commit相关内容
git add .
git commit -m "使用按键控制LED灯亮灭"

# 2. 切换回 develop
git checkout develop

# 3. 使用 --no-ff 进行合并
# 这会弹出一个编辑器让你输入合并信息，直接保存即可
git merge --no-ff feat/GPIOA_LED

# 4. （图形化显示历史）
git log --graph --oneline --all

# 5. 通过tag方便溯洄
# 给当前版本打一个标签，比如 v0.1-alpha
git tag -a v3_3 -m "led,key函数封装"
```

       