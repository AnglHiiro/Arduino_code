import sys
import requests
from PyQt6.QtWidgets import QApplication, QMainWindow
from PyQt6 import uic
from PyQt6.QtCore import QTimer

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        uic.loadUi("view2.ui", self)

        self.setWindowTitle("Control de IoT")
        
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.actualizar_datos)
        self.timer.start(5000)

        self.actualizar_datos()

    def actualizar_datos(self):
        try:
            temperatura_respuesta = requests.get('http://localhost:5000/temperatura')
            luz_respuesta = requests.get('http://localhost:5000/luz')
            movimiento_respuesta = requests.get('http://localhost:5000/movimiento')

            temperatura = temperatura_respuesta.json()["message"]
            luz = luz_respuesta.json()["message"]
            movimiento = movimiento_respuesta.json()["message"]

            self.temperaturaLabel.setText(f"Temperatura: {temperatura}")
            self.luzLabel.setText(f"Estado de la luz: {luz}")
            self.movimientoLabel.setText(f"Movimiento: {movimiento}")
        except Exception as e:
            print("Error al obtener los datos:", e)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
