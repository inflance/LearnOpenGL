#include "Practice3.h"

Practice3::Practice3()
{
	//初始化GLFW
	glfwInit();
	//配置GLFW, 3.3版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//设置宽，高，标题
	GLFWwindow* window = glfwCreateWindow(800, 600, "learnOpengl", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "无法创建GLFW窗口" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	//所以在调用任何OpenGL的函数之前我们需要初始化GLAD。

	//传入glad加载系统相关的OpenGL函数指针地址的函数
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "无法初始化GLAD" << std::endl;
	}

	//设置视口ViewPort（x, y, width, height）
	glViewport(0, 0, 800, 600);

	//设置回调函数，这样用户改变窗口大小时视口也会被调整
	glfwSetFramebufferSizeCallback(window, &framebuffer_size_callback);
	//创建顶点着色器
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//编译着色器
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//查看编译是否成功
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	//创建片段着色器


	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSourceOrange, NULL);
	glCompileShader(fragmentShader);

	unsigned int fragmentShaderY;
	fragmentShaderY = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderY, 1, &fragmentShaderSourceYellow, NULL);
	glCompileShader(fragmentShaderY);
	//合并，链接着色器程序
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	unsigned int shaderProgramY;
	shaderProgramY = glCreateProgram();
	glAttachShader(shaderProgramY, vertexShader);
	glAttachShader(shaderProgramY, fragmentShaderY);
	glLinkProgram(shaderProgramY);

	//检查
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glGetProgramiv(shaderProgramY, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramY, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//激活程序对象
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(fragmentShaderY);


	//链接顶点属性
	float vertices1[] = {
		//第一个三角形
		-0.9f, -0.5f, 0.0f,
		 0.0f, -0.5f, 0.0f,
		-0.45f, 0.5f, 0.0f,
	};

	float vertices2[] = {
		//第二个三角形
		 0.0f, -0.5f, 0.0f,
		 0.9f, -0.5f, 0.0f,
		 0.45f, 0.5f, 0.0f,
	};
	//使用glGenBuffers函数和一个缓冲ID生成一个VBO对象：
	unsigned int VBOs[2], VAOs[2];

	//索引缓冲对象（index buffer obj
	//unsigned int IBO;

	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	//绑定第一个
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//绑定第二个
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//启用
	glEnableVertexAttribArray(0);

	//GL_LINE线框模式 GL_FILL 图形模式
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//添加循环渲染
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		//渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//设置清空屏幕所用的颜色
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAOs[0]);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgramY);
		glBindVertexArray(VAOs[1]);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		//渲染指令
		//检查调用事件
		glfwPollEvents();

		//交换颜色缓冲区
		//双缓冲区，一前一后，当后缓冲区渲染完毕才替换前缓冲区，这样图像不会闪烁
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteProgram(shaderProgram);
	//释放资源
	glfwTerminate();
}
