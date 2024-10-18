import matplotlib.pyplot as plt

def read_txt_file(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()
        data = [list(map(float, line.strip().split())) for line in lines]
    return data

def plot_line_chart(data):
    for series in data:
        plt.plot(series)
    plt.xlabel('n')
    plt.ylabel('Run_time')
    plt.show()

if __name__ == "__main__":
    file_path = r"E:\algorithm\lab1-2\output.txt"
    data = read_txt_file(file_path)
    plot_line_chart(data)
