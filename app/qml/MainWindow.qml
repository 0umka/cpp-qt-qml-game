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

    property point currentMousePos: Qt.point(0, 0)

    // ─── Фоновые частицы (те же что в StartScreen) ───────────────────
    Canvas {
        id: bgCanvas
        anchors.fill: parent
        opacity: 0.2
        z: 0

        property var particles: []
        property bool ready: false

        Component.onCompleted: {
            for (var i = 0; i < 50; i++) {
                particles.push({
                    x: Math.random() * width,
                    y: Math.random() * height,
                    r: Math.random() * 1.2 + 0.2,
                    vx: (Math.random() - 0.5) * 0.25,
                    vy: (Math.random() - 0.5) * 0.25,
                    a: Math.random() * Math.PI * 2
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
                p.x += p.vx; p.y += p.vy; p.a += 0.008
                if (p.x < 0) p.x = width
                if (p.x > width) p.x = 0
                if (p.y < 0) p.y = height
                if (p.y > height) p.y = 0
                ctx.beginPath()
                ctx.arc(p.x, p.y, p.r, 0, Math.PI * 2)
                ctx.fillStyle = "rgba(168, 85, 247, " + (0.35 + 0.25 * Math.sin(p.a)) + ")"
                ctx.fill()
            }
        }
    }

    // ─── Игровое поле ────────────────────────────────────────────────
    Item {
        id: gameField
        anchors.fill: parent
        z: 1

        Player {
            playerData: player
        }

        Repeater {
            model: game.enemyModel
            delegate: Enemy {
                enemyData: model.enemyObject
            }
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true

            onPressed: (mouse) => {
                currentMousePos = Qt.point(mouse.x, mouse.y)
                player.startFollowingMouse()
                player.setTarget(mouse.x, mouse.y)
            }
            onPositionChanged: (mouse) => {
                if (pressed) {
                    currentMousePos = Qt.point(mouse.x, mouse.y)
                    player.setTarget(mouse.x, mouse.y)
                }
            }
            onReleased: {
                player.stopFollowingMouse()
            }
        }
    }

    // ─── UI OVERLAY ──────────────────────────────────────────────────
    Item {
        anchors.fill: parent
        z: 2

        // ── Верхняя панель ──────────────────────────────────────────
        Rectangle {
            id: topBar
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 48
            color: "#080810"
            opacity: 0.92

            // Нижняя грань топбара
            Rectangle {
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                height: 1
                color: "#2a1a3e"
            }

            // Левый акцент-ромб
            Rectangle {
                anchors.verticalCenter: parent.verticalCenter
                x: 16
                width: 6; height: 6
                rotation: 45
                color: "#7c3aed"
            }

            // Название
            Text {
                anchors.verticalCenter: parent.verticalCenter
                x: 30
                text: "ROGUE"
                font.pixelSize: 13
                font.letterSpacing: 5
                font.weight: Font.Black
                color: "#e9d5ff"
            }

            // Уровень
            Row {
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 6

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "LVL"
                    font.pixelSize: 9
                    font.letterSpacing: 3
                    color: "#6b21a8"
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: player.level
                    font.pixelSize: 18
                    font.weight: Font.Black
                    color: "#a855f7"
                }
            }

            // Счётчик врагов
            Row {
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 16
                spacing: 6

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "ENEMIES"
                    font.pixelSize: 9
                    font.letterSpacing: 2
                    color: "#6b21a8"
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: game.enemyCount
                    font.pixelSize: 14
                    font.weight: Font.Bold
                    color: "#f43f5e"
                }
            }
        }

        // ── Блок HP игрока (нижний левый угол) ──────────────────────
        Item {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.margins: 16
            anchors.bottomMargin: 20
            width: 200
            height: 56

            // Фон
            Rectangle {
                anchors.fill: parent
                radius: 6
                color: "#0f0f1a"
                border.color: "#2a1a3e"
                border.width: 1
                opacity: 0.9
            }

            Column {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 6

                // Лейбл HP
                Row {
                    spacing: 6
                    Text {
                        text: "HP"
                        font.pixelSize: 9
                        font.letterSpacing: 3
                        color: "#6b21a8"
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Text {
                        text: player.health + " / " + player.maxHealth
                        font.pixelSize: 11
                        font.family: "Courier New"
                        color: {
                            var ratio = player.health / player.maxHealth
                            if (ratio > 0.6) return "#4ade80"
                            if (ratio > 0.3) return "#facc15"
                            return "#f43f5e"
                        }
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                // Полоса HP
                Rectangle {
                    width: parent.width
                    height: 6
                    radius: 3
                    color: "#1a0a2e"

                    Rectangle {
                        width: parent.parent.width * (player.health / player.maxHealth)
                        height: parent.height
                        radius: parent.radius
                        color: {
                            var ratio = player.health / player.maxHealth
                            if (ratio > 0.6) return "#16a34a"
                            if (ratio > 0.3) return "#ca8a04"
                            return "#dc2626"
                        }

                        Behavior on width {
                            NumberAnimation { duration: 200; easing.type: Easing.OutQuad }
                        }

                        // Блик
                        Rectangle {
                            anchors.top: parent.top
                            anchors.left: parent.left
                            anchors.right: parent.right
                            height: 2
                            radius: 1
                            color: "white"
                            opacity: 0.15
                        }
                    }
                }
            }
        }

        // ── Панель кнопок (правый нижний угол) ──────────────────────
        Column {
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.margins: 16
            anchors.bottomMargin: 20
            spacing: 6

            // Кнопка-компонент
            component ActionButton: Rectangle {
                id: btn
                property string label: ""
                property color accentColor: "#4c1d95"
                property color hoverColor: "#6d28d9"
                signal clicked()

                width: 130; height: 34
                radius: 4
                color: btnArea.containsMouse ? hoverColor : accentColor
                Behavior on color { ColorAnimation { duration: 100 } }

                Rectangle {
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: 1; radius: parent.radius
                    color: "#a855f7"; opacity: 0.4
                }

                Text {
                    anchors.centerIn: parent
                    text: btn.label
                    font.pixelSize: 10
                    font.letterSpacing: 2
                    font.weight: Font.Bold
                    color: "#e9d5ff"
                }

                MouseArea {
                    id: btnArea
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: btn.clicked()
                }
            }

            ActionButton {
                label: "▶  ADD ENEMY"
                accentColor: "#1a0a2e"
                hoverColor: "#2d1060"
                onClicked: game.spawnEnemy()
            }

            ActionButton {
                label: "✦  HEAL  +10"
                accentColor: "#052e16"
                hoverColor: "#14532d"
                onClicked: player.heal(10)
            }

            ActionButton {
                label: "⚡  DAMAGE  -10"
                accentColor: "#2d0a0a"
                hoverColor: "#5a1212"
                onClicked: {
                    player.takeDamage(10)
                    for (var i = 0; i < game.enemyModel.rowCount(); i++) {
                        var e = game.enemyModel.get(i)
                        if (e) e.takeDamage(10)
                    }
                }
            }
        }

        // ── Угловой декор (нижний центр) ────────────────────────────
        Row {
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 14
            spacing: 6

            Repeater {
                model: 5
                Rectangle {
                    width: index === 2 ? 20 : 4
                    height: 2
                    radius: 1
                    color: index === 2 ? "#7c3aed" : "#2a1a3e"
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
    }

    // ─── Анимация появления ──────────────────────────────────────────
    NumberAnimation on opacity {
        from: 0; to: 1
        duration: 500
        easing.type: Easing.OutCubic
        running: true
    }
}
