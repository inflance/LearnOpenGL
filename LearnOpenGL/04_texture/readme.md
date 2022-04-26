# 03_texture

## 纹理

纹理：纹理是一张2d图片（也有1d和3d的）

纹理映射：将纹理映射到图形上，需要借助纹理坐标(Texture Coordinate)

纹理坐标：openGL上的纹理坐标大概长这样：

![img](https://learnopengl-cn.github.io/img/01/06/tex_coords.png)

code:

```c++
float texCoords[] = {
    0.0f, 0.0f, // 左下角
    1.0f, 0.0f, // 右下角
    0.5f, 1.0f // 上中
};
```

当我们设置好纹理坐标，openGL会进行采样(sampling),将纹理映射到对应的坐标上

## 纹理环绕方式

openGL的纹理环绕方式有四种

GL_REPEAT ：当纹理坐标超出默认范围时一直重复

GL_MIRRORED_REPEAT ： 当纹理坐标超出默认范围时一直重复，但是镜像翻转

GL_CLAMP_TO_EDGE ： 当纹理坐标超出默认范围时拉伸

GL_CLAMP_TO_BORDER ： 当纹理坐标超出默认范围时设置为指定颜色

可以对每个坐标轴单独设置

```c++
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);//三维
```

如果选择GL_CLAMP_TO_BORDER ，那么就必须设置一个颜色，而且需要用fv后缀函数

```c++
float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
```



## 纹理过滤

纹理过滤是一种显示像素的技术，图片的像素不一定和屏幕的像素一一对应，所以就需要对颜色进行插值，根据插值方式不同过滤方式也不相同，openGL其中有最重要的两种邻近过滤(GL_NEAREST)和线性过滤(GL_LINEAR):

邻近过滤是OpenGL默认的纹理过滤方式，取最近像素的颜色：

![filter_nearest](https://learnopengl-cn.github.io/img/01/06/filter_nearest.png)

线性过滤取根据周围像素的距离取颜色的线性插值：

![filter_linear](https://learnopengl-cn.github.io/img/01/06/filter_linear.png)

综合来看，邻近过滤适合像素风的游戏 ，而线性过滤能产生更平滑的图案

可以设置放大和缩小时的纹理过滤

```c
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//缩小
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//放大
```

## 多级渐远纹理

多级渐远纹理(mipmap)，想想一个平原场景，当我们望向远方时，远处的物体就会变得很小很小，甚至不足一个像素，OpenGL从高分辨率纹理中为这些片段获取正确的颜色值就很困难，这时就要用一个技术解决——mipmap

mipmap就是逐渐生成小于自身的纹理，在不同的像素情况下匹配不同大小的纹理

![img](https://learnopengl-cn.github.io/img/01/06/mipmaps.png)

| 过滤方式                  | 描述                                                         |
| :------------------------ | :----------------------------------------------------------- |
| GL_NEAREST_MIPMAP_NEAREST | 使用最邻近的多级渐远纹理来匹配像素大小，并使用邻近插值进行纹理采样 |
| GL_LINEAR_MIPMAP_NEAREST  | 使用最邻近的多级渐远纹理级别，并使用线性插值进行采样         |
| GL_NEAREST_MIPMAP_LINEAR  | 在两个最匹配像素大小的多级渐远纹理之间进行线性插值，使用邻近插值进行采样 |
| GL_LINEAR_MIPMAP_LINEAR   | 在两个邻近的多级渐远纹理之间使用线性插值，并使用线性插值进行采样 |

```c++
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
```

放大不要使用mipmap，会产生错误

![image-20220426201410743](img\image-20220426201410743.png)
