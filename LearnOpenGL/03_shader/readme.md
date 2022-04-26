# 02_着色器

## 着色器

着色器是运行在GPU上的小程序，openGL中的着色器程序语言是GLSL，它是一种类C语言。

directx中的着色器语言是HLSL。

着色器一般具有如下结构

```c++
#version version_number
in type in_variable_name;
in type in_variable_name;

out type out_variable_name;

uniform type uniform_name;

int main()
{
  // 处理输入并进行一些图形操作
  ...
  // 输出处理过的结果到输出变量
  out_variable_name = weird_stuff_we_processed;
}
```

## 数据类型

  b（bool ）| i（int） | u（unsigned int）|d（double）              vecn 包含n个float分量的向量

 向量重组 Swizzling

```c++
vec2 someVec;
vec4 differentVec = someVec.xyxx;
vec3 anotherVec = differentVec.zyw;
vec4 otherVec = someVec.xxxx + anotherVec.yxzy;
```

## 输入与输出

in 输入 out 输出

### 顶点着色器

让顶点着色器为片段着色器决定颜色

```c++
#version 330 core
layout (location = 0) in vec3 aPos; // 位置变量的属性位置值为0

out vec4 vertexColor; // 为片段着色器指定一个颜色输出

void main()
{
    gl_Position = vec4(aPos, 1.0); // 注意我们如何把一个vec3作为vec4的构造器的参数
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // 把输出变量设置为暗红色
}
```

### 片段着色器

```c++
#version 330 core
out vec4 FragColor;

in vec4 vertexColor; // 从顶点着色器传来的输入变量（名称相同、类型相同）

void main()
{
    FragColor = vertexColor;
}
```

## Uniform

Uniform 是一种cpu向gpu发送数据的一种方式，Uniform是全局的，但是如果uniform变量不用的话可能会出错误

声明一个Uniform 向量

```c++
#version 330 core
out vec4 FragColor;

uniform vec4 ourColor; // 在OpenGL程序代码中设定这个变量

void main()
{
    FragColor = ourColor;
}
```



给uniform向量添加数据

```c
float timeValue = glfwGetTime();
float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
glUseProgram(shaderProgram);
glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
```

最后应该得到一个可变色的三角形

![image-20220330203509782](img\image-20220330203509782.png)

## 添加更多属性

![image-20220330203603134](img\image-20220330203603134.png)

## 练习

1 修改顶点着色器让三角形上下颠倒

![image-20220331161411493](img\image-20220331161411493.png)

2 使用uniform定义一个水平偏移量，在顶点着色器中使用这个偏移量把三角形移动到屏幕右侧

![image-20220331161446896](img\image-20220331161446896.png)

3使用`out`关键字把顶点位置输出到片段着色器，并将片段的颜色设置为与顶点位置相等（来看看连顶点位置值都在三角形中被插值的结果）。做完这些后，尝试回答下面的问题：为什么在三角形的左下角是黑的?

![image-20220331161521097](C:\Users\liyun\AppData\Roaming\Typora\typora-user-images\image-20220331161521097.png)

因为左下角坐标

-0.5 -0.5 0 0

颜色范围 0-1，低于0一般为0，所以0 0 0 0为黑色