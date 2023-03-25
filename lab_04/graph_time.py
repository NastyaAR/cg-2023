import matplotlib.pyplot as plt

def get_graph(filename):
    file = open(filename, 'r')
    times = file.readline().split()

    for i in range(len(times)):
        times[i] = float(times[i].replace(",", "."))
        
    print(times)
        
    file.close()

    plt.figure(1, figsize=(12, 7))

    plt.title("Сравнение эффективности")

    y = range(len(times))

    labels = ('Библиотечный', 'Канон.ур-е', 'Парам. ур-е', 'Брезенхем', 'Средняя точка')

    plt.bar(y, times)
    plt.xticks(y, labels)

    plt.ylabel("Время в мкс.\n")
    plt.show()


get_graph('/home/nastya/sem4/cg-2023/lab_04/circle_time.txt')
get_graph('/home/nastya/sem4/cg-2023/lab_04/ellipse_time.txt')
