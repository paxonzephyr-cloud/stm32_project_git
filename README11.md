# stm32开发学习模板使用

## 开发环境
- vs code embedded + keil armcc + openOCD  

## 使用方法
1. 设置工具链,在EIDE的**操作**中点击设置工具链,选择keil MDK,添加自己的keil安装目录中的UV4.exe路径
2. 导入项目,在EIDE的**操作**中使用导入项目,选择keil MDK,选择文件夹中的.urprojs文件,打开即导入
3. 添加到路径,在新建的文件夹中编写代码前需要在EIDE中的项目资源中添加文件夹,建议选择虚拟文件夹使用相同的名字,然后添加.c,.h文件,然后在C/C++属性中包含实际文件夹的路径(**纯英文路径**)
4. 设置构建选项,在EIDE中点击构建配置,选择编译器AC5;点击构建器选项,在连接器中输出格式选择生成axf,勾选hex生成
5. 配置烧录器,在EIDE的烧录配置中选择OPENOCD,在程序文件中选择openOCD的安装位置,选择芯片型号为stm32f1x.cfg,接口选择自己使用的链接器,如st link(以下调试以此作为使用)

## 调试设置
1. 安装Cortex,在插件中安装Cortex插件
2. 安装 arm-none-eabi-gcc 工具链,在EIDE的**操作**中安装使用工具,搜索下载stm32 cube Program CLI,STLink GDB Serve
3. 完毕后启动右上角的调试按钮即可启动,不需要配置launch文件
4. 查看寄存器值,想要查看寄存器值,需要对应的svd文件,相关的svd文件可以在(Arm/Pack/.Download)找到对应的pack,在EIDE中的芯片支持包打开即可使用,为了储存考虑,可以选择对应芯片的svd,将对应对的svd文件放到根目录下,然后删除pack

## 其它的一些说明
### erase擦除
在烧录程序测试完成后往往想要立马结束当前程序,拔插头固然快速,但既不绅士,再次通电后程序依旧存在,主动按复位也是体现不出电子人的头脑,所以一键删除单片机中一些惹人厌的程序(如led闪烁,蜂鸣)就显得很有必要了  
在tasks中可以这样配置一个erase功能  
```json
        {
            "label": "Erase Chip",
            "type": "shell",
            "command": "D:/openocd-v0.12.0-i686-w64-mingw32/bin/openocd.exe",//选择自己的openocd路径
            "args": [
                "-f", "interface/stlink.cfg",
                "-f", "target/stm32f1x.cfg",
                "-c", "init",
                "-c", "halt",
                "-c", "stm32f1x mass_erase 0",
                "-c", "reset run",  // 增加这一行，让芯片复位
                "-c", "exit"
            ],
            "options": {
                "shell": {
                    "executable": "cmd.exe",
                    "args": ["/d", "/c"] 
                }
            },
            "group": "build",
            "problemMatcher": []
        }
```

## target设置
在EIDE中,右击EIDE选择切换目标即可创建删除切换不同的target(默认复制当下的target配置),使用不同的target就可以对项目资源中的文件选择"从项目中移除",从而在编译中排除该选项,可以用在编写example中排除"main.c",这样就可以在example里使用int main了
