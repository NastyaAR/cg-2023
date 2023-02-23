import sys, re  # sys - для передачи argv в QApplication
from PyQt5 import QtWidgets, QtGui
from PyQt5.QtCore import Qt

from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt5agg import NavigationToolbar2QT as NavigationToolBar
from matplotlib.patches import Circle
import matplotlib.pyplot as plt

import design #дизайн

INP_DIGIT_ERROR = -1
INCORRECT_POINT = -2
POINTS_ERROR = -3

INDENT = 10
PIXEL = 96.358115
POINT_RADIOUS = 5
INITIAL_WIDTH = 653
INITIAL_HEIGHT = 560
MARKERSIZE = 5
EPS = 1e-8
RIGHT_BUTTON = 3
LEFT_BUTTON = 1
GREEN = QtGui.QColor(144, 238, 144)
RED = QtGui.QColor(240, 128, 128)
RAD_EPS = 0.005


class MyApp(QtWidgets.QMainWindow, design.Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        
        self.width = INITIAL_WIDTH
        self.height = INITIAL_HEIGHT
        
        self.points_x1 = []
        self.points_y1 = []
        
        self.points_x2 = []
        self.points_y2 = []
        
        self.from_line_edit = False
        
        self.figure, self.canvas, self.toolbar, self.axes = None, None, None, None
        self.init_plot()
        #self.axes.plot([1, 2, 3, 4], [5, 6, 7, 8], '*')
        
        #self.axes.plot(4, 56, '*')
        
        #c1 = Circle((4, 5), 6, fill=False)
        #self.axes.add_patch(c1)
        
        #self.axes.axis('equal')
        
        self.number_of_points = 0
        self.number_first_points = 0
        self.number_second_points = 0
        
        self.lineEdit.returnPressed.connect(self.create_table) # Ввод по нажатию Enter
        self.pushButton_5.clicked.connect(self.draw_points) # Привязка отрисовки точек к кнопке
        self.pushButton.clicked.connect(self.delete_point_from_table) # Удаление точки из таблицы по нажатию кнопки
        
        
    def init_plot(self): # График
        self.figure = plt.figure(figsize=(self.width / PIXEL, self.height / PIXEL))
        self.canvas = FigureCanvas(self.figure)
        self.canvas.mpl_connect('button_press_event', self.draw_point_onclick)
        self.toolbar = NavigationToolBar(self.canvas, self)
        self.axes = self.figure.add_subplot(111)
        self.formLayout_3.addWidget(self.toolbar)
        self.formLayout_3.addWidget(self.canvas)
        
        
    def uninit_plot(self):
        self.formLayout_3.removeRow(self.toolbar)
        self.formLayout_3.removeRow(self.canvas)
        del self.figure, self.canvas, self.toolbar, self.axes
        
        
    def error_handling(self, code): # Обработчик ошибок
        match code:
            case -1:
                self.textEdit.setText("Некорректное количество точек!")
            case -2:
                self.textEdit.setText("Некорректное заполнение таблицы!")
            case -3:
                self.textEdit.setText("Точки отсутствуют!")
                
    
    def is_correct_number(self, number, string): # Проверка числовых полей на корректность
        return re.fullmatch(string, number)
      
      
    def input_number_of_points(self): # Ввод кол-ва точек
        text = self.lineEdit.text().strip()
        if self.is_correct_number(text, r'\d+ \d+') == None:
            self.number_of_points = 0
            self.error_handling(INP_DIGIT_ERROR)
        else:
            self.number_first_points, self.number_second_points = map(int, text.split())
            self.number_of_points = self.number_first_points + self.number_second_points
        self.lineEdit.clear() # стереть
        
    
    def create_table(self): # Создание таблицы
        if self.from_line_edit == False: 
            self.input_number_of_points() # Получение количества точек
            number = self.number_of_points
        else:
            number = 1
        if self.number_of_points == 0 and self.from_line_edit == False:
            self.tableWidget.setColumnCount(0)
            self.tableWidget.setRowCount(0)
            return
        
        self.tableWidget.setColumnCount(2) # Отображение таблицы
        self.tableWidget.setColumnWidth(0, 75)
        self.tableWidget.setColumnWidth(1, 75)
        self.tableWidget.setRowCount(number)
        
        
    def clear_points(self):
            self.tableWidget.clear()
            self.points_x1 = []
            self.points_y1 = []     
            self.error_handling(-2)        
        
        
    def read_points_from_one_set(self, begin, end, points_x, points_y):
        x = QtWidgets.QTableWidgetItem()
        y = QtWidgets.QTableWidgetItem()
        
        for i in range(begin, end):
            x = self.tableWidget.item(i, 0)
            y = self.tableWidget.item(i, 1)
            if begin == 0 and self.number_first_points != 0:
                x.setBackground(GREEN)
                y.setBackground(GREEN)
            else:
                x.setBackground(RED)
                y.setBackground(RED)
            if x == None or y == None:
                self.clear_points()
                break
            if self.is_correct_number(x.text(), r'\d+\.?\d*') == None or self.is_correct_number(y.text(), r'\d+\.?\d*') == None:
                self.clear_points()
                break
            else:
                points_x.append(eval(x.text()))
                points_y.append(eval(y.text()))
                
        del x, y
        
        
    def get_points(self):
        self.read_points_from_one_set(0, self.number_first_points, self.points_x1, self.points_y1)
        self.read_points_from_one_set(self.number_first_points, self.number_of_points, self.points_x2, self.points_y2)
        
    
    def update_canvas(self):
        self.canvas.draw()
        self.axes.axis('equal')
        
        
    def draw_points(self, from_table):
        if from_table == False: self.get_points()
        if self.number_first_points == 0 and self.number_second_points == 0:
            self.error_handling(POINTS_ERROR)
            return
        
        if self.points_x1: self.axes.plot(self.points_x1, self.points_y1, 'go', markersize=MARKERSIZE)
        if self.points_x2: self.axes.plot(self.points_x2, self.points_y2, 'ro', markersize=MARKERSIZE)
        self.update_canvas()
        
        
    def draw_point(self, x, y, color):
        self.axes.plot(x, y, color, markersize=MARKERSIZE)
        self.update_canvas()
        
        
    def insert_row(self, x, y, ind, color):
        new_x = QtWidgets.QTableWidgetItem()
        new_y = QtWidgets.QTableWidgetItem()
        
        if ind == 0: 
            self.from_line_edit = True
            self.create_table()
            self.from_line_edit = False
        else: 
            self.tableWidget.insertRow(ind)
        self.tableWidget.setItem(ind, 0, QtWidgets.QTableWidgetItem('{:.3f}'.format(x)))
        self.tableWidget.setItem(ind, 1, QtWidgets.QTableWidgetItem('{:.3f}'.format(y)))
        new_x = self.tableWidget.item(ind, 0)
        new_y = self.tableWidget.item(ind, 1)
        new_x.setBackground(color)
        new_y.setBackground(color)
        ind += 1
        
        del new_x, new_y
        
        
    def add_point_in_table(self, x, y, color):
        if color == 'green':
            self.insert_row(x, y, self.number_first_points, GREEN)
            self.points_x1.append(x)
            self.points_y1.append(y)
            self.number_first_points += 1
        elif color == 'red':
            self.insert_row(x, y, self.number_second_points + self.number_first_points, RED)
            self.points_x2.append(x)
            self.points_y2.append(y)
            self.number_second_points += 1
        self.number_of_points += 1
        
        
    def delete_point(self, point_x, point_y, ind, ind_in_table):
        point_x.pop(ind)
        point_y.pop(ind)
        self.tableWidget.removeRow(ind_in_table)
        
        
    def draw_point_onclick(self, event):
        if event.button == RIGHT_BUTTON:
            sets = ('Первое множество', 'Второе множество')
            color, ok = QtWidgets.QInputDialog.getItem(self, 'В какое множество добавить точку?', 'Множества:', sets, 0, False)
            if color == 'Первое множество' and ok:
                self.draw_point(event.xdata, event.ydata, 'go')
                self.add_point_in_table(event.xdata, event.ydata, 'green')
            elif color == 'Второе множество' and ok:
                self.draw_point(event.xdata, event.ydata, 'ro')
                self.add_point_in_table(event.xdata, event.ydata, 'red')
        if event.button == LEFT_BUTTON:
            set_1 = [(self.points_x1[i], self.points_y1[i]) for i in range(self.number_first_points)]
            set_2 = [(self.points_x2[i], self.points_y2[i]) for i in range(self.number_second_points)]

            all_points = set_1 + set_2
            for i in range(self.number_of_points):
                if all_points[i][0] - RAD_EPS <= event.xdata <= all_points[i][0] + RAD_EPS and all_points[i][1] - RAD_EPS <= event.ydata <= all_points[i][1]:
                    self.uninit_plot()
                    self.init_plot()
                    if i >= self.number_first_points:
                        self.delete_point(self.points_x2, self.points_y2, i - self.number_first_points, i)
                        self.number_second_points -= 1
                    else:
                        self.delete_point(self.points_x1, self.points_y1, i, i)
                        self.number_first_points -= 1
                    self.number_of_points -= 1
                    print(self.number_of_points, self.number_first_points, self.number_second_points)
                    self.draw_points(True)
                    break
                
        
    def delete_point_from_table(self):
        if (ind := self.tableWidget.currentRow()) != -1:
            self.tableWidget.removeRow(ind)
            
                        
                    

        
def main():
    app = QtWidgets.QApplication(sys.argv)
    window = MyApp()  # объект класса MyApp
    window.show()  # окно
    app.exec()
    
    
if __name__ == '__main__':
    main()
