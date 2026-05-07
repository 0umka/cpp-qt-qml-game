import QtQuick
import QtQuick.Window
import QtQuick.Controls

ApplicationWindow {
    id: root
    visible: true
    width: 800
    height: 600
    title: "Isometric Rogue"
    color: "#0a0a0f"

    // ─── Фоновые частицы ───────────────────────────────────────────────
    Canvas {
        id: bgCanvas
        anchors.fill: parent
        opacity: 0.35

        property var particles: []
        property bool ready: false

        Component.onCompleted: {
            for (var i = 0; i < 60; i++) {
                particles.push({
                    x: Math.random() * width,
                    y: Math.random() * height,
                    r: Math.random() * 1.5 + 0.3,
                    vx: (Math.random() - 0.5) * 0.3,
                    vy: (Math.random() - 0.5) * 0.3,
                    a: Math.random()
                })
            }
            ready = true
        }

        Timer {
            interval: 40
            running: true
            repeat: true
            onTriggered: bgCanvas.requestPaint()
        }

        onPaint: {
            if (!ready) return
            var ctx = getContext("2d")
            ctx.clearRect(0, 0, width, height)
            for (var i = 0; i < particles.length; i++) {
                var p = particles[i]
                p.x += p.vx
                p.y += p.vy
                p.a += 0.01
                if (p.x < 0) p.x = width
                if (p.x > width) p.x = 0
                if (p.y < 0) p.y = height
                if (p.y > height) p.y = 0
                ctx.beginPath()
                ctx.arc(p.x, p.y, p.r, 0, Math.PI * 2)
                ctx.fillStyle = "rgba(180, 100, 255, " + (0.4 + 0.3 * Math.sin(p.a)) + ")"
                ctx.fill()
            }
        }
    }

    // ─── Горизонтальная линия-акцент ──────────────────────────────────
    Rectangle {
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height * 0.18
        width: 280
        height: 1
        color: "#6b21a8"
        opacity: 0.6

        Rectangle {
            anchors.centerIn: parent
            width: 6; height: 6
            radius: 3
            color: "#a855f7"
        }
    }

    // ─── Заголовок ────────────────────────────────────────────────────
    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height * 0.12
        spacing: 6

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "ROGUE"
            font.pixelSize: 64
            font.letterSpacing: 18
            font.weight: Font.Black
            color: "#f0e6ff"

            layer.enabled: true
            layer.effect: null

            // свечение через тень
            Text {
                anchors.centerIn: parent
                text: parent.text
                font: parent.font
                color: "transparent"
                z: -1

                Rectangle {
                    anchors.centerIn: parent
                    width: parent.implicitWidth + 60
                    height: parent.implicitHeight + 20
                    radius: 40
                    color: "transparent"
                    border.color: "#7c3aed"
                    border.width: 0
                    opacity: 0.0
                }
            }
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "SELECT YOUR WEAPON"
            font.pixelSize: 11
            font.letterSpacing: 6
            color: "#7c3aed"
            opacity: 0.9
        }
    }

    // ─── Карточки оружия ──────────────────────────────────────────────
    Row {
        id: weaponRow
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -20
        spacing: 24

        Repeater {
            model: [
                { id: 0, name: "FIRE STAFF",  sub: "Ranged · Magic",  icon: "🔥", desc: "Attacks nearest\nenemy automatically",  dmg: "DMG  ██░░░",  spd: "SPD  ████░" },
                { id: 1, name: "SWORD",       sub: "Melee · Physical", icon: "⚔️", desc: "Close combat\nhigh damage output",   dmg: "DMG  ████░",  spd: "SPD  ██░░░" }
            ]

            delegate: Rectangle {
                id: card
                width: 200
                height: 260
                radius: 12
                color: startScreen.selectedWeapon === modelData.id
                       ? "#1a0a2e" : "#0f0f1a"
                border.color: startScreen.selectedWeapon === modelData.id
                              ? "#7c3aed" : "#2a1a3e"
                border.width: startScreen.selectedWeapon === modelData.id ? 2 : 1

                property bool hovered: false

                // Свечение выбранной карточки
                Rectangle {
                    anchors.fill: parent
                    radius: parent.radius
                    color: "transparent"
                    border.color: "#a855f7"
                    border.width: startScreen.selectedWeapon === modelData.id ? 1 : 0
                    opacity: 0.3
                    scale: 1.03
                }

                Behavior on border.color { ColorAnimation { duration: 150 } }
                Behavior on color        { ColorAnimation { duration: 150 } }

                scale: hovered ? 1.03 : 1.0
                Behavior on scale { NumberAnimation { duration: 120; easing.type: Easing.OutQuad } }

                Column {
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 12

                    // Иконка
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: modelData.icon
                        font.pixelSize: 42
                    }

                    // Название
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: modelData.name
                        font.pixelSize: 14
                        font.letterSpacing: 3
                        font.weight: Font.Bold
                        color: startScreen.selectedWeapon === modelData.id ? "#e9d5ff" : "#94a3b8"
                        Behavior on color { ColorAnimation { duration: 150 } }
                    }

                    // Подзаголовок
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: modelData.sub
                        font.pixelSize: 10
                        font.letterSpacing: 1
                        color: "#6b21a8"
                    }

                    // Разделитель
                    Rectangle {
                        width: parent.width
                        height: 1
                        color: "#2a1a3e"
                    }

                    // Описание
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: modelData.desc
                        font.pixelSize: 11
                        color: "#64748b"
                        lineHeight: 1.5
                        horizontalAlignment: Text.AlignHCenter
                    }

                    // Статы
                    Column {
                        spacing: 4
                        Text {
                            text: modelData.dmg
                            font.pixelSize: 10
                            font.family: "Courier New"
                            color: startScreen.selectedWeapon === modelData.id ? "#a855f7" : "#4a3a5e"
                            Behavior on color { ColorAnimation { duration: 150 } }
                        }
                        Text {
                            text: modelData.spd
                            font.pixelSize: 10
                            font.family: "Courier New"
                            color: startScreen.selectedWeapon === modelData.id ? "#a855f7" : "#4a3a5e"
                            Behavior on color { ColorAnimation { duration: 150 } }
                        }
                    }
                }

                // Галочка выбора
                Rectangle {
                    visible: startScreen.selectedWeapon === modelData.id
                    anchors.top: parent.top
                    anchors.right: parent.right
                    anchors.margins: 10
                    width: 20; height: 20
                    radius: 10
                    color: "#7c3aed"

                    Text {
                        anchors.centerIn: parent
                        text: "✓"
                        font.pixelSize: 11
                        color: "white"
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: card.hovered = true
                    onExited:  card.hovered = false
                    onClicked: startScreen.selectWeapon(modelData.id)
                }
            }
        }
    }

    // ─── Кнопка START ─────────────────────────────────────────────────
    Item {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 60
        width: 220
        height: 52

        property bool hovered: false

        Rectangle {
            anchors.fill: parent
            radius: 4
            color: parent.hovered ? "#6d28d9" : "#4c1d95"
            Behavior on color { ColorAnimation { duration: 120 } }

            // Верхняя светлая грань
            Rectangle {
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                height: 1
                color: "#a855f7"
                opacity: 0.5
                radius: parent.radius
            }
        }

        Text {
            anchors.centerIn: parent
            text: "▶  START GAME"
            font.pixelSize: 13
            font.letterSpacing: 4
            font.weight: Font.Bold
            color: "#e9d5ff"
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: parent.hovered = true
            onExited:  parent.hovered = false
            onClicked: startScreen.startGame()
        }
    }

    // ─── Версия / копирайт ────────────────────────────────────────────
    Text {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 12
        text: "v0.1-alpha"
        font.pixelSize: 10
        font.letterSpacing: 1
        color: "#2a1a3e"
    }

    // ─── Анимация появления ───────────────────────────────────────────
    NumberAnimation on opacity {
        from: 0; to: 1
        duration: 600
        easing.type: Easing.OutCubic
        running: true
    }
}
