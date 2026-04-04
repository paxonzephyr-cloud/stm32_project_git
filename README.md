
---

# 使用 Git 管理 STM32 项目规范

## 一、整体分支模型

采用 **Git Flow** 的核心思想，简化分支结构以适配嵌入式开发特点。

| 分支类型 | 说明 |
|----------|------|
| `main` | 稳定分支，存放经过充分测试、可直接烧录运行的正式版本代码，每个 commit 对应一个里程碑版本 |
| `develop` | 集成分支，日常开发的主战场，所有功能分支最终都合并于此 |
| 临时分支 | 用于具体任务开发，完成后根据需求选择删除（`feat/*`、`fix/*`、`docs/*`、`refactor/*`） |

---

## 二、分支命名规范

### 1. 功能开发分支：`feat/模块/任务`

```bash
git switch -c feat/adc_dma
git commit -m "feat: 增加ADC的DMA数据采集功能"
```

适用场景：新增传感器驱动、外设驱动、业务逻辑等。

### 2. 问题修复分支：`fix/模块/问题`

```bash
git switch -c fix/exti_interrupt
git commit -m "fix: 修复外部中断标志位未清除导致的死循环"
```

适用场景：中断异常、配置错误、逻辑缺陷等紧急修复。

### 3. 文档维护分支：`docs/主题`

```bash
git switch -c docs/literature_review
git commit -m "docs: 补充海上风能替代模型的参考文献笔记"
```

适用场景：更新 README、维护论文笔记、记录设计文档等。

### 4. 代码重构分支：`refactor/模块`

```bash
git switch -c refactor/linked_list_protect
git commit -m "refactor: 优化头指针保护逻辑，精简代码"
```

适用场景：代码功能正常，但需要优化结构、提高可读性或可维护性。

### 5. 任务细分命名（可选）

当一个功能模块包含多个独立任务时，可采用三级命名：

```
feat/exti/count-sensor    # exti模块下的计数传感器任务
feat/exti/encoder         # exti模块下的编码器任务
feat/timer/pwm            # timer模块下的PWM输出任务
feat/timer/capture        # timer模块下的输入捕获任务
```

---

## 三、典型操作流程

### 1. 仓库初始化（项目模板准备阶段）

```bash
# 创建并切换到 main 分支
git checkout -b main

# 提交基础模板（作为第一个稳定版本）
git add .
git commit -m "init: 项目模板初始化"

# 创建 develop 分支用于后续开发
git checkout -b develop
```

> 注：`main` 仅用于大版本发布，日常开发在 `develop` 及临时分支中进行。

### 2. 日常开发流程（以新增按键控制LED功能为例）

```bash
# 1. 从 develop 切出功能分支
git checkout develop
git checkout -b feat/key_led

# 2. 完成开发后提交代码
git add .
git commit -m "feat: 使用按键控制LED灯亮灭"

# 3. 切回 develop 分支并拉取最新代码（团队协作时尤其重要）
git checkout develop
git pull origin develop

# 4. 合并功能分支（保留分支结构）
git merge --no-ff feat/key_led -m "merge: 合并按键控制LED功能"

# 5. 删除已合并的临时分支（可选）
git branch -d feat/key_led
```

### 3. 版本标记（Tag）

在每个稳定版本发布时，通过 Tag 标记便于回溯：

```bash
# 标记当前版本（例如：v3.3）
git tag -a v3.3 -m "版本 v3.3: LED、按键驱动封装完成"

# 推送 Tag 到远程仓库
git push origin v3.3
```

### 4. 查看提交历史（图形化）

```bash
git log --graph --oneline --all
```

---

## 四、最佳实践建议

1. **提交信息格式**  
   建议采用 `<type>: <subject>` 格式，如 `feat: xxx`、`fix: xxx`，便于后续检索和生成 changelog。

2. **单次提交粒度**  
   一个 commit 应只完成一个逻辑上完整的改动，避免将多个无关修改混在一起提交。

3. **合并策略**  
   推荐使用 `--no-ff` 选项进行合并，保留分支的清晰脉络，方便追溯功能来源。

4. **.gitignore 配置**  
   嵌入式项目建议忽略以下文件：
   - 编译中间文件（`.o`, `.d`, `.elf`, `.hex`, `.bin`）
   - IDE 工程配置（`.ioc`, `.mxproject` 可选，若多人协作建议统一纳入）
   - 临时文件（`*.swp`, `*.swo`, `*.log`）

---

## 五、常见场景速查

| 场景 | 命令 |
|------|------|
| 创建并切换到新功能分支 | `git checkout -b feat/xxx` |
| 提交本地修改 | `git add . && git commit -m "feat: xxx"` |
| 合并分支并保留历史 | `git merge --no-ff feat/xxx -m "merge: xxx"` |
| 打版本标签 | `git tag -a v1.0 -m "版本说明"` |
| 查看简洁历史图 | `git log --graph --oneline --all` |

---

### 主要改动说明
1. **结构重组**：将原方案拆分为“整体模型 → 分支规范 → 操作流程 → 最佳实践 → 速查表”五个清晰章节。
2. **表格化信息**：用表格呈现分支类型、常见场景，提升信息密度和可读性。
3. **补充细节**：增加了 `.gitignore` 建议、提交信息格式规范、单次提交粒度等嵌入式项目实际需要的补充。
4. **命令连贯性**：将初始化、日常开发、版本标记等流程串联成可直接复制的命令块。
5. **去除冗余**：合并重复示例，精简未完成或意义不明确的注释。
