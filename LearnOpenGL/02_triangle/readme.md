# 01_triangle



## 相关名词

- 顶点数组对象：Vertex Array Objext,  VAO 
- 顶点缓冲对象：Vertex Buffer Object，VBO 管理GPU内存缓存
- 索引缓冲对象：Element Buffer Object，EBO或Index Buffer Object，IBO
- 顶点着色器：Vertex Shader 
- 几何着色器：Geometry Shader 将顶点连接成形状
- 光栅化：Rasterization Stage 将图元映射成像素
- 片段着色器：Fragment Shader 计算像素最终颜色

## 图形渲染管线



​    ![img](https://learnopengl-cn.github.io/img/01/04/pipeline.png)

## 第一个三角形

在main中添加如下代码

```c++
#include "FirstTriangle.h"

int main()
{
	FirstTriangle firstTriangle;


	return 0;
}
```

如果没报错的话，最后应该生成如下三角形

![image-20220327134222522](img\image-20220327134222522.png)

我们可以通过改变片段着色器改变它的颜色

```C++
const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor; \n"
		"void main()\n"
		"{\n"
		"FragColor = vec4(1.0f, 0.9f, 0.2f, 1.0f);\n"
		"} ";
```

![image-20220327135139754](img\image-20220327135139754.png)

## 索引缓冲对象

为了减少多边形的渲染重复的三角形顶点，要使用索引缓冲对象

比如说想创建一个矩形，我们要使用两个三角形：

代码如下：

```
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,    //第一个三角形
		 0.5f, -0.5f, 0.0f,   
		-0.5f, -0.5f, 0.0f, 
		 0.5f,  0.5f, 0.0f,		//第二个三角形
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f    
	};
```

可以发现实际有两个顶点是重复定义的（左下和右上

![image-20220327141924360](img\image-20220327141924360.png)

 因此可以使用索引缓冲对象

```c++
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,    //右上角
		 0.5f, -0.5f, 0.0f,   //右下角
		-0.5f, -0.5f, 0.0f,  //左下角
		-0.5f,  0.5f, 0.0f    //左上角
	};

	unsigned int indices[] = {  //注意索引从0开始! 
		0, 1, 2,  //第一个三角形
		0, 2, 3   //第二个三角形
	};

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
//然后在渲染循环中调用DrawElements
	while()
    {
        ...
            //指定类型，起始索引，顶点数
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        ...
    }
```

结果如下：

![image-20220327142543968](img\image-20220327142543968.png)

也可以设置线框模式

```c++
//GL_LINE线框模式 GL_FILL 图形模式
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
```

![image-20220327141924360](img\image-20220327141924360.png)

## 小练习

### 练习1

添加更多顶点到数据中，使用glDrawArrays，尝试绘制两个彼此相连的三角形：

![image-20220327183541601](img\image-20220327183541601.png)

### 练习2

创建相同的两个三角形，但对它们的数据使用不同的VAO和VBO

![image-20220327183657318](img\image-20220327183657318.png)

### 练习3

创建两个着色器程序，第二个程序使用一个不同的片段着色器，输出黄色；再次绘制这两个三角形，让其中一个输出为黄色

![image-20220327183805016](img\image-20220327183805016.png)
