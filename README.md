﻿```mermaid
sequenceDiagram
    被控制端 ->> + 控制端: 连接对方8888端口
	控制端 -->> - 被控制端: 监听自身8888端口

	被控制端 ->> + 控制端: 发送屏幕信息
	控制端 -->> - 被控制端: 接收屏幕信息并显示

	控制端 ->> + 被控制端: 发送按键信息
	被控制端 -->> - 控制端: 接收按键信息并模拟按键信息
```
