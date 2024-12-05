# CHANGELOG
## 2.2.1b3

- 修改：Android 平台调整部分属性接口命名
    - vendor.svep.version 修改为 debug.svep.version
    - 新增 debug.svep.log 日志调试属性
- 新增：Android 平台新增 sys.svep.json_path 属性，用于system进程设置json路径
- 修改：授权逻辑调整 json 路径判断逻辑，从 vendor/system 两个路径尝试获取json文件信息

## 2.2.1b2

- 新增：支持RK3562平台支持，支持 540p/720p/1080p 算法模型
- 新增：RK3562 性能测试数据

## 2.2.1b1

- 新增：支持算法JSON鉴权方式
- 新增：支持算法试用逻辑，试用时间为开机30分钟内
- 优化：优化写码工具，支持向 VendorStorage 写 1024长度的离线授权激活码
- 更新：文档增加JSON授权说明章节

## 2.2.0

- 新增：支持RK3576 480p/540p/720p/1080p模型
- 新增：支持SR后级缩放与格式转换
- 新增：授权码支持UFS，解决
- 新增：更新Android 11/12/13/14 SurfaceFlinger 补丁与对应文档说明
- 优化：优化算法处理耗时：
    - 分配不带cache的npu输出内存，减少刷cache的时间
    - 将所有 rknn_create_mem 修改为 rknn_create_mem2 uncahce buffer
- 修复：修复若干稳定性问题
- 修改：移除对librknnrt-svep.so依赖

## 2.1.1b3
- 解决SrBuffer类函数unlock未刷cpu cache问题

## 2.1.1b2
- 解决Linux平台OSD模块概率出现Segment Fault问题
- 解决概率出现输出有OSD但没有SR效果问题
- 优化CPU调频策略
- 更新Android 11/12/13/14 平台显示系统补丁
- 增加Linux初始化Vulkan报错章节说明

## 2.1.0

- 支持RK3588使能SRAM，可减少40%以上的NPU端的DDR带宽数据量
- 支持RK3568/RK3566平台
- 优化SR调用接口
- 解决内存泄漏问题
- 解决若干稳定性问题
- 完善用户文档

## 1.9.1

- SR算法模型DDR带宽优化
- 增加用户说明文档