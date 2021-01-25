from PySide2.QtWidgets import QApplication
from PySide2.QtQuick import QQuickView
from PySide2.QtCore import QUrl, QObject, Slot

class Tunnel(QObject):
    @Slot(str)
    def on_ticket(self, ticket):
        print("Got ticket: %s"%(ticket))

app = QApplication([])
tunnel = Tunnel()
view = QQuickView()
view.rootContext().setContextProperty("tunnel", tunnel)
url = QUrl("view.qml")
view.setSource(url)
view.show()

app.exec_()
