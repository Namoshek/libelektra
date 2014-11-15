import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.1

Item {
	id: template

	property string usedNames
	property alias	wizardText: wizardText
	property alias	buttonRow: buttonRow
	property alias	label: label
	property alias	textField: textField
	property bool	buttonVisible: false

	BasicRectangle {
		id: wizardRectangle

		anchors.top: parent.top
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.bottom: buttonRow.top
		anchors.margins: defaultMargins

		Text {
			id: wizardText

			anchors.right: parent.right
			anchors.left: parent.left
			anchors.top: parent.top
			anchors.bottom: wizardRow.top
			anchors.margins: defaultMargins
			verticalAlignment: Text.AlignVCenter
			wrapMode: Text.WordWrap
			color: activePalette.text
		}

		RowLayout {
			id: wizardRow

			anchors.left: parent.left
			anchors.right: parent.right
			anchors.bottom: parent.bottom
			anchors.margins: defaultMargins
			spacing: defaultSpacing

			Label {
				id:label
			}
			TextField {
				id:textField

				Layout.fillWidth: true
			}
			Button {
				id: fileDialogButton

				implicitWidth: textField.height
				implicitHeight: textField.height
				text: "..."
				visible: buttonVisible
				onClicked: {
					importFileDialog.nameFilters = ["All Files (*.*)"]
					importFileDialog.open()
				}
			}
		}
	}
	ButtonRow {
		id: buttonRow

		cancelButton.onClicked: wizardLoader.close()
	}
}
