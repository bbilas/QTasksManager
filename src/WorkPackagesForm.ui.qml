// Copyright 2020 Bartosz Bilas <bartosz.bilas@hotmail.com>
import QtQuick 2.12
import QtQuick.Controls 1.4 as QQC1
import QtQuick.Layouts 1.11

Item {
    anchors.fill: parent
    property alias tasksTable: tasksTable
    property alias projectNameColumn: projectNameColumn
    property alias taskNameColumn: taskNameColumn
    property alias actionsColumn: actionsColumn

    QQC1.TableView {
        id: tasksTable
        anchors.fill: parent
        height: 150
        model: taskModel

        QQC1.TableViewColumn {
            id: projectNameColumn
            title: "Project"
            resizable: false
        }

        QQC1.TableViewColumn {
            id: taskNameColumn
            title: "Task"
            resizable: false
        }

        QQC1.TableViewColumn {
            id: actionsColumn
            title: "Actions"
            resizable: false
        }
    }
}
