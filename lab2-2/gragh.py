import matplotlib.pyplot as plt

file_path = 'E:\\algorithm\\lab2-2\\output.txt'

# 存储x和y的列表
x_values = []
y_values = []
 
# 读取文件并提取数据
with open(file_path, 'r') as file:
    for line in file:
        # 假设数据以空格或逗号分隔
        x, y = map(float, line.strip().split())
        x_values.append(x)
        y_values.append(y)
 
print(x_values)
print(y_values)
# 绘制图形
plt.plot(x_values, y_values)
plt.title('DataScale-RunTime')
plt.xlabel('n')
plt.ylabel('Time(s)')
plt.grid(True)
plt.show()