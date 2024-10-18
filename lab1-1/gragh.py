import matplotlib.pyplot as plt

def read_txt_file(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()
        # 处理每一行，将字符串中的数值分割并转换为浮点数
        data = [list(map(float, line.strip().split())) for line in lines]
    return data

def plot_line_chart(data):
    # 假设每行的数据都是一个系列，可以根据需要修改
    for series in data:
        plt.plot(series)
    plt.xlabel('n')
    plt.ylabel('Run_time')
    plt.show()

if __name__ == "__main__":
    file_path = r"E:\VScode\lab1-1\output.txt"  # 使用原始字符串
    data = read_txt_file(file_path)
    plot_line_chart(data)